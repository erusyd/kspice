/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1988 Hong J. Park
**********/
/*
 */

#include "spice.h"
#include <stdio.h>
#include "ifsim.h"
#include "cktdefs.h"
#include "devdefs.h"
#include "bsim1def.h"
#include "sperror.h"
#include "suffix.h"


/*ARGSUSED*/
int
BSIM1mAsk(ckt,inst,which,value)
    CKTcircuit *ckt;
    GENmodel *inst;
    int which;
    IFvalue *value;
{
    BSIM1model *model = (BSIM1model *)inst;
        switch(which) {
        case BSIM1_MOD_VFB0: 
            value->rValue = model->BSIM1vfb0; 
            return(OK);
        case BSIM1_MOD_VFBL:
            value->rValue = model->BSIM1vfbL; 
            return(OK);
        case BSIM1_MOD_VFBW:
            value->rValue = model->BSIM1vfbW; 
            return(OK);
        case BSIM1_MOD_PHI0:
            value->rValue = model->BSIM1phi0; 
            return(OK);
        case BSIM1_MOD_PHIL:
            value->rValue = model->BSIM1phiL; 
            return(OK);
        case BSIM1_MOD_PHIW:
            value->rValue = model->BSIM1phiW; 
            return(OK);
        case BSIM1_MOD_K10:
            value->rValue = model->BSIM1K10; 
            return(OK);
        case BSIM1_MOD_K1L:
            value->rValue = model->BSIM1K1L; 
            return(OK);
        case BSIM1_MOD_K1W:
            value->rValue = model->BSIM1K1W; 
            return(OK);
        case BSIM1_MOD_K20:
            value->rValue = model->BSIM1K20; 
            return(OK);
        case BSIM1_MOD_K2L:
            value->rValue = model->BSIM1K2L; 
            return(OK);
        case BSIM1_MOD_K2W:
            value->rValue = model->BSIM1K2W; 
            return(OK);
        case BSIM1_MOD_ETA0:
            value->rValue = model->BSIM1eta0; 
            return(OK);
        case BSIM1_MOD_ETAL:
            value->rValue = model->BSIM1etaL; 
            return(OK);
        case BSIM1_MOD_ETAW:
            value->rValue = model->BSIM1etaW; 
            return(OK);
        case BSIM1_MOD_ETAB0:
            value->rValue = model->BSIM1etaB0; 
            return(OK);
        case BSIM1_MOD_ETABL:
            value->rValue = model->BSIM1etaBl; 
            return(OK);
        case BSIM1_MOD_ETABW:
            value->rValue = model->BSIM1etaBw; 
            return(OK);
        case BSIM1_MOD_ETAD0:
            value->rValue = model->BSIM1etaD0; 
            return(OK);
        case BSIM1_MOD_ETADL:
            value->rValue = model->BSIM1etaDl; 
            return(OK);
        case BSIM1_MOD_ETADW:
            value->rValue = model->BSIM1etaDw; 
            return(OK);
        case BSIM1_MOD_DELTAL:
            value->rValue = model->BSIM1deltaL; 
            return(OK);
        case BSIM1_MOD_DELTAW:
            value->rValue = model->BSIM1deltaW; 
            return(OK);
        case BSIM1_MOD_MOBZERO:
            value->rValue = model->BSIM1mobZero; 
            return(OK);
        case BSIM1_MOD_MOBZEROB0:
            value->rValue = model->BSIM1mobZeroB0; 
            return(OK);
        case BSIM1_MOD_MOBZEROBL:
            value->rValue = model->BSIM1mobZeroBl; 
            return(OK);
        case BSIM1_MOD_MOBZEROBW:
            value->rValue = model->BSIM1mobZeroBw; 
            return(OK);
        case BSIM1_MOD_MOBVDD0:
            value->rValue = model->BSIM1mobVdd0; 
            return(OK);
        case BSIM1_MOD_MOBVDDL:
            value->rValue = model->BSIM1mobVddl; 
            return(OK);
        case BSIM1_MOD_MOBVDDW:
            value->rValue = model->BSIM1mobVddw; 
            return(OK);
        case BSIM1_MOD_MOBVDDB0:
            value->rValue = model->BSIM1mobVddB0; 
            return(OK);
        case BSIM1_MOD_MOBVDDBL:
            value->rValue = model->BSIM1mobVddBl; 
            return(OK);
        case BSIM1_MOD_MOBVDDBW:
            value->rValue = model->BSIM1mobVddBw; 
            return(OK);
        case BSIM1_MOD_MOBVDDD0:
            value->rValue = model->BSIM1mobVddD0; 
            return(OK);
        case BSIM1_MOD_MOBVDDDL:
            value->rValue = model->BSIM1mobVddDl; 
            return(OK);
        case BSIM1_MOD_MOBVDDDW:
            value->rValue = model->BSIM1mobVddDw; 
            return(OK);
        case BSIM1_MOD_UGS0:
            value->rValue = model->BSIM1ugs0; 
            return(OK);
        case BSIM1_MOD_UGSL:
            value->rValue = model->BSIM1ugsL; 
            return(OK);
        case BSIM1_MOD_UGSW:
            value->rValue = model->BSIM1ugsW; 
            return(OK);
        case BSIM1_MOD_UGSB0:
            value->rValue = model->BSIM1ugsB0; 
            return(OK);
        case BSIM1_MOD_UGSBL:
            value->rValue = model->BSIM1ugsBL; 
            return(OK);
        case BSIM1_MOD_UGSBW:
            value->rValue = model->BSIM1ugsBW; 
            return(OK);
        case BSIM1_MOD_UDS0:
            value->rValue = model->BSIM1uds0; 
            return(OK);
        case BSIM1_MOD_UDSL:
            value->rValue = model->BSIM1udsL; 
            return(OK);
        case BSIM1_MOD_UDSW:
            value->rValue = model->BSIM1udsW; 
            return(OK);
        case BSIM1_MOD_UDSB0:
            value->rValue = model->BSIM1udsB0; 
            return(OK);
        case BSIM1_MOD_UDSBL:
            value->rValue = model->BSIM1udsBL; 
            return(OK);
        case BSIM1_MOD_UDSBW:
            value->rValue = model->BSIM1udsBW; 
            return(OK);
        case BSIM1_MOD_UDSD0:
            value->rValue = model->BSIM1udsD0; 
            return(OK);
        case BSIM1_MOD_UDSDL:
            value->rValue = model->BSIM1udsDL; 
            return(OK);
        case BSIM1_MOD_UDSDW:
            value->rValue = model->BSIM1udsDW; 
            return(OK);
        case BSIM1_MOD_N00:
            value->rValue = model->BSIM1subthSlope0; 
            return(OK);
        case BSIM1_MOD_N0L:
            value->rValue = model->BSIM1subthSlopeL; 
            return(OK);
        case BSIM1_MOD_N0W:
            value->rValue = model->BSIM1subthSlopeW; 
            return(OK);
        case BSIM1_MOD_NB0:
            value->rValue = model->BSIM1subthSlopeB0; 
            return(OK);
        case BSIM1_MOD_NBL:
            value->rValue = model->BSIM1subthSlopeBL; 
            return(OK);
        case BSIM1_MOD_NBW:
            value->rValue = model->BSIM1subthSlopeBW; 
            return(OK);
        case BSIM1_MOD_ND0:
            value->rValue = model->BSIM1subthSlopeD0; 
            return(OK);
        case BSIM1_MOD_NDL:
            value->rValue = model->BSIM1subthSlopeDL; 
            return(OK);
        case BSIM1_MOD_NDW:
            value->rValue = model->BSIM1subthSlopeDW; 
            return(OK);
        case BSIM1_MOD_TOX:
            value->rValue = model->BSIM1oxideThickness; 
            return(OK);
        case BSIM1_MOD_TEMP:
            value->rValue = model->BSIM1temp; 
            return(OK);
        case BSIM1_MOD_VDD:
            value->rValue = model->BSIM1vdd; 
            return(OK);
        case BSIM1_MOD_CGSO:
            value->rValue = model->BSIM1gateSourceOverlapCap; 
            return(OK);
        case BSIM1_MOD_CGDO:
            value->rValue = model->BSIM1gateDrainOverlapCap; 
            return(OK);
        case BSIM1_MOD_CGBO:
            value->rValue = model->BSIM1gateBulkOverlapCap; 
            return(OK);
        case BSIM1_MOD_XPART:
            value->rValue = model->BSIM1channelChargePartitionFlag; 
            return(OK);
        case BSIM1_MOD_RSH:
            value->rValue = model->BSIM1sheetResistance; 
            return(OK);
        case BSIM1_MOD_JS:
            value->rValue = model->BSIM1jctSatCurDensity; 
            return(OK);
        case BSIM1_MOD_PB:
            value->rValue = model->BSIM1bulkJctPotential; 
            return(OK);
        case BSIM1_MOD_MJ:
            value->rValue = model->BSIM1bulkJctBotGradingCoeff; 
            return(OK);
        case BSIM1_MOD_PBSW:
            value->rValue = model->BSIM1sidewallJctPotential; 
            return(OK);
        case BSIM1_MOD_MJSW:
            value->rValue = model->BSIM1bulkJctSideGradingCoeff; 
            return(OK);
        case BSIM1_MOD_CJ:
            value->rValue = model->BSIM1unitAreaJctCap; 
            return(OK);
        case BSIM1_MOD_CJSW:
            value->rValue = model->BSIM1unitLengthSidewallJctCap; 
            return(OK);
        case BSIM1_MOD_DEFWIDTH:
            value->rValue = model->BSIM1defaultWidth; 
            return(OK);
        case BSIM1_MOD_DELLENGTH:
            value->rValue = model->BSIM1deltaLength; 
            return(OK);
        default:
            return(E_BADPARM);
    }
    /* NOTREACHED */
}

