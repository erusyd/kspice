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
#include "bsim2def.h"
#include "sperror.h"
#include "suffix.h"


/*ARGSUSED*/
int
BSIM2mAsk(ckt,inst,which,value)
    CKTcircuit *ckt;
    GENmodel *inst;
    int which;
    IFvalue *value;
{
    BSIM2model *model = (BSIM2model *)inst;
        switch(which) {
        case BSIM2_MOD_VFB0: 
            value->rValue = model->BSIM2vfb0; 
            return(OK);
        case  BSIM2_MOD_VFBL :
          value->rValue = model->BSIM2vfbL;
            return(OK);
        case  BSIM2_MOD_VFBW :
          value->rValue = model->BSIM2vfbW;
            return(OK);
        case  BSIM2_MOD_PHI0 :
          value->rValue = model->BSIM2phi0;
            return(OK);
        case  BSIM2_MOD_PHIL :
          value->rValue = model->BSIM2phiL;
            return(OK);
        case  BSIM2_MOD_PHIW :
          value->rValue = model->BSIM2phiW;
            return(OK);
        case  BSIM2_MOD_K10 :
          value->rValue = model->BSIM2k10;
            return(OK);
        case  BSIM2_MOD_K1L :
          value->rValue = model->BSIM2k1L;
            return(OK);
        case  BSIM2_MOD_K1W :
          value->rValue = model->BSIM2k1W;
            return(OK);
        case  BSIM2_MOD_K20 :
          value->rValue = model->BSIM2k20;
            return(OK);
        case  BSIM2_MOD_K2L :
          value->rValue = model->BSIM2k2L;
            return(OK);
        case  BSIM2_MOD_K2W :
          value->rValue = model->BSIM2k2W;
            return(OK);
        case  BSIM2_MOD_ETA00 :
          value->rValue = model->BSIM2eta00;
            return(OK);
        case  BSIM2_MOD_ETA0L :
          value->rValue = model->BSIM2eta0L;
            return(OK);
        case  BSIM2_MOD_ETA0W :
          value->rValue = model->BSIM2eta0W;
            return(OK);
        case  BSIM2_MOD_ETAB0 :
          value->rValue = model->BSIM2etaB0;
            return(OK);
        case  BSIM2_MOD_ETABL :
          value->rValue = model->BSIM2etaBL;
            return(OK);
        case  BSIM2_MOD_ETABW :
          value->rValue = model->BSIM2etaBW;
            return(OK);
        case  BSIM2_MOD_DELTAL :
          value->rValue = model->BSIM2deltaL =  value->rValue;
            return(OK);
        case  BSIM2_MOD_DELTAW :
          value->rValue = model->BSIM2deltaW =  value->rValue;
            return(OK);
        case  BSIM2_MOD_MOB00 :
          value->rValue = model->BSIM2mob00;
            return(OK);
        case  BSIM2_MOD_MOB0B0 :
          value->rValue = model->BSIM2mob0B0;
            return(OK);
        case  BSIM2_MOD_MOB0BL :
          value->rValue = model->BSIM2mob0BL;
            return(OK);
        case  BSIM2_MOD_MOB0BW :
          value->rValue = model->BSIM2mob0BW;
            return(OK);
        case  BSIM2_MOD_MOBS00 :
          value->rValue = model->BSIM2mobs00;
            return(OK);
        case  BSIM2_MOD_MOBS0L :
          value->rValue = model->BSIM2mobs0L;
            return(OK);
        case  BSIM2_MOD_MOBS0W :
          value->rValue = model->BSIM2mobs0W;
            return(OK);
        case  BSIM2_MOD_MOBSB0 :
          value->rValue = model->BSIM2mobsB0;
            return(OK);
        case  BSIM2_MOD_MOBSBL :
          value->rValue = model->BSIM2mobsBL;
            return(OK);
        case  BSIM2_MOD_MOBSBW :
          value->rValue = model->BSIM2mobsBW;
            return(OK);
        case  BSIM2_MOD_MOB200 :
          value->rValue = model->BSIM2mob200;
            return(OK);
        case  BSIM2_MOD_MOB20L :
          value->rValue = model->BSIM2mob20L;
            return(OK);
        case  BSIM2_MOD_MOB20W :
          value->rValue = model->BSIM2mob20W;
            return(OK);
        case  BSIM2_MOD_MOB2B0 :
          value->rValue = model->BSIM2mob2B0;
            return(OK);
        case  BSIM2_MOD_MOB2BL :
          value->rValue = model->BSIM2mob2BL;
            return(OK);
        case  BSIM2_MOD_MOB2BW :
          value->rValue = model->BSIM2mob2BW;
            return(OK);
        case  BSIM2_MOD_MOB2G0 :
          value->rValue = model->BSIM2mob2G0;
            return(OK);
        case  BSIM2_MOD_MOB2GL :
          value->rValue = model->BSIM2mob2GL;
            return(OK);
        case  BSIM2_MOD_MOB2GW :
          value->rValue = model->BSIM2mob2GW;
            return(OK);
        case  BSIM2_MOD_MOB300 :
          value->rValue = model->BSIM2mob300;
            return(OK);
        case  BSIM2_MOD_MOB30L :
          value->rValue = model->BSIM2mob30L;
            return(OK);
        case  BSIM2_MOD_MOB30W :
          value->rValue = model->BSIM2mob30W;
            return(OK);
        case  BSIM2_MOD_MOB3B0 :
          value->rValue = model->BSIM2mob3B0;
            return(OK);
        case  BSIM2_MOD_MOB3BL :
          value->rValue = model->BSIM2mob3BL;
            return(OK);
        case  BSIM2_MOD_MOB3BW :
          value->rValue = model->BSIM2mob3BW;
            return(OK);
        case  BSIM2_MOD_MOB3G0 :
          value->rValue = model->BSIM2mob3G0;
            return(OK);
        case  BSIM2_MOD_MOB3GL :
          value->rValue = model->BSIM2mob3GL;
            return(OK);
        case  BSIM2_MOD_MOB3GW :
          value->rValue = model->BSIM2mob3GW;
            return(OK);
        case  BSIM2_MOD_MOB400 :
          value->rValue = model->BSIM2mob400;
            return(OK);
        case  BSIM2_MOD_MOB40L :
          value->rValue = model->BSIM2mob40L;
            return(OK);
        case  BSIM2_MOD_MOB40W :
          value->rValue = model->BSIM2mob40W;
            return(OK);
        case  BSIM2_MOD_MOB4B0 :
          value->rValue = model->BSIM2mob4B0;
            return(OK);
        case  BSIM2_MOD_MOB4BL :
          value->rValue = model->BSIM2mob4BL;
            return(OK);
        case  BSIM2_MOD_MOB4BW :
          value->rValue = model->BSIM2mob4BW;
            return(OK);
        case  BSIM2_MOD_MOB4G0 :
          value->rValue = model->BSIM2mob4G0;
            return(OK);
        case  BSIM2_MOD_MOB4GL :
          value->rValue = model->BSIM2mob4GL;
            return(OK);
        case  BSIM2_MOD_MOB4GW :
          value->rValue = model->BSIM2mob4GW;
            return(OK);
        case  BSIM2_MOD_UA00 :
          value->rValue = model->BSIM2ua00;
            return(OK);
        case  BSIM2_MOD_UA0L :
          value->rValue = model->BSIM2ua0L;
            return(OK);
        case  BSIM2_MOD_UA0W :
          value->rValue = model->BSIM2ua0W;
            return(OK);
        case  BSIM2_MOD_UAB0 :
          value->rValue = model->BSIM2uaB0;
            return(OK);
        case  BSIM2_MOD_UABL :
          value->rValue = model->BSIM2uaBL;
            return(OK);
        case  BSIM2_MOD_UABW :
          value->rValue = model->BSIM2uaBW;
            return(OK);
        case  BSIM2_MOD_UB00 :
          value->rValue = model->BSIM2ub00;
            return(OK);
        case  BSIM2_MOD_UB0L :
          value->rValue = model->BSIM2ub0L;
            return(OK);
        case  BSIM2_MOD_UB0W :
          value->rValue = model->BSIM2ub0W;
            return(OK);
        case  BSIM2_MOD_UBB0 :
          value->rValue = model->BSIM2ubB0;
            return(OK);
        case  BSIM2_MOD_UBBL :
          value->rValue = model->BSIM2ubBL;
            return(OK);
        case  BSIM2_MOD_UBBW :
          value->rValue = model->BSIM2ubBW;
            return(OK);
        case  BSIM2_MOD_U100 :
          value->rValue = model->BSIM2u100;
            return(OK);
        case  BSIM2_MOD_U10L :
          value->rValue = model->BSIM2u10L;
            return(OK);
        case  BSIM2_MOD_U10W :
          value->rValue = model->BSIM2u10W;
            return(OK);
        case  BSIM2_MOD_U1B0 :
          value->rValue = model->BSIM2u1B0;
            return(OK);
        case  BSIM2_MOD_U1BL :
          value->rValue = model->BSIM2u1BL;
            return(OK);
        case  BSIM2_MOD_U1BW :
          value->rValue = model->BSIM2u1BW;
            return(OK);
        case  BSIM2_MOD_U1D0 :
          value->rValue = model->BSIM2u1D0;
            return(OK);
        case  BSIM2_MOD_U1DL :
          value->rValue = model->BSIM2u1DL;
            return(OK);
        case  BSIM2_MOD_U1DW :
          value->rValue = model->BSIM2u1DW;
            return(OK);
        case  BSIM2_MOD_N00 :
          value->rValue = model->BSIM2n00;
            return(OK);
        case  BSIM2_MOD_N0L :
          value->rValue = model->BSIM2n0L;
            return(OK);
        case  BSIM2_MOD_N0W :
          value->rValue = model->BSIM2n0W;
            return(OK);
        case  BSIM2_MOD_NB0 :
          value->rValue = model->BSIM2nB0;
            return(OK);
        case  BSIM2_MOD_NBL :
          value->rValue = model->BSIM2nBL;
            return(OK);
        case  BSIM2_MOD_NBW :
          value->rValue = model->BSIM2nBW;
            return(OK);
        case  BSIM2_MOD_ND0 :
          value->rValue = model->BSIM2nD0;
            return(OK);
        case  BSIM2_MOD_NDL :
          value->rValue = model->BSIM2nDL;
            return(OK);
        case  BSIM2_MOD_NDW :
          value->rValue = model->BSIM2nDW;
            return(OK);
        case  BSIM2_MOD_VOF00 :
          value->rValue = model->BSIM2vof00;
            return(OK);
        case  BSIM2_MOD_VOF0L :
          value->rValue = model->BSIM2vof0L;
            return(OK);
        case  BSIM2_MOD_VOF0W :
          value->rValue = model->BSIM2vof0W;
            return(OK);
        case  BSIM2_MOD_VOFB0 :
          value->rValue = model->BSIM2vofB0;
            return(OK);
        case  BSIM2_MOD_VOFBL :
          value->rValue = model->BSIM2vofBL;
            return(OK);
        case  BSIM2_MOD_VOFBW :
          value->rValue = model->BSIM2vofBW;
            return(OK);
        case  BSIM2_MOD_VOFD0 :
          value->rValue = model->BSIM2vofD0;
            return(OK);
        case  BSIM2_MOD_VOFDL :
          value->rValue = model->BSIM2vofDL;
            return(OK);
        case  BSIM2_MOD_VOFDW :
          value->rValue = model->BSIM2vofDW;
            return(OK);
        case  BSIM2_MOD_AI00 :
          value->rValue = model->BSIM2ai00;
            return(OK);
        case  BSIM2_MOD_AI0L :
          value->rValue = model->BSIM2ai0L;
            return(OK);
        case  BSIM2_MOD_AI0W :
          value->rValue = model->BSIM2ai0W;
            return(OK);
        case  BSIM2_MOD_AIB0 :
          value->rValue = model->BSIM2aiB0;
            return(OK);
        case  BSIM2_MOD_AIBL :
          value->rValue = model->BSIM2aiBL;
            return(OK);
        case  BSIM2_MOD_AIBW :
          value->rValue = model->BSIM2aiBW;
            return(OK);
        case  BSIM2_MOD_BI00 :
          value->rValue = model->BSIM2bi00;
            return(OK);
        case  BSIM2_MOD_BI0L :
          value->rValue = model->BSIM2bi0L;
            return(OK);
        case  BSIM2_MOD_BI0W :
          value->rValue = model->BSIM2bi0W;
            return(OK);
        case  BSIM2_MOD_BIB0 :
          value->rValue = model->BSIM2biB0;
            return(OK);
        case  BSIM2_MOD_BIBL :
          value->rValue = model->BSIM2biBL;
            return(OK);
        case  BSIM2_MOD_BIBW :
          value->rValue = model->BSIM2biBW;
            return(OK);
        case  BSIM2_MOD_VGHIGH0 :
          value->rValue = model->BSIM2vghigh0;
            return(OK);
        case  BSIM2_MOD_VGHIGHL :
          value->rValue = model->BSIM2vghighL;
            return(OK);
        case  BSIM2_MOD_VGHIGHW :
          value->rValue = model->BSIM2vghighW;
            return(OK);
        case  BSIM2_MOD_VGLOW0 :
          value->rValue = model->BSIM2vglow0;
            return(OK);
        case  BSIM2_MOD_VGLOWL :
          value->rValue = model->BSIM2vglowL;
            return(OK);
        case  BSIM2_MOD_VGLOWW :
          value->rValue = model->BSIM2vglowW;
            return(OK);
        case  BSIM2_MOD_TOX :
          value->rValue = model->BSIM2tox;
            return(OK);
        case  BSIM2_MOD_TEMP :
          value->rValue = model->BSIM2temp;
            return(OK);
        case  BSIM2_MOD_VDD :
          value->rValue = model->BSIM2vdd;
            return(OK);
        case  BSIM2_MOD_VGG :
          value->rValue = model->BSIM2vgg;
            return(OK);
        case  BSIM2_MOD_VBB :
          value->rValue = model->BSIM2vbb;
            return(OK);
        case BSIM2_MOD_CGSO:
            value->rValue = model->BSIM2gateSourceOverlapCap; 
            return(OK);
        case BSIM2_MOD_CGDO:
            value->rValue = model->BSIM2gateDrainOverlapCap; 
            return(OK);
        case BSIM2_MOD_CGBO:
            value->rValue = model->BSIM2gateBulkOverlapCap; 
            return(OK);
        case BSIM2_MOD_XPART:
            value->rValue = model->BSIM2channelChargePartitionFlag; 
            return(OK);
        case BSIM2_MOD_RSH:
            value->rValue = model->BSIM2sheetResistance; 
            return(OK);
        case BSIM2_MOD_JS:
            value->rValue = model->BSIM2jctSatCurDensity; 
            return(OK);
        case BSIM2_MOD_PB:
            value->rValue = model->BSIM2bulkJctPotential; 
            return(OK);
        case BSIM2_MOD_MJ:
            value->rValue = model->BSIM2bulkJctBotGradingCoeff; 
            return(OK);
        case BSIM2_MOD_PBSW:
            value->rValue = model->BSIM2sidewallJctPotential; 
            return(OK);
        case BSIM2_MOD_MJSW:
            value->rValue = model->BSIM2bulkJctSideGradingCoeff; 
            return(OK);
        case BSIM2_MOD_CJ:
            value->rValue = model->BSIM2unitAreaJctCap; 
            return(OK);
        case BSIM2_MOD_CJSW:
            value->rValue = model->BSIM2unitLengthSidewallJctCap; 
            return(OK);
        case BSIM2_MOD_DEFWIDTH:
            value->rValue = model->BSIM2defaultWidth; 
            return(OK);
        case BSIM2_MOD_DELLENGTH:
            value->rValue = model->BSIM2deltaLength; 
            return(OK);
        default:
            return(E_BADPARM);
    }
    /* NOTREACHED */
}


