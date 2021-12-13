/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Hong J. Park, Thomas L. Quarles
**********/
/*
 */

#include "spice.h"
#include <stdio.h>
#include <math.h>
#include "cktdefs.h"
#include "bsim2def.h"
#include "sperror.h"
#include "suffix.h"


int
BSIM2trunc(inModel,ckt,timeStep)
    GENmodel *inModel;
    register CKTcircuit *ckt;
    double *timeStep;

{
    register BSIM2model *model = (BSIM2model*)inModel;
    register BSIM2instance *here;
#ifdef STEPDEBUG
    double debugtemp;
#endif /* STEPDEBUG */

    for( ; model != NULL; model = model->BSIM2nextModel) {
        for(here=model->BSIM2instances;here!=NULL;here = here->BSIM2nextInstance){
#ifdef STEPDEBUG
            debugtemp = *timeStep;
#endif /* STEPDEBUG */
            CKTterr(here->BSIM2qb,ckt,timeStep);
            CKTterr(here->BSIM2qg,ckt,timeStep);
            CKTterr(here->BSIM2qd,ckt,timeStep);
#ifdef STEPDEBUG
            if(debugtemp != *timeStep) {
                printf("device %s reduces step from %g to %g\n",
                        here->BSIM2name,debugtemp,*timeStep);
            }
#endif /* STEPDEBUG */
        }
    }
    return(OK);
}


