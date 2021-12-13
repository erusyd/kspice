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
#include "bsim2def.h"
#include "trandefs.h"
#include "const.h"
#include "devdefs.h"
#include "sperror.h"
#include "suffix.h"


int
BSIM2convTest(inModel,ckt)

    GENmodel *inModel;
    register CKTcircuit *ckt;

        /* actually load the current value into the 
         * sparse matrix previously provided 
         */
{
    register BSIM2model *model = (BSIM2model*)inModel;
    register BSIM2instance *here;
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


    /*  loop through all the BSIM2 device models */
    for( ; model != NULL; model = model->BSIM2nextModel ) {

        /* loop through all the instances of the model */
        for (here = model->BSIM2instances; here != NULL ;
                here=here->BSIM2nextInstance) {

            vbs = model->BSIM2type * ( 
                *(ckt->CKTrhsOld+here->BSIM2bNode) -
                *(ckt->CKTrhsOld+here->BSIM2sNodePrime));
            vgs = model->BSIM2type * ( 
                *(ckt->CKTrhsOld+here->BSIM2gNode) -
                *(ckt->CKTrhsOld+here->BSIM2sNodePrime));
            vds = model->BSIM2type * ( 
                *(ckt->CKTrhsOld+here->BSIM2dNodePrime) -
                *(ckt->CKTrhsOld+here->BSIM2sNodePrime));
            vbd=vbs-vds;
            vgd=vgs-vds;
            vgdo = *(ckt->CKTstate0 + here->BSIM2vgs) - 
                *(ckt->CKTstate0 + here->BSIM2vds);
            delvbs = vbs - *(ckt->CKTstate0 + here->BSIM2vbs);
            delvbd = vbd - *(ckt->CKTstate0 + here->BSIM2vbd);
            delvgs = vgs - *(ckt->CKTstate0 + here->BSIM2vgs);
            delvds = vds - *(ckt->CKTstate0 + here->BSIM2vds);
            delvgd = vgd-vgdo;

            if (here->BSIM2mode >= 0) {
                cdhat=
                    *(ckt->CKTstate0 + here->BSIM2cd) -
                    *(ckt->CKTstate0 + here->BSIM2gbd) * delvbd +
                    *(ckt->CKTstate0 + here->BSIM2gmbs) * delvbs +
                    *(ckt->CKTstate0 + here->BSIM2gm) * delvgs + 
                    *(ckt->CKTstate0 + here->BSIM2gds) * delvds ;
            } else {
                cdhat=
                    *(ckt->CKTstate0 + here->BSIM2cd) -
                    ( *(ckt->CKTstate0 + here->BSIM2gbd) -
                      *(ckt->CKTstate0 + here->BSIM2gmbs)) * delvbd -
                    *(ckt->CKTstate0 + here->BSIM2gm) * delvgd +
                    *(ckt->CKTstate0 + here->BSIM2gds) * delvds;
            }
            cbhat=
                *(ckt->CKTstate0 + here->BSIM2cbs) +
                *(ckt->CKTstate0 + here->BSIM2cbd) +
                *(ckt->CKTstate0 + here->BSIM2gbd) * delvbd +
                *(ckt->CKTstate0 + here->BSIM2gbs) * delvbs ;

            cd = *(ckt->CKTstate0 + here->BSIM2cd);
            cbs = *(ckt->CKTstate0 + here->BSIM2cbs);
            cbd = *(ckt->CKTstate0 + here->BSIM2cbd);
            /*
             *  check convergence
             */
            if ( (here->BSIM2off == 0)  || (!(ckt->CKTmode & MODEINITFIX)) ){
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

