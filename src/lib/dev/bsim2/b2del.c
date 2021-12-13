/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Hong J. Park, Thomas L. Quarles
**********/
/*
 */

#include "spice.h"
#include <stdio.h>
#include "util.h"
#include "bsim2def.h"
#include "sperror.h"
#include "gendefs.h"
#include "suffix.h"


int
BSIM2delete(inModel,name,inInst)
    GENmodel *inModel;
    IFuid name;
    GENinstance **inInst;

{

    BSIM2instance **fast = (BSIM2instance**)inInst;
    BSIM2model *model = (BSIM2model*)inModel;
    BSIM2instance **prev = NULL;
    BSIM2instance *here;

    for( ; model ; model = model->BSIM2nextModel) {
        prev = &(model->BSIM2instances);
        for(here = *prev; here ; here = *prev) {
            if(here->BSIM2name == name || (fast && here==*fast) ) {
                *prev= here->BSIM2nextInstance;
                FREE(here);
                return(OK);
            }
            prev = &(here->BSIM2nextInstance);
        }
    }
    return(E_NODEV);
}
