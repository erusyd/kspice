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
#include "suffix.h"


void
BSIM1destroy(inModel)
    GENmodel **inModel;

{

    BSIM1model **model = (BSIM1model**)inModel;
    BSIM1instance *here;
    BSIM1instance *prev = NULL;
    BSIM1model *mod = *model;
    BSIM1model *oldmod = NULL;

    for( ; mod ; mod = mod->BSIM1nextModel) {
        if(oldmod) FREE(oldmod);
        oldmod = mod;
        prev = (BSIM1instance *)NULL;
        for(here = mod->BSIM1instances ; here ; here = here->BSIM1nextInstance) {
            if(prev) FREE(prev);
            prev = here;
        }
        if(prev) FREE(prev);
    }
    if(oldmod) FREE(oldmod);
    *model = NULL;
}
