/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Hong J. Park, Thomas L. Quarles
**********/
/*
 */

#include "spice.h"
#include <stdio.h>
#include "util.h"
#include "bsim1def.h"
#include "sperror.h"
#include "gendefs.h"
#include "suffix.h"


int
BSIM1delete(inModel,name,inInst)
    GENmodel *inModel;
    IFuid name;
    GENinstance **inInst;

{

    BSIM1instance **fast = (BSIM1instance**)inInst;
    BSIM1model *model = (BSIM1model*)inModel;
    BSIM1instance **prev = NULL;
    BSIM1instance *here;

    for( ; model ; model = model->BSIM1nextModel) {
        prev = &(model->BSIM1instances);
        for(here = *prev; here ; here = *prev) {
            if(here->BSIM1name == name || (fast && here==*fast) ) {
                *prev= here->BSIM1nextInstance;
                FREE(here);
                return(OK);
            }
            prev = &(here->BSIM1nextInstance);
        }
    }
    return(E_NODEV);
}
