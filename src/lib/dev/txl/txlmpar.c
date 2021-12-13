/**********
Copyright 1992 Regents of the University of California.  All rights
reserved.
Author: 1992 Charles Hough
**********/


#include "spice.h"
#include <stdio.h>
#include "const.h"
#include "util.h"
#include "ifsim.h"
#include "txldefs.h"
#include "sperror.h"
#include "suffix.h"


int
TXLmParam(param,value,inModel)
    int param;
    IFvalue *value;
    GENmodel *inModel;
{
    register TXLmodel *model = (TXLmodel *)inModel;
    switch(param) {
        case TXL_R:
            model->R = value->rValue;
            model->Rgiven = TRUE;
            break;
        case TXL_L:
            model->L = value->rValue;
            model->Lgiven = TRUE;
            break;
        case TXL_G:
            model->G = value->rValue;
            model->Ggiven = TRUE;
            break;
        case TXL_C:
            model->C = value->rValue;
            model->Cgiven = TRUE;
            break;
        case TXL_length:
            model->length = value->rValue;
            model->lengthgiven = TRUE;
            break;
		case TXL_MOD_R:
			break;
        default:
            return(E_BADPARM);
    }
    return(OK);
}
