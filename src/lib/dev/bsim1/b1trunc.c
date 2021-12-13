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
#include "bsim1def.h"
#include "sperror.h"
#include "suffix.h"


int
BSIM1trunc(inModel,ckt,timeStep)
    GENmodel *inModel;
    register CKTcircuit *ckt;
    double *timeStep;

{
    register BSIM1model *model = (BSIM1model*)inModel;
    register BSIM1instance *here;
#ifdef STEPDEBUG
    double debugtemp;
#endif /* STEPDEBUG */

    for( ; model != NULL; model = model->BSIM1nextModel) {
        for(here=model->BSIM1instances;here!=NULL;here = here->BSIM1nextInstance){
#ifdef STEPDEBUG
            debugtemp = *timeStep;
#endif /* STEPDEBUG */
            CKTterr(here->BSIM1qb,ckt,timeStep);
            CKTterr(here->BSIM1qg,ckt,timeStep);
            CKTterr(here->BSIM1qd,ckt,timeStep);
#ifdef STEPDEBUG
            if(debugtemp != *timeStep) {
                printf("device %s reduces step from %g to %g\n",
                        here->BSIM1name,debugtemp,*timeStep);
            }
#endif /* STEPDEBUG */
        }
    }
    return(OK);
}

