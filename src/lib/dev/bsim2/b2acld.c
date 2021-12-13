/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Hong J. Park, Thomas L. Quarles
**********/
/*
 */

#include "spice.h"
#include <stdio.h>
#include "cktdefs.h"
#include "bsim2def.h"
#include "sperror.h"
#include "suffix.h"


int
BSIM2acLoad(inModel,ckt)
    GENmodel *inModel;
    register CKTcircuit *ckt;
{
    register BSIM2model *model = (BSIM2model*)inModel;
    register BSIM2instance *here;
    int xnrm;
    int xrev;
    double gdpr;
    double gspr;
    double gm;
    double gds;
    double gmbs;
    double gbd;
    double gbs;
    double capbd;
    double capbs;
    double xcggb;
    double xcgdb;
    double xcgsb;
    double xcbgb;
    double xcbdb;
    double xcbsb;
    double xcddb;
    double xcssb;
    double xcdgb;
    double xcsgb;
    double xcdsb;
    double xcsdb;
    double cggb;
    double cgdb;
    double cgsb;
    double cbgb;
    double cbdb;
    double cbsb;
    double cddb;
    double cdgb;
    double cdsb;
    double omega; /* angular fequency of the signal */

    omega = ckt->CKTomega;
    for( ; model != NULL; model = model->BSIM2nextModel) {
        for(here = model->BSIM2instances; here!= NULL;
                here = here->BSIM2nextInstance) {
        
            if (here->BSIM2mode >= 0) {
                xnrm=1;
                xrev=0;
            } else {
                xnrm=0;
                xrev=1;
            }
            gdpr=here->BSIM2drainConductance;
            gspr=here->BSIM2sourceConductance;
            gm= *(ckt->CKTstate0 + here->BSIM2gm);
            gds= *(ckt->CKTstate0 + here->BSIM2gds);
            gmbs= *(ckt->CKTstate0 + here->BSIM2gmbs);
            gbd= *(ckt->CKTstate0 + here->BSIM2gbd);
            gbs= *(ckt->CKTstate0 + here->BSIM2gbs);
            capbd= *(ckt->CKTstate0 + here->BSIM2capbd);
            capbs= *(ckt->CKTstate0 + here->BSIM2capbs);
            /*
             *    charge oriented model parameters
             */

            cggb = *(ckt->CKTstate0 + here->BSIM2cggb);
            cgsb = *(ckt->CKTstate0 + here->BSIM2cgsb);
            cgdb = *(ckt->CKTstate0 + here->BSIM2cgdb);

            cbgb = *(ckt->CKTstate0 + here->BSIM2cbgb);
            cbsb = *(ckt->CKTstate0 + here->BSIM2cbsb);
            cbdb = *(ckt->CKTstate0 + here->BSIM2cbdb);

            cdgb = *(ckt->CKTstate0 + here->BSIM2cdgb);
            cdsb = *(ckt->CKTstate0 + here->BSIM2cdsb);
            cddb = *(ckt->CKTstate0 + here->BSIM2cddb);

            xcdgb = (cdgb - here->pParam->BSIM2GDoverlapCap) * omega;
            xcddb = (cddb + capbd + here->pParam->BSIM2GDoverlapCap) * omega;
            xcdsb = cdsb * omega;
            xcsgb = -(cggb + cbgb + cdgb + here->pParam->BSIM2GSoverlapCap)
		  * omega;
            xcsdb = -(cgdb + cbdb + cddb) * omega;
            xcssb = (capbs + here->pParam->BSIM2GSoverlapCap
		  - (cgsb+cbsb+cdsb)) * omega;
            xcggb = (cggb + here->pParam->BSIM2GDoverlapCap 
		  + here->pParam->BSIM2GSoverlapCap
		  + here->pParam->BSIM2GBoverlapCap) * omega;
            xcgdb = (cgdb - here->pParam->BSIM2GDoverlapCap ) * omega;
            xcgsb = (cgsb - here->pParam->BSIM2GSoverlapCap) * omega;
            xcbgb = (cbgb - here->pParam->BSIM2GBoverlapCap) * omega;
            xcbdb = (cbdb - capbd ) * omega;
            xcbsb = (cbsb - capbs ) * omega;


            *(here->BSIM2GgPtr +1) += xcggb;
            *(here->BSIM2BbPtr +1) += -xcbgb-xcbdb-xcbsb;
            *(here->BSIM2DPdpPtr +1) += xcddb;
            *(here->BSIM2SPspPtr +1) += xcssb;
            *(here->BSIM2GbPtr +1) += -xcggb-xcgdb-xcgsb;
            *(here->BSIM2GdpPtr +1) += xcgdb;
            *(here->BSIM2GspPtr +1) += xcgsb;
            *(here->BSIM2BgPtr +1) += xcbgb;
            *(here->BSIM2BdpPtr +1) += xcbdb;
            *(here->BSIM2BspPtr +1) += xcbsb;
            *(here->BSIM2DPgPtr +1) += xcdgb;
            *(here->BSIM2DPbPtr +1) += -xcdgb-xcddb-xcdsb;
            *(here->BSIM2DPspPtr +1) += xcdsb;
            *(here->BSIM2SPgPtr +1) += xcsgb;
            *(here->BSIM2SPbPtr +1) += -xcsgb-xcsdb-xcssb;
            *(here->BSIM2SPdpPtr +1) += xcsdb;
            *(here->BSIM2DdPtr) += gdpr;
            *(here->BSIM2SsPtr) += gspr;
            *(here->BSIM2BbPtr) += gbd+gbs;
            *(here->BSIM2DPdpPtr) += gdpr+gds+gbd+xrev*(gm+gmbs);
            *(here->BSIM2SPspPtr) += gspr+gds+gbs+xnrm*(gm+gmbs);
            *(here->BSIM2DdpPtr) -= gdpr;
            *(here->BSIM2SspPtr) -= gspr;
            *(here->BSIM2BdpPtr) -= gbd;
            *(here->BSIM2BspPtr) -= gbs;
            *(here->BSIM2DPdPtr) -= gdpr;
            *(here->BSIM2DPgPtr) += (xnrm-xrev)*gm;
            *(here->BSIM2DPbPtr) += -gbd+(xnrm-xrev)*gmbs;
            *(here->BSIM2DPspPtr) += -gds-xnrm*(gm+gmbs);
            *(here->BSIM2SPgPtr) += -(xnrm-xrev)*gm;
            *(here->BSIM2SPsPtr) -= gspr;
            *(here->BSIM2SPbPtr) += -gbs-(xnrm-xrev)*gmbs;
            *(here->BSIM2SPdpPtr) += -gds-xrev*(gm+gmbs);

        }
    }
return(OK);
}



