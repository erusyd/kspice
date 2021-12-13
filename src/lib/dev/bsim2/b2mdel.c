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
#include "suffix.h"


int
BSIM2mDelete(inModel,modname,kill)
    GENmodel **inModel;
    IFuid modname;
    GENmodel *kill;

{
    BSIM2model **model = (BSIM2model**)inModel;
    BSIM2model *modfast = (BSIM2model*)kill;
    BSIM2instance *here;
    BSIM2instance *prev = NULL;
    BSIM2model **oldmod;
    oldmod = model;
    for( ; *model ; model = &((*model)->BSIM2nextModel)) {
        if( (*model)->BSIM2modName == modname || 
                (modfast && *model == modfast) ) goto delgot;
        oldmod = model;
    }
    return(E_NOMOD);

delgot:
    *oldmod = (*model)->BSIM2nextModel; /* cut deleted device out of list */
    for(here = (*model)->BSIM2instances ; here ; here = here->BSIM2nextInstance) {
        if(prev) FREE(prev);
        prev = here;
    }
    if(prev) FREE(prev);
    FREE(*model);
    return(OK);

}

