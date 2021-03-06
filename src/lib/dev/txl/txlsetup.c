/**********
Copyright 1992 Regents of the University of California.  All rights
reserved.
Author: 1992 Charles Hough
**********/


#include "spice.h"
#include <stdio.h>
#include "util.h"
#include "smpdefs.h"
#include "txldefs.h"
#include "sperror.h"
#include "suffix.h"

#include "capdefs.h"

static int 		ReadTxL();
static int 		multC();
static int 		main_pade();
static int 		mac();
static int 		divC();
static int 		div_C();
static int 		div3();
static double 	approx1();
static double 	approx2();
static int 		find_roots();
static double 	f3();
static double 	f2();
static int 		expC();
static double 	exp_approx1();
static double 	exp_approx2();
static int 		exp_pade();
static int 		exp_div3();
static int 		exp_find_roots();
static double 	eval2();
static int 		get_c();
static int 		get_h3();
static int 		Gaussian_Elimination2();
static int 		Gaussian_Elimination1();
static int 		pade();
static int 		update_h1C_c();
static void 	y_pade();
static double 	root3();
static NDnamePt insert_ND();
static NODE 	*insert_node();
static NODE 	*NEW_node();
static VI_list_txl *new_vi_txl();

NODE     		*node_tab = NULL;
NDnamePt 		ndn = NULL;
VI_list_txl 	*pool_vi_txl = NULL;

/* pade.c */
static double xx1, xx2, xx3, xx4, xx5, xx6;
static double cc1, cc2, cc3, cc4, cc5, cc6;

/* y.c */
static double sqtCdL;
static double b1, b2, b3, b4, b5;
static double p1, p2, p3, q1, q2, q3;
static double c1, c2, c3, x1, x2, x3;
static double A[3][4];

/* exp.c */
static double RdL, GdC, RG, tau, RC, GL;
static double a0, a1, a2, a3, a4, a5;
static double ep1, ep2, ep3, eq1, eq2, eq3;
static double ec1, ec2, ec3, ex1, ex2, ex3;
static int    ifImg;
static double AA[3][4];

#define epsi 1.0e-16
#define epsi2 1.0e-28

/* ARGSUSED */
int
TXLsetup(matrix,inModel,ckt,state)
    register SMPmatrix *matrix;
    GENmodel *inModel;
    CKTcircuit*ckt;
    int *state;
{
    register TXLmodel *model = (TXLmodel *)inModel;
    register CAPmodel *model2;
	register TXLinstance *here;
	register CAPinstance *there;
	register GENinstance *txl;
	CKTnode *tmp, *node;
	int error, m;
	NODE *nd;

    /*  loop through all the models */
    for( ; model != NULL; model = model->TXLnextModel ) {

        /* loop through all the instances of the model */
        for (here = model->TXLinstances; here != NULL ;
                here=here->TXLnextInstance) {
            
/* macro to make elements with built in test for out of memory */
#define TSTALLOC(ptr,first,second) \
if((here->ptr = SMPmakeElt(matrix,here->first,here->second))==(double *)NULL){\
    return(E_NOMEM);\
}

			if (! here->TXLibr1Given) {
				error = CKTmkCur(ckt, &tmp, here->TXLname, "branch1");
				if (error) return (error);
				here->TXLibr1 = tmp->number;
			}
			if (! here->TXLibr2Given) {
				error = CKTmkCur(ckt, &tmp, here->TXLname, "branch2");
				if (error) return (error);
				here->TXLibr2 = tmp->number;
			}

            TSTALLOC(TXLposPosptr, TXLposNode, TXLposNode);
            TSTALLOC(TXLposNegptr, TXLposNode, TXLnegNode);
            TSTALLOC(TXLnegPosptr, TXLnegNode, TXLposNode);
            TSTALLOC(TXLnegNegptr, TXLnegNode, TXLnegNode);
            TSTALLOC(TXLibr1Posptr, TXLibr1, TXLposNode);
            TSTALLOC(TXLibr2Negptr, TXLibr2, TXLnegNode);
            TSTALLOC(TXLnegIbr2ptr, TXLnegNode, TXLibr2);
            TSTALLOC(TXLposIbr1ptr, TXLposNode, TXLibr1);
            TSTALLOC(TXLibr1Ibr1ptr, TXLibr1, TXLibr1);
            TSTALLOC(TXLibr2Ibr2ptr, TXLibr2, TXLibr2);
            TSTALLOC(TXLibr1Negptr, TXLibr1, TXLnegNode);
            TSTALLOC(TXLibr2Posptr, TXLibr2, TXLposNode);
            TSTALLOC(TXLibr1Ibr2ptr, TXLibr1, TXLibr2);
            TSTALLOC(TXLibr2Ibr1ptr, TXLibr2, TXLibr1);

			here->in_node_name = CKTnodName(ckt,here->TXLposNode);
			here->out_node_name = CKTnodName(ckt,here->TXLnegNode);
			ReadTxL(here, ckt);

        }
    }

    return(OK);
}

static VI_list_txl
*new_vi_txl()
{
	VI_list_txl *q;

	if (pool_vi_txl) {
		q = pool_vi_txl;
		pool_vi_txl = pool_vi_txl->pool;
		return(q);
	} else
		return((VI_list_txl *) malloc (sizeof (VI_list_txl)));
}

static int ReadTxL(tx, ckt)
TXLinstance *tx;
CKTcircuit *ckt;
{
   double R, L, G, C, l;
   char *p, *n;
   NODE *nd;
   ETXLine *et;
   TXLine *t, *t2;
   int i;
   RLINE *line;
   ERLINE *er;
   register CKTnode *node;
   double LL = 1e-12;
	
   p = tx->in_node_name;
   n = tx->out_node_name;

   line = (RLINE *) malloc(sizeof (RLINE));
   er = (ERLINE *) malloc(sizeof (ERLINE));
   et = (ETXLine *) malloc(sizeof (ETXLine));
   t = (TXLine *) malloc(sizeof (TXLine));
   t2 = (TXLine *) malloc(sizeof (TXLine));
   tx->txline = t;
   tx->txline2 = t2;
   t->newtp = 0;
   t2->newtp = 0;
   t->vi_head = t->vi_tail = NULL;
   nd = insert_node(p);
   et->link = nd->tptr;
   nd->tptr = et;
   et->line = t;
   t->in_node = nd;
   t2->in_node = nd;
   er->link = nd->rlptr;
   nd->rlptr = er;
   er->rl = line;
   line->in_node = nd;
   et = (ETXLine *) malloc(sizeof (ETXLine));
   nd = insert_node(n);
   et->link = nd->tptr;
   nd->tptr = et;
   et->line = t;
   t->out_node = nd;
   t2->out_node = nd;
   er = (ERLINE *) malloc(sizeof (ERLINE));
   er->link = nd->rlptr;
   nd->rlptr = er;
   er->rl = line;
   line->out_node = nd;
   t->dc1 = t->dc2 = 0.0;
   t2->dc1 = t2->dc2 = 0.0;
   t->lsl = 0;
   t2->lsl = 0;
   l = 0.0;

   R = tx->TXLmodPtr->R;
   L = tx->TXLmodPtr->L;
   L = MAX(L, LL);
   C = tx->TXLmodPtr->C;
   G = tx->TXLmodPtr->G;
   if (tx->TXLlengthgiven == TRUE)
   		l = tx->TXLlength;
   else l = tx->TXLmodPtr->length;	


   if (l == 0.0) {
	   printf(stderr, "(Error) transmission line of zero length\n");
	   exit(0);
   }
   else {
		if (R / L  < 5.0e+5) {
			line->g = 1.0e+2;
			if (G < 1.0e-2) {
				t->lsl = 1;  /* lossless line */
				t->taul = sqrt((double) C * L) * l * 1.0e12;
				t->h3_aten = t->sqtCdL = sqrt((double) C / L);
				t->h2_aten = 1.0;
				t->h1C = 0.0;
			}
		}
		else line->g = 1.0 / (R * l);
	}

   if (! t->lsl)
   		main_pade(R, L, G, C, l, t);

   return(1);
}


/****************************************************************
     pade.c  :  Calculate the Pade Approxximation of Y(s)
 ****************************************************************/


static int main_pade(R, L, G, C, l, h)
   double R, L, G, C, l;
   TXLine *h;
{
   double st, t;
   int s;

   y_pade(R, L, G, C, h);
   h->ifImg = exp_pade(R, L, G, C, l, h);
   get_h3(h);
   h->taul *= 1.0e12;
   update_h1C_c(h);

   return(1);
}

static int div_C(ar, ai, br, bi, cr, ci)
   double ar, ai, br, bi;
   double *cr, *ci;
{
   *cr = ar * br + ai * bi;
   *ci = - ar * bi + ai * br;
   *cr = *cr / (br * br + bi * bi);
   *ci = *ci / (br * br + bi * bi);
}

static int expC(ar, ai, h, cr, ci)
   double ar, ai, *cr, *ci;
   float h;
{
   double e, cs, si;

   e = exp((double) ar * h);
   cs = cos((double) ai * h);
   si = sin((double) ai * h);
   *cr = e * cs;
   *ci = e * si;

   return(1);
}

static int multC(ar, ai, br, bi, cr, ci)
   double ar, ai, br, bi;
   double *cr, *ci;
{
   *cr = ar*br - ai*bi;
   *ci = ar*bi + ai*br;

   return(1);
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

static int get_h3(h)
   TXLine *h;
{
   double cc1, cc2, cc3, cc4, cc5, cc6;
   double xx1, xx2, xx3, xx4, xx5, xx6;

   h->h3_aten = h->h2_aten * h->sqtCdL;
   h->h3_term[0].x = xx1 = h->h1_term[0].x;
   h->h3_term[1].x = xx2 = h->h1_term[1].x;
   h->h3_term[2].x = xx3 = h->h1_term[2].x;
   h->h3_term[3].x = xx4 = h->h2_term[0].x;
   h->h3_term[4].x = xx5 = h->h2_term[1].x;
   h->h3_term[5].x = xx6 = h->h2_term[2].x;
   cc1 = h->h1_term[0].c;
   cc2 = h->h1_term[1].c;
   cc3 = h->h1_term[2].c;
   cc4 = h->h2_term[0].c;
   cc5 = h->h2_term[1].c;
   cc6 = h->h2_term[2].c;

   if (h->ifImg) {
      double r, i;

      h->h3_term[0].c = cc1 + cc1 * (cc4/(xx1-xx4) + 
         2.0*(cc5*xx1-xx6*cc6-xx5*cc5)/(xx1*xx1-2.0*xx5*xx1+xx5*xx5+xx6*xx6));
      h->h3_term[1].c = cc2 + cc2 * (cc4/(xx2-xx4) + 
         2.0*(cc5*xx2-xx6*cc6-xx5*cc5)/(xx2*xx2-2.0*xx5*xx2+xx5*xx5+xx6*xx6));
      h->h3_term[2].c = cc3 + cc3 * (cc4/(xx3-xx4) + 
         2.0*(cc5*xx3-xx6*cc6-xx5*cc5)/(xx3*xx3-2.0*xx5*xx3+xx5*xx5+xx6*xx6));

      h->h3_term[3].c = cc4 + cc4 * (cc1/(xx4-xx1) + cc2/(xx4-xx2) + cc3/(xx4-xx3));

      h->h3_term[4].c = cc5;
      h->h3_term[5].c = cc6;
      div_C(cc5, cc6, xx5-xx1, xx6, &r, &i);
      h->h3_term[4].c += r * cc1;
      h->h3_term[5].c += i * cc1;
      div_C(cc5, cc6, xx5-xx2, xx6, &r, &i);
      h->h3_term[4].c += r * cc2;
      h->h3_term[5].c += i * cc2;
      div_C(cc5, cc6, xx5-xx3, xx6, &r, &i);
      h->h3_term[4].c += r * cc3;
      h->h3_term[5].c += i * cc3;
   } else {
      h->h3_term[0].c = cc1 + cc1 * (cc4/(xx1-xx4) + cc5/(xx1-xx5) + cc6/(xx1-xx6));
      h->h3_term[1].c = cc2 + cc2 * (cc4/(xx2-xx4) + cc5/(xx2-xx5) + cc6/(xx2-xx6));
      h->h3_term[2].c = cc3 + cc3 * (cc4/(xx3-xx4) + cc5/(xx3-xx5) + cc6/(xx3-xx6));

      h->h3_term[3].c = cc4 + cc4 * (cc1/(xx4-xx1) + cc2/(xx4-xx2) + cc3/(xx4-xx3));
      h->h3_term[4].c = cc5 + cc5 * (cc1/(xx5-xx1) + cc2/(xx5-xx2) + cc3/(xx5-xx3));
      h->h3_term[5].c = cc6 + cc6 * (cc1/(xx6-xx1) + cc2/(xx6-xx2) + cc3/(xx6-xx3));
   }
      
   return(1);
}

static int update_h1C_c(h)
   TXLine *h;
{
   int i;
   double d = 0;

   for (i = 0; i < 3; i++) {
      h->h1_term[i].c *= h->sqtCdL;
      d += h->h1_term[i].c;
   }
   h->h1C = d;

   for (i = 0; i < 3; i++) 
      h->h2_term[i].c *= h->h2_aten;
   
   for (i = 0; i < 6; i++) 
      h->h3_term[i].c *= h->h3_aten;

   return(1);
}
/****************************************************************
     y.c  :  Calculate the Pade Approximation of Y(s)
 ****************************************************************/


static double eval2(a, b, c, x)
   double a, b, c, x;
{
   return(a*x*x + b*x + c);
}

static double approx1(st)
   double st;
{
   double s3, s2, s1;

   s1 = st;
   s2 = s1 * s1;
   s3 = s2 * s1;

   return((s3 + q1*s2 + q2*s1 + q3) / (s3 + p1*s2 + p2*s1 + p3));
}


static double approx2(st)
   double st;
{
   return(1.0 + c1/(st - x1) + c2/(st - x2) + c3/(st - x3));
}

static void y_pade(R, L, G, C, h)
   double R, L, G, C;
   TXLine *h;
{

   double t;

   /* float RdL, GdC; */
   double RdL, GdC; 

   sqtCdL = sqrt((double) C / L);
   RdL = R / L;
   GdC = G / C;

   mac(GdC, RdL, &b1, &b2, &b3, &b4, &b5);

   A[0][0] = 1.0 - sqrt((double) (GdC / RdL));
   A[0][1] = b1;
   A[0][2] = b2;
   A[0][3] = -b3;

   A[1][0] = b1;
   A[1][1] = b2;
   A[1][2] = b3;
   A[1][3] = -b4;

   A[2][0] = b2;
   A[2][1] = b3;
   A[2][2] = b4;
   A[2][3] = -b5;

   Gaussian_Elimination1(3);

   p3 = A[0][3];
   p2 = A[1][3];
   p1 = A[2][3];

   q1 = p1 + b1;
   q2 = b1 * p1 + p2 + b2;
   q3 = p3 * sqrt((double) (GdC / RdL));

   find_roots(p1, p2, p3, &x1, &x2, &x3);
   c1 = eval2(q1 - p1, q2 - p2, q3 - p3, x1) / 
		   eval2((double) 3.0, (double) 2.0 * p1, p2, x1);
   c2 = eval2(q1 - p1, q2 - p2, q3 - p3, x2) / 
		   eval2((double) 3.0, (double) 2.0 * p1, p2, x2);
   c3 = eval2(q1 - p1, q2 - p2, q3 - p3, x3) / 
		   eval2((double) 3.0, (double) 2.0 * p1, p2, x3);

   h->sqtCdL = sqtCdL;
   h->h1_term[0].c = c1;
   h->h1_term[1].c = c2;
   h->h1_term[2].c = c3;
   h->h1_term[0].x = x1;
   h->h1_term[1].x = x2;
   h->h1_term[2].x = x3;

}

static int Gaussian_Elimination1(dims)
   int dims;
{
   register int i, j, k, dim;
   register double f;
   int imax;
   double max;

   dim = dims;

   for (i = 0; i < dim; i++) {
      imax = i;
      max = ABS(A[i][i]);
      for (j = i+1; j < dim; j++)
         if (ABS(A[j][i]) > max) {
	    imax = j;
	    max = ABS(A[j][i]);
	 } 
      if (max < epsi) {
         fprintf(stderr, " can not choose a pivot \n");
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

      for (j = 0; j < dim ; j++) {
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

static double root3(a1, a2, a3, x)
   double x;
   double a1, a2, a3;
{
   double t1, t2;

   t1 = x*x*x + a1*x*x + a2*x + a3;
   t2 = 3.0*x*x + 2.0*a1*x + a2;

   return(x - t1 / t2);
}

static int div3(a1, a2, a3, x, p1, p2)
   double x;
   double a1, a2, a3;
   double *p1, *p2;
{
   *p1 = a1 + x;
   *p2 = - a3 / x;

   return(1);
}


/****************************************************************
         Calculate the Maclaurin series of F(z)

   F(z) = sqrt((1+az) / (1+bz))
	= 1 + b1 z + b2 z^2 + b3 z^3 + b4 z^4 + b5 z^5 
 ****************************************************************/

static double f3(a, b, z)
   double a, b, z;
{
   double t4, t3, t2, t1;
   double t14, t13, t12, t11;
   double sqt11;

   t1 = 1 / (1.0 + b * z);
   t2 = t1 * t1;
   t3 = t2 * t1;
   t4 = t3 * t1;

   t11 = (1.0 + a * z) * t1;
   t12 = (1.0 + a * z) * t2;
   t13 = (1.0 + a * z) * t3;
   t14 = (1.0 + a * z) * t4;

   sqt11 = sqrt(t11);


   return(
     -0.5 * (-2.0*a*b*t2 + 2.0*b*b*t13) * (a*t1 - b*t12) / (t11*sqt11)
     +3.0/8.0 * (a*t1-b*t12)*(a*t1-b*t12)*(a*t1-b*t12) / (t11*t11*sqt11)
     +0.5 * (4.0*a*b*b*t3 + 2.0*a*b*b*t3 - 6.0*b*b*b*t14) / sqt11
     -0.25 * (-2.0*a*b*t2 + 2.0*b*b*t13) * (a*t1-b*(1.0+a*z)) / 
     (t11*sqt11)
     );
}

static double f2(a, b, z)
   double a, b, z;
{
   double t3, t2, t1;
   double t13, t12, t11;
   double sqt11;

   t1 = 1 / (1.0 + b * z);
   t2 = t1 * t1;
   t3 = t2 * t1;

   t11 = (1.0 + a * z) * t1;
   t12 = (1.0 + a * z) * t2;
   t13 = (1.0 + a * z) * t3;

   sqt11 = sqrt(t11);

   return(
     -0.25 * (a*t1-b*t12) * (a*t1-b*t12) / (t11*sqt11)
     +0.5 * (-2.0*a*b*t2 + 2.0*b*b*t13) / sqt11
   );
}   

static int mac(at, bt, b1, b2, b3, b4, b5)
   /* float at, bt; */
   double at, bt;
   double *b1, *b2, *b3, *b4, *b5;
{
   double a, b;
   double y1, y2, y3, y4, y5;

   a = at;
   b = bt;

   y1 = *b1 = 0.5 * (a - b);
   y2 = 0.5 * (3.0 * b * b - 2.0 * a * b - a * a) * y1 / (a - b);
   y3 = ((3.0 * b * b + a * a) * y1 * y1 + 0.5 * (3.0 * b * b 
	- 2.0 * a * b - a * a) * y2) / (a - b);
   y4 = ((3.0 * b * b - 3.0 * a * a) * y1 * y1 * y1 + (9.0 * b * b
	+ 3.0 * a * a) * y1 * y2 + 0.5 * (3.0 * b * b - 2.0 * a * b
	- a * a) * y3) / (a - b);
   y5 = (12.0 * a * a * y1 * y1 * y1 * y1 + y1 * y1 * y2 * (
	 18.0 * b * b - 18.0 * a * a) + (9.0 * b * b + 3.0 * a * a) *
	 (y2 * y2 + y1 * y3) + (3.0 * b * b + a * a) * y1 * y3 +
	 0.5 * (3.0 * b * b - 2.0 * a * b - a * a) * y4) / (a - b);

   *b2 = y2 / 2.0;
   *b3 = y3 / 6.0;
   *b4 = y4 / 24.0;
   *b5 = y5 / 120.0;

   return(1);
}


/****************************************************
 exp.c
 ****************************************************/

static double exp_approx1(st)
   double st;
{
   double s3, s2, s1;

   s1 = st;
   s2 = s1 * s1;
   s3 = s2 * s1;

   return(exp((double) - st * tau - a0) * 
	(s3 + eq1*s2 + eq2*s1 + eq3) / (s3 + ep1*s2 + ep2*s1 + ep3));
}

static int get_c(eq1, eq2, eq3, ep1, ep2, a, b, cr, ci)
   double eq1, eq2, eq3, ep1, ep2, a, b;
   double *cr, *ci;
{
   double d, n;

   d = (3.0*(a*a-b*b)+2.0*ep1*a+ep2)*(3.0*(a*a-b*b)+2.0*ep1*a+ep2);
   d += (6.0*a*b+2.0*ep1*b)*(6.0*a*b+2.0*ep1*b);
   n = -(eq1*(a*a-b*b)+eq2*a+eq3)*(6.0*a*b+2.0*ep1*b);
   n += (2.0*eq1*a*b+eq2*b)*(3.0*(a*a-b*b)+2.0*ep1*a+ep2);
   *ci = n/d;
   n = (3.0*(a*a-b*b)+2.0*ep1*a+ep2)*(eq1*(a*a-b*b)+eq2*a+eq3);
   n += (6.0*a*b+2.0*ep1*b)*(2.0*eq1*a*b+eq2*b);
   *cr = n/d;

   return(1);
}

static double exp_approx2(st)
   double st;
{
   if (ifImg) 
      return(1.0 + ec1/(st - ex1) + 2.0*(ec2*(st-ex2)-ec3*ex3) /
	 ((st-ex2)*(st-ex2) + ex3*ex3));
   else 
      return(1.0 + ec1/(st - ex1) + ec2/(st - ex2) + ec3/(st - ex3));
}

static int exp_pade(R, L, G, C, l, h)
   float R, L, G, C, l;
   TXLine *h;
{

   double t;

   tau = sqrt((double) L*C);
   RdL = R / L;
   GdC = G / C;
   RG  = R * G;
   RC = R * C;
   GL = G * L;

   {
      double a, b, t;
      double y1, y2, y3, y4, y5, y6;

      a = RdL;
      b = GdC;
      t = tau;

      /*
      y1 = 0.5 * (a + b);
      y2 = a * b - y1 * y1;
      y3 = - a * b * y1 - 2.0 * y1 * y2 + y1 * y1 * y1;
      y4 = 2.0 * a * b * y1 * y1 - a * b * y2 - 2.0 * y2 * y2
          - 2.0 * y1 * y3 + 5.0 * y1 * y1 * y2
          - 2.0 * y1 * y1 * y1 * y1;
      y5 = 6.0 * a * b * (y1 * y2 - y1 * y1 * y1) - a * b * y3
           - 2.0 * y1 * y4
           - 6.0 * y2 * y3 + 12.0 * y2 * y2 * y1 + 7.0 * y1 * y1 * y3
           -10.0 * y1 * y1 * y1 * y2 - 8.0 * y1 * y1 * y1 * y2
           + 6.0 * y1 * y1 * y1 * y1 * y1;
   y6 = 24.0 * a * b * y1 * y1 * y1 * y1 - 36.0 * a * b * y1 * y1 * y2
        + 6.0 * a * b * y2 * y2 + 8.0 * a * b * y1 * y3 - 2.0 * y2 * y4
        - 2.0 * y1 * y5 + 2.0 * y1 * y1 * y4 - a * b * y4 -6.0 * y3 * y3
        + 44.0 * y1 * y2 * y3 + 60.0 * y1 * y1 * y1 * y1 * y2
	-24.0 * y1 * y1 * y1 * y1 * y1 * y1 + 12.0 * y2 * y2 * y2
	-54.0 * y1 * y1 * y2 * y2 + 7.0 * y1 * y1 * y4
	-24.0 * y1 * y1 * y1 * y3 - 24.0 * y1 * y1 * y2 * y2
	-8.0 * y1 * y1 * y1 * y3 + 24.0 * y1 * y1 * y1 * y1 * y2
	- 6.0 * y2 * y4;
	*/

       y1 = 0.5 * (a + b);
       y2 = a * b - y1 * y1;
       y3 = -3.0 * y1 * y2;
       y4 = -3.0 * y2 * y2 - 4.0 * y1 * y3;
       y5 = - 5.0 * y1 * y4 -10.0 * y2 * y3;
       y6 = -10.0 * y3 * y3 - 15.0 * y2 * y4 - 6.0 * y1 * y5;

       a0 = y1 * t;
       a1 = y2 * t * t / 2.0;
       a2 = y3 * t * t * t / 6.0;
       a3 = y4 * t * t * t * t / 24.0;
       a4 = y5 * t * t * t * t * t / 120.0;
       a5 = y6 * t * t * t * t * t * t / 720.0;

   }

   a0 *= l;
   a1 *= l;
   a2 *= l;
   a3 *= l;
   a4 *= l;
   a5 *= l;

   pade(l);

      h->taul = tau * l;
      h->h2_aten = exp(- a0);
      h->h2_term[0].c = ec1;
      h->h2_term[1].c = ec2;
      h->h2_term[2].c = ec3;
      h->h2_term[0].x = ex1;
      h->h2_term[1].x = ex2;
      h->h2_term[2].x = ex3;

   return(ifImg);
}

static int pade(l)
   float l;
{
   int i, j;
   double a[6];
   double b[6];

   a[1] = -a1;
   a[2] = -a2;
   a[3] = -a3;
   a[4] = -a4;
   a[5] = -a5;
   
   b[0] = 1.0;
   b[1] = a[1];
   for (i = 2; i <= 5; i++) {
      b[i] = 0.0;
      for (j = 1; j <= i; j++)
	 b[i] += j * a[j] * b[i-j];
      b[i] = b[i] / (double) i;
   }

   AA[0][0] = 1.0 - exp((double) a0 - l * sqrt(RG));
   AA[0][1] = b[1];
   AA[0][2] = b[2];
   AA[0][3] = -b[3];

   AA[1][0] = b[1];
   AA[1][1] = b[2];
   AA[1][2] = b[3];
   AA[1][3] = -b[4];

   AA[2][0] = b[2];
   AA[2][1] = b[3];
   AA[2][2] = b[4];
   AA[2][3] = -b[5];

   Gaussian_Elimination2(3);

   ep3 = AA[0][3];
   ep2 = AA[1][3];
   ep1 = AA[2][3];

   eq1 = ep1 + b[1];
   eq2 = b[1] * ep1 + ep2 + b[2];
   eq3 = ep3 * exp((double) a0 - l * sqrt(RG));

   ep3 = ep3 / (tau*tau*tau);
   ep2 = ep2 / (tau*tau);
   ep1 = ep1 / tau;
   eq3 = eq3 / (tau*tau*tau);
   eq2 = eq2 / (tau*tau);
   eq1 = eq1 / tau;
    /*
   printf("factor = %e\n", exp(-a0));
   printf("ep1 = %e ep2 = %e ep3 = %e\n", ep1, ep2, ep3);
     */
   exp_find_roots(ep1, ep2, ep3, &ex1, &ex2, &ex3);
    /*
   printf("roots are %e %e %e \n", ex1, ex2, ex3);
     */
   ec1 = eval2(eq1 - ep1, eq2 - ep2, eq3 - ep3, ex1) / 
		   eval2((double) 3.0, (double) 2.0 * ep1, ep2, ex1);
   if (ifImg) 
      get_c(eq1 - ep1, eq2 - ep2, eq3 - ep3, ep1, ep2, ex2, ex3, &ec2, &ec3);
   else {
      ec2 = eval2(eq1 - ep1, eq2 - ep2, eq3 - ep3, ex2) / 
		   eval2((double) 3.0, (double) 2.0 * ep1, ep2, ex2);
      ec3 = eval2(eq1 - ep1, eq2 - ep2, eq3 - ep3, ex3) / 
		   eval2((double) 3.0, (double) 2.0 * ep1, ep2, ex3);
   }
}

static int Gaussian_Elimination2(dims)
   int dims;
{
   register int i, j, k, dim;
   register double f;
   double max;
   int imax;

   dim = dims;

   for (i = 0; i < dim; i++) {
      imax = i;
      max = ABS(AA[i][i]);
      for (j = i+1; j < dim; j++)
         if (ABS(AA[j][i]) > max) {
            imax = j;
            max = ABS(AA[j][i]);
         }
      if (max < epsi2) {
         fprintf(stderr, " can not choose a pivot \n");
         exit(0);
      }
      if (imax != i)
	 for (k = i; k <= dim; k++) {
	    f = AA[i][k];
	    AA[i][k] = AA[imax][k];
	    AA[imax][k] = f;
	 }
      
      f = 1.0 / AA[i][i];
      AA[i][i] = 1.0;

      for (j = i+1; j <= dim; j++)
	 AA[i][j] *= f;

      for (j = 0; j < dim ; j++) {
	 if (i == j)
	    continue;
	 f = AA[j][i];
	 AA[j][i] = 0.0;
	 for (k = i+1; k <= dim; k++)
	    AA[j][k] -= f * AA[i][k];
      }
   }
   return(1);
}

static int exp_div3(a1, a2, a3, x, p1, p2)
   double x;
   double a1, a2, a3;
   double *p1, *p2;
   {
   *p1 = a1 + x;
   *p2 = - a3 / x;

   return(1);
}

/***
 ***/

static int exp_find_roots(a1, a2, a3, ex1, ex2, ex3)
   double a1, a2, a3;
   double *ex1, *ex2, *ex3;
{
   double x, t;
   double p, q;

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
   {
      double ex1;
      int i = 0;
      ex1 = x;
      for (t = root3(a1, a2, a3, x); ABS(t-x) > 5.0e-4;
           t = root3(a1, a2, a3, x))
	 if (++i == 32) {
            x = ex1;
            break;
         } else
            x = t;
   }
   /***
   x = a1;
   for (t = root3(a1, a2, a3, x); ABS(t-x) > epsi2; 
			    t = root3(a1, a2, a3, x)) {
      x = t;
      i++;
      if (i > 1000) {
         x = 0.5 * (x + root3(a1, a2, a3, x));
         j++;
         if (j == 3)
            break;
         i = 0;
      }
   }
    ***/
   *ex1 = x;
   div3(a1, a2, a3, x, &a1, &a2);

   t = a1 * a1 - 4.0 * a2;
   if (t < 0) {
      ifImg = 1;
      printf("***** Two Imaginary Roots.\n");
      *ex3 = 0.5 * sqrt(-t);
      *ex2 = -0.5 * a1;
   } else {
      ifImg = 0;
      t *= 1.0e-16;
      t = sqrt(t)*1.0e8;
      if (a1 >= 0.0)
         *ex2 = t = -0.5 * (a1 + t);
      else
         *ex2 = t = -0.5 * (a1 - t);
      *ex3 = a2 / t;
      /*
      *ex2 = 0.5 * (-a1 + t);
      *ex3 = 0.5 * (-a1 - t);
       */
   }

   return(1);
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


static NODE 
*insert_node(name)
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

static NODE
*NEW_node()
{
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
   n->CL = 0.0;
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

static int find_roots(a1, a2, a3, x1, x2, x3)
   double a1, a2, a3;
   double *x1, *x2, *x3;
{
   double x, t;
   double p, q;

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
   x = a1;
   i = 0;
   j = 0;
   for (t = root3(a1, a2, a3, x); ABS(t-x) > epsi; 
			    t = root3(a1, a2, a3, x)) {
      x = t;
      i++;
      if (i > 1000) {
	 x = 0.5 * (x + root3(a1, a2, a3, x));
	 j++;
	 if (j == 3)
	    break;
	 i = 0;
      }
   }
    */

   *x1 = x;
   div3(a1, a2, a3, x, &a1, &a2);

   t = a1 * a1 - 4.0 * a2;
   if (t < 0) {
      printf("***** Two Imaginary Roots in Characteristic Admittance.\n");
      exit(0);
   }

   t *= 1.0e-18;
   t = sqrt(t) * 1.0e9;
   if (a1 >= 0.0)
      *x2 = t = -0.5 * (a1 + t);
   else
      *x2 = t = -0.5 * (a1 - t);
   *x3 = a2 / t;
   /*
   *x2 = 0.5 * (-a1 + t);
   *x3 = 0.5 * (-a1 - t);
    */
   return(1);
}

