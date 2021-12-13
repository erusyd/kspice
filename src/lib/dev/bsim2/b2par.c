/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Hong J. Park, Thomas L. Quarles
**********/
/*
 */

#include "spice.h"
#include <stdio.h>
#include "ifsim.h"
#include "bsim2def.h"
#include "util.h"
#include "sperror.h"
#include "suffix.h"


/* ARGSUSED */
int
BSIM2param(param,value,inst,select)
    int param;
    IFvalue *value;
    GENinstance *inst;
    IFvalue *select;
{
    BSIM2instance *here = (BSIM2instance*)inst;
    switch(param) {
        case BSIM2_W:
            here->BSIM2w = value->rValue;
            here->BSIM2wGiven = TRUE;
            break;
        case BSIM2_L:
            here->BSIM2l = value->rValue;
            here->BSIM2lGiven = TRUE;
            break;
        case BSIM2_AS:
            here->BSIM2sourceArea = value->rValue;
            here->BSIM2sourceAreaGiven = TRUE;
            break;
        case BSIM2_AD:
            here->BSIM2drainArea = value->rValue;
            here->BSIM2drainAreaGiven = TRUE;
            break;
        case BSIM2_PS:
            here->BSIM2sourcePerimeter = value->rValue;
            here->BSIM2sourcePerimeterGiven = TRUE;
            break;
        case BSIM2_PD:
            here->BSIM2drainPerimeter = value->rValue;
            here->BSIM2drainPerimeterGiven = TRUE;
            break;
        case BSIM2_NRS:
            here->BSIM2sourceSquares = value->rValue;
            here->BSIM2sourceSquaresGiven = TRUE;
            break;
        case BSIM2_NRD:
            here->BSIM2drainSquares = value->rValue;
            here->BSIM2drainSquaresGiven = TRUE;
            break;
        case BSIM2_OFF:
            here->BSIM2off = value->iValue;
            break;
        case BSIM2_IC_VBS:
            here->BSIM2icVBS = value->rValue;
            here->BSIM2icVBSGiven = TRUE;
            break;
        case BSIM2_IC_VDS:
            here->BSIM2icVDS = value->rValue;
            here->BSIM2icVDSGiven = TRUE;
            break;
        case BSIM2_IC_VGS:
            here->BSIM2icVGS = value->rValue;
            here->BSIM2icVGSGiven = TRUE;
            break;
        case BSIM2_IC:
            switch(value->v.numValue){
                case 3:
                    here->BSIM2icVBS = *(value->v.vec.rVec+2);
                    here->BSIM2icVBSGiven = TRUE;
                case 2:
                    here->BSIM2icVGS = *(value->v.vec.rVec+1);
                    here->BSIM2icVGSGiven = TRUE;
                case 1:
                    here->BSIM2icVDS = *(value->v.vec.rVec);
                    here->BSIM2icVDSGiven = TRUE;
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



