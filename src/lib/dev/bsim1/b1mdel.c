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
#include "suffix.h"


int
BSIM1mDelete(inModel,modname,kill)
    GENmodel **inModel;
    IFuid modname;
    GENmodel *kill;

{
    BSIM1model **model = (BSIM1model**)inModel;
    BSIM1model *modfast = (BSIM1model*)kill;
    BSIM1instance *here;
    BSIM1instance *prev = NULL;
    BSIM1model **oldmod;
    oldmod = model;
    for( ; *model ; model = &((*model)->BSIM1nextModel)) {
        if( (*model)->BSIM1modName == modname || 
                (modfast && *model == modfast) ) goto delgot;
        oldmod = model;
    }
    return(E_NOMOD);

delgot:
    *oldmod = (*model)->BSIM1nextModel; /* cut deleted device out of list */
    for(here = (*model)->BSIM1instances ; here ; here = here->BSIM1nextInstance) {
        if(prev) FREE(prev);
        prev = here;
    }
    if(prev) FREE(prev);
    FREE(*model);
    return(OK);

}
