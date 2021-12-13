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


int
BSIM1setup(matrix,inModel,ckt,states)
    register SMPmatrix *matrix;
    register GENmodel *inModel;
    register CKTcircuit *ckt;
    int *states;
        /* load the BSIM1 device structure with those pointers needed later 
         * for fast matrix loading 
         */

{
    register BSIM1model *model = (BSIM1model*)inModel;
    register BSIM1instance *here;
    int error;
    CKTnode *tmp;

    /*  loop through all the BSIM1 device models */
    for( ; model != NULL; model = model->BSIM1nextModel ) {
    
/* Default value Processing for BSIM1 MOSFET Models */
        if( ! model->BSIM1typeGiven) {
            model->BSIM1type = NMOS;  /* NMOS */
        }
        if( ! model->BSIM1vfb0Given) {
            model->BSIM1vfb0 = 0.0;
        }
        if( ! model->BSIM1vfbLGiven) {
            model->BSIM1vfbL = 0.0;
        }
        if( ! model->BSIM1vfbWGiven) {
            model->BSIM1vfbW = 0.0;
        }
        if( ! model->BSIM1phi0Given) {
            model->BSIM1phi0 = 0.0;
        }
        if( ! model->BSIM1phiLGiven) {
            model->BSIM1phiL = 0.0;
        }
        if( ! model->BSIM1phiWGiven) {
            model->BSIM1phiW = 0.0;
        }
        if( ! model->BSIM1K10Given) {
            model->BSIM1K10 = 0.0;
        }
        if( ! model->BSIM1K1LGiven) {
            model->BSIM1K1L = 0.0;
        }
        if( ! model->BSIM1K1WGiven) {
            model->BSIM1K1W = 0.0;
        }
        if( ! model->BSIM1K20Given) {
            model->BSIM1K20 = 0.0;
        }
        if( ! model->BSIM1K2LGiven) {
            model->BSIM1K2L = 0.0;
        }
        if( ! model->BSIM1K2WGiven) {
            model->BSIM1K2W = 0.0;
        }
        if( ! model->BSIM1eta0Given) {
            model->BSIM1eta0 = 0.0;
        }
        if( ! model->BSIM1etaLGiven) {
            model->BSIM1etaL = 0.0;
        }
        if( ! model->BSIM1etaWGiven) {
            model->BSIM1etaW = 0.0;
        }
        if( ! model->BSIM1mobZeroGiven) {
            model->BSIM1mobZero = 0.0;
        }
        if( ! model->BSIM1deltaLGiven) {
            model->BSIM1deltaL = 0.0;
        }
        if( ! model->BSIM1deltaWGiven) {
            model->BSIM1deltaW = 0.0;
        }
        if( ! model->BSIM1ugs0Given) {
            model->BSIM1ugs0 = 0.0;
        }
        if( ! model->BSIM1ugsLGiven) {
            model->BSIM1ugsL = 0.0;
        }
        if( ! model->BSIM1ugsWGiven) {
            model->BSIM1ugsW = 0.0;
        }
        if( ! model->BSIM1uds0Given) {
            model->BSIM1uds0 = 0.0;
        }
        if( ! model->BSIM1udsLGiven) {
            model->BSIM1udsL = 0.0;
        }
        if( ! model->BSIM1udsWGiven) {
            model->BSIM1udsW = 0.0;
        }
        if( ! model->BSIM1mobZeroB0Given) {
            model->BSIM1mobZeroB0 = 0.0;
        }
        if( ! model->BSIM1mobZeroBlGiven) {
            model->BSIM1mobZeroBl = 0.0;
        }
        if( ! model->BSIM1mobZeroBwGiven) {
            model->BSIM1mobZeroBw = 0.0;
        }
        if( ! model->BSIM1etaB0Given) {
            model->BSIM1etaB0 = 0.0;
        }
        if( ! model->BSIM1etaBlGiven) {
            model->BSIM1etaBl = 0.0;
        }
        if( ! model->BSIM1etaBwGiven) {
            model->BSIM1etaBw = 0.0;
        }
        if( ! model->BSIM1etaD0Given) {
            model->BSIM1etaD0 = 0.0;
        }
        if( ! model->BSIM1etaDlGiven) {
            model->BSIM1etaDl = 0.0;
        }
        if( ! model->BSIM1etaDwGiven) {
            model->BSIM1etaDw = 0.0;
        }
        if( ! model->BSIM1ugsB0Given) {
            model->BSIM1ugsB0 = 0.0;
        }
        if( ! model->BSIM1ugsBLGiven) {
            model->BSIM1ugsBL = 0.0;
        }
        if( ! model->BSIM1ugsBWGiven) {
            model->BSIM1ugsBW = 0.0;
        }
        if( ! model->BSIM1udsB0Given) {
            model->BSIM1udsB0 = 0.0;
        }
        if( ! model->BSIM1udsBLGiven) {
            model->BSIM1udsBL = 0.0;
        }
        if( ! model->BSIM1udsBWGiven) {
            model->BSIM1udsBW = 0.0;
        }
        if( ! model->BSIM1mobVdd0Given) {
            model->BSIM1mobVdd0 = 0.0;
        }
        if( ! model->BSIM1mobVddlGiven) {
            model->BSIM1mobVddl = 0.0;
        }
        if( ! model->BSIM1mobVddwGiven) {
            model->BSIM1mobVddw = 0.0;
        }
        if( ! model->BSIM1mobVddB0Given) {
            model->BSIM1mobVddB0 = 0.0;
        }
        if( ! model->BSIM1mobVddBlGiven) {
            model->BSIM1mobVddBl = 0.0;
        }
        if( ! model->BSIM1mobVddBwGiven) {
            model->BSIM1mobVddBw = 0.0;
        }
        if( ! model->BSIM1mobVddD0Given) {
            model->BSIM1mobVddD0 = 0.0;
        }
        if( ! model->BSIM1mobVddDlGiven) {
            model->BSIM1mobVddDl = 0.0;
        }
        if( ! model->BSIM1mobVddDwGiven) {
            model->BSIM1mobVddDw = 0.0;
        }
        if( ! model->BSIM1udsD0Given) {
            model->BSIM1udsD0 = 0.0;
        }
        if( ! model->BSIM1udsDLGiven) {
            model->BSIM1udsDL = 0.0;
        }
        if( ! model->BSIM1udsDWGiven) {
            model->BSIM1udsDW = 0.0;
        }
        if( ! model->BSIM1oxideThicknessGiven) {
            model->BSIM1oxideThickness = 0.0;  /* um */
        }
        if( ! model->BSIM1tempGiven) {
            model->BSIM1temp = 0.0;
        }
        if( ! model->BSIM1vddGiven) {
            model->BSIM1vdd = 0.0;
        }
        if( ! model->BSIM1gateDrainOverlapCapGiven) {
            model->BSIM1gateDrainOverlapCap = 0.0;
        }
        if( ! model->BSIM1gateSourceOverlapCapGiven) {
            model->BSIM1gateSourceOverlapCap = 0.0;
        }
        if( ! model->BSIM1gateBulkOverlapCapGiven) {
            model->BSIM1gateBulkOverlapCap = 0.0;
        }
        if( ! model->BSIM1channelChargePartitionFlagGiven) {
            model->BSIM1channelChargePartitionFlag = 0.0;
        }
        if( ! model->BSIM1subthSlope0Given) {
            model->BSIM1subthSlope0 = 0.0;
        }
        if( ! model->BSIM1subthSlopeLGiven) {
            model->BSIM1subthSlopeL = 0.0;
        }
        if( ! model->BSIM1subthSlopeWGiven) {
            model->BSIM1subthSlopeW = 0.0;
        }
        if( ! model->BSIM1subthSlopeB0Given) {
            model->BSIM1subthSlopeB0 = 0.0;
        }
        if( ! model->BSIM1subthSlopeBLGiven) {
            model->BSIM1subthSlopeBL = 0.0;
        }
        if( ! model->BSIM1subthSlopeBWGiven) {
            model->BSIM1subthSlopeBW = 0.0;
        }
        if( ! model->BSIM1subthSlopeD0Given) {
            model->BSIM1subthSlopeD0 = 0.0;
        }
        if( ! model->BSIM1subthSlopeDLGiven) {
            model->BSIM1subthSlopeDL = 0.0;
        }
        if( ! model->BSIM1subthSlopeDWGiven) {
            model->BSIM1subthSlopeDW = 0.0;
        }
        if( ! model->BSIM1sheetResistanceGiven) {
            model->BSIM1sheetResistance = 0.0;
        }
        if( ! model->BSIM1unitAreaJctCapGiven) {
            model->BSIM1unitAreaJctCap = 0.0;
        }
        if( ! model->BSIM1unitLengthSidewallJctCapGiven) {
            model->BSIM1unitLengthSidewallJctCap = 0.0;
        }
        if( ! model->BSIM1jctSatCurDensityGiven) {
            model->BSIM1jctSatCurDensity = 0.0;
        }
        if( ! model->BSIM1bulkJctPotentialGiven) {
            model->BSIM1bulkJctPotential = 0.0;
        }
        if( ! model->BSIM1sidewallJctPotentialGiven) {
            model->BSIM1sidewallJctPotential = 0.0;
        }
        if( ! model->BSIM1bulkJctBotGradingCoeffGiven) {
            model->BSIM1bulkJctBotGradingCoeff = 0.0;
        }
        if( ! model->BSIM1bulkJctSideGradingCoeffGiven) {
            model->BSIM1bulkJctSideGradingCoeff = 0.0;
        }
        if( ! model->BSIM1defaultWidthGiven) {
            model->BSIM1defaultWidth = 0.0;
        }
        if( ! model->BSIM1deltaLengthGiven) {
            model->BSIM1deltaLength = 0.0;
        }

        /* loop through all the instances of the model */
        for (here = model->BSIM1instances; here != NULL ;
                here=here->BSIM1nextInstance) {

            /* allocate a chunk of the state vector */
            here->BSIM1states = *states;
            *states += BSIM1numStates;

            /* perform the parameter defaulting */

            if(!here->BSIM1drainAreaGiven) {
                here->BSIM1drainArea = 0;
            }
            if(!here->BSIM1drainPerimeterGiven) {
                here->BSIM1drainPerimeter = 0;
            }
            if(!here->BSIM1drainSquaresGiven) {
                here->BSIM1drainSquares = 1;
            }
            if(!here->BSIM1icVBSGiven) {
                here->BSIM1icVBS = 0;
            }
            if(!here->BSIM1icVDSGiven) {
                here->BSIM1icVDS = 0;
            }
            if(!here->BSIM1icVGSGiven) {
                here->BSIM1icVGS = 0;
            }
            if(!here->BSIM1lGiven) {
                here->BSIM1l = 5e-6;
            }
            if(!here->BSIM1sourceAreaGiven) {
                here->BSIM1sourceArea = 0;
            }
            if(!here->BSIM1sourcePerimeterGiven) {
                here->BSIM1sourcePerimeter = 0;
            }
            if(!here->BSIM1sourceSquaresGiven) {
                here->BSIM1sourceSquares = 1;
            }
            if(!here->BSIM1vdsatGiven) {
                here->BSIM1vdsat = 0;
            }
            if(!here->BSIM1vonGiven) {
                here->BSIM1von = 0;
            }
            if(!here->BSIM1wGiven) {
                here->BSIM1w = 5e-6;
            }

            /* process drain series resistance */
            if( (model->BSIM1sheetResistance != 0) && 
                    (here->BSIM1drainSquares != 0.0 ) &&
                    (here->BSIM1dNodePrime == 0) ) {
                error = CKTmkVolt(ckt,&tmp,here->BSIM1name,"drain");
                if(error) return(error);
                here->BSIM1dNodePrime = tmp->number;
            } else {
                    here->BSIM1dNodePrime = here->BSIM1dNode;
            }
                   
            /* process source series resistance */
            if( (model->BSIM1sheetResistance != 0) && 
                    (here->BSIM1sourceSquares != 0.0 ) &&
                    (here->BSIM1sNodePrime == 0) ) {
                if(here->BSIM1sNodePrime == 0) {
                    error = CKTmkVolt(ckt,&tmp,here->BSIM1name,"source");
                    if(error) return(error);
                    here->BSIM1sNodePrime = tmp->number;
                }
            } else  {
                here->BSIM1sNodePrime = here->BSIM1sNode;
            }
                   

        /* set Sparse Matrix Pointers */

/* macro to make elements with built in test for out of memory */
#define TSTALLOC(ptr,first,second) \
if((here->ptr = SMPmakeElt(matrix,here->first,here->second))==(double *)NULL){\
    return(E_NOMEM);\
}

            TSTALLOC(BSIM1DdPtr, BSIM1dNode, BSIM1dNode)
            TSTALLOC(BSIM1GgPtr, BSIM1gNode, BSIM1gNode)
            TSTALLOC(BSIM1SsPtr, BSIM1sNode, BSIM1sNode)
            TSTALLOC(BSIM1BbPtr, BSIM1bNode, BSIM1bNode)
            TSTALLOC(BSIM1DPdpPtr, BSIM1dNodePrime, BSIM1dNodePrime)
            TSTALLOC(BSIM1SPspPtr, BSIM1sNodePrime, BSIM1sNodePrime)
            TSTALLOC(BSIM1DdpPtr, BSIM1dNode, BSIM1dNodePrime)
            TSTALLOC(BSIM1GbPtr, BSIM1gNode, BSIM1bNode)
            TSTALLOC(BSIM1GdpPtr, BSIM1gNode, BSIM1dNodePrime)
            TSTALLOC(BSIM1GspPtr, BSIM1gNode, BSIM1sNodePrime)
            TSTALLOC(BSIM1SspPtr, BSIM1sNode, BSIM1sNodePrime)
            TSTALLOC(BSIM1BdpPtr, BSIM1bNode, BSIM1dNodePrime)
            TSTALLOC(BSIM1BspPtr, BSIM1bNode, BSIM1sNodePrime)
            TSTALLOC(BSIM1DPspPtr, BSIM1dNodePrime, BSIM1sNodePrime)
            TSTALLOC(BSIM1DPdPtr, BSIM1dNodePrime, BSIM1dNode)
            TSTALLOC(BSIM1BgPtr, BSIM1bNode, BSIM1gNode)
            TSTALLOC(BSIM1DPgPtr, BSIM1dNodePrime, BSIM1gNode)
            TSTALLOC(BSIM1SPgPtr, BSIM1sNodePrime, BSIM1gNode)
            TSTALLOC(BSIM1SPsPtr, BSIM1sNodePrime, BSIM1sNode)
            TSTALLOC(BSIM1DPbPtr, BSIM1dNodePrime, BSIM1bNode)
            TSTALLOC(BSIM1SPbPtr, BSIM1sNodePrime, BSIM1bNode)
            TSTALLOC(BSIM1SPdpPtr, BSIM1sNodePrime, BSIM1dNodePrime)

        }
    }
    return(OK);
}  


