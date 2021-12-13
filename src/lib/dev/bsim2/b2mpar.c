/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1988 Min-Chie Jeng, Hong J. Park, Thomas L. Quarles
**********/
/*
 */

#include "spice.h"
#include <stdio.h>
#include "util.h"
#include "bsim2def.h"
#include "ifsim.h"
#include "sperror.h"
#include "suffix.h"


int
BSIM2mParam(param,value,inMod)
    int param;
    IFvalue *value;
    GENmodel *inMod;
{
    BSIM2model *mod = (BSIM2model*)inMod;
    switch(param) {
        case  BSIM2_MOD_VFB0 :
            mod->BSIM2vfb0 = value->rValue;
            mod->BSIM2vfb0Given = TRUE;
            break;
        case  BSIM2_MOD_VFBL :
            mod->BSIM2vfbL = value->rValue;
            mod->BSIM2vfbLGiven = TRUE;
            break;
        case  BSIM2_MOD_VFBW :
            mod->BSIM2vfbW = value->rValue;
            mod->BSIM2vfbWGiven = TRUE;
            break;
        case  BSIM2_MOD_PHI0 :
            mod->BSIM2phi0 = value->rValue;
            mod->BSIM2phi0Given = TRUE;
            break;
        case  BSIM2_MOD_PHIL :
            mod->BSIM2phiL = value->rValue;
            mod->BSIM2phiLGiven = TRUE;
            break;
        case  BSIM2_MOD_PHIW :
            mod->BSIM2phiW = value->rValue;
            mod->BSIM2phiWGiven = TRUE;
            break;
        case  BSIM2_MOD_K10 :
            mod->BSIM2k10 = value->rValue;
            mod->BSIM2k10Given = TRUE;
            break;
        case  BSIM2_MOD_K1L :
            mod->BSIM2k1L = value->rValue;
            mod->BSIM2k1LGiven = TRUE;
            break;
        case  BSIM2_MOD_K1W :
            mod->BSIM2k1W = value->rValue;
            mod->BSIM2k1WGiven = TRUE;
            break;
        case  BSIM2_MOD_K20 :
            mod->BSIM2k20 = value->rValue;
            mod->BSIM2k20Given = TRUE;
            break;
        case  BSIM2_MOD_K2L :
            mod->BSIM2k2L = value->rValue;
            mod->BSIM2k2LGiven = TRUE;
            break;
        case  BSIM2_MOD_K2W :
            mod->BSIM2k2W = value->rValue;
            mod->BSIM2k2WGiven = TRUE;
            break;
        case  BSIM2_MOD_ETA00 :
            mod->BSIM2eta00 = value->rValue;
            mod->BSIM2eta00Given = TRUE;
            break;
        case  BSIM2_MOD_ETA0L :
            mod->BSIM2eta0L = value->rValue;
            mod->BSIM2eta0LGiven = TRUE;
            break;
        case  BSIM2_MOD_ETA0W :
            mod->BSIM2eta0W = value->rValue;
            mod->BSIM2eta0WGiven = TRUE;
            break;
        case  BSIM2_MOD_ETAB0 :
            mod->BSIM2etaB0 = value->rValue;
            mod->BSIM2etaB0Given = TRUE;
            break;
        case  BSIM2_MOD_ETABL :
            mod->BSIM2etaBL = value->rValue;
            mod->BSIM2etaBLGiven = TRUE;
            break;
        case  BSIM2_MOD_ETABW :
            mod->BSIM2etaBW = value->rValue;
            mod->BSIM2etaBWGiven = TRUE;
            break;
        case  BSIM2_MOD_DELTAL :
            mod->BSIM2deltaL =  value->rValue;
            mod->BSIM2deltaLGiven = TRUE;
            break;
        case  BSIM2_MOD_DELTAW :
            mod->BSIM2deltaW =  value->rValue;
            mod->BSIM2deltaWGiven = TRUE;
            break;
        case  BSIM2_MOD_MOB00 :
            mod->BSIM2mob00 = value->rValue;
            mod->BSIM2mob00Given = TRUE;
            break;
        case  BSIM2_MOD_MOB0B0 :
            mod->BSIM2mob0B0 = value->rValue;
            mod->BSIM2mob0B0Given = TRUE;
            break;
        case  BSIM2_MOD_MOB0BL :
            mod->BSIM2mob0BL = value->rValue;
            mod->BSIM2mob0BLGiven = TRUE;
            break;
        case  BSIM2_MOD_MOB0BW :
            mod->BSIM2mob0BW = value->rValue;
            mod->BSIM2mob0BWGiven = TRUE;
            break;
        case  BSIM2_MOD_MOBS00 :
            mod->BSIM2mobs00 = value->rValue;
            mod->BSIM2mobs00Given = TRUE;
            break;
        case  BSIM2_MOD_MOBS0L :
            mod->BSIM2mobs0L = value->rValue;
            mod->BSIM2mobs0LGiven = TRUE;
            break;
        case  BSIM2_MOD_MOBS0W :
            mod->BSIM2mobs0W = value->rValue;
            mod->BSIM2mobs0WGiven = TRUE;
            break;
        case  BSIM2_MOD_MOBSB0 :
            mod->BSIM2mobsB0 = value->rValue;
            mod->BSIM2mobsB0Given = TRUE;
            break;
        case  BSIM2_MOD_MOBSBL :
            mod->BSIM2mobsBL = value->rValue;
            mod->BSIM2mobsBLGiven = TRUE;
            break;
        case  BSIM2_MOD_MOBSBW :
            mod->BSIM2mobsBW = value->rValue;
            mod->BSIM2mobsBWGiven = TRUE;
            break;
        case  BSIM2_MOD_MOB200 :
            mod->BSIM2mob200 = value->rValue;
            mod->BSIM2mob200Given = TRUE;
            break;
        case  BSIM2_MOD_MOB20L :
            mod->BSIM2mob20L = value->rValue;
            mod->BSIM2mob20LGiven = TRUE;
            break;
        case  BSIM2_MOD_MOB20W :
            mod->BSIM2mob20W = value->rValue;
            mod->BSIM2mob20WGiven = TRUE;
            break;
        case  BSIM2_MOD_MOB2B0 :
            mod->BSIM2mob2B0 = value->rValue;
            mod->BSIM2mob2B0Given = TRUE;
            break;
        case  BSIM2_MOD_MOB2BL :
            mod->BSIM2mob2BL = value->rValue;
            mod->BSIM2mob2BLGiven = TRUE;
            break;
        case  BSIM2_MOD_MOB2BW :
            mod->BSIM2mob2BW = value->rValue;
            mod->BSIM2mob2BWGiven = TRUE;
            break;
        case  BSIM2_MOD_MOB2G0 :
            mod->BSIM2mob2G0 = value->rValue;
            mod->BSIM2mob2G0Given = TRUE;
            break;
        case  BSIM2_MOD_MOB2GL :
            mod->BSIM2mob2GL = value->rValue;
            mod->BSIM2mob2GLGiven = TRUE;
            break;
        case  BSIM2_MOD_MOB2GW :
            mod->BSIM2mob2GW = value->rValue;
            mod->BSIM2mob2GWGiven = TRUE;
            break;
        case  BSIM2_MOD_MOB300 :
            mod->BSIM2mob300 = value->rValue;
            mod->BSIM2mob300Given = TRUE;
            break;
        case  BSIM2_MOD_MOB30L :
            mod->BSIM2mob30L = value->rValue;
            mod->BSIM2mob30LGiven = TRUE;
            break;
        case  BSIM2_MOD_MOB30W :
            mod->BSIM2mob30W = value->rValue;
            mod->BSIM2mob30WGiven = TRUE;
            break;
        case  BSIM2_MOD_MOB3B0 :
            mod->BSIM2mob3B0 = value->rValue;
            mod->BSIM2mob3B0Given = TRUE;
            break;
        case  BSIM2_MOD_MOB3BL :
            mod->BSIM2mob3BL = value->rValue;
            mod->BSIM2mob3BLGiven = TRUE;
            break;
        case  BSIM2_MOD_MOB3BW :
            mod->BSIM2mob3BW = value->rValue;
            mod->BSIM2mob3BWGiven = TRUE;
            break;
        case  BSIM2_MOD_MOB3G0 :
            mod->BSIM2mob3G0 = value->rValue;
            mod->BSIM2mob3G0Given = TRUE;
            break;
        case  BSIM2_MOD_MOB3GL :
            mod->BSIM2mob3GL = value->rValue;
            mod->BSIM2mob3GLGiven = TRUE;
            break;
        case  BSIM2_MOD_MOB3GW :
            mod->BSIM2mob3GW = value->rValue;
            mod->BSIM2mob3GWGiven = TRUE;
            break;
        case  BSIM2_MOD_MOB400 :
            mod->BSIM2mob400 = value->rValue;
            mod->BSIM2mob400Given = TRUE;
            break;
        case  BSIM2_MOD_MOB40L :
            mod->BSIM2mob40L = value->rValue;
            mod->BSIM2mob40LGiven = TRUE;
            break;
        case  BSIM2_MOD_MOB40W :
            mod->BSIM2mob40W = value->rValue;
            mod->BSIM2mob40WGiven = TRUE;
            break;
        case  BSIM2_MOD_MOB4B0 :
            mod->BSIM2mob4B0 = value->rValue;
            mod->BSIM2mob4B0Given = TRUE;
            break;
        case  BSIM2_MOD_MOB4BL :
            mod->BSIM2mob4BL = value->rValue;
            mod->BSIM2mob4BLGiven = TRUE;
            break;
        case  BSIM2_MOD_MOB4BW :
            mod->BSIM2mob4BW = value->rValue;
            mod->BSIM2mob4BWGiven = TRUE;
            break;
        case  BSIM2_MOD_MOB4G0 :
            mod->BSIM2mob4G0 = value->rValue;
            mod->BSIM2mob4G0Given = TRUE;
            break;
        case  BSIM2_MOD_MOB4GL :
            mod->BSIM2mob4GL = value->rValue;
            mod->BSIM2mob4GLGiven = TRUE;
            break;
        case  BSIM2_MOD_MOB4GW :
            mod->BSIM2mob4GW = value->rValue;
            mod->BSIM2mob4GWGiven = TRUE;
            break;
        case  BSIM2_MOD_UA00 :
            mod->BSIM2ua00 = value->rValue;
            mod->BSIM2ua00Given = TRUE;
            break;
        case  BSIM2_MOD_UA0L :
            mod->BSIM2ua0L = value->rValue;
            mod->BSIM2ua0LGiven = TRUE;
            break;
        case  BSIM2_MOD_UA0W :
            mod->BSIM2ua0W = value->rValue;
            mod->BSIM2ua0WGiven = TRUE;
            break;
        case  BSIM2_MOD_UAB0 :
            mod->BSIM2uaB0 = value->rValue;
            mod->BSIM2uaB0Given = TRUE;
            break;
        case  BSIM2_MOD_UABL :
            mod->BSIM2uaBL = value->rValue;
            mod->BSIM2uaBLGiven = TRUE;
            break;
        case  BSIM2_MOD_UABW :
            mod->BSIM2uaBW = value->rValue;
            mod->BSIM2uaBWGiven = TRUE;
            break;
        case  BSIM2_MOD_UB00 :
            mod->BSIM2ub00 = value->rValue;
            mod->BSIM2ub00Given = TRUE;
            break;
        case  BSIM2_MOD_UB0L :
            mod->BSIM2ub0L = value->rValue;
            mod->BSIM2ub0LGiven = TRUE;
            break;
        case  BSIM2_MOD_UB0W :
            mod->BSIM2ub0W = value->rValue;
            mod->BSIM2ub0WGiven = TRUE;
            break;
        case  BSIM2_MOD_UBB0 :
            mod->BSIM2ubB0 = value->rValue;
            mod->BSIM2ubB0Given = TRUE;
            break;
        case  BSIM2_MOD_UBBL :
            mod->BSIM2ubBL = value->rValue;
            mod->BSIM2ubBLGiven = TRUE;
            break;
        case  BSIM2_MOD_UBBW :
            mod->BSIM2ubBW = value->rValue;
            mod->BSIM2ubBWGiven = TRUE;
            break;
        case  BSIM2_MOD_U100 :
            mod->BSIM2u100 = value->rValue;
            mod->BSIM2u100Given = TRUE;
            break;
        case  BSIM2_MOD_U10L :
            mod->BSIM2u10L = value->rValue;
            mod->BSIM2u10LGiven = TRUE;
            break;
        case  BSIM2_MOD_U10W :
            mod->BSIM2u10W = value->rValue;
            mod->BSIM2u10WGiven = TRUE;
            break;
        case  BSIM2_MOD_U1B0 :
            mod->BSIM2u1B0 = value->rValue;
            mod->BSIM2u1B0Given = TRUE;
            break;
        case  BSIM2_MOD_U1BL :
            mod->BSIM2u1BL = value->rValue;
            mod->BSIM2u1BLGiven = TRUE;
            break;
        case  BSIM2_MOD_U1BW :
            mod->BSIM2u1BW = value->rValue;
            mod->BSIM2u1BWGiven = TRUE;
            break;
        case  BSIM2_MOD_U1D0 :
            mod->BSIM2u1D0 = value->rValue;
            mod->BSIM2u1D0Given = TRUE;
            break;
        case  BSIM2_MOD_U1DL :
            mod->BSIM2u1DL = value->rValue;
            mod->BSIM2u1DLGiven = TRUE;
            break;
        case  BSIM2_MOD_U1DW :
            mod->BSIM2u1DW = value->rValue;
            mod->BSIM2u1DWGiven = TRUE;
            break;
        case  BSIM2_MOD_N00 :
            mod->BSIM2n00 = value->rValue;
            mod->BSIM2n00Given = TRUE;
            break;
        case  BSIM2_MOD_N0L :
            mod->BSIM2n0L = value->rValue;
            mod->BSIM2n0LGiven = TRUE;
            break;
        case  BSIM2_MOD_N0W :
            mod->BSIM2n0W = value->rValue;
            mod->BSIM2n0WGiven = TRUE;
            break;
        case  BSIM2_MOD_NB0 :
            mod->BSIM2nB0 = value->rValue;
            mod->BSIM2nB0Given = TRUE;
            break;
        case  BSIM2_MOD_NBL :
            mod->BSIM2nBL = value->rValue;
            mod->BSIM2nBLGiven = TRUE;
            break;
        case  BSIM2_MOD_NBW :
            mod->BSIM2nBW = value->rValue;
            mod->BSIM2nBWGiven = TRUE;
            break;
        case  BSIM2_MOD_ND0 :
            mod->BSIM2nD0 = value->rValue;
            mod->BSIM2nD0Given = TRUE;
            break;
        case  BSIM2_MOD_NDL :
            mod->BSIM2nDL = value->rValue;
            mod->BSIM2nDLGiven = TRUE;
            break;
        case  BSIM2_MOD_NDW :
            mod->BSIM2nDW = value->rValue;
            mod->BSIM2nDWGiven = TRUE;
            break;
        case  BSIM2_MOD_VOF00 :
            mod->BSIM2vof00 = value->rValue;
            mod->BSIM2vof00Given = TRUE;
            break;
        case  BSIM2_MOD_VOF0L :
            mod->BSIM2vof0L = value->rValue;
            mod->BSIM2vof0LGiven = TRUE;
            break;
        case  BSIM2_MOD_VOF0W :
            mod->BSIM2vof0W = value->rValue;
            mod->BSIM2vof0WGiven = TRUE;
            break;
        case  BSIM2_MOD_VOFB0 :
            mod->BSIM2vofB0 = value->rValue;
            mod->BSIM2vofB0Given = TRUE;
            break;
        case  BSIM2_MOD_VOFBL :
            mod->BSIM2vofBL = value->rValue;
            mod->BSIM2vofBLGiven = TRUE;
            break;
        case  BSIM2_MOD_VOFBW :
            mod->BSIM2vofBW = value->rValue;
            mod->BSIM2vofBWGiven = TRUE;
            break;
        case  BSIM2_MOD_VOFD0 :
            mod->BSIM2vofD0 = value->rValue;
            mod->BSIM2vofD0Given = TRUE;
            break;
        case  BSIM2_MOD_VOFDL :
            mod->BSIM2vofDL = value->rValue;
            mod->BSIM2vofDLGiven = TRUE;
            break;
        case  BSIM2_MOD_VOFDW :
            mod->BSIM2vofDW = value->rValue;
            mod->BSIM2vofDWGiven = TRUE;
            break;
        case  BSIM2_MOD_AI00 :
            mod->BSIM2ai00 = value->rValue;
            mod->BSIM2ai00Given = TRUE;
            break;
        case  BSIM2_MOD_AI0L :
            mod->BSIM2ai0L = value->rValue;
            mod->BSIM2ai0LGiven = TRUE;
            break;
        case  BSIM2_MOD_AI0W :
            mod->BSIM2ai0W = value->rValue;
            mod->BSIM2ai0WGiven = TRUE;
            break;
        case  BSIM2_MOD_AIB0 :
            mod->BSIM2aiB0 = value->rValue;
            mod->BSIM2aiB0Given = TRUE;
            break;
        case  BSIM2_MOD_AIBL :
            mod->BSIM2aiBL = value->rValue;
            mod->BSIM2aiBLGiven = TRUE;
            break;
        case  BSIM2_MOD_AIBW :
            mod->BSIM2aiBW = value->rValue;
            mod->BSIM2aiBWGiven = TRUE;
            break;
        case  BSIM2_MOD_BI00 :
            mod->BSIM2bi00 = value->rValue;
            mod->BSIM2bi00Given = TRUE;
            break;
        case  BSIM2_MOD_BI0L :
            mod->BSIM2bi0L = value->rValue;
            mod->BSIM2bi0LGiven = TRUE;
            break;
        case  BSIM2_MOD_BI0W :
            mod->BSIM2bi0W = value->rValue;
            mod->BSIM2bi0WGiven = TRUE;
            break;
        case  BSIM2_MOD_BIB0 :
            mod->BSIM2biB0 = value->rValue;
            mod->BSIM2biB0Given = TRUE;
            break;
        case  BSIM2_MOD_BIBL :
            mod->BSIM2biBL = value->rValue;
            mod->BSIM2biBLGiven = TRUE;
            break;
        case  BSIM2_MOD_BIBW :
            mod->BSIM2biBW = value->rValue;
            mod->BSIM2biBWGiven = TRUE;
            break;
        case  BSIM2_MOD_VGHIGH0 :
            mod->BSIM2vghigh0 = value->rValue;
            mod->BSIM2vghigh0Given = TRUE;
            break;
        case  BSIM2_MOD_VGHIGHL :
            mod->BSIM2vghighL = value->rValue;
            mod->BSIM2vghighLGiven = TRUE;
            break;
        case  BSIM2_MOD_VGHIGHW :
            mod->BSIM2vghighW = value->rValue;
            mod->BSIM2vghighWGiven = TRUE;
            break;
        case  BSIM2_MOD_VGLOW0 :
            mod->BSIM2vglow0 = value->rValue;
            mod->BSIM2vglow0Given = TRUE;
            break;
        case  BSIM2_MOD_VGLOWL :
            mod->BSIM2vglowL = value->rValue;
            mod->BSIM2vglowLGiven = TRUE;
            break;
        case  BSIM2_MOD_VGLOWW :
            mod->BSIM2vglowW = value->rValue;
            mod->BSIM2vglowWGiven = TRUE;
            break;
        case  BSIM2_MOD_TOX :
            mod->BSIM2tox = value->rValue;
            mod->BSIM2toxGiven = TRUE;
            break;
        case  BSIM2_MOD_TEMP :
            mod->BSIM2temp = value->rValue;
            mod->BSIM2tempGiven = TRUE;
            break;
        case  BSIM2_MOD_VDD :
            mod->BSIM2vdd = value->rValue;
            mod->BSIM2vddGiven = TRUE;
            break;
        case  BSIM2_MOD_VGG :
            mod->BSIM2vgg = value->rValue;
            mod->BSIM2vggGiven = TRUE;
            break;
        case  BSIM2_MOD_VBB :
            mod->BSIM2vbb = value->rValue;
            mod->BSIM2vbbGiven = TRUE;
            break;
        case  BSIM2_MOD_CGSO :
            mod->BSIM2gateSourceOverlapCap = value->rValue;
            mod->BSIM2gateSourceOverlapCapGiven = TRUE;
            break;
        case  BSIM2_MOD_CGDO :
            mod->BSIM2gateDrainOverlapCap = value->rValue;
            mod->BSIM2gateDrainOverlapCapGiven = TRUE;
            break;
        case  BSIM2_MOD_CGBO :
            mod->BSIM2gateBulkOverlapCap = value->rValue;
            mod->BSIM2gateBulkOverlapCapGiven = TRUE;
            break;
        case  BSIM2_MOD_XPART :
            mod->BSIM2channelChargePartitionFlag = value->rValue;
            mod->BSIM2channelChargePartitionFlagGiven = TRUE;
            break;
        case  BSIM2_MOD_RSH :
            mod->BSIM2sheetResistance = value->rValue;
            mod->BSIM2sheetResistanceGiven = TRUE;
            break;
        case  BSIM2_MOD_JS :
            mod->BSIM2jctSatCurDensity = value->rValue;
            mod->BSIM2jctSatCurDensityGiven = TRUE;
            break;
        case  BSIM2_MOD_PB :
            mod->BSIM2bulkJctPotential = value->rValue;
            mod->BSIM2bulkJctPotentialGiven = TRUE;
            break;
        case  BSIM2_MOD_MJ :
            mod->BSIM2bulkJctBotGradingCoeff = value->rValue;
            mod->BSIM2bulkJctBotGradingCoeffGiven = TRUE;
            break;
        case  BSIM2_MOD_PBSW :
            mod->BSIM2sidewallJctPotential = value->rValue;
            mod->BSIM2sidewallJctPotentialGiven = TRUE;
            break;
        case  BSIM2_MOD_MJSW :
            mod->BSIM2bulkJctSideGradingCoeff = value->rValue;
            mod->BSIM2bulkJctSideGradingCoeffGiven = TRUE;
            break;
        case  BSIM2_MOD_CJ :
            mod->BSIM2unitAreaJctCap = value->rValue;
            mod->BSIM2unitAreaJctCapGiven = TRUE;
            break;
        case  BSIM2_MOD_CJSW :
            mod->BSIM2unitLengthSidewallJctCap = value->rValue;
            mod->BSIM2unitLengthSidewallJctCapGiven = TRUE;
            break;
        case  BSIM2_MOD_DEFWIDTH :
            mod->BSIM2defaultWidth = value->rValue;
            mod->BSIM2defaultWidthGiven = TRUE;
            break;
        case  BSIM2_MOD_DELLENGTH :
            mod->BSIM2deltaLength = value->rValue;
            mod->BSIM2deltaLengthGiven = TRUE;
            break;
        case  BSIM2_MOD_NMOS  :
            if(value->iValue) {
                mod->BSIM2type = 1;
                mod->BSIM2typeGiven = TRUE;
            }
            break;
        case  BSIM2_MOD_PMOS  :
            if(value->iValue) {
                mod->BSIM2type = - 1;
                mod->BSIM2typeGiven = TRUE;
            }
            break;
        default:
            return(E_BADPARM);
    }
    return(OK);
}
