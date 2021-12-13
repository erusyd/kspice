/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Hong J. Park, Thomas L. Quarles
**********/
/*
 */

#include "spice.h"
#include <stdio.h>
#include "util.h"
#include "bsim1def.h"
#include "ifsim.h"
#include "sperror.h"
#include "suffix.h"


int
BSIM1mParam(param,value,inMod)
    int param;
    IFvalue *value;
    GENmodel *inMod;
{
    BSIM1model *mod = (BSIM1model*)inMod;
    switch(param) {
        case  BSIM1_MOD_VFB0 :
            mod->BSIM1vfb0 = value->rValue;
            mod->BSIM1vfb0Given = TRUE;
            break;
        case  BSIM1_MOD_VFBL :
            mod->BSIM1vfbL = value->rValue;
            mod->BSIM1vfbLGiven = TRUE;
            break;
        case  BSIM1_MOD_VFBW :
            mod->BSIM1vfbW = value->rValue;
            mod->BSIM1vfbWGiven = TRUE;
            break;
        case  BSIM1_MOD_PHI0 :
            mod->BSIM1phi0 = value->rValue;
            mod->BSIM1phi0Given = TRUE;
            break;
        case  BSIM1_MOD_PHIL :
            mod->BSIM1phiL = value->rValue;
            mod->BSIM1phiLGiven = TRUE;
            break;
        case  BSIM1_MOD_PHIW :
            mod->BSIM1phiW = value->rValue;
            mod->BSIM1phiWGiven = TRUE;
            break;
        case  BSIM1_MOD_K10 :
            mod->BSIM1K10 = value->rValue;
            mod->BSIM1K10Given = TRUE;
            break;
        case  BSIM1_MOD_K1L :
            mod->BSIM1K1L = value->rValue;
            mod->BSIM1K1LGiven = TRUE;
            break;
        case  BSIM1_MOD_K1W :
            mod->BSIM1K1W = value->rValue;
            mod->BSIM1K1WGiven = TRUE;
            break;
        case  BSIM1_MOD_K20 :
            mod->BSIM1K20 = value->rValue;
            mod->BSIM1K20Given = TRUE;
            break;
        case  BSIM1_MOD_K2L :
            mod->BSIM1K2L = value->rValue;
            mod->BSIM1K2LGiven = TRUE;
            break;
        case  BSIM1_MOD_K2W :
            mod->BSIM1K2W = value->rValue;
            mod->BSIM1K2WGiven = TRUE;
            break;
        case  BSIM1_MOD_ETA0 :
            mod->BSIM1eta0 = value->rValue;
            mod->BSIM1eta0Given = TRUE;
            break;
        case  BSIM1_MOD_ETAL :
            mod->BSIM1etaL = value->rValue;
            mod->BSIM1etaLGiven = TRUE;
            break;
        case  BSIM1_MOD_ETAW :
            mod->BSIM1etaW = value->rValue;
            mod->BSIM1etaWGiven = TRUE;
            break;
        case  BSIM1_MOD_ETAB0 :
            mod->BSIM1etaB0 = value->rValue;
            mod->BSIM1etaB0Given = TRUE;
            break;
        case  BSIM1_MOD_ETABL :
            mod->BSIM1etaBl = value->rValue;
            mod->BSIM1etaBlGiven = TRUE;
            break;
        case  BSIM1_MOD_ETABW :
            mod->BSIM1etaBw = value->rValue;
            mod->BSIM1etaBwGiven = TRUE;
            break;
        case  BSIM1_MOD_ETAD0 :
            mod->BSIM1etaD0 = value->rValue;
            mod->BSIM1etaD0Given = TRUE;
            break;
        case  BSIM1_MOD_ETADL :
            mod->BSIM1etaDl = value->rValue;
            mod->BSIM1etaDlGiven = TRUE;
            break;
        case  BSIM1_MOD_ETADW :
            mod->BSIM1etaDw = value->rValue;
            mod->BSIM1etaDwGiven = TRUE;
            break;
        case  BSIM1_MOD_DELTAL :
            mod->BSIM1deltaL =  value->rValue;
            mod->BSIM1deltaLGiven = TRUE;
            break;
        case  BSIM1_MOD_DELTAW :
            mod->BSIM1deltaW =  value->rValue;
            mod->BSIM1deltaWGiven = TRUE;
            break;
        case  BSIM1_MOD_MOBZERO :
            mod->BSIM1mobZero = value->rValue;
            mod->BSIM1mobZeroGiven = TRUE;
            break;
        case  BSIM1_MOD_MOBZEROB0 :
            mod->BSIM1mobZeroB0 = value->rValue;
            mod->BSIM1mobZeroB0Given = TRUE;
            break;
        case  BSIM1_MOD_MOBZEROBL :
            mod->BSIM1mobZeroBl = value->rValue;
            mod->BSIM1mobZeroBlGiven = TRUE;
            break;
        case  BSIM1_MOD_MOBZEROBW :
            mod->BSIM1mobZeroBw = value->rValue;
            mod->BSIM1mobZeroBwGiven = TRUE;
            break;
        case  BSIM1_MOD_MOBVDD0 :
            mod->BSIM1mobVdd0 = value->rValue;
            mod->BSIM1mobVdd0Given = TRUE;
            break;
        case  BSIM1_MOD_MOBVDDL :
            mod->BSIM1mobVddl = value->rValue;
            mod->BSIM1mobVddlGiven = TRUE;
            break;
        case  BSIM1_MOD_MOBVDDW :
            mod->BSIM1mobVddw = value->rValue;
            mod->BSIM1mobVddwGiven = TRUE;
            break;
        case  BSIM1_MOD_MOBVDDB0 :
            mod->BSIM1mobVddB0 = value->rValue;
            mod->BSIM1mobVddB0Given = TRUE;
            break;
        case  BSIM1_MOD_MOBVDDBL :
            mod->BSIM1mobVddBl = value->rValue;
            mod->BSIM1mobVddBlGiven = TRUE;
            break;
        case  BSIM1_MOD_MOBVDDBW :
            mod->BSIM1mobVddBw = value->rValue;
            mod->BSIM1mobVddBwGiven = TRUE;
            break;
        case  BSIM1_MOD_MOBVDDD0 :
            mod->BSIM1mobVddD0 = value->rValue;
            mod->BSIM1mobVddD0Given = TRUE;
            break;
        case  BSIM1_MOD_MOBVDDDL :
            mod->BSIM1mobVddDl = value->rValue;
            mod->BSIM1mobVddDlGiven = TRUE;
            break;
        case  BSIM1_MOD_MOBVDDDW :
            mod->BSIM1mobVddDw = value->rValue;
            mod->BSIM1mobVddDwGiven = TRUE;
            break;
        case  BSIM1_MOD_UGS0 :
            mod->BSIM1ugs0 = value->rValue;
            mod->BSIM1ugs0Given = TRUE;
            break;
        case  BSIM1_MOD_UGSL :
            mod->BSIM1ugsL = value->rValue;
            mod->BSIM1ugsLGiven = TRUE;
            break;
        case  BSIM1_MOD_UGSW :
            mod->BSIM1ugsW = value->rValue;
            mod->BSIM1ugsWGiven = TRUE;
            break;
        case  BSIM1_MOD_UGSB0 :
            mod->BSIM1ugsB0 = value->rValue;
            mod->BSIM1ugsB0Given = TRUE;
            break;
        case  BSIM1_MOD_UGSBL :
            mod->BSIM1ugsBL = value->rValue;
            mod->BSIM1ugsBLGiven = TRUE;
            break;
        case  BSIM1_MOD_UGSBW :
            mod->BSIM1ugsBW = value->rValue;
            mod->BSIM1ugsBWGiven = TRUE;
            break;
        case  BSIM1_MOD_UDS0 :
            mod->BSIM1uds0 = value->rValue;
            mod->BSIM1uds0Given = TRUE;
            break;
        case  BSIM1_MOD_UDSL :
            mod->BSIM1udsL = value->rValue;
            mod->BSIM1udsLGiven = TRUE;
            break;
        case  BSIM1_MOD_UDSW :
            mod->BSIM1udsW = value->rValue;
            mod->BSIM1udsWGiven = TRUE;
            break;
        case  BSIM1_MOD_UDSB0 :
            mod->BSIM1udsB0 = value->rValue;
            mod->BSIM1udsB0Given = TRUE;
            break;
        case  BSIM1_MOD_UDSBL :
            mod->BSIM1udsBL = value->rValue;
            mod->BSIM1udsBLGiven = TRUE;
            break;
        case  BSIM1_MOD_UDSBW :
            mod->BSIM1udsBW = value->rValue;
            mod->BSIM1udsBWGiven = TRUE;
            break;
        case  BSIM1_MOD_UDSD0 :
            mod->BSIM1udsD0 = value->rValue;
            mod->BSIM1udsD0Given = TRUE;
            break;
        case  BSIM1_MOD_UDSDL :
            mod->BSIM1udsDL = value->rValue;
            mod->BSIM1udsDLGiven = TRUE;
            break;
        case  BSIM1_MOD_UDSDW :
            mod->BSIM1udsDW = value->rValue;
            mod->BSIM1udsDWGiven = TRUE;
            break;
        case  BSIM1_MOD_N00 :
            mod->BSIM1subthSlope0 = value->rValue;
            mod->BSIM1subthSlope0Given = TRUE;
            break;
        case  BSIM1_MOD_N0L :
            mod->BSIM1subthSlopeL = value->rValue;
            mod->BSIM1subthSlopeLGiven = TRUE;
            break;
        case  BSIM1_MOD_N0W :
            mod->BSIM1subthSlopeW = value->rValue;
            mod->BSIM1subthSlopeWGiven = TRUE;
            break;
        case  BSIM1_MOD_NB0 :
            mod->BSIM1subthSlopeB0 = value->rValue;
            mod->BSIM1subthSlopeB0Given = TRUE;
            break;
        case  BSIM1_MOD_NBL :
            mod->BSIM1subthSlopeBL = value->rValue;
            mod->BSIM1subthSlopeBLGiven = TRUE;
            break;
        case  BSIM1_MOD_NBW :
            mod->BSIM1subthSlopeBW = value->rValue;
            mod->BSIM1subthSlopeBWGiven = TRUE;
            break;
        case  BSIM1_MOD_ND0 :
            mod->BSIM1subthSlopeD0 = value->rValue;
            mod->BSIM1subthSlopeD0Given = TRUE;
            break;
        case  BSIM1_MOD_NDL :
            mod->BSIM1subthSlopeDL = value->rValue;
            mod->BSIM1subthSlopeDLGiven = TRUE;
            break;
        case  BSIM1_MOD_NDW :
            mod->BSIM1subthSlopeDW = value->rValue;
            mod->BSIM1subthSlopeDWGiven = TRUE;
            break;
        case  BSIM1_MOD_TOX :
            mod->BSIM1oxideThickness = value->rValue;
            mod->BSIM1oxideThicknessGiven = TRUE;
            break;
        case  BSIM1_MOD_TEMP :
            mod->BSIM1temp = value->rValue;
            mod->BSIM1tempGiven = TRUE;
            break;
        case  BSIM1_MOD_VDD :
            mod->BSIM1vdd = value->rValue;
            mod->BSIM1vddGiven = TRUE;
            break;
        case  BSIM1_MOD_CGSO :
            mod->BSIM1gateSourceOverlapCap = value->rValue;
            mod->BSIM1gateSourceOverlapCapGiven = TRUE;
            break;
        case  BSIM1_MOD_CGDO :
            mod->BSIM1gateDrainOverlapCap = value->rValue;
            mod->BSIM1gateDrainOverlapCapGiven = TRUE;
            break;
        case  BSIM1_MOD_CGBO :
            mod->BSIM1gateBulkOverlapCap = value->rValue;
            mod->BSIM1gateBulkOverlapCapGiven = TRUE;
            break;
        case  BSIM1_MOD_XPART :
            mod->BSIM1channelChargePartitionFlag = value->rValue;
            mod->BSIM1channelChargePartitionFlagGiven = TRUE;
            break;
        case  BSIM1_MOD_RSH :
            mod->BSIM1sheetResistance = value->rValue;
            mod->BSIM1sheetResistanceGiven = TRUE;
            break;
        case  BSIM1_MOD_JS :
            mod->BSIM1jctSatCurDensity = value->rValue;
            mod->BSIM1jctSatCurDensityGiven = TRUE;
            break;
        case  BSIM1_MOD_PB :
            mod->BSIM1bulkJctPotential = value->rValue;
            mod->BSIM1bulkJctPotentialGiven = TRUE;
            break;
        case  BSIM1_MOD_MJ :
            mod->BSIM1bulkJctBotGradingCoeff = value->rValue;
            mod->BSIM1bulkJctBotGradingCoeffGiven = TRUE;
            break;
        case  BSIM1_MOD_PBSW :
            mod->BSIM1sidewallJctPotential = value->rValue;
            mod->BSIM1sidewallJctPotentialGiven = TRUE;
            break;
        case  BSIM1_MOD_MJSW :
            mod->BSIM1bulkJctSideGradingCoeff = value->rValue;
            mod->BSIM1bulkJctSideGradingCoeffGiven = TRUE;
            break;
        case  BSIM1_MOD_CJ :
            mod->BSIM1unitAreaJctCap = value->rValue;
            mod->BSIM1unitAreaJctCapGiven = TRUE;
            break;
        case  BSIM1_MOD_CJSW :
            mod->BSIM1unitLengthSidewallJctCap = value->rValue;
            mod->BSIM1unitLengthSidewallJctCapGiven = TRUE;
            break;
        case  BSIM1_MOD_DEFWIDTH :
            mod->BSIM1defaultWidth = value->rValue;
            mod->BSIM1defaultWidthGiven = TRUE;
            break;
        case  BSIM1_MOD_DELLENGTH :
            mod->BSIM1deltaLength = value->rValue;
            mod->BSIM1deltaLengthGiven = TRUE;
            break;
        case  BSIM1_MOD_NMOS  :
            if(value->iValue) {
                mod->BSIM1type = 1;
                mod->BSIM1typeGiven = TRUE;
            }
            break;
        case  BSIM1_MOD_PMOS  :
            if(value->iValue) {
                mod->BSIM1type = - 1;
                mod->BSIM1typeGiven = TRUE;
            }
            break;
        default:
            return(E_BADPARM);
    }
    return(OK);
}


