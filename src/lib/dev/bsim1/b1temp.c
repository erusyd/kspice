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
#include "bsim1def.h"
#include "util.h"
#include "const.h"
#include "sperror.h"
#include "suffix.h"


/* ARGSUSED */
int
BSIM1temp(inModel,ckt)
    GENmodel *inModel;
    CKTcircuit *ckt;
        /* load the BSIM1 device structure with those pointers needed later 
         * for fast matrix loading 
         */

{
    register BSIM1model *model = (BSIM1model*) inModel;
    register BSIM1instance *here;
    double  EffChanLength;
    double EffChanWidth;
    double Cox;
    double CoxWoverL ;
    double Leff;    /* effective channel length im micron */
    double Weff;    /* effective channel width in micron */

    /*  loop through all the BSIM1 device models */
    for( ; model != NULL; model = model->BSIM1nextModel ) {
    
/* Default value Processing for BSIM1 MOSFET Models */
        /* Some Limiting for Model Parameters */
        if( model->BSIM1bulkJctPotential < 0.1)  {
            model->BSIM1bulkJctPotential = 0.1;
        }
        if( model->BSIM1sidewallJctPotential < 0.1)  {
            model->BSIM1sidewallJctPotential = 0.1;
        }

        Cox = 3.453e-13/(model->BSIM1oxideThickness * 1.0e-4);/*in F/cm**2 */
        model->BSIM1Cox = Cox;     /* unit:  F/cm**2  */

        /* loop through all the instances of the model */
        for (here = model->BSIM1instances; here != NULL ;
                here=here->BSIM1nextInstance) {

            if( (EffChanLength = here->BSIM1l - model->BSIM1deltaL *1e-6 )<=0) { 
                IFuid namarray[2];
                namarray[0] = model->BSIM1modName;
                namarray[1] = here->BSIM1name;
                (*(SPfrontEnd->IFerror))(ERR_FATAL,
                    "BSIM1: mosfet %s, model %s: Effective channel length <=0",
                    namarray);
                return(E_BADPARM);
            }
            if( (EffChanWidth = here->BSIM1w - model->BSIM1deltaW *1e-6 ) <= 0 ) {
                IFuid namarray[2];
                namarray[0] = model->BSIM1modName;
                namarray[1] = here->BSIM1name;
                (*(SPfrontEnd->IFerror))(ERR_FATAL,
                    "BSIM1: mosfet %s, model %s: Effective channel width <=0",
                    namarray);
                return(E_BADPARM);
            }
            here->BSIM1GDoverlapCap=EffChanWidth *model->BSIM1gateDrainOverlapCap;
            here->BSIM1GSoverlapCap=EffChanWidth*model->BSIM1gateSourceOverlapCap;
            here->BSIM1GBoverlapCap=here->BSIM1l * model->BSIM1gateBulkOverlapCap;

            /* process drain series resistance */
            if( (here->BSIM1drainConductance=model->BSIM1sheetResistance *
                    here->BSIM1drainSquares) != 0.0 ) {   
                here->BSIM1drainConductance = 1. / here->BSIM1drainConductance ;
            } 
                   
            /* process source series resistance */
            if( (here->BSIM1sourceConductance=model->BSIM1sheetResistance *
                    here->BSIM1sourceSquares) != 0.0 ) { 
                here->BSIM1sourceConductance = 1. / here->BSIM1sourceConductance ;
            }
                   
            Leff = EffChanLength * 1.e6; /* convert into micron */
            Weff = EffChanWidth * 1.e6; /* convert into micron */
            CoxWoverL = Cox * Weff / Leff ; /* F/cm**2 */

            here->BSIM1vfb = model->BSIM1vfb0 + 
                model->BSIM1vfbL / Leff + model->BSIM1vfbW / Weff;
            here->BSIM1phi = model->BSIM1phi0 +
                model->BSIM1phiL / Leff + model->BSIM1phiW / Weff;
            here->BSIM1K1 = model->BSIM1K10 +
                model->BSIM1K1L / Leff + model->BSIM1K1W / Weff;
            here->BSIM1K2 = model->BSIM1K20 +
                model->BSIM1K2L / Leff + model->BSIM1K2W / Weff;
            here->BSIM1eta = model->BSIM1eta0 +
                model->BSIM1etaL / Leff + model->BSIM1etaW / Weff;
            here->BSIM1etaB = model->BSIM1etaB0 +
                model->BSIM1etaBl / Leff + model->BSIM1etaBw / Weff;
            here->BSIM1etaD = model->BSIM1etaD0 +
                model->BSIM1etaDl / Leff + model->BSIM1etaDw / Weff;
            here->BSIM1betaZero = model->BSIM1mobZero;
            here->BSIM1betaZeroB = model->BSIM1mobZeroB0 + 
                model->BSIM1mobZeroBl / Leff + model->BSIM1mobZeroBw / Weff;
            here->BSIM1ugs = model->BSIM1ugs0 +
                model->BSIM1ugsL / Leff + model->BSIM1ugsW / Weff;
            here->BSIM1ugsB = model->BSIM1ugsB0 +
                model->BSIM1ugsBL / Leff + model->BSIM1ugsBW / Weff;
            here->BSIM1uds = model->BSIM1uds0 +
                model->BSIM1udsL / Leff + model->BSIM1udsW / Weff;
            here->BSIM1udsB = model->BSIM1udsB0 +
                model->BSIM1udsBL / Leff + model->BSIM1udsBW / Weff;
            here->BSIM1udsD = model->BSIM1udsD0 +
                model->BSIM1udsDL / Leff + model->BSIM1udsDW / Weff;
            here->BSIM1betaVdd = model->BSIM1mobVdd0 +
                model->BSIM1mobVddl / Leff + model->BSIM1mobVddw / Weff;
            here->BSIM1betaVddB = model->BSIM1mobVddB0 + 
                model->BSIM1mobVddBl / Leff + model->BSIM1mobVddBw / Weff;
            here->BSIM1betaVddD = model->BSIM1mobVddD0 +
                model->BSIM1mobVddDl / Leff + model->BSIM1mobVddDw / Weff;
            here->BSIM1subthSlope = model->BSIM1subthSlope0 + 
                model->BSIM1subthSlopeL / Leff + model->BSIM1subthSlopeW / Weff;
            here->BSIM1subthSlopeB = model->BSIM1subthSlopeB0 +
                model->BSIM1subthSlopeBL / Leff + model->BSIM1subthSlopeBW / Weff;
            here->BSIM1subthSlopeD = model->BSIM1subthSlopeD0 + 
                model->BSIM1subthSlopeDL / Leff + model->BSIM1subthSlopeDW / Weff;

            if(here->BSIM1phi < 0.1 ) here->BSIM1phi = 0.1;
            if(here->BSIM1K1 < 0.0) here->BSIM1K1 = 0.0;
            if(here->BSIM1K2 < 0.0) here->BSIM1K2 = 0.0;

            here->BSIM1vt0 = here->BSIM1vfb + here->BSIM1phi + here->BSIM1K1 * 
                sqrt(here->BSIM1phi) - here->BSIM1K2 * here->BSIM1phi;

            here->BSIM1von = here->BSIM1vt0;  /* added for initialization*/

                /* process Beta Parameters (unit: A/V**2) */

            here->BSIM1betaZero = here->BSIM1betaZero * CoxWoverL;
            here->BSIM1betaZeroB = here->BSIM1betaZeroB * CoxWoverL;
            here->BSIM1betaVdd = here->BSIM1betaVdd * CoxWoverL;
            here->BSIM1betaVddB = here->BSIM1betaVddB * CoxWoverL;
            here->BSIM1betaVddD = MAX(here->BSIM1betaVddD * CoxWoverL,0.0);

        }
    }
    return(OK);
}  


