/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/
/*
 */

#include "spice.h"
#include <stdio.h>
#include "cktdefs.h"
#include "complex.h"
#include "sperror.h"
#include "bsim1def.h"
#include "suffix.h"


int
BSIM1pzLoad(inModel,ckt,s)
    GENmodel *inModel;
    register CKTcircuit *ckt;
    register SPcomplex *s;
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

            xcdgb = (cdgb - here->BSIM1GDoverlapCap) ;
            xcddb = (cddb + capbd + here->BSIM1GDoverlapCap) ;
            xcdsb = cdsb ;
            xcsgb = -(cggb + cbgb + cdgb + here->BSIM1GSoverlapCap ) ;
            xcsdb = -(cgdb + cbdb + cddb) ;
            xcssb = (capbs + here->BSIM1GSoverlapCap - (cgsb+cbsb+cdsb)) ;
            xcggb = (cggb + here->BSIM1GDoverlapCap + here->BSIM1GSoverlapCap + 
                    here->BSIM1GBoverlapCap) ;
            xcgdb = (cgdb - here->BSIM1GDoverlapCap ) ;
            xcgsb = (cgsb - here->BSIM1GSoverlapCap) ;
            xcbgb = (cbgb - here->BSIM1GBoverlapCap) ;
            xcbdb = (cbdb - capbd ) ;
            xcbsb = (cbsb - capbs ) ;


            *(here->BSIM1GgPtr   ) += xcggb * s->real;
            *(here->BSIM1GgPtr +1) += xcggb * s->imag;
            *(here->BSIM1BbPtr   ) += (-xcbgb-xcbdb-xcbsb) * s->real;
            *(here->BSIM1BbPtr +1) += (-xcbgb-xcbdb-xcbsb) * s->imag;
            *(here->BSIM1DPdpPtr   ) += xcddb * s->real;
            *(here->BSIM1DPdpPtr +1) += xcddb * s->imag;
            *(here->BSIM1SPspPtr   ) += xcssb * s->real;
            *(here->BSIM1SPspPtr +1) += xcssb * s->imag;
            *(here->BSIM1GbPtr   ) += (-xcggb-xcgdb-xcgsb) * s->real;
            *(here->BSIM1GbPtr +1) += (-xcggb-xcgdb-xcgsb) * s->imag;
            *(here->BSIM1GdpPtr   ) += xcgdb * s->real;
            *(here->BSIM1GdpPtr +1) += xcgdb * s->imag;
            *(here->BSIM1GspPtr   ) += xcgsb * s->real;
            *(here->BSIM1GspPtr +1) += xcgsb * s->imag;
            *(here->BSIM1BgPtr   ) += xcbgb * s->real;
            *(here->BSIM1BgPtr +1) += xcbgb * s->imag;
            *(here->BSIM1BdpPtr   ) += xcbdb * s->real;
            *(here->BSIM1BdpPtr +1) += xcbdb * s->imag;
            *(here->BSIM1BspPtr   ) += xcbsb * s->real;
            *(here->BSIM1BspPtr +1) += xcbsb * s->imag;
            *(here->BSIM1DPgPtr   ) += xcdgb * s->real;
            *(here->BSIM1DPgPtr +1) += xcdgb * s->imag;
            *(here->BSIM1DPbPtr   ) += (-xcdgb-xcddb-xcdsb) * s->real;
            *(here->BSIM1DPbPtr +1) += (-xcdgb-xcddb-xcdsb) * s->imag;
            *(here->BSIM1DPspPtr   ) += xcdsb * s->real;
            *(here->BSIM1DPspPtr +1) += xcdsb * s->imag;
            *(here->BSIM1SPgPtr   ) += xcsgb * s->real;
            *(here->BSIM1SPgPtr +1) += xcsgb * s->imag;
            *(here->BSIM1SPbPtr   ) += (-xcsgb-xcsdb-xcssb) * s->real;
            *(here->BSIM1SPbPtr +1) += (-xcsgb-xcsdb-xcssb) * s->imag;
            *(here->BSIM1SPdpPtr   ) += xcsdb * s->real;
            *(here->BSIM1SPdpPtr +1) += xcsdb * s->imag;
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
