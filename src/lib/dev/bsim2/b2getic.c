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
BSIM2getic(inModel,ckt)
    GENmodel *inModel;
    CKTcircuit *ckt;

{

    BSIM2model *model = (BSIM2model*)inModel;
    BSIM2instance *here;
    /*
     * grab initial conditions out of rhs array.   User specified, so use
     * external nodes to get values
     */

    for( ; model ; model = model->BSIM2nextModel) {
        for(here = model->BSIM2instances; here ; here = here->BSIM2nextInstance) {
            if(!here->BSIM2icVBSGiven) {
                here->BSIM2icVBS = 
                        *(ckt->CKTrhs + here->BSIM2bNode) - 
                        *(ckt->CKTrhs + here->BSIM2sNode);
            }
            if(!here->BSIM2icVDSGiven) {
                here->BSIM2icVDS = 
                        *(ckt->CKTrhs + here->BSIM2dNode) - 
                        *(ckt->CKTrhs + here->BSIM2sNode);
            }
            if(!here->BSIM2icVGSGiven) {
                here->BSIM2icVGS = 
                        *(ckt->CKTrhs + here->BSIM2gNode) - 
                        *(ckt->CKTrhs + here->BSIM2sNode);
            }
        }
    }
    return(OK);
}

