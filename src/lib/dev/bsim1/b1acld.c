/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Hong J. Park, Thomas L. Quarles
**********/
/*
 */

#include "spice.h"
#include <stdio.h>
#include "cktdefs.h"
#include "bsim1def.h"
#include "sperror.h"
#include "suffix.h"


int
BSIM1acLoad(inModel,ckt)
    GENmodel *inModel;
    register CKTcircuit *ckt;
{
    register BSIM1model *model = (BSIM1model*)inModel;
    register BSIM1instance *here;
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
    for( ; model != NULL; model = model->BSIM1nextModel) {
        for(here = model->BSIM1instances; here!= NULL;
                here = here->BSIM1nextInstance) {
        
            if (here->BSIM1mode >= 0) {
                xnrm=1;
                xrev=0;
            } else {
                xnrm=0;
                xrev=1;
            }
            gdpr=here->BSIM1drainConductance;
            gspr=here->BSIM1sourceConductance;
            gm= *(ckt->CKTstate0 + here->BSIM1gm);
            gds= *(ckt->CKTstate0 + here->BSIM1gds);
            gmbs= *(ckt->CKTstate0 + here->BSIM1gmbs);
            gbd= *(ckt->CKTstate0 + here->BSIM1gbd);
            gbs= *(ckt->CKTstate0 + here->BSIM1gbs);
            capbd= *(ckt->CKTstate0 + here->BSIM1capbd);
            capbs= *(ckt->CKTstate0 + here->BSIM1capbs);
            /*
             *    charge oriented model parameters
             */

            cggb = *(ckt->CKTstate0 + here->BSIM1cggb);
            cgsb = *(ckt->CKTstate0 + here->BSIM1cgsb);
            cgdb = *(ckt->CKTstate0 + here->BSIM1cgdb);

            cbgb = *(ckt->CKTstate0 + here->BSIM1cbgb);
            cbsb = *(ckt->CKTstate0 + here->BSIM1cbsb);
            cbdb = *(ckt->CKTstate0 + here->BSIM1cbdb);

            cdgb = *(ckt->CKTstate0 + here->BSIM1cdgb);
            cdsb = *(ckt->CKTstate0 + here->BSIM1cdsb);
            cddb = *(ckt->CKTstate0 + here->BSIM1cddb);

            xcdgb = (cdgb - here->BSIM1GDoverlapCap) * omega;
            xcddb = (cddb + capbd + here->BSIM1GDoverlapCap) * omega;
            xcdsb = cdsb * omega;
            xcsgb = -(cggb + cbgb + cdgb + here->BSIM1GSoverlapCap ) * omega;
            xcsdb = -(cgdb + cbdb + cddb) * omega;
            xcssb = (capbs + here->BSIM1GSoverlapCap - (cgsb+cbsb+cdsb)) * omega;
            xcggb = (cggb + here->BSIM1GDoverlapCap + here->BSIM1GSoverlapCap + 
                    here->BSIM1GBoverlapCap) * omega;
            xcgdb = (cgdb - here->BSIM1GDoverlapCap ) * omega;
            xcgsb = (cgsb - here->BSIM1GSoverlapCap) * omega;
            xcbgb = (cbgb - here->BSIM1GBoverlapCap) * omega;
            xcbdb = (cbdb - capbd ) * omega;
            xcbsb = (cbsb - capbs ) * omega;


            *(here->BSIM1GgPtr +1) += xcggb;
            *(here->BSIM1BbPtr +1) += -xcbgb-xcbdb-xcbsb;
            *(here->BSIM1DPdpPtr +1) += xcddb;
            *(here->BSIM1SPspPtr +1) += xcssb;
            *(here->BSIM1GbPtr +1) += -xcggb-xcgdb-xcgsb;
            *(here->BSIM1GdpPtr +1) += xcgdb;
            *(here->BSIM1GspPtr +1) += xcgsb;
            *(here->BSIM1BgPtr +1) += xcbgb;
            *(here->BSIM1BdpPtr +1) += xcbdb;
            *(here->BSIM1BspPtr +1) += xcbsb;
            *(here->BSIM1DPgPtr +1) += xcdgb;
            *(here->BSIM1DPbPtr +1) += -xcdgb-xcddb-xcdsb;
            *(here->BSIM1DPspPtr +1) += xcdsb;
            *(here->BSIM1SPgPtr +1) += xcsgb;
            *(here->BSIM1SPbPtr +1) += -xcsgb-xcsdb-xcssb;
            *(here->BSIM1SPdpPtr +1) += xcsdb;
            *(here->BSIM1DdPtr) += gdpr;
            *(here->BSIM1SsPtr) += gspr;
            *(here->BSIM1BbPtr) += gbd+gbs;
            *(here->BSIM1DPdpPtr) += gdpr+gds+gbd+xrev*(gm+gmbs);
            *(here->BSIM1SPspPtr) += gspr+gds+gbs+xnrm*(gm+gmbs);
            *(here->BSIM1DdpPtr) -= gdpr;
            *(here->BSIM1SspPtr) -= gspr;
            *(here->BSIM1BdpPtr) -= gbd;
            *(here->BSIM1BspPtr) -= gbs;
            *(here->BSIM1DPdPtr) -= gdpr;
            *(here->BSIM1DPgPtr) += (xnrm-xrev)*gm;
            *(here->BSIM1DPbPtr) += -gbd+(xnrm-xrev)*gmbs;
            *(here->BSIM1DPspPtr) += -gds-xnrm*(gm+gmbs);
            *(here->BSIM1SPgPtr) += -(xnrm-xrev)*gm;
            *(here->BSIM1SPsPtr) -= gspr;
            *(here->BSIM1SPbPtr) += -gbs-(xnrm-xrev)*gmbs;
            *(here->BSIM1SPdpPtr) += -gds-xrev*(gm+gmbs);

        }
    }
return(OK);
}


