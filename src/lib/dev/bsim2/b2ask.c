/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1988 Hong J. Park
**********/
/*
 */

#include "spice.h"
#include <stdio.h>
#include <math.h>
#include "ifsim.h"
#include "cktdefs.h"
#include "devdefs.h"
#include "bsim2def.h"
#include "sperror.h"
#include "util.h"
#include "suffix.h"


/*ARGSUSED*/
int
BSIM2ask(ckt,inst,which,value,select)
    CKTcircuit *ckt;
    GENinstance *inst;
    int which;
    IFvalue *value;
    IFvalue *select;
{
    BSIM2instance *here = (BSIM2instance*)inst;

    switch(which) {
        case BSIM2_L:
            value->rValue = here->BSIM2l;
            return(OK);
        case BSIM2_W:
            value->rValue = here->BSIM2w;
            return(OK);
        case BSIM2_AS:
            value->rValue = here->BSIM2sourceArea;
            return(OK);
        case BSIM2_AD:
            value->rValue = here->BSIM2drainArea;
            return(OK);
        case BSIM2_PS:
            value->rValue = here->BSIM2sourcePerimeter;
            return(OK);
        case BSIM2_PD:
            value->rValue = here->BSIM2drainPerimeter;
            return(OK);
        case BSIM2_NRS:
            value->rValue = here->BSIM2sourceSquares;
            return(OK);
        case BSIM2_NRD:
            value->rValue = here->BSIM2drainSquares;
            return(OK);
        case BSIM2_OFF:
            value->rValue = here->BSIM2off;
            return(OK);
        case BSIM2_IC_VBS:
            value->rValue = here->BSIM2icVBS;
            return(OK);
        case BSIM2_IC_VDS:
            value->rValue = here->BSIM2icVDS;
            return(OK);
        case BSIM2_IC_VGS:
            value->rValue = here->BSIM2icVGS;
            return(OK);
        case BSIM2_DNODE:
            value->iValue = here->BSIM2dNode;
            return(OK);
        case BSIM2_GNODE:
            value->iValue = here->BSIM2gNode;
            return(OK);
        case BSIM2_SNODE:
            value->iValue = here->BSIM2sNode;
            return(OK);
        case BSIM2_BNODE:
            value->iValue = here->BSIM2bNode;
            return(OK);
        case BSIM2_DNODEPRIME:
            value->iValue = here->BSIM2dNodePrime;
            return(OK);
        case BSIM2_SNODEPRIME:
            value->iValue = here->BSIM2sNodePrime;
            return(OK);
        case BSIM2_SOURCECONDUCT:
            value->rValue = here->BSIM2sourceConductance;
            return(OK);
        case BSIM2_DRAINCONDUCT:
            value->rValue = here->BSIM2drainConductance;
            return(OK);
        case BSIM2_VBD:
            value->rValue = *(ckt->CKTstate0 + here->BSIM2vbd);
            return(OK);
        case BSIM2_VBS:
            value->rValue = *(ckt->CKTstate0 + here->BSIM2vbs);
            return(OK);
        case BSIM2_VGS:
            value->rValue = *(ckt->CKTstate0 + here->BSIM2vgs);
            return(OK);
        case BSIM2_VDS:
            value->rValue = *(ckt->CKTstate0 + here->BSIM2vds);
            return(OK);
        case BSIM2_CD:
            value->rValue = *(ckt->CKTstate0 + here->BSIM2cd); 
            return(OK);
        case BSIM2_CBS:
            value->rValue = *(ckt->CKTstate0 + here->BSIM2cbs); 
            return(OK);
        case BSIM2_CBD:
            value->rValue = *(ckt->CKTstate0 + here->BSIM2cbd); 
            return(OK);
        case BSIM2_GM:
            value->rValue = *(ckt->CKTstate0 + here->BSIM2gm); 
            return(OK);
        case BSIM2_GDS:
            value->rValue = *(ckt->CKTstate0 + here->BSIM2gds); 
            return(OK);
        case BSIM2_GMBS:
            value->rValue = *(ckt->CKTstate0 + here->BSIM2gmbs); 
            return(OK);
        case BSIM2_GBD:
            value->rValue = *(ckt->CKTstate0 + here->BSIM2gbd); 
            return(OK);
        case BSIM2_GBS:
            value->rValue = *(ckt->CKTstate0 + here->BSIM2gbs); 
            return(OK);
        case BSIM2_QB:
            value->rValue = *(ckt->CKTstate0 + here->BSIM2qb); 
            return(OK);
        case BSIM2_CQB:
            value->rValue = *(ckt->CKTstate0 + here->BSIM2cqb); 
            return(OK);
        case BSIM2_QG:
            value->rValue = *(ckt->CKTstate0 + here->BSIM2qg); 
            return(OK);
        case BSIM2_CQG:
            value->rValue = *(ckt->CKTstate0 + here->BSIM2cqg); 
            return(OK);
        case BSIM2_QD:
            value->rValue = *(ckt->CKTstate0 + here->BSIM2qd); 
            return(OK);
        case BSIM2_CQD:
            value->rValue = *(ckt->CKTstate0 + here->BSIM2cqd); 
            return(OK);
        case BSIM2_CGG:
            value->rValue = *(ckt->CKTstate0 + here->BSIM2cggb); 
            return(OK);
        case BSIM2_CGD:
            value->rValue = *(ckt->CKTstate0 + here->BSIM2cgdb); 
            return(OK);
        case BSIM2_CGS:
            value->rValue = *(ckt->CKTstate0 + here->BSIM2cgsb); 
            return(OK);
        case BSIM2_CBG:
            value->rValue = *(ckt->CKTstate0 + here->BSIM2cbgb); 
            return(OK);
        case BSIM2_CAPBD:
            value->rValue = *(ckt->CKTstate0 + here->BSIM2capbd); 
            return(OK);
        case BSIM2_CQBD:
            value->rValue = *(ckt->CKTstate0 + here->BSIM2cqbd); 
            return(OK);
        case BSIM2_CAPBS:
            value->rValue = *(ckt->CKTstate0 + here->BSIM2capbs); 
            return(OK);
        case BSIM2_CQBS:
            value->rValue = *(ckt->CKTstate0 + here->BSIM2cqbs); 
            return(OK);
        case BSIM2_CDG:
            value->rValue = *(ckt->CKTstate0 + here->BSIM2cdgb); 
            return(OK);
        case BSIM2_CDD:
            value->rValue = *(ckt->CKTstate0 + here->BSIM2cddb); 
            return(OK);
        case BSIM2_CDS:
            value->rValue = *(ckt->CKTstate0 + here->BSIM2cdsb); 
            return(OK);
        case BSIM2_VON:
            value->rValue = *(ckt->CKTstate0 + here->BSIM2vono); 
            return(OK);
        case BSIM2_QBS:
            value->rValue = *(ckt->CKTstate0 + here->BSIM2qbs); 
            return(OK);
        case BSIM2_QBD:
            value->rValue = *(ckt->CKTstate0 + here->BSIM2qbd); 
            return(OK);
        default:
            return(E_BADPARM);
    }
    /* NOTREACHED */
}


