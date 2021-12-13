/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1988 Kanwar Jit Singh
**********/
/*
 * singh@ic.Berkeley.edu
 */

#include "spice.h"
#include <stdio.h>
#include "misc.h"
#include "cktdefs.h"
#include "asrcdefs.h"
#include "sperror.h"
#include "util.h"
#include "suffix.h"


int
ASRCconvTest( inModel, ckt)
GENmodel *inModel;
CKTcircuit *ckt;
{
    register ASRCmodel *model = (ASRCmodel *)inModel;
    register ASRCinstance *here;
    int i, node_num, branch;
    double *vals, *derivs;
    double diff;
    double prev;
    double tol;
    double rhs;

    for( ; model != NULL; model = model->ASRCnextModel) {
        for( here = model->ASRCinstances; here != NULL;
                here = here->ASRCnextInstance) {
            vals = (double *)MALLOC((here->ASRCtree->numVars)*sizeof(double));
            derivs = (double *)MALLOC((here->ASRCtree->numVars)*sizeof(double));

            for( i=0; i < here->ASRCtree->numVars; i++){
                if( here->ASRCtree->varTypes[i] == IF_INSTANCE){
                     branch = CKTfndBranch(ckt,here->ASRCtree->vars[i].uValue);
                     vals[i] = *(ckt->CKTrhsOld+branch);
                } else {
                    node_num = ((CKTnode *)(here->ASRCtree->vars[i].nValue))
                            ->number;
                    vals[i] = *(ckt->CKTrhsOld+node_num);
                }
            }

            if( (*(here->ASRCtree->IFeval))(here->ASRCtree, ckt->CKTgmin, &rhs,
                    vals,derivs) == OK){

		tfree(vals);
		tfree(derivs);

                prev = here->ASRCprev_value;
                diff = FABS( prev - rhs);
                if ( here->ASRCtype == ASRC_VOLTAGE){
                    tol = ckt->CKTreltol * 
                            MAX(FABS(rhs),FABS(prev)) + ckt->CKTvoltTol;
                } else {
                    tol = ckt->CKTreltol * 
                            MAX(FABS(rhs),FABS(prev)) + ckt->CKTabstol;
                }

                if ( diff > tol) {
                    ckt->CKTnoncon++;
		    ckt->CKTtroubleElt = (GENinstance *) here;
                    return(OK);
                }
            } else {

		tfree(vals);
		tfree(derivs);

                return(E_BADPARM);
            }
        }
    }
    return(OK);
}
