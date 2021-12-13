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
#include "bsim1def.h"
#include "sperror.h"
#include "util.h"
#include "suffix.h"


/*ARGSUSED*/
int
BSIM1ask(ckt,inst,which,value,select)
    CKTcircuit *ckt;
    GENinstance *inst;
    int which;
    IFvalue *value;
    IFvalue *select;
{
    BSIM1instance *here = (BSIM1instance*)inst;

    switch(which) {
        case BSIM1_L:
            value->rValue = here->BSIM1l;
            return(OK);
        case BSIM1_W:
            value->rValue = here->BSIM1w;
            return(OK);
        case BSIM1_AS:
            value->rValue = here->BSIM1sourceArea;
            return(OK);
        case BSIM1_AD:
            value->rValue = here->BSIM1drainArea;
            return(OK);
        case BSIM1_PS:
            value->rValue = here->BSIM1sourcePerimeter;
            return(OK);
        case BSIM1_PD:
            value->rValue = here->BSIM1drainPerimeter;
            return(OK);
        case BSIM1_NRS:
            value->rValue = here->BSIM1sourceSquares;
            return(OK);
        case BSIM1_NRD:
            value->rValue = here->BSIM1drainSquares;
            return(OK);
        case BSIM1_OFF:
            value->rValue = here->BSIM1off;
            return(OK);
        case BSIM1_IC_VBS:
            value->rValue = here->BSIM1icVBS;
            return(OK);
        case BSIM1_IC_VDS:
            value->rValue = here->BSIM1icVDS;
            return(OK);
        case BSIM1_IC_VGS:
            value->rValue = here->BSIM1icVGS;
            return(OK);
        case BSIM1_DNODE:
            value->iValue = here->BSIM1dNode;
            return(OK);
        case BSIM1_GNODE:
            value->iValue = here->BSIM1gNode;
            return(OK);
        case BSIM1_SNODE:
            value->iValue = here->BSIM1sNode;
            return(OK);
        case BSIM1_BNODE:
            value->iValue = here->BSIM1bNode;
            return(OK);
        case BSIM1_DNODEPRIME:
            value->iValue = here->BSIM1dNodePrime;
            return(OK);
        case BSIM1_SNODEPRIME:
            value->iValue = here->BSIM1sNodePrime;
            return(OK);
        case BSIM1_SOURCECONDUCT:
            value->rValue = here->BSIM1sourceConductance;
            return(OK);
        case BSIM1_DRAINCONDUCT:
            value->rValue = here->BSIM1drainConductance;
            return(OK);
        case BSIM1_VBD:
            value->rValue = *(ckt->CKTstate0 + here->BSIM1vbd);
            return(OK);
        case BSIM1_VBS:
            value->rValue = *(ckt->CKTstate0 + here->BSIM1vbs);
            return(OK);
        case BSIM1_VGS:
            value->rValue = *(ckt->CKTstate0 + here->BSIM1vgs);
            return(OK);
        case BSIM1_VDS:
            value->rValue = *(ckt->CKTstate0 + here->BSIM1vds);
            return(OK);
        case BSIM1_CD:
            value->rValue = *(ckt->CKTstate0 + here->BSIM1cd); 
            return(OK);
        case BSIM1_CBS:
            value->rValue = *(ckt->CKTstate0 + here->BSIM1cbs); 
            return(OK);
        case BSIM1_CBD:
            value->rValue = *(ckt->CKTstate0 + here->BSIM1cbd); 
            return(OK);
        case BSIM1_GM:
            value->rValue = *(ckt->CKTstate0 + here->BSIM1gm); 
            return(OK);
        case BSIM1_GDS:
            value->rValue = *(ckt->CKTstate0 + here->BSIM1gds); 
            return(OK);
        case BSIM1_GMBS:
            value->rValue = *(ckt->CKTstate0 + here->BSIM1gmbs); 
            return(OK);
        case BSIM1_GBD:
            value->rValue = *(ckt->CKTstate0 + here->BSIM1gbd); 
            return(OK);
        case BSIM1_GBS:
            value->rValue = *(ckt->CKTstate0 + here->BSIM1gbs); 
            return(OK);
        case BSIM1_QB:
            value->rValue = *(ckt->CKTstate0 + here->BSIM1qb); 
            return(OK);
        case BSIM1_CQB:
            value->rValue = *(ckt->CKTstate0 + here->BSIM1cqb); 
            return(OK);
        case BSIM1_QG:
            value->rValue = *(ckt->CKTstate0 + here->BSIM1qg); 
            return(OK);
        case BSIM1_CQG:
            value->rValue = *(ckt->CKTstate0 + here->BSIM1cqg); 
            return(OK);
        case BSIM1_QD:
            value->rValue = *(ckt->CKTstate0 + here->BSIM1qd); 
            return(OK);
        case BSIM1_CQD:
            value->rValue = *(ckt->CKTstate0 + here->BSIM1cqd); 
            return(OK);
        case BSIM1_CGG:
            value->rValue = *(ckt->CKTstate0 + here->BSIM1cggb); 
            return(OK);
        case BSIM1_CGD:
            value->rValue = *(ckt->CKTstate0 + here->BSIM1cgdb); 
            return(OK);
        case BSIM1_CGS:
            value->rValue = *(ckt->CKTstate0 + here->BSIM1cgsb); 
            return(OK);
        case BSIM1_CBG:
            value->rValue = *(ckt->CKTstate0 + here->BSIM1cbgb); 
            return(OK);
        case BSIM1_CAPBD:
            value->rValue = *(ckt->CKTstate0 + here->BSIM1capbd); 
            return(OK);
        case BSIM1_CQBD:
            value->rValue = *(ckt->CKTstate0 + here->BSIM1cqbd); 
            return(OK);
        case BSIM1_CAPBS:
            value->rValue = *(ckt->CKTstate0 + here->BSIM1capbs); 
            return(OK);
        case BSIM1_CQBS:
            value->rValue = *(ckt->CKTstate0 + here->BSIM1cqbs); 
            return(OK);
        case BSIM1_CDG:
            value->rValue = *(ckt->CKTstate0 + here->BSIM1cdgb); 
            return(OK);
        case BSIM1_CDD:
            value->rValue = *(ckt->CKTstate0 + here->BSIM1cddb); 
            return(OK);
        case BSIM1_CDS:
            value->rValue = *(ckt->CKTstate0 + here->BSIM1cdsb); 
            return(OK);
        case BSIM1_VON:
            value->rValue = *(ckt->CKTstate0 + here->BSIM1vono); 
            return(OK);
        case BSIM1_QBS:
            value->rValue = *(ckt->CKTstate0 + here->BSIM1qbs); 
            return(OK);
        case BSIM1_QBD:
            value->rValue = *(ckt->CKTstate0 + here->BSIM1qbd); 
            return(OK);
        default:
            return(E_BADPARM);
    }
    /* NOTREACHED */
}

