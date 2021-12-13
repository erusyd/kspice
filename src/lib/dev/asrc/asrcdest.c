/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1987 Kanwar Jit Singh
**********/
/*
 * singh@ic.Berkeley.edu
 */

#include "spice.h"
#include <stdio.h>
#include "asrcdefs.h"
#include "util.h"
#include "suffix.h"


void
ASRCdestroy(model)
    GENmodel **model;

{

    ASRCmodel **start = (ASRCmodel**)model; /* starting model */
    ASRCinstance *here;     /* current instance */
    ASRCinstance *prev = NULL;  /* previous instance */
    ASRCmodel *mod = *start;    /* current model */
    ASRCmodel *oldmod = NULL;   /* previous model */

    for( ; mod ; mod = mod->ASRCnextModel) {
        if(oldmod) FREE(oldmod);
        oldmod = mod;
        prev = (ASRCinstance *)NULL;
        for(here = mod->ASRCinstances ; here ; here = here->ASRCnextInstance) {
            if(prev) FREE(prev);
            prev = here;
        }
        if(prev) FREE(prev);
    }
    if(oldmod) FREE(oldmod);
    *model = NULL;
}
