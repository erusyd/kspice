/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Hong J. Park, Thomas L. Quarles
**********/
/*
 */

#include "spice.h"
#include <stdio.h>
#include <math.h>
#include "util.h"
#include "cktdefs.h"
#include "bsim1def.h"
#include "trandefs.h"
#include "const.h"
#include "devdefs.h"
#include "sperror.h"
#include "suffix.h"


int
BSIM1convTest(inModel,ckt)

    GENmodel *inModel;
    register CKTcircuit *ckt;

        /* actually load the current value into the 
         * sparse matrix previously provided 
         */
{
    register BSIM1model *model = (BSIM1model*)inModel;
    register BSIM1instance *here;
    double cbd;
    double cbhat;
    double cbs;
    double cd;
    double cdhat;
    double delvbd;
    double delvbs;
    double delvds;
    double delvgd;
    double delvgs;
    double tol;
    double vbd;
    double vbs;
    double vds;
    double vgd;
    double vgdo;
    double vgs;


    /*  loop through all the BSIM1 device models */
    for( ; model != NULL; model = model->BSIM1nextModel ) {

        /* loop through all the instances of the model */
        for (here = model->BSIM1instances; here != NULL ;
                here=here->BSIM1nextInstance) {

            vbs = model->BSIM1type * ( 
                *(ckt->CKTrhsOld+here->BSIM1bNode) -
                *(ckt->CKTrhsOld+here->BSIM1sNodePrime));
            vgs = model->BSIM1type * ( 
                *(ckt->CKTrhsOld+here->BSIM1gNode) -
                *(ckt->CKTrhsOld+here->BSIM1sNodePrime));
            vds = model->BSIM1type * ( 
                *(ckt->CKTrhsOld+here->BSIM1dNodePrime) -
                *(ckt->CKTrhsOld+here->BSIM1sNodePrime));
            vbd=vbs-vds;
            vgd=vgs-vds;
            vgdo = *(ckt->CKTstate0 + here->BSIM1vgs) - 
                *(ckt->CKTstate0 + here->BSIM1vds);
            delvbs = vbs - *(ckt->CKTstate0 + here->BSIM1vbs);
            delvbd = vbd - *(ckt->CKTstate0 + here->BSIM1vbd);
            delvgs = vgs - *(ckt->CKTstate0 + here->BSIM1vgs);
            delvds = vds - *(ckt->CKTstate0 + here->BSIM1vds);
            delvgd = vgd-vgdo;

            if (here->BSIM1mode >= 0) {
                cdhat=
                    *(ckt->CKTstate0 + here->BSIM1cd) -
                    *(ckt->CKTstate0 + here->BSIM1gbd) * delvbd +
                    *(ckt->CKTstate0 + here->BSIM1gmbs) * delvbs +
                    *(ckt->CKTstate0 + here->BSIM1gm) * delvgs + 
                    *(ckt->CKTstate0 + here->BSIM1gds) * delvds ;
            } else {
                cdhat=
                    *(ckt->CKTstate0 + here->BSIM1cd) -
                    ( *(ckt->CKTstate0 + here->BSIM1gbd) -
                      *(ckt->CKTstate0 + here->BSIM1gmbs)) * delvbd -
                    *(ckt->CKTstate0 + here->BSIM1gm) * delvgd +
                    *(ckt->CKTstate0 + here->BSIM1gds) * delvds;
            }
            cbhat=
                *(ckt->CKTstate0 + here->BSIM1cbs) +
                *(ckt->CKTstate0 + here->BSIM1cbd) +
                *(ckt->CKTstate0 + here->BSIM1gbd) * delvbd +
                *(ckt->CKTstate0 + here->BSIM1gbs) * delvbs ;

            cd = *(ckt->CKTstate0 + here->BSIM1cd);
            cbs = *(ckt->CKTstate0 + here->BSIM1cbs);
            cbd = *(ckt->CKTstate0 + here->BSIM1cbd);
            /*
             *  check convergence
             */
            if ( (here->BSIM1off == 0)  || (!(ckt->CKTmode & MODEINITFIX)) ){
                tol=ckt->CKTreltol*MAX(FABS(cdhat),FABS(cd))+ckt->CKTabstol;
                if (FABS(cdhat-cd) >= tol) { 
                    ckt->CKTnoncon++;
                    return(OK);
                } 
                tol=ckt->CKTreltol*MAX(FABS(cbhat),FABS(cbs+cbd))+
                    ckt->CKTabstol;
                if (FABS(cbhat-(cbs+cbd)) > tol) {
                    ckt->CKTnoncon++;
                    return(OK);
                }
            }
        }
    }
    return(OK);
}

