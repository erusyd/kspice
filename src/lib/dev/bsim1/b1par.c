/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Hong J. Park, Thomas L. Quarles
**********/
/*
 */

#include "spice.h"
#include <stdio.h>
#include "ifsim.h"
#include "bsim1def.h"
#include "util.h"
#include "sperror.h"
#include "suffix.h"


/* ARGSUSED */
int
BSIM1param(param,value,inst,select)
    int param;
    IFvalue *value;
    GENinstance *inst;
    IFvalue *select;
{
    BSIM1instance *here = (BSIM1instance*)inst;
    switch(param) {
        case BSIM1_W:
            here->BSIM1w = value->rValue;
            here->BSIM1wGiven = TRUE;
            break;
        case BSIM1_L:
            here->BSIM1l = value->rValue;
            here->BSIM1lGiven = TRUE;
            break;
        case BSIM1_AS:
            here->BSIM1sourceArea = value->rValue;
            here->BSIM1sourceAreaGiven = TRUE;
            break;
        case BSIM1_AD:
            here->BSIM1drainArea = value->rValue;
            here->BSIM1drainAreaGiven = TRUE;
            break;
        case BSIM1_PS:
            here->BSIM1sourcePerimeter = value->rValue;
            here->BSIM1sourcePerimeterGiven = TRUE;
            break;
        case BSIM1_PD:
            here->BSIM1drainPerimeter = value->rValue;
            here->BSIM1drainPerimeterGiven = TRUE;
            break;
        case BSIM1_NRS:
            here->BSIM1sourceSquares = value->rValue;
            here->BSIM1sourceSquaresGiven = TRUE;
            break;
        case BSIM1_NRD:
            here->BSIM1drainSquares = value->rValue;
            here->BSIM1drainSquaresGiven = TRUE;
            break;
        case BSIM1_OFF:
            here->BSIM1off = value->iValue;
            break;
        case BSIM1_IC_VBS:
            here->BSIM1icVBS = value->rValue;
            here->BSIM1icVBSGiven = TRUE;
            break;
        case BSIM1_IC_VDS:
            here->BSIM1icVDS = value->rValue;
            here->BSIM1icVDSGiven = TRUE;
            break;
        case BSIM1_IC_VGS:
            here->BSIM1icVGS = value->rValue;
            here->BSIM1icVGSGiven = TRUE;
            break;
        case BSIM1_IC:
            switch(value->v.numValue){
                case 3:
                    here->BSIM1icVBS = *(value->v.vec.rVec+2);
                    here->BSIM1icVBSGiven = TRUE;
                case 2:
                    here->BSIM1icVGS = *(value->v.vec.rVec+1);
                    here->BSIM1icVGSGiven = TRUE;
                case 1:
                    here->BSIM1icVDS = *(value->v.vec.rVec);
                    here->BSIM1icVDSGiven = TRUE;
                    break;
                default:
                    return(E_BADPARM);
            }
            break;
        default:
            return(E_BADPARM);
    }
    return(OK);
}


