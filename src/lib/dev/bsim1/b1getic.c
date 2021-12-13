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
BSIM1getic(inModel,ckt)
    GENmodel *inModel;
    CKTcircuit *ckt;

{

    BSIM1model *model = (BSIM1model*)inModel;
    BSIM1instance *here;
    /*
     * grab initial conditions out of rhs array.   User specified, so use
     * external nodes to get values
     */

    for( ; model ; model = model->BSIM1nextModel) {
        for(here = model->BSIM1instances; here ; here = here->BSIM1nextInstance) {
            if(!here->BSIM1icVBSGiven) {
                here->BSIM1icVBS = 
                        *(ckt->CKTrhs + here->BSIM1bNode) - 
                        *(ckt->CKTrhs + here->BSIM1sNode);
            }
            if(!here->BSIM1icVDSGiven) {
                here->BSIM1icVDS = 
                        *(ckt->CKTrhs + here->BSIM1dNode) - 
                        *(ckt->CKTrhs + here->BSIM1sNode);
            }
            if(!here->BSIM1icVGSGiven) {
                here->BSIM1icVGS = 
                        *(ckt->CKTrhs + here->BSIM1gNode) - 
                        *(ckt->CKTrhs + here->BSIM1sNode);
            }
        }
    }
    return(OK);
}
