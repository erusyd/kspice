/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Hong J. Park, Thomas L. Quarles
**********/
/*
 */

#include "spice.h"
#include <stdio.h>
#include <math.h>
#include "smpdefs.h"
#include "cktdefs.h"
#include "bsim2def.h"
#include "util.h"
#include "const.h"
#include "sperror.h"
#include "suffix.h"


/* ARGSUSED */
int
BSIM2temp(inModel,ckt)
    GENmodel *inModel;
    CKTcircuit *ckt;
        /* load the BSIM2 device structure with those pointers needed later 
         * for fast matrix loading 
         */

{
    register BSIM2model *model = (BSIM2model*) inModel;
    register BSIM2instance *here;
    register struct bsim2SizeDependParam *pSizeDependParamKnot, *pLastKnot;
    double  EffectiveLength;
    double EffectiveWidth;
    double CoxWoverL, Inv_L, Inv_W, tmp;
    int Size_Not_Found;

    /*  loop through all the BSIM2 device models */
    for( ; model != NULL; model = model->BSIM2nextModel ) {
    
/* Default value Processing for BSIM2 MOSFET Models */
        /* Some Limiting for Model Parameters */
        if( model->BSIM2bulkJctPotential < 0.1)  {
            model->BSIM2bulkJctPotential = 0.1;
        }
        if( model->BSIM2sidewallJctPotential < 0.1)  {
            model->BSIM2sidewallJctPotential = 0.1;
        }

        model->BSIM2Cox = 3.453e-13/(model->BSIM2tox * 1.0e-4);/*in F/cm**2 */
	model->BSIM2vdd2 = 2.0 * model->BSIM2vdd;
	model->BSIM2vgg2 = 2.0 * model->BSIM2vgg;
	model->BSIM2vbb2 = 2.0 * model->BSIM2vbb;
	model->BSIM2Vtm = 8.625e-5 * (model->BSIM2temp + 273.0);
	model->pSizeDependParamKnot = NULL;
	pLastKnot = NULL;

        /* loop through all the instances of the model */
        for (here = model->BSIM2instances; here != NULL ;
                here=here->BSIM2nextInstance) {

	    pSizeDependParamKnot = model->pSizeDependParamKnot;
	    Size_Not_Found = 1;

	    while ((pSizeDependParamKnot != NULL) && Size_Not_Found)
	    {   if ((here->BSIM2l == pSizeDependParamKnot->Length)
		    && (here->BSIM2w == pSizeDependParamKnot->Width))
                {   Size_Not_Found = 0;
		    here->pParam = pSizeDependParamKnot;
		}
		else
		{   pLastKnot = pSizeDependParamKnot;
		    pSizeDependParamKnot = pSizeDependParamKnot->pNext;
		}
            }

	    if (Size_Not_Found)
	    {   here->pParam = (struct bsim2SizeDependParam *)malloc(
	                        sizeof(struct bsim2SizeDependParam));
                if (pLastKnot == NULL)
		    model->pSizeDependParamKnot = here->pParam;
                else
		    pLastKnot->pNext = here->pParam;
                here->pParam->pNext = NULL;

		EffectiveLength = here->BSIM2l - model->BSIM2deltaL * 1.0e-6;
		EffectiveWidth = here->BSIM2w - model->BSIM2deltaW * 1.0e-6;

                if(EffectiveLength<=0)
		{  IFuid namarray[2];
                   namarray[0] = model->BSIM2modName;
                   namarray[1] = here->BSIM2name;
                   (*(SPfrontEnd->IFerror))(ERR_FATAL,
                    "BSIM2: mosfet %s, model %s: Effective channel length <=0",
                    namarray);
                   return(E_BADPARM);
                }

                if(EffectiveWidth <= 0)
		{  IFuid namarray[2];
                   namarray[0] = model->BSIM2modName;
                   namarray[1] = here->BSIM2name;
                   (*(SPfrontEnd->IFerror))(ERR_FATAL,
                    "BSIM2: mosfet %s, model %s: Effective channel width <=0",
                    namarray);
                   return(E_BADPARM);
                }

		Inv_L = 1.0e-6 / EffectiveLength;
		Inv_W = 1.0e-6 / EffectiveWidth;
		here->pParam->Width = here->BSIM2w;
		here->pParam->Length = here->BSIM2l;
                here->pParam->BSIM2vfb = model->BSIM2vfb0 + model->BSIM2vfbW * Inv_W
			       + model->BSIM2vfbL * Inv_L;
                here->pParam->BSIM2phi = model->BSIM2phi0 + model->BSIM2phiW * Inv_W
			       + model->BSIM2phiL * Inv_L;
                here->pParam->BSIM2k1 = model->BSIM2k10 + model->BSIM2k1W * Inv_W
			       + model->BSIM2k1L * Inv_L;
                here->pParam->BSIM2k2 = model->BSIM2k20 + model->BSIM2k2W * Inv_W
			       + model->BSIM2k2L * Inv_L;
                here->pParam->BSIM2eta0 = model->BSIM2eta00 
			       + model->BSIM2eta0W * Inv_W
			       + model->BSIM2eta0L * Inv_L;
                here->pParam->BSIM2etaB = model->BSIM2etaB0 + model->BSIM2etaBW 
			       * Inv_W + model->BSIM2etaBL * Inv_L;
                here->pParam->BSIM2beta0 = model->BSIM2mob00;
                here->pParam->BSIM2beta0B = model->BSIM2mob0B0 
			       + model->BSIM2mob0BW * Inv_W
			       + model->BSIM2mob0BL * Inv_L;
                here->pParam->BSIM2betas0 = model->BSIM2mobs00 
			       + model->BSIM2mobs0W * Inv_W
			       + model->BSIM2mobs0L * Inv_L;
                if (here->pParam->BSIM2betas0 < 1.01 * here->pParam->BSIM2beta0)
	            here->pParam->BSIM2betas0 = 1.01 * here->pParam->BSIM2beta0;
                here->pParam->BSIM2betasB = model->BSIM2mobsB0 
			       + model->BSIM2mobsBW * Inv_W
			       + model->BSIM2mobsBL * Inv_L;
                tmp = (here->pParam->BSIM2betas0 - here->pParam->BSIM2beta0
		               - here->pParam->BSIM2beta0B * model->BSIM2vbb);
                if ((-here->pParam->BSIM2betasB * model->BSIM2vbb) > tmp)
	            here->pParam->BSIM2betasB = -tmp / model->BSIM2vbb;
                here->pParam->BSIM2beta20 = model->BSIM2mob200 
			      + model->BSIM2mob20W * Inv_W
			      + model->BSIM2mob20L * Inv_L;
                here->pParam->BSIM2beta2B = model->BSIM2mob2B0 
			      + model->BSIM2mob2BW * Inv_W
			      + model->BSIM2mob2BL * Inv_L;
                here->pParam->BSIM2beta2G = model->BSIM2mob2G0 
			      + model->BSIM2mob2GW * Inv_W
			      + model->BSIM2mob2GL * Inv_L;
                here->pParam->BSIM2beta30 = model->BSIM2mob300 
			      + model->BSIM2mob30W * Inv_W
			      + model->BSIM2mob30L * Inv_L;
                here->pParam->BSIM2beta3B = model->BSIM2mob3B0 
			      + model->BSIM2mob3BL * Inv_W
			      + model->BSIM2mob3BL * Inv_L;
                here->pParam->BSIM2beta3G = model->BSIM2mob3G0 
			      + model->BSIM2mob3GW * Inv_W
			      + model->BSIM2mob3GL * Inv_L;
                here->pParam->BSIM2beta40 = model->BSIM2mob400 
			      + model->BSIM2mob40W * Inv_W
			      + model->BSIM2mob40L * Inv_L;
                here->pParam->BSIM2beta4B = model->BSIM2mob4B0 
			      + model->BSIM2mob4BW * Inv_W
			      + model->BSIM2mob4BL * Inv_L;
                here->pParam->BSIM2beta4G = model->BSIM2mob4G0 
			      + model->BSIM2mob4GW * Inv_W
			      + model->BSIM2mob4GL * Inv_L;

		CoxWoverL = model->BSIM2Cox * EffectiveWidth / EffectiveLength;

	        here->pParam->BSIM2beta0 *= CoxWoverL;
	        here->pParam->BSIM2beta0B *= CoxWoverL;
	        here->pParam->BSIM2betas0 *= CoxWoverL;
	        here->pParam->BSIM2betasB *= CoxWoverL;
	        here->pParam->BSIM2beta30 *= CoxWoverL;
	        here->pParam->BSIM2beta3B *= CoxWoverL;
	        here->pParam->BSIM2beta3G *= CoxWoverL;
	        here->pParam->BSIM2beta40 *= CoxWoverL;
	        here->pParam->BSIM2beta4B *= CoxWoverL;
	        here->pParam->BSIM2beta4G *= CoxWoverL;

                here->pParam->BSIM2ua0 = model->BSIM2ua00 + model->BSIM2ua0W * Inv_W
			       + model->BSIM2ua0L * Inv_L;
                here->pParam->BSIM2uaB = model->BSIM2uaB0 + model->BSIM2uaBW * Inv_W
			       + model->BSIM2uaBL * Inv_L;
                here->pParam->BSIM2ub0 = model->BSIM2ub00 + model->BSIM2ub0W * Inv_W
			       + model->BSIM2ub0L * Inv_L;
                here->pParam->BSIM2ubB = model->BSIM2ubB0 + model->BSIM2ubBW * Inv_W
			       + model->BSIM2ubBL * Inv_L;
                here->pParam->BSIM2u10 = model->BSIM2u100 + model->BSIM2u10W * Inv_W
			       + model->BSIM2u10L * Inv_L;
                here->pParam->BSIM2u1B = model->BSIM2u1B0 + model->BSIM2u1BW * Inv_W
			       + model->BSIM2u1BL * Inv_L;
                here->pParam->BSIM2u1D = model->BSIM2u1D0 + model->BSIM2u1DW * Inv_W
			       + model->BSIM2u1DL * Inv_L;
                here->pParam->BSIM2n0 = model->BSIM2n00 + model->BSIM2n0W * Inv_W
			       + model->BSIM2n0L * Inv_L;
                here->pParam->BSIM2nB = model->BSIM2nB0 + model->BSIM2nBW * Inv_W
			       + model->BSIM2nBL * Inv_L;
                here->pParam->BSIM2nD = model->BSIM2nD0 + model->BSIM2nDW * Inv_W
			       + model->BSIM2nDL * Inv_L;
                if (here->pParam->BSIM2n0 < 0.0)
	            here->pParam->BSIM2n0 = 0.0;

                here->pParam->BSIM2vof0 = model->BSIM2vof00 
			       + model->BSIM2vof0W * Inv_W
			       + model->BSIM2vof0L * Inv_L;
                here->pParam->BSIM2vofB = model->BSIM2vofB0 
			       + model->BSIM2vofBW * Inv_W
			       + model->BSIM2vofBL * Inv_L;
                here->pParam->BSIM2vofD = model->BSIM2vofD0 
			       + model->BSIM2vofDW * Inv_W
			       + model->BSIM2vofDL * Inv_L;
                here->pParam->BSIM2ai0 = model->BSIM2ai00 + model->BSIM2ai0W * Inv_W
			       + model->BSIM2ai0L * Inv_L;
                here->pParam->BSIM2aiB = model->BSIM2aiB0 + model->BSIM2aiBW * Inv_W
			       + model->BSIM2aiBL * Inv_L;
                here->pParam->BSIM2bi0 = model->BSIM2bi00 + model->BSIM2bi0W * Inv_W
			       + model->BSIM2bi0L * Inv_L;
                here->pParam->BSIM2biB = model->BSIM2biB0 + model->BSIM2biBW * Inv_W
			       + model->BSIM2biBL * Inv_L;
                here->pParam->BSIM2vghigh = model->BSIM2vghigh0 
			       + model->BSIM2vghighW * Inv_W
			       + model->BSIM2vghighL * Inv_L;
                here->pParam->BSIM2vglow = model->BSIM2vglow0 
			       + model->BSIM2vglowW * Inv_W
			       + model->BSIM2vglowL * Inv_L;

		here->pParam->CoxWL = model->BSIM2Cox * EffectiveLength
			       * EffectiveWidth * 1.0e4;
		here->pParam->One_Third_CoxWL = here->pParam->CoxWL / 3.0;
		here->pParam->Two_Third_CoxWL = 2.0 
			       * here->pParam->One_Third_CoxWL;
                here->pParam->BSIM2GSoverlapCap = model->BSIM2gateSourceOverlapCap 
			       * EffectiveWidth;
                here->pParam->BSIM2GDoverlapCap = model->BSIM2gateDrainOverlapCap 
			       * EffectiveWidth;
                here->pParam->BSIM2GBoverlapCap = model->BSIM2gateBulkOverlapCap 
			       * EffectiveLength;
                here->pParam->SqrtPhi = sqrt(here->pParam->BSIM2phi);
		here->pParam->Phis3 = here->pParam->SqrtPhi
		               * here->pParam->BSIM2phi;
                here->pParam->Arg = here->pParam->BSIM2betasB
			       - here->pParam->BSIM2beta0B - model->BSIM2vdd
	                       * (here->pParam->BSIM2beta3B - model->BSIM2vdd
	                       * here->pParam->BSIM2beta4B);


             }


            /* process drain series resistance */
            if( (here->BSIM2drainConductance=model->BSIM2sheetResistance *
                    here->BSIM2drainSquares) != 0.0 ) {   
                here->BSIM2drainConductance = 1. / here->BSIM2drainConductance ;
            } 
                   
            /* process source series resistance */
            if( (here->BSIM2sourceConductance=model->BSIM2sheetResistance *
                    here->BSIM2sourceSquares) != 0.0 ) { 
                here->BSIM2sourceConductance = 1. / here->BSIM2sourceConductance ;
            }


            here->pParam->BSIM2vt0 = here->pParam->BSIM2vfb 
			  + here->pParam->BSIM2phi 
			  + here->pParam->BSIM2k1 * here->pParam->SqrtPhi 
			  - here->pParam->BSIM2k2 * here->pParam->BSIM2phi;
            here->BSIM2von = here->pParam->BSIM2vt0; /* added for initialization*/
        }
    }
    return(OK);
}  



