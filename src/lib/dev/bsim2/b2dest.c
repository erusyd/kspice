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
#include "suffix.h"


void
BSIM2destroy(inModel)
    GENmodel **inModel;

{

    BSIM2model **model = (BSIM2model**)inModel;
    BSIM2instance *here;
    BSIM2instance *prev = NULL;
    BSIM2model *mod = *model;
    BSIM2model *oldmod = NULL;

    for( ; mod ; mod = mod->BSIM2nextModel) {
        if(oldmod) FREE(oldmod);
        oldmod = mod;
        prev = (BSIM2instance *)NULL;
        for(here = mod->BSIM2instances ; here ; here = here->BSIM2nextInstance) {
            if(prev) FREE(prev);
            prev = here;
        }
        if(prev) FREE(prev);
    }
    if(oldmod) FREE(oldmod);
    *model = NULL;
}

