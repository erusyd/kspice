/**********
Copyright 1992 Regents of the University of California.  All rights
reserved.
Author: 1992 Charles Hough
**********/


#include "spice.h"
#include <stdio.h>
#include "util.h"
#include "smpdefs.h"
#include "cpldefs.h"
#include "sperror.h"
#include "suffix.h"

#include "capdefs.h"
#include "multi_line.h"

#define VECTOR_ALLOC(vec, n) { \
	int i; \
	vec = (double **) malloc(n * sizeof(double *)); \
	for (i = 0; i < n; i++) {  \
		vec[i] = (double *) malloc(sizeof(double)); \
	} \
}
#define MATRIX_ALLOC(mat, m, j) { \
	int k; \
	mat = (double ***) malloc(m * sizeof(double **)); \
	for (k = 0; k < m; k++) {  \
		VECTOR_ALLOC(mat[k], j); \
	} \
}

#define MAX_DEG 8
#define epsilon 1.0e-88
#define ABS(x) ((x) >= 0 ? (x) : (-(x)))
#define MAX_STRING 128

static  double  ZY[MAX_DIM][MAX_DIM]; 
static  double  Sv[MAX_DIM][MAX_DIM]; 
static  double  D[MAX_DIM]; 
static  double  Y5[MAX_DIM][MAX_DIM];
static  double  Y5_1[MAX_DIM][MAX_DIM];
static  double  Sv_1[MAX_DIM][MAX_DIM];

static  double R_m[MAX_DIM][MAX_DIM];
static  double G_m[MAX_DIM][MAX_DIM];
static  double L_m[MAX_DIM][MAX_DIM];
static  double C_m[MAX_DIM][MAX_DIM];
static  double length;
static  double TAU[MAX_DIM];

static  double  A[MAX_DIM][2*MAX_DIM];

static  double  frequency[MAX_DEG];

static  double Si[MAX_DIM][MAX_DIM];
static  double Si_1[MAX_DIM][MAX_DIM];

/*  MacLaurin Series  */
static  double *SiSv_1[MAX_DIM][MAX_DIM];
static  double *Sip[MAX_DIM][MAX_DIM];
static  double *Si_1p[MAX_DIM][MAX_DIM];
static  double *Sv_1p[MAX_DIM][MAX_DIM];
static  double *W[MAX_DIM];

static  Mult_Out IWI[MAX_DIM][MAX_DIM];
static  Mult_Out IWV[MAX_DIM][MAX_DIM];
static  Single_Out SIV[MAX_DIM][MAX_DIM];
static  double  At[4][4];
static  double  Scaling_F;
static  double  Scaling_F2;

/* misc.c match */
static void new_memory();
static double *vector();
static void free_vector();
static void polint();
static int match_x();
static int match();
static int Gaussian_Elimination2();
static void eval_Si_Si_1();
static void loop_ZY();
static void poly_matrix();
static int checkW();
static void poly_W();
static void eval_frequency();
static void store();
static void store_SiSv_1();
static int check();
static int coupled();
static int generate_out();
static int ReadCpL();
static int divC();

/* mult */
static void mult_p();
static void matrix_p_mult();
static double approx_mode();
static double eval2();
static int get_c();
static int Pade_apx();
static int Gaussian_Elimination();
static double root3();
static int div3();
static int find_roots();

static NODE* insert_node();
static NDnamePt insert_ND();
static NODE* NEW_node();
static NDnamePt ndn;
static NODE *node_tab;
#define epsi_mult 1e-28

/* diag */
static MAXE_PTR sort();
static void ordering();
static MAXE_PTR delete_1();
static void reordering();
static void diag();
static int rotate();

#define epsi 1.0e-16
static char *message = "tau of coupled lines is larger than max time step";

/* ARGSUSED */
int
CPLsetup(matrix,inModel,ckt,state)
    register SMPmatrix *matrix;
    GENmodel *inModel;
    CKTcircuit*ckt;
    int *state;
{
    register CPLmodel *model = (CPLmodel *)inModel;
    register CAPmodel *model2;
	register CPLinstance *here;
	register CAPinstance *there;
	CKTnode *tmp, *node;
	int error, m, p;
	NODE *nd;
	char **branchname;
	int noL;

    /*  loop through all the models */
    for( ; model != NULL; model = model->CPLnextModel ) {

        /* loop through all the instances of the model */
        for (here = model->CPLinstances; here != NULL ;
                here=here->CPLnextInstance) {
            
/* macro to make elements with built in test for out of memory */
#define TSTALLOC(ptr,first,second) \
if((here->ptr = SMPmakeElt(matrix,here->first,here->second))==(double *)NULL){\
    return(E_NOMEM);\
}
			noL = here->dimension;

			here->CPLposNodes = (int *) malloc(noL * sizeof(int));
			here->CPLnegNodes = (int *) malloc(noL * sizeof(int));
			here->CPLibr1 = (int *) malloc(noL * sizeof(int));
			here->CPLibr2 = (int *) malloc(noL * sizeof(int));

			VECTOR_ALLOC(here->CPLibr1Ibr1, noL);
			VECTOR_ALLOC(here->CPLibr2Ibr2, noL);
			VECTOR_ALLOC(here->CPLposIbr1, noL);
			VECTOR_ALLOC(here->CPLnegIbr2, noL);
			VECTOR_ALLOC(here->CPLposPos, noL);
			VECTOR_ALLOC(here->CPLnegNeg, noL);
			VECTOR_ALLOC(here->CPLnegPos, noL);
			VECTOR_ALLOC(here->CPLposNeg, noL);

			MATRIX_ALLOC(here->CPLibr1Pos, noL, noL);
			MATRIX_ALLOC(here->CPLibr2Neg, noL, noL);
			MATRIX_ALLOC(here->CPLibr1Neg, noL, noL);
			MATRIX_ALLOC(here->CPLibr2Pos, noL, noL);
			MATRIX_ALLOC(here->CPLibr1Ibr2, noL, noL);
			MATRIX_ALLOC(here->CPLibr2Ibr1, noL, noL);

			branchname = (char **) malloc(sizeof(char *) * here->dimension);
			if (! here->CPLibr1Given) {
				for (m = 0; m < here->dimension; m++) {
					branchname[m] = malloc(MAX_STRING);
					sprintf(branchname[m], "branch1_%d", m);
					error = 
					CKTmkCur(ckt, &tmp, here->CPLname, branchname[m]);
					if (error) return (error);
					here->CPLibr1[m] = tmp->number;
				}
				here->CPLibr1Given = 1;
			}
			free(branchname);
			branchname = (char **) malloc(sizeof(char *) * here->dimension);
			if (! here->CPLibr2Given) {
				for (m = 0; m < here->dimension; m++) {
					branchname[m] = malloc(MAX_STRING);
					sprintf(branchname[m], "branch2_%d", m);
					error = 
					CKTmkCur(ckt, &tmp, here->CPLname, branchname[m]);
					if (error) return (error);
					here->CPLibr2[m] = tmp->number;
				}
				here->CPLibr2Given = 1;
			}
			free(branchname);

			for (m = 0; m < here->dimension; m++) {
				for (node = ckt->CKTnodes; node; node = node->next) {
					if (strcmp(here->in_node_names[m], 
						node->name) == 0){
						here->CPLposNodes[m] = node->number;
					}
				}
			}
			for (m = 0; m < here->dimension; m++) {
				for (node = ckt->CKTnodes; node; node = node->next) {
					if (strcmp(here->out_node_names[m],
						node->name) == 0){
						here->CPLnegNodes[m] = node->number;
					}
				}
			}

			for (m = 0; m < here->dimension; m++) {
				TSTALLOC(CPLibr1Ibr1[m],CPLibr1[m],CPLibr1[m]);
				TSTALLOC(CPLibr2Ibr2[m],CPLibr2[m],CPLibr2[m]);
				TSTALLOC(CPLposIbr1[m],CPLposNodes[m],CPLibr1[m]);
	            TSTALLOC(CPLnegIbr2[m],CPLnegNodes[m],CPLibr2[m]);
	            TSTALLOC(CPLposPos[m],CPLposNodes[m],CPLposNodes[m]);
	            TSTALLOC(CPLnegNeg[m],CPLnegNodes[m],CPLnegNodes[m]);
	            TSTALLOC(CPLnegPos[m],CPLnegNodes[m],CPLposNodes[m]);
	            TSTALLOC(CPLposNeg[m],CPLposNodes[m],CPLnegNodes[m]);

				for (p = 0; p < here->dimension; p++) {

            TSTALLOC(CPLibr1Pos[m][p],CPLibr1[m],CPLposNodes[p]);
            TSTALLOC(CPLibr2Neg[m][p],CPLibr2[m],CPLnegNodes[p]);
            TSTALLOC(CPLibr1Neg[m][p],CPLibr1[m],CPLnegNodes[p]);
            TSTALLOC(CPLibr2Pos[m][p],CPLibr2[m],CPLposNodes[p]);
            TSTALLOC(CPLibr1Ibr2[m][p],CPLibr1[m],CPLibr2[p]);
            TSTALLOC(CPLibr2Ibr1[m][p],CPLibr2[m],CPLibr1[p]);

				}
			}

			ReadCpL(here, ckt);

        }
    }

	return(OK);
}


static int 
ReadCpL(here, ckt)
CPLinstance *here;
CKTcircuit *ckt;
{
   int i, j, k, noL, counter;
   float f;
   char *name;
   CPLine *c, *c2;
   ECPLine *ec;
   NODE *nd;
   RLINE *lines[MAX_CP_TX_LINES];
   ERLINE *er;

   c = (CPLine *) malloc(sizeof (CPLine));
   c2 = (CPLine *) malloc(sizeof (CPLine));
   c->vi_head = c->vi_tail = NULL;
   noL = c->noL = here->dimension;
   here->cplines = c;
   here->cplines2 = c2;

   for (i = 0; i < noL; i++) {
      ec = (ECPLine *) malloc(sizeof (ECPLine));
	  name = here->in_node_names[i];
      nd = insert_node(name);
      ec->link = nd->cplptr;
      nd->cplptr = ec;
      ec->line = c;
      c->in_node[i] = nd;
      c2->in_node[i] = nd;

      er = (ERLINE *) malloc(sizeof (ERLINE));
      er->link = nd->rlptr;
      nd->rlptr = er;
      er->rl = lines[i] = (RLINE *) malloc(sizeof (RLINE));
      er->rl->in_node = nd;

      c->dc1[i] = c->dc2[i] = 0.0;
   }

   for (i = 0; i < noL; i++) {
      ec = (ECPLine *) malloc(sizeof (ECPLine));
	  name = here->out_node_names[i];
      nd = insert_node(name);
      ec->link = nd->cplptr;
      nd->cplptr = ec;
      ec->line = c;
      c->out_node[i] = nd;
      c2->out_node[i] = nd;

      er = (ERLINE *) malloc(sizeof (ERLINE));
      er->link = nd->rlptr;
      nd->rlptr = er;
      er->rl = lines[i];
      er->rl->out_node = nd;
   }

   
	counter = 0;
	for (i = 0; i < noL; i++) {
		for (j = 0; j < noL; j++) {
			if (i > j) {
				R_m[i][j] = R_m[j][i];
				G_m[i][j] = G_m[j][i];
				C_m[i][j] = C_m[j][i];
				L_m[i][j] = L_m[j][i];
			}
			else {
				f = here->CPLmodPtr->Rm[counter];
				R_m[i][j] =here->CPLmodPtr->Rm[counter]= MAX(f, 1.0e-4);
				G_m[i][j] = here->CPLmodPtr->Gm[counter];
				L_m[i][j] = here->CPLmodPtr->Lm[counter];
				C_m[i][j] = here->CPLmodPtr->Cm[counter];
				counter++;
			}
		}
	}
	if (here->CPLlengthgiven)
		length = here->CPLlength;
	else length = here->CPLmodPtr->length;

   for (i = 0; i < noL; i++) 
      lines[i]->g = 1.0 / (R_m[i][i] * length);

   coupled(noL);

   for (i = 0; i < noL; i++) {
      double d, t;
      int k;

      c->taul[i] = TAU[i] * 1.0e+12;
      for (j  = 0; j < noL; j++) {
         if (SIV[i][j].C_0 == 0.0)
            c->h1t[i][j] = NULL;
	 else {
	    c->h1t[i][j] = (TMS *) malloc(sizeof (TMS));
	    d = c->h1t[i][j]->aten = SIV[i][j].C_0;
	    c->h1t[i][j]->ifImg = (int) SIV[i][j].Poly[6] - 1.0;
	        /* since originally 2 for img 1 for noimg */
	    c->h1t[i][j]->tm[0].c = SIV[i][j].Poly[0] * d;
	    c->h1t[i][j]->tm[1].c = SIV[i][j].Poly[1] * d;
	    c->h1t[i][j]->tm[2].c = SIV[i][j].Poly[2] * d;
	    c->h1t[i][j]->tm[0].x = SIV[i][j].Poly[3];
	    c->h1t[i][j]->tm[1].x = SIV[i][j].Poly[4];
	    c->h1t[i][j]->tm[2].x = SIV[i][j].Poly[5];
	    if (c->h1t[i][j]->ifImg)
	       c->h1C[i][j] = c->h1t[i][j]->tm[0].c + 2.0 * c->h1t[i][j]->tm[1].c;
            else {
	       t = 0.0;
               for (k = 0; k < 3; k++)
                  t += c->h1t[i][j]->tm[k].c;
	       c->h1C[i][j] = t;
	    }
	 }

         for (k = 0; k < noL; k++) {
            if (IWI[i][j].C_0[k] == 0.0)
               c->h2t[i][j][k] = NULL;
            else {
               c->h2t[i][j][k] = (TMS *) malloc(sizeof (TMS));
               d = c->h2t[i][j][k]->aten = IWI[i][j].C_0[k];
               c->h2t[i][j][k]->ifImg = (int) IWI[i][j].Poly[k][6] - 1.0;
                /* since originally 2 for img 1 for noimg */
               c->h2t[i][j][k]->tm[0].c = IWI[i][j].Poly[k][0] * d;
               c->h2t[i][j][k]->tm[1].c = IWI[i][j].Poly[k][1] * d;
               c->h2t[i][j][k]->tm[2].c = IWI[i][j].Poly[k][2] * d;
               c->h2t[i][j][k]->tm[0].x = IWI[i][j].Poly[k][3];
               c->h2t[i][j][k]->tm[1].x = IWI[i][j].Poly[k][4];
               c->h2t[i][j][k]->tm[2].x = IWI[i][j].Poly[k][5];
	       if (c->h2t[i][j][k]->ifImg)
	          c->h2C[i][j][k] = c->h2t[i][j][k]->tm[0].c + 2.0 * 
			  c->h2t[i][j][k]->tm[1].c;
               else 
		  c->h2C[i][j][k] =  c->h2t[i][j][k]->tm[0].c +
				     c->h2t[i][j][k]->tm[1].c +
				     c->h2t[i][j][k]->tm[2].c;
            }
            if (IWV[i][j].C_0[k] == 0.0)
               c->h3t[i][j][k] = NULL;
            else {
               c->h3t[i][j][k] = (TMS *) malloc(sizeof (TMS));
               d = c->h3t[i][j][k]->aten = IWV[i][j].C_0[k];
               c->h3t[i][j][k]->ifImg = (int) IWV[i][j].Poly[k][6] - 1.0;
                /* since originally 2 for img 1 for noimg */
               c->h3t[i][j][k]->tm[0].c = IWV[i][j].Poly[k][0] * d;
               c->h3t[i][j][k]->tm[1].c = IWV[i][j].Poly[k][1] * d;
               c->h3t[i][j][k]->tm[2].c = IWV[i][j].Poly[k][2] * d;
               c->h3t[i][j][k]->tm[0].x = IWV[i][j].Poly[k][3];
               c->h3t[i][j][k]->tm[1].x = IWV[i][j].Poly[k][4];
               c->h3t[i][j][k]->tm[2].x = IWV[i][j].Poly[k][5];
	       if (c->h3t[i][j][k]->ifImg)
	          c->h3C[i][j][k] = c->h3t[i][j][k]->tm[0].c + 2.0 * 
			  c->h3t[i][j][k]->tm[1].c;
               else 
		  c->h3C[i][j][k] =  c->h3t[i][j][k]->tm[0].c +
				     c->h3t[i][j][k]->tm[1].c +
				     c->h3t[i][j][k]->tm[2].c;
            }
         }
      }
   }

   for (i = 0; i < noL; i++) {
		if (c->taul[i] < ckt->CKTmaxStep) {
			errMsg = MALLOC(strlen(message)+1);
			strcpy(errMsg,message);
			return(-1);
		}
	}

   return(1);
}


/****************************************************************
     misc.c      Miscellaneous procedures for simulation of
		 coupled transmission lines.
 ****************************************************************/


static void 
new_memory(dim, deg, deg_o)
   int dim, deg, deg_o;
{
   int i, j;

   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++) 
         SiSv_1[i][j] = (double *) calloc(deg_o+1, sizeof(double));

   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++) 
         Sip[i][j] = (double *) calloc(deg_o+1, sizeof(double));

   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++) 
         Si_1p[i][j] = (double *) calloc(deg_o+1, sizeof(double));

   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++) 
         Sv_1p[i][j] = (double *) calloc(deg_o+1, sizeof(double));

   for (i = 0; i < dim; i++) 
      W[i] = (double *) calloc(MAX_DEG, sizeof(double));
}

/***
 ***/

/****************************************************************
     match     Create a polynomial matching given data points 
 ****************************************************************/


static double 
*vector(nl, nh)
   int nl, nh;
{
   double *v;

   v = (double *) malloc((unsigned) (nh - nl +1) * sizeof(double));
   if (!v) {
      fprintf(stderr, "Memory Allocation Error by malloc in vector().\n");
      fprintf(stderr, "...now exiting to system ...\n");
      exit(0);
   }
   return v-nl;
}

static void 
free_vector(v, nl, nh)
   double *v;
   int nl, nh;
{
   free((char*) (v +nl));
}

static void 
polint(xa, ya, n, x, y, dy)
/*
   Given arrays xa[1..n] and ya[1..n], and given a value x, this routine
   returns a value y, and an error estimate dy.  If P(x) is the 
   polynomial of degree n-1 such that P(xa) = ya, then the returned 
   value y = P(x)
 */
   double xa[], ya[], x, *y, *dy;
   int n;
{
   int i, m, ns = 1;
   double den, dif, dift, ho, hp, w;
   double *c, *d, *vector();
   void free_vector();

   dif = ABS(x - xa[1]);
   c = vector(1, n);
   d = vector(1, n);
   for (i = 1; i <= n; i++) {
      if ((dift = ABS(x - xa[i])) < dif) {
	 ns = i;
	 dif = dift;
      }
      c[i] = ya[i];
      d[i] = ya[i];
   }
   *y = ya[ns--];
   for (m = 1; m < n; m++) {
      for (i = 1; i <= n-m; i++) {
	 ho = xa[i]-x;
	 hp = xa[i+m]-x;
	 w = c[i+1]-d[i];
	 if ((den=ho-hp) == 0.0) {
	    fprintf(stderr, "(Error) in routine POLINT\n");
            fprintf(stderr, "...now exiting to system ...\n");
            exit(0);
	 }
	 den = w/den;
	 d[i] = hp * den;
	 c[i] = ho * den;
      }
      *y += (*dy = (2*ns < (n-m) ? c[ns+1] : d[ns--]));
   }
   free_vector(d, 1, n);
   free_vector(c, 1, n);
}

static int 
match(n, cof, xa, ya)
   double xa[], ya[], cof[];
   int n;
/*
   Given arrays xa[0..n] and ya[0..n] containing a tabulated function
   ya = f(xa), this routine returns an array of coefficients cof[0..n],
   such that ya[i] = sum_j {cof[j]*xa[i]**j}.
 */
{
   int k, j, i;
   double xmin, dy, *x, *y, *xx, *vector();
   void polint(), free_vector();

   x = vector(0, n);
   y = vector(0, n);
   xx = vector(0, n);
   for (j = 0; j <= n; j++) {
      x[j] = xa[j];
      xx[j] = y[j] = ya[j];
   }
   for (j = 0; j <= n; j++) {
      polint(x-1, y-1, n+1-j, (double) 0.0, &cof[j], &dy);
      xmin = 1.0e38;
      k = -1;
      for (i = 0; i <= n-j; i++) {
	 if (ABS(x[i]) < xmin) {
	    xmin = ABS(x[i]);
	    k = i;
	 }
	 if (x[i]) y[i] = (y[i] - cof[j]) / x[i];
      }
      for (i = k+1; i <= n-j; i++) {
	 y[i-1] = y[i];
	 x[i-1] = x[i];
      }
   }
   free_vector(y, 0, n);
   free_vector(x, 0, n);

   /****   check   ****/
   /*
   for (i = 0; i <= n; i++) {
      xmin = xa[i];
      dy = cof[0];
      for (j = 1; j <= n; j++) {
	 dy += xmin * cof[j];
         xmin *= xa[i];
      }
      printf("*** real x = %e y = %e\n", xa[i], xx[i]);
      printf("*** calculated  y = %e\n", dy);
      printf("*** error = %e \% \n", (dy-xx[i])/xx[i]);
   }
   */
}

/***
 ***/

static int
match_x(dim, Alfa, X, Y)
   int dim;
   double  X[]; 
   double  Y[]; 
   double  Alfa[];
{
   int i, j;
   double f;
   double scale;

   /****   check   ****/
   double xx[16];
   for (i = 0; i <= dim; i++)
      xx[i] = Y[i];

   if (Y[1] == Y[0])
      scale = 1.0;
   else
      scale = X[1] / (Y[1] - Y[0]);
   for (i = 0; i < dim; i++) {
      f = X[i+1];
      for (j = dim-1; j >= 0; j--) {
         A[i][j] = f;
	 f *= X[i+1];
      }
      A[i][dim] = (Y[i+1] - Y[0])*scale;
   }
   Gaussian_Elimination2(dim, 1);
   Alfa[0] = Y[0];
   for (i = 1; i <= dim; i++) 
      Alfa[i] = A[dim-i][dim] / scale;

   /****   check   ****/
   /* 
   for (i = 0; i <= dim; i++) {
      f = X[i];
      scale = Alfa[0];
      for (j = 1; j <= dim; j++) {
	 scale += f * Alfa[j];
         f *= X[i];
      }
      printf("*** real x = %e y = %e\n", X[i], xx[i]);
      printf("*** calculated  y = %e\n", scale);
      printf("*** error = %e \% \n", (scale-xx[i])/xx[i]);
   }
   */

   return(1);
}

/***
 ***/

static int 
Gaussian_Elimination2(dims, type)
   /*  type = 1 : to solve a linear system  
	     -1 : to inverse a matrix  */
   int dims;
   int type;
{
   register int i, j, k, dim;
   register double f;
   double max;
   int imax;

   if (type == -1)
      dim = 2 * dims;
   else
      dim = dims;

   for (i = 0; i < dims; i++) {
      imax = i;
      max = ABS(A[i][i]);
      for (j = i+1; j < dim; j++)
         if (ABS(A[j][i]) > max) {
	    imax = j;
	    max = ABS(A[j][i]);
	 }
      if (max < epsilon) {
         fprintf(stderr, " can not choose a pivot (misc)\n");
         exit(0);
      }
      if (imax != i)
         for (k = i; k <= dim; k++) {
            f = A[i][k];
            A[i][k] = A[imax][k];
	    A[imax][k] = f;
	 }

      f = 1.0 / A[i][i];
      A[i][i] = 1.0;

      for (j = i+1; j <= dim; j++)
	 A[i][j] *= f;

      for (j = 0; j < dims ; j++) {
	 if (i == j)
	    continue;
	 f = A[j][i];
	 A[j][i] = 0.0;
	 for (k = i+1; k <= dim; k++)
	    A[j][k] -= f * A[i][k];
      }
   }

   return(1);
}

/***

static void
eval_Si_Si_1(dim, y)
   int dim;
   double y;
{
   int i, j, k;

   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++) {
	 Si_1[i][j] = 0.0;
	 for (k = 0; k < dim; k++)
	    if (k == j)
			Si_1[i][j] += Sv_1[i][k] *
				(y * R_m[k][j] + Scaling_F * L_m[k][j]);
	    else 
			Si_1[i][j] += Sv_1[i][k] * L_m[k][j] * Scaling_F;
			/
			Si_1[i][j] *= Scaling_F;
			/
      }

   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++)
	 Si_1[i][j] /= sqrt((double) D[i]);

   for (i = 0; i < dim; i++) {
      for (j = 0; j < dim; j++)
	 A[i][j] = Si_1[i][j];
      for (j = dim; j < 2* dim; j++)
	 A[i][j] = 0.0;
      A[i][i+dim] = 1.0;
   }
   Gaussian_Elimination2(dim, -1);

   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++)
	 Si[i][j] = A[i][j+dim];
}

***/

static void
eval_Si_Si_1(dim, y)
   int dim;
   double y;
{
   int i, j, k;

   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++) {
	 Si_1[i][j] = 0.0;
	 for (k = 0; k < dim; k++)
	    Si_1[i][j] += Sv_1[i][k] * (y * R_m[k][j] + Scaling_F * L_m[k][j]);
	       /*
	    else 
	       Si_1[i][j] += Sv_1[i][k] * L_m[k][j] * Scaling_F;
	 Si_1[i][j] *= Scaling_F;
		*/
      }

   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++)
	 Si_1[i][j] /= sqrt((double) D[i]);

   for (i = 0; i < dim; i++) {
      for (j = 0; j < dim; j++)
	 A[i][j] = Si_1[i][j];
      for (j = dim; j < 2* dim; j++)
	 A[i][j] = 0.0;
      A[i][i+dim] = 1.0;
   }
   Gaussian_Elimination2(dim, -1);

   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++)
	 Si[i][j] = A[i][j+dim];
}

/***

static void
loop_ZY(dim, y)
   int dim;
   double y;
{
   int i, j, k;
   double fmin, fmin1;

   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++) 
	 if (i == j) 
	    ZY[i][j] = Scaling_F * C_m[i][i] + G_m[i] * y;
	 else
	    ZY[i][j] = Scaling_F * C_m[i][j];
   diag(dim);
   fmin = D[0];
   for (i = 1; i < dim; i++)
      if (D[i] < fmin)
	 fmin = D[i];
   if (fmin < 0) {
      fprintf(stderr, "(Error) The capacitance matrix of the multiconductor system is not positive definite.\n");
      exit(0);
   } else {
      fmin = sqrt(fmin);
      fmin1 = 1 / fmin;
   }
   for (i = 0; i < dim; i++)
      D[i] = sqrt((double) D[i]);
   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++) {
	 Y5[i][j] = D[i] * Sv[j][i];
	 Y5_1[i][j] = Sv[j][i] / D[i];
      }
   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++) {
	 Sv_1[i][j] = 0.0;
	 for (k = 0; k < dim; k++) 
	    Sv_1[i][j] += Sv[i][k] * Y5[k][j];
      }
   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++) 
	 Y5[i][j] = Sv_1[i][j]; 
   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++) {
	 Sv_1[i][j] = 0.0;
	 for (k = 0; k < dim; k++) 
	    Sv_1[i][j] += Sv[i][k] * Y5_1[k][j];
      }
   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++) 
	 Y5_1[i][j] = Sv_1[i][j]; 

   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++) {
	 ZY[i][j] = 0.0;
	 for (k = 0; k < dim; k++)
            if (k == i) 
	       ZY[i][j] += (Scaling_F *  L_m[i][i] + R_m[i] * y) * 
			       Y5[k][j];
	    else 
	       ZY[i][j] += L_m[i][k] * Y5[k][j] * Scaling_F;
      }
   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++) {
	 Sv_1[i][j] = 0.0;
	 for (k = 0; k < dim; k++) 
	    Sv_1[i][j] += Y5[i][k] * ZY[k][j];
      }
   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++) 
	 ZY[i][j] = Sv_1[i][j]; 

   diag(dim);

   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++) {
	 Sv_1[i][j] = 0.0; 
	 for (k = 0; k < dim; k++) 
	    Sv_1[i][j] += Sv[k][i] * Y5[k][j];
	 Sv_1[i][j] *= fmin1;
      }
   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++) {
	 ZY[i][j] = 0.0; 
	 for (k = 0; k < dim; k++) 
	    ZY[i][j] += Y5_1[i][k] * Sv[k][j];
	 ZY[i][j] *= fmin;
      }
   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++) 
	 Sv[i][j] = ZY[i][j]; 

}
***/

static void
loop_ZY(dim, y)
   int dim;
   double y;
{
   int i, j, k;
   double fmin, fmin1;

   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++) 
	 ZY[i][j] = Scaling_F * C_m[i][j] + G_m[i][j] * y;
	    /*
	 else
	    ZY[i][j] = Scaling_F * C_m[i][j];
	     */
   diag(dim);
   fmin = D[0];
   for (i = 1; i < dim; i++)
      if (D[i] < fmin)
	 fmin = D[i];
   if (fmin < 0) {
      fprintf(stderr, "(Error) The capacitance matrix of the multiconductor system is not positive definite.\n");
      exit(0);
   } else {
      fmin = sqrt(fmin);
      fmin1 = 1 / fmin;
   }
   for (i = 0; i < dim; i++)
      D[i] = sqrt((double) D[i]);
   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++) {
	 Y5[i][j] = D[i] * Sv[j][i];
	 Y5_1[i][j] = Sv[j][i] / D[i];
      }
   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++) {
	 Sv_1[i][j] = 0.0;
	 for (k = 0; k < dim; k++) 
	    Sv_1[i][j] += Sv[i][k] * Y5[k][j];
      }
   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++) 
	 Y5[i][j] = Sv_1[i][j]; 
   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++) {
	 Sv_1[i][j] = 0.0;
	 for (k = 0; k < dim; k++) 
	    Sv_1[i][j] += Sv[i][k] * Y5_1[k][j];
      }
   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++) 
	 Y5_1[i][j] = Sv_1[i][j]; 

   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++) {
	 ZY[i][j] = 0.0;
	 for (k = 0; k < dim; k++)
	    ZY[i][j] += (Scaling_F *  L_m[i][k] + R_m[i][k] * y) * Y5[k][j];
	 /*
	    else 
	       ZY[i][j] += L_m[i][k] * Y5[k][j] * Scaling_F;
	  */
      }
   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++) {
	 Sv_1[i][j] = 0.0;
	 for (k = 0; k < dim; k++) 
	    Sv_1[i][j] += Y5[i][k] * ZY[k][j];
      }
   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++) 
	 ZY[i][j] = Sv_1[i][j]; 

   diag(dim);

   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++) {
	 Sv_1[i][j] = 0.0; 
	 for (k = 0; k < dim; k++) 
	    Sv_1[i][j] += Sv[k][i] * Y5[k][j];
	 Sv_1[i][j] *= fmin1;
      }
   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++) {
	 ZY[i][j] = 0.0; 
	 for (k = 0; k < dim; k++) 
	    ZY[i][j] += Y5_1[i][k] * Sv[k][j];
	 ZY[i][j] *= fmin;
      }
   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++) 
	 Sv[i][j] = ZY[i][j]; 

}


/***
 ***/

static void 
poly_matrix(A, dim, deg)
   double *A[MAX_DIM][MAX_DIM];
   int dim, deg;
{
   int i, j;

   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++)
	 match(deg, A[i][j], frequency, A[i][j]);
}

/***
 ***/

static int 
checkW(W, d)
   double W[], d;
{
  double f, y;
  float  y1;
  int k;

  printf("(W)y =");
  scanf("%f", &y1);

  f = W[0];
  y = y1;
  f += y * W[1];
  for (k = 2; k < 6; k++) {
     y *= y1;
     f += y * W[k];
  }
  printf("W[i]= %e\n ", f*exp((double)-d/y1));

  return(1);
}

/***
 ***/

static void 
poly_W(dim, deg)
   int dim, deg;
{
   int i;
   extern double approx_mode();

   for (i = 0; i < dim; i++) {
      match(deg, W[i], frequency, W[i]);
      TAU[i] = approx_mode(W[i], W[i], length);
	  /*
      checkW(W[i], TAU[i]);
	  */
   }
}

/***
 ***/
   
static void
eval_frequency(dim, deg_o)
   int deg_o;
{
   int i, im;
   double min;

   min = D[0];
   im = 0;

   for (i = 1; i < dim; i++) 
      if (D[i] < min) {
	 min = D[i];
	 im = i;
      }

   if (min <= 0) {
      fprintf(stderr, "A mode frequency is not positive.  Abort!\n");
      exit(0);
   }

   Scaling_F2 = 1.0 / min;
   Scaling_F = sqrt(Scaling_F2);
   min = length * 8.0;
   /*
   min *= 1.0e18;
   min = sqrt(min)*1.0e-9*length/8.0;
    */

   frequency[0] = 0.0;

   for (i = 1; i <= deg_o; i++)
      frequency[i] = frequency[i-1] + min;

   for (i = 0; i < dim; i++)
      D[i] *= Scaling_F2;
}

/***
 ***/

static void
store(dim, ind)
   int ind;
{
   int i, j;

   for (i = 0; i < dim; i++) {
      for (j = 0; j < dim; j++) {
         /*  store_Sip  */
	 Sip[i][j][ind] = Si[i][j];
         /*  store_Si_1p  */
	 Si_1p[i][j][ind] = Si_1[i][j];
         /*  store_Sv_1p  */
	 Sv_1p[i][j][ind] = Sv_1[i][j];
      }
      /*  store_W  */
      W[i][ind] = D[i];
   }
}

/***
 ***/

static void
store_SiSv_1(dim, ind)
{
   int i, j, k;
   double temp;

   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++) {
	 temp = 0.0;
	 for (k = 0; k < dim; k++)
	   temp += Si[i][k] * Sv_1[k][j];
      SiSv_1[i][j][ind] = temp;
   }
}

/***
 ***/

static int 
check(Sip, Si_1p, Sv_1p, SiSv_1p)
   double *Sip[MAX_DIM][MAX_DIM];
   double *Si_1p[MAX_DIM][MAX_DIM];
   double *Sv_1p[MAX_DIM][MAX_DIM];
   double *SiSv_1p[MAX_DIM][MAX_DIM];
{
   double f, y;
   float  y1;
   int i, j, k;

   printf("y =");
   scanf("%f", &y1);

   printf("\n");
   printf("Si =\n");
   for (i = 0; i < 4; i++) {
      for (j = 0; j < 4; j++) {
	 f = Sip[i][j][0];
         y = y1;
	 f += y * Sip[i][j][1];
	 for (k = 2; k < 8; k++) {
	    y *= y1;
	    f += y * Sip[i][j][k];
	 }
	 printf("%e ", f);
      }
      printf("\n");
   }
   printf("\n");
   printf("Si_1 =\n");
   for (i = 0; i < 4; i++) {
      for (j = 0; j < 4; j++) {
	 f = Si_1p[i][j][0];
         y = y1;
	 f += y * Si_1p[i][j][1];
	 for (k = 2; k < 8; k++) {
	    y *= y1;
	    f += y * Si_1p[i][j][k];
	 }
	 printf("%e ", f);
      }
      printf("\n");
   }
   printf("\n");
   printf("Sv_1 =\n");
   for (i = 0; i < 4; i++) {
      for (j = 0; j < 4; j++) {
	 f = Sv_1p[i][j][0];
         y = y1;
	 f += y * Sv_1p[i][j][1];
	 for (k = 2; k < 8; k++) {
	    y *= y1;
	    f += y * Sv_1p[i][j][k];
	 }
	 printf("%e ", f);
      }
      printf("\n");
   }
   printf("\n");
   printf("SiSv_1 =\n");
   for (i = 0; i < 4; i++) {
      for (j = 0; j < 4; j++) {
	 f = SiSv_1p[i][j][0];
         y = y1;
	 f += y * SiSv_1p[i][j][1];
	 for (k = 2; k < 8; k++) {
	    y *= y1;
	    f += y * SiSv_1p[i][j][k];
	 }
	 printf("%e ", f);
      }
      printf("\n");
   }
   return(1);
}

/***
 ***/

static int 
coupled(dim)
   int dim;
{
   int deg, deg_o;
   int i;

   deg = Right_deg;
   deg_o =  Left_deg;
   new_memory(dim, deg, deg_o);

   Scaling_F = Scaling_F2 = 1.0;

   /***     y = 0 : ZY = LC    ***/
   loop_ZY(dim, (double) 0.0);
   eval_frequency(dim, deg_o);
   eval_Si_Si_1(dim, (double) 0.0);
   store_SiSv_1(dim, (int) 0);
   store(dim, (int) 0);

   /***     Step  1     ***/
   /***     Step  2     ***/
   for (i = 1; i <= deg_o; i++) { 
       loop_ZY(dim, frequency[i]);
       eval_Si_Si_1(dim, frequency[i]);
       store_SiSv_1(dim, i);
       store(dim, i);
   }
   poly_matrix(Sip, dim, deg_o);
   poly_matrix(Si_1p, dim, deg_o);
   poly_matrix(Sv_1p, dim, deg_o);
   poly_W(dim, deg_o);
   matrix_p_mult(Sip, W, Si_1p, dim, deg_o, deg_o, IWI);
   matrix_p_mult(Sip, W, Sv_1p, dim, deg_o, deg_o, IWV);

   poly_matrix(SiSv_1, dim, deg_o);

   /***
   check(Sip, Si_1p, Sv_1p, SiSv_1);
   ***/

   generate_out(dim, deg_o);

   return(1);
}

/***
 ***/

static int 
generate_out(dim, deg_o)
   int dim, deg_o;
{
   int i, j, k, rtv;
   double C;
   double *p;
   double c1, c2, c3, x1, x2, x3;

   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++) {
	 p = SiSv_1[i][j];
	 SIV[i][j].C_0 = C = p[0];
	 if (C == 0.0)
	    continue;
	 for (k = 0; k <= deg_o; k++) 
	    p[k] /= C;
	 if (i == j) {
	    rtv = Pade_apx((double) sqrt((double) G_m[i][i] / R_m[i][i]) / C, 
		  p, &c1, &c2, &c3, &x1, &x2, &x3);
	    if (rtv == 0) {
	       SIV[i][j].C_0 = 0.0;
	       printf("SIV\n");
	       continue;
	    }
	 } else {
	    rtv = Pade_apx((double) 0.0, 
		  p, &c1, &c2, &c3, &x1, &x2, &x3);
	    if (rtv == 0) {
	       SIV[i][j].C_0 = 0.0;
	       printf("SIV\n");
	       continue;
	    }
	 }
         p = SIV[i][j].Poly = (double *) calloc(7, sizeof(double));
	 p[0] = c1;
	 p[1] = c2;
	 p[2] = c3;
	 p[3] = x1;
	 p[4] = x2;
	 p[5] = x3;
	 p[6] = (double) rtv;
      }
   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++) 
	 for (k = 0; k < dim; k++) {
	    p = IWI[i][j].Poly[k];
	    C = IWI[i][j].C_0[k];
	    if (C == 0.0)
	       continue;
	    if (i == j && k == i) {
	       rtv = Pade_apx((double) 
	             exp(- sqrt((double) G_m[i][i] * R_m[i][i]) * length) / C,
		     p, &c1, &c2, &c3, &x1, &x2, &x3);
	       if (rtv == 0) {
		  IWI[i][j].C_0[k] = 0.0;
		  printf("IWI %d %d %d\n", i, j, k);
		  continue;
	       }
	    } else {
	       rtv = Pade_apx((double) 0.0, 
		  p, &c1, &c2, &c3, &x1, &x2, &x3);
	       if (rtv == 0) {
		  IWI[i][j].C_0[k] = 0.0;
		  printf("IWI %d %d %d\n", i, j, k);
		  continue;
	       }
	    }
	    p[0] = c1;
	    p[1] = c2;
	    p[2] = c3;
	    p[3] = x1;
	    p[4] = x2;
	    p[5] = x3;
	    p[6] = (double) rtv;
         }

   for (i = 0; i < dim; i++)
      for (j = 0; j < dim; j++) 
	 for (k = 0; k < dim; k++) {
	    p = IWV[i][j].Poly[k];
	    C = IWV[i][j].C_0[k];
	    if (C == 0.0)
	       continue;
	    if (i == j && k == i) {
	       rtv = Pade_apx((double) sqrt((double) G_m[i][i] / R_m[i][i]) * 
		     exp(- sqrt((double) G_m[i][i] * R_m[i][i]) * length) / C,
		     p, &c1, &c2, &c3, &x1, &x2, &x3);
	       if (rtv == 0) {
		  IWV[i][j].C_0[k] = 0.0;
		  printf("IWV %d %d %d\n", i, j, k);
		  continue;
	       }
	    } else {
	       rtv = Pade_apx((double) 0.0, 
		  p, &c1, &c2, &c3, &x1, &x2, &x3);
	       if (rtv == 0) {
		  IWV[i][j].C_0[k] = 0.0;
		  printf("IWV %d %d %d\n", i, j, k);
		  continue;
	       }
            }
	    p[0] = c1;
	    p[1] = c2;
	    p[2] = c3;
	    p[3] = x1;
	    p[4] = x2;
	    p[5] = x3;
	    p[6] = (double) rtv;
         }
   return(1);
}

/****************************************************************
     mult.c     Multiplication for Matrix of Polynomial 
		   X(y) = A(y) D(y) B(y),
		   where D(y) is a diagonal matrix with each 
		   diagonal entry of the form
			   e^{-a_i s}d(y), for which s = 1/y
				                 and i = 1..N.
		   Each entry of X(y) will be of the form
		      \sum_{i=1}^N c_i e^{-a_i s} b_i(y), where
		      b_i(0) = 1; therefore, those
		      b_i(y)'s will be each entry's output. 
 ****************************************************************/

static void
mult_p(p1, p2, p3, d1, d2, d3)
/*   p3 = p1 * p2   */
   double *p1, *p2, *p3;
   int    d1, d2, d3;
{
   int i, j, k;

   for (i = 0; i <= d3; i++)
      p3[i] = 0.0;
   for (i = 0; i <= d1; i++)
      for (j = i, k = 0; k <= d2; j++, k++) {
	 if (j > d3)
	    break;
	 p3[j] += p1[i] * p2[k];
      }
}


static void
matrix_p_mult(A, D, B, dim, deg, deg_o, X)
   double  *A[MAX_DIM][MAX_DIM]; 
   double  *D[MAX_DIM]; 
   double  *B[MAX_DIM][MAX_DIM]; 
   int     dim, deg, deg_o;
   Mult_Out  X[MAX_DIM][MAX_DIM]; 
{
   int i, j, k, l;
   double *p;
   double *T[MAX_DIM][MAX_DIM];
   double t1;

   for (i  = 0; i < dim; i++) 
      for (j = 0; j < dim; j++) {
	 p = T[i][j] = (double *) calloc(deg_o+1, sizeof(double));
	 mult_p(B[i][j], D[i], p, deg, deg_o, deg_o);
      }
   for (i  = 0; i < dim; i++)
      for (j = 0; j < dim; j++) 
	 for (k = 0; k < dim; k++) {
	    p = X[i][j].Poly[k] = 
			    (double *) calloc(deg_o+1, sizeof(double));
	    mult_p(A[i][k], T[k][j], p, deg, deg_o, deg_o);
	    t1 = X[i][j].C_0[k] = p[0];
	    if (t1 != 0.0) {
	       p[0] = 1.0;
	       for (l = 1; l <= deg_o; l++)
	          p[l] /= t1;
	    }
	 }
      
      /**********
   for (i  = 0; i < dim; i++)
      for (j = 0; j < dim; j++) {
	    for (k = 0; k < dim; k++) {
	    fprintf(outFile, "(%5.3f)", X[i][j].C_0[k]);
	    p = X[i][j].Poly[k];
	    for (l = 0; l <= deg_o; l++)
	       fprintf(outFile, "%5.3f ", p[l]); 
	    fprintf(outFile, "\n");
	 }
         fprintf(outFile, "\n");
      }
       ***********/
}

/****************************************************************
	          mode  approximation  

 ****************************************************************/

/***
 ***/

static double 
approx_mode(X, b, length)
   double X[], b[], length;
{
   double w0, w1, w2, w3, w4, w5;
   double a[8];
   double delay, atten;
   double y1, y2, y3, y4, y5, y6;
   int    i, j;

   w0 = X[0];
   w1 = X[1] / w0;  /* a */
   w2 = X[2] / w0;  /* b */
   w3 = X[3] / w0;  /* c */
   w4 = X[4] / w0;  /* d */
   w5 = X[5] / w0;  /* e */

   y1 = 0.5 * w1;
   y2 = w2 - y1 * y1;
   y3 = 3 * w3 - 3.0 * y1 * y2;
   y4 = 12.0 * w4 - 3.0 * y2 * y2 - 4.0 * y1 * y3;
   y5 = 60.0 * w5 - 5.0 * y1 * y4 -10.0 * y2 * y3;
   y6 = -10.0 * y3 * y3 - 15.0 * y2 * y4 - 6.0 * y1 * y5;

   delay = sqrt(w0) * length / Scaling_F;
   atten = exp((double) - delay * y1);

   a[1] = y2 / 2.0;
   a[2] = y3 / 6.0;
   a[3] = y4 / 24.0;
   a[4] = y5 / 120.0;
   a[5] = y6 / 720.0;

   a[1] *= -delay;
   a[2] *= -delay;
   a[3] *= -delay;
   a[4] *= -delay;
   a[5] *= -delay;
   
   b[0] = 1.0;
   b[1] = a[1];
   for (i = 2; i <= 5; i++) {
      b[i] = 0.0;
      for (j = 1; j <= i; j++)
	 b[i] += j * a[j] * b[i-j];
      b[i] = b[i] / (double) i;
   }

   for (i = 0; i <= 5; i++)
      b[i] *= atten;

   return(delay);
}

/***
 ***/

static double 
eval2(a, b, c, x)
   double a, b, c, x;
{
   return(a*x*x + b*x + c);
}

/***
 ***/

static int 
get_c(q1, q2, q3, p1, p2, a, b, cr, ci)
   double q1, q2, q3, p1, p2, a, b;
   double *cr, *ci;
{
   double d, n;

   d = (3.0*(a*a-b*b)+2.0*p1*a+p2)*(3.0*(a*a-b*b)+2.0*p1*a+p2);
   d += (6.0*a*b+2.0*p1*b)*(6.0*a*b+2.0*p1*b);
   n = -(q1*(a*a-b*b)+q2*a+q3)*(6.0*a*b+2.0*p1*b);
   n += (2.0*q1*a*b+q2*b)*(3.0*(a*a-b*b)+2.0*p1*a+p2);
   *ci = n/d;
   n = (3.0*(a*a-b*b)+2.0*p1*a+p2)*(q1*(a*a-b*b)+q2*a+q3);
   n += (6.0*a*b+2.0*p1*b)*(2.0*q1*a*b+q2*b);
   *cr = n/d;

   return(1);
}


static int 
Pade_apx(a_b, b, c1, c2, c3, x1, x2, x3)
/*     
        b[0] + b[1]*y + b[2]*y^2 + ... + b[5]*y^5 + ...
      = (q3*y^3 + q2*y^2 + q1*y + 1) / (p3*y^3 + p2*y^2 + p1*y + 1)
       
	where b[0] is always equal to 1.0 and neglected,
	  and y = 1/s.

	(q3*y^3 + q2*y^2 + q1*y + 1) / (p3*y^3 + p2*y^2 + p1*y + 1)
      = (s^3 + q1*s^2 + q2*s + q3) / (s^3 + p1*s^2 + p2*s + p3)
      = c1 / (s - x1) + c2 / (s - x2) + c3 / (s - x3) + 1.0
 */
   double a_b;
   double b[];
   double *c1, *c2, *c3;
   double *x1, *x2, *x3;
{
   double p1, p2, p3, q1, q2, q3;

   At[0][0] = 1.0 - a_b;
   At[0][1] = b[1];
   At[0][2] = b[2];
   At[0][3] = -b[3];

   At[1][0] = b[1];
   At[1][1] = b[2];
   At[1][2] = b[3];
   At[1][3] = -b[4];

   At[2][0] = b[2];
   At[2][1] = b[3];
   At[2][2] = b[4];
   At[2][3] = -b[5];

   Gaussian_Elimination(3);

   p3 = At[0][3];
   p2 = At[1][3];
   p1 = At[2][3];
   /*
   if (p3 < 0.0 || p2 < 0.0 || p1 < 0.0 || p1*p2 <= p3)
      return(0);
    */
   q1 = p1 + b[1];
   q2 = b[1] * p1 + p2 + b[2];
   q3 = p3 * a_b;

   if (find_roots(p1, p2, p3, x1, x2, x3)) {
      /*
      printf("complex roots : %e %e %e \n", *x1, *x2, *x3);
       */
      *c1 = eval2(q1 - p1, q2 - p2, q3 - p3, *x1) /
                   eval2((double) 3.0, (double) 2.0 * p1, p2, *x1);
      get_c(q1 - p1, q2 - p2, q3 - p3, p1, p2, *x2, *x3, c2, c3);
      return(2);
   } else {
      /* new
	  printf("roots are %e %e %e \n", *x1, *x2, *x3);
	  */
      *c1 = eval2(q1 - p1, q2 - p2, q3 - p3, *x1) / 
		   eval2((double) 3.0, (double) 2.0 * p1, p2, *x1);
      *c2 = eval2(q1 - p1, q2 - p2, q3 - p3, *x2) / 
		   eval2((double) 3.0, (double) 2.0 * p1, p2, *x2);
      *c3 = eval2(q1 - p1, q2 - p2, q3 - p3, *x3) / 
		   eval2((double) 3.0, (double) 2.0 * p1, p2, *x3);
      return(1);
   }
}

static int 
Gaussian_Elimination(dims)
   int dims;
{
   register int i, j, k, dim;
   register double f;
   double max;
   int imax;

   dim = dims;

   for (i = 0; i < dim; i++) {
      imax = i;
      max = ABS(At[i][i]);
      for (j = i+1; j < dim; j++)
	 if (ABS(At[j][i]) > max) {
	    imax = j;
	    max = ABS(At[j][i]);
         }
      if (max < epsi_mult) {
         fprintf(stderr, " can not choose a pivot (mult)\n");
         exit(0);
      }
      if (imax != i)
	 for (k = i; k <= dim; k++) {
	    f = At[i][k];
	    At[i][k] = At[imax][k];
	    At[imax][k] = f;
	 }
      
      f = 1.0 / At[i][i];
      At[i][i] = 1.0;

      for (j = i+1; j <= dim; j++)
	 At[i][j] *= f;

      for (j = 0; j < dim ; j++) {
	 if (i == j)
	    continue;
	 f = At[j][i];
	 At[j][i] = 0.0;
	 for (k = i+1; k <= dim; k++)
	    At[j][k] -= f * At[i][k];
      }
   }
   return(1);
}

static double 
root3(a1, a2, a3, x)
   double x;
   double a1, a2, a3;
{
   double t1, t2;

   t1 = x * (x * (x + a1) + a2) + a3;
   t2 = x * (2.0*a1 + 3.0*x) + a2;

   return(x - t1 / t2);
}

static int 
div3(a1, a2, a3, x, p1, p2)
   double x;
   double a1, a2, a3;
   double *p1, *p2;
{
	*p1 = a1 + x;

	/* *p2 = a2 + (a1 + x) * x; */

	*p2 = - a3 / x;

   return(1);
}


static int 
find_roots(a1, a2, a3, x1, x2, x3)
   double  a1, a2, a3;
   double *x1, *x2, *x3;
{
   double x, t;
   double p, q, m, n;

   /***********************************************
   p = a1*a1/3.0 - a2;
   q = a1*a2/3.0 - a3 - 2.0*a1*a1*a1/27.0;
   p = p*p*p/27.0;
   t = q*q - 4.0*p;
   if (t < 0.0) {
      if (q != 0.0) {
	 t = atan(sqrt((double)-t)/q);
	 if (t < 0.0)
	    t += 3.141592654;
	 t /= 3.0;
	 x = 2.0 * pow(p, 0.16666667) * cos(t) - a1 / 3.0;
      } else {
         t /= -4.0;
         x = pow(t, 0.16666667) * 1.732 - a1 / 3.0;
      }
   } else {
      t = sqrt(t);
      m = 0.5*(q - t);
      n = 0.5*(q + t);
      if (m < 0.0)
         m = -pow((double) -m, (double) 0.3333333);
      else
         m = pow((double) m, (double) 0.3333333);
      if (n < 0.0)
         n = -pow((double) -n, (double) 0.3333333);
      else
         n = pow((double) n, (double) 0.3333333);
      x = m + n - a1 / 3.0;
   }
    ************************************************/
   q = (a1*a1-3.0*a2) / 9.0;
   p = (2.0*a1*a1*a1-9.0*a1*a2+27.0*a3) / 54.0;
   t = q*q*q - p*p;
   if (t >= 0.0) {
      t = acos((double) p /(q * sqrt(q)));
      x = -2.0*sqrt(q)*cos(t / 3.0) - a1/3.0;
   } else {
      if (p > 0.0) {
	 t = pow(sqrt(-t)+p, (double) 1.0 / 3.0);
	 x = -(t + q / t) - a1/3.0;
      } else if (p == 0.0) {
	 x = -a1/3.0;
      } else {
	 t = pow(sqrt(-t)-p, (double) 1.0 / 3.0);
	 x = (t + q / t) - a1/3.0;
      }
   }
   /*
   fprintf(stderr, "..1.. %e\n", x*x*x+a1*x*x+a2*x+a3);
    */
   { 
      double x1;
      int i = 0;
   x1 = x;
   for (t = root3(a1, a2, a3, x); ABS(t-x) > 5.0e-4; 
			    t = root3(a1, a2, a3, x)) 
      if (++i == 32) {
	 x = x1;
	 break;
      } else 
         x = t;
   }
   /*
   fprintf(stderr, "..2.. %e\n", x*x*x+a1*x*x+a2*x+a3);
    */


   *x1 = x;
   div3(a1, a2, a3, x, &a1, &a2);

   t = a1 * a1 - 4.0 * a2;
   if (t < 0) {
      /*
      fprintf(stderr, "***** Two Imaginary Roots.\n Update.\n");
      *x2 = -0.5 * a1;
      *x3 = a2 / *x2;
       */
      *x3 = 0.5 * sqrt(-t);
      *x2 = -0.5 * a1;
      return(1);
   } else {
      t = sqrt(t);
      if (a1 >= 0.0)
	 *x2 = t = -0.5 * (a1 + t);
      else
	 *x2 = t = -0.5 * (a1 - t);
      *x3 = a2 / t;
      return(0);
   }
}


static NDnamePt
insert_ND(name, ndn)
   char *name;
   NDnamePt *ndn;
{
   int       cmp;
   NDnamePt  p;

   if (*ndn == NULL) {
      p = *ndn = (NDnamePt) malloc(sizeof (NDname));
      p->nd = NULL;
      p->right = p->left = NULL;
      strcpy(p->id, name);
      return(p);
   }
   cmp = strcmp((*ndn)->id, name);
   if (cmp == 0) 
      return(*ndn);
   else {
      if (cmp < 0)
         return(insert_ND(name, &((*ndn)->left)));
      else
         return(insert_ND(name, &((*ndn)->right)));
   }
}

static NODE *
insert_node(name)
   char *name;
{
   NDnamePt n;
   NODE    *p;

   n = insert_ND(name, &ndn);
   if (n->nd == NULL) {
      p = NEW_node();
      p->name = n;
      n->nd = p;
      p->next = node_tab;
      node_tab = p;
      return(p);
   } else
      return(n->nd);
}

static int divC(ar, ai, br, bi, cr, ci)
double ar, ai, br, bi;
double *cr, *ci;
{
	double t;

	t = br*br + bi*bi;
	*cr = (ar*br + ai*bi) / t;
	*ci = (ai*br - ar*bi) / t;

	return(1);
}


static NODE
*NEW_node()
{
   /*
   char *malloc();
    */
   NODE *n;

   n = (NODE *) malloc (sizeof (NODE));
   n->mptr = NULL;
   n->gptr = NULL;
   n->cptr = NULL;
   n->rptr = NULL;
   n->tptr = NULL;
   n->cplptr = NULL;
   n->rlptr = NULL;
   n->ddptr = NULL;
   n->cvccsptr = NULL;
   n->vccsptr = NULL;
   n->CL = 0.001;
   n->V = n->dv = 0.0;
   n->gsum = n->cgsum = 0;
   n->is   = 0;
   n->tag  = 0;
   n->flag = 0;
   n->region = NULL;
   n->ofile = NULL;
   n->dvtag = 0;

   return(n);
}



/****************************************************************
     diag.c      This file contains the main().
 ****************************************************************/

#define  epsi2    1.0e-8

static  int         dim;
static  MAXE_PTR    row;

static MAXE_PTR 
sort(list, val, r, c, e)
   MAXE_PTR list, e;
   float val;
   int r, c;
{
   if (list == NULL || list->value < val) {
      e->row = r;
      e->col = c;
      e->value = val;
      e->next = list;
      return(e);
   } else {
      list->next = sort(list->next, val, r, c, e);
      return(list);
   }
}


static void
ordering()
{
   MAXE_PTR e;
   int i, j, m;
   float mv;

   for (i = 0; i < dim-1; i++) {
      m = i+1;
      mv = ABS(ZY[i][m]);
      for (j = m+1; j < dim; j++) 
	if ((int)(ABS(ZY[i][j]) * 1e7) > (int) (1e7 *mv)) {

	    mv = ABS(ZY[i][j]);
	    m = j;
	 }
      e = (MAXE_PTR) malloc(sizeof (MAXE));
      row = sort(row, mv, i, m, e);
   }
}
      

static MAXE_PTR 
delete_1(list, rc)
   MAXE_PTR *list;
   int rc;
{
   MAXE_PTR list1, e;

   list1 = *list;
   if ((*list)->row == rc) {
      *list = (*list)->next;
      return(list1);
   }
   for (e = list1->next; e->row != rc; e = e->next) 
      list1 = e;
   list1->next = e->next;
   return(e);
}


static void
reordering(p, q)
   int p, q;
{
   MAXE_PTR e;
   int j, m;
   float mv;

   m = p+1;
   mv = ABS(ZY[p][m]);
   for (j = m+1; j < dim; j++) 
	if ((int)(ABS(ZY[p][j]) * 1e7) > (int) (1e7 *mv)) {
         mv = ABS(ZY[p][j]);
         m = j;
      }
   e = delete_1(&row, p);
   row = sort(row, mv, p, m, e);
   
   m = q+1;
   if (m != dim) {
      mv = ABS(ZY[q][m]);
      for (j = m+1; j < dim; j++)
	if ((int)(ABS(ZY[q][j]) * 1e7) > (int) (1e7 *mv)) {
	
            mv = ABS(ZY[q][j]);
            m = j;
         }
      e = delete_1(&row, q);
      row = sort(row, mv, q, m, e);
   }

}

static void 
diag(dims)
   int dims;
{
   int i, j, c;
   double fmin, fmax;

   dim = dims;
   row = NULL;

   fmin = fmax = ABS(ZY[0][0]);
   for (i = 0; i < dim; i++) 
      for (j = i; j < dim; j++) 
	 if (ABS(ZY[i][j]) > fmax)
	    fmax = ABS(ZY[i][j]);
	 else if (ABS(ZY[i][j]) < fmin)
	    fmin = ABS(ZY[i][j]);
   fmin = 2.0 / (fmin + fmax);
   for (i = 0; i < dim; i++)
      for (j = i; j < dim; j++)
         ZY[i][j] *= fmin;

   for (i = 0; i < dim; i++) {
      for (j = 0; j < dim; j++) 
		if (i == j)
			Sv[i][i] = 1.0;
		else 
			Sv[i][j] = 0.0;
   }

   ordering();

   if (row)
	   for (c = 0; row->value > epsi2; c++) {
   		   int p, q;

   		   p = row->row;
   		   q = row->col;

   		   rotate(dim, p, q);
   		   reordering(p, q);
   		}

   for (i = 0; i < dim; i++)
      D[i] = ZY[i][i] / fmin;
}

/****************************************************************
     rotate()      rotation of the Jacobi's method
 ****************************************************************/

static int
rotate(dim, p, q)
   int  p, q, dim;
{
   int j;
   double co, si;
   double ve, mu, ld;
   double T[MAX_DIM];
   double t;

   ld = - ZY[p][q];
   mu = 0.5 * (ZY[p][p] - ZY[q][q]);
   ve = sqrt((double) ld*ld + mu*mu);
   co = sqrt((double) (ve + ABS(mu)) / (2.0 * ve));
   si = SGN(mu) * ld / (2.0 * ve * co);

   for (j = p+1; j < dim; j++)
      T[j] = ZY[p][j];
   for (j = 0; j < p; j++)
      T[j] = ZY[j][p];

   for (j = p+1; j < dim; j++) {
      if (j == q)
	 continue;
      if (j > q)
         ZY[p][j] = T[j] * co - ZY[q][j] * si;
      else
         ZY[p][j] = T[j] * co - ZY[j][q] * si;
   }
   for (j = q+1; j < dim; j++) {
      if (j == p)
	 continue;
      ZY[q][j] = T[j] * si + ZY[q][j] * co;
   }
   for (j = 0; j < p; j++) {
      if (j == q)
	 continue;
      ZY[j][p] = T[j] * co - ZY[j][q] * si;
   }
   for (j = 0; j < q; j++) {
      if (j == p)
	 continue;
      ZY[j][q] = T[j] * si + ZY[j][q] * co;
   }

   t = ZY[p][p];
   ZY[p][p] = t * co * co + ZY[q][q] * si * si - 2.0 * ZY[p][q] * si * co;
   ZY[q][q] = t * si * si + ZY[q][q] * co * co + 2.0 * ZY[p][q] * si * co;

   ZY[p][q] = 0.0;

   {
      double R[MAX_DIM];

      for (j = 0; j < dim; j++) {
         T[j] = Sv[j][p];
         R[j] = Sv[j][q];
      }

      for (j = 0; j < dim; j++) {
         Sv[j][p] = T[j] * co - R[j] * si;
	 Sv[j][q] = T[j] * si + R[j] * co;
      }
   }

   return(1);

}

