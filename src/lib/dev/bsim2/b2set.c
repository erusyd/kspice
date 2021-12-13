/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1988 Min-Chie Jeng, Hong J. Park, Thomas L. Quarles
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


int
BSIM2setup(matrix,inModel,ckt,states)
    register SMPmatrix *matrix;
    register GENmodel *inModel;
    register CKTcircuit *ckt;
    int *states;
        /* load the BSIM2 device structure with those pointers needed later 
         * for fast matrix loading 
         */

{
    register BSIM2model *model = (BSIM2model*)inModel;
    register BSIM2instance *here;
    int error;
    CKTnode *tmp;

    /*  loop through all the BSIM2 device models */
    for( ; model != NULL; model = model->BSIM2nextModel ) {
    
/* Default value Processing for BSIM2 MOSFET Models */
        if( ! model->BSIM2typeGiven) {
            model->BSIM2type = NMOS;  /* NMOS */
        }
        if( ! model->BSIM2vfb0Given) {
            model->BSIM2vfb0 = -1.0;
        }
        if( ! model->BSIM2vfbLGiven) {
            model->BSIM2vfbL = 0.0;
        }
        if( ! model->BSIM2vfbWGiven) {
            model->BSIM2vfbW = 0.0;
        }
        if( ! model->BSIM2phi0Given) {
            model->BSIM2phi0 = 0.75;
        }
        if( ! model->BSIM2phiLGiven) {
            model->BSIM2phiL = 0.0;
        }
        if( ! model->BSIM2phiWGiven) {
            model->BSIM2phiW = 0.0;
        }
        if( ! model->BSIM2k10Given) {
            model->BSIM2k10 = 0.8;
        }
        if( ! model->BSIM2k1LGiven) {
            model->BSIM2k1L = 0.0;
        }
        if( ! model->BSIM2k1WGiven) {
            model->BSIM2k1W = 0.0;
        }
        if( ! model->BSIM2k20Given) {
            model->BSIM2k20 = 0.0;
        }
        if( ! model->BSIM2k2LGiven) {
            model->BSIM2k2L = 0.0;
        }
        if( ! model->BSIM2k2WGiven) {
            model->BSIM2k2W = 0.0;
        }
        if( ! model->BSIM2eta00Given) {
            model->BSIM2eta00 = 0.0;
        }
        if( ! model->BSIM2eta0LGiven) {
            model->BSIM2eta0L = 0.0;
        }
        if( ! model->BSIM2eta0WGiven) {
            model->BSIM2eta0W = 0.0;
        }
        if( ! model->BSIM2etaB0Given) {
            model->BSIM2etaB0 = 0.0;
        }
        if( ! model->BSIM2etaBLGiven) {
            model->BSIM2etaBL = 0.0;
        }
        if( ! model->BSIM2etaBWGiven) {
            model->BSIM2etaBW = 0.0;
        }
        if( ! model->BSIM2deltaLGiven) {
            model->BSIM2deltaL = 0.0;
        }
        if( ! model->BSIM2deltaWGiven) {
            model->BSIM2deltaW = 0.0;
        }
        if( ! model->BSIM2ua00Given) {
            model->BSIM2ua00 = 0.2;
        }
        if( ! model->BSIM2ua0LGiven) {
            model->BSIM2ua0L = 0.0;
        }
        if( ! model->BSIM2ua0WGiven) {
            model->BSIM2ua0W = 0.0;
        }
        if( ! model->BSIM2uaB0Given) {
            model->BSIM2uaB0 = 0.0;
        }
        if( ! model->BSIM2uaBLGiven) {
            model->BSIM2uaBL = 0.0;
        }
        if( ! model->BSIM2uaBWGiven) {
            model->BSIM2uaBW = 0.0;
        }
        if( ! model->BSIM2ub00Given) {
            model->BSIM2ub00 = 0.0;
        }
        if( ! model->BSIM2ub0LGiven) {
            model->BSIM2ub0L = 0.0;
        }
        if( ! model->BSIM2ub0WGiven) {
            model->BSIM2ub0W = 0.0;
        }
        if( ! model->BSIM2ubB0Given) {
            model->BSIM2ubB0 = 0.0;
        }
        if( ! model->BSIM2ubBLGiven) {
            model->BSIM2ubBL = 0.0;
        }
        if( ! model->BSIM2ubBWGiven) {
            model->BSIM2ubBW = 0.0;
        }
        if( ! model->BSIM2u100Given) {
            model->BSIM2u100 = 0.1;
        }
        if( ! model->BSIM2u10LGiven) {
            model->BSIM2u10L = 0.0;
        }
        if( ! model->BSIM2u10WGiven) {
            model->BSIM2u10W = 0.0;
        }
        if( ! model->BSIM2u1B0Given) {
            model->BSIM2u1B0 = 0.0;
        }
        if( ! model->BSIM2u1BLGiven) {
            model->BSIM2u1BL = 0.0;
        }
        if( ! model->BSIM2u1BWGiven) {
            model->BSIM2u1BW = 0.0;
        }
        if( ! model->BSIM2u1D0Given) {
            model->BSIM2u1D0 = 0.0;
        }
        if( ! model->BSIM2u1DLGiven) {
            model->BSIM2u1DL = 0.0;
        }
        if( ! model->BSIM2u1DWGiven) {
            model->BSIM2u1DW = 0.0;
        }
        if( ! model->BSIM2mob00Given) {
            model->BSIM2mob00 = 400.0;
        }
        if( ! model->BSIM2mob0B0Given) {
            model->BSIM2mob0B0 = 0.0;
        }
        if( ! model->BSIM2mob0BLGiven) {
            model->BSIM2mob0BL = 0.0;
        }
        if( ! model->BSIM2mob0BWGiven) {
            model->BSIM2mob0BW = 0.0;
        }
        if( ! model->BSIM2mobs00Given) {
            model->BSIM2mobs00 = 500.0;
        }
        if( ! model->BSIM2mobs0LGiven) {
            model->BSIM2mobs0L = 0.0;
        }
        if( ! model->BSIM2mobs0WGiven) {
            model->BSIM2mobs0W = 0.0;
        }
        if( ! model->BSIM2mobsB0Given) {
            model->BSIM2mobsB0 = 0.0;
        }
        if( ! model->BSIM2mobsBLGiven) {
            model->BSIM2mobsBL = 0.0;
        }
        if( ! model->BSIM2mobsBWGiven) {
            model->BSIM2mobsBW = 0.0;
        }
        if( ! model->BSIM2mob200Given) {
            model->BSIM2mob200 = 1.5;
        }
        if( ! model->BSIM2mob20LGiven) {
            model->BSIM2mob20L = 0.0;
        }
        if( ! model->BSIM2mob20WGiven) {
            model->BSIM2mob20W = 0.0;
        }
        if( ! model->BSIM2mob2B0Given) {
            model->BSIM2mob2B0 = 0.0;
        }
        if( ! model->BSIM2mob2BLGiven) {
            model->BSIM2mob2BL = 0.0;
        }
        if( ! model->BSIM2mob2BWGiven) {
            model->BSIM2mob2BW = 0.0;
        }
        if( ! model->BSIM2mob2G0Given) {
            model->BSIM2mob2G0 = 0.0;
        }
        if( ! model->BSIM2mob2GLGiven) {
            model->BSIM2mob2GL = 0.0;
        }
        if( ! model->BSIM2mob2GWGiven) {
            model->BSIM2mob2GW = 0.0;
        }
        if( ! model->BSIM2mob300Given) {
            model->BSIM2mob300 = 10;
        }
        if( ! model->BSIM2mob30LGiven) {
            model->BSIM2mob30L = 0.0;
        }
        if( ! model->BSIM2mob30WGiven) {
            model->BSIM2mob30W = 0.0;
        }
        if( ! model->BSIM2mob3B0Given) {
            model->BSIM2mob3B0 = 0.0;
        }
        if( ! model->BSIM2mob3BLGiven) {
            model->BSIM2mob3BL = 0.0;
        }
        if( ! model->BSIM2mob3BWGiven) {
            model->BSIM2mob3BW = 0.0;
        }
        if( ! model->BSIM2mob3G0Given) {
            model->BSIM2mob3G0 = 0.0;
        }
        if( ! model->BSIM2mob3GLGiven) {
            model->BSIM2mob3GL = 0.0;
        }
        if( ! model->BSIM2mob3GWGiven) {
            model->BSIM2mob3GW = 0.0;
        }
        if( ! model->BSIM2mob400Given) {
            model->BSIM2mob400 = 0.0;
        }
        if( ! model->BSIM2mob40LGiven) {
            model->BSIM2mob40L = 0.0;
        }
        if( ! model->BSIM2mob40WGiven) {
            model->BSIM2mob40W = 0.0;
        }
        if( ! model->BSIM2mob4B0Given) {
            model->BSIM2mob4B0 = 0.0;
        }
        if( ! model->BSIM2mob4BLGiven) {
            model->BSIM2mob4BL = 0.0;
        }
        if( ! model->BSIM2mob4BWGiven) {
            model->BSIM2mob4BW = 0.0;
        }
        if( ! model->BSIM2mob4G0Given) {
            model->BSIM2mob4G0 = 0.0;
        }
        if( ! model->BSIM2mob4GLGiven) {
            model->BSIM2mob4GL = 0.0;
        }
        if( ! model->BSIM2mob4GWGiven) {
            model->BSIM2mob4GW = 0.0;
        }
        if( ! model->BSIM2n00Given) {
            model->BSIM2n00 = 1.4;
        }
        if( ! model->BSIM2n0LGiven) {
            model->BSIM2n0L = 0.0;
        }
        if( ! model->BSIM2n0WGiven) {
            model->BSIM2n0W = 0.0;
        }
        if( ! model->BSIM2nB0Given) {
            model->BSIM2nB0 = 0.5;
        }
        if( ! model->BSIM2nBLGiven) {
            model->BSIM2nBL = 0.0;
        }
        if( ! model->BSIM2nBWGiven) {
            model->BSIM2nBW = 0.0;
        }
        if( ! model->BSIM2nD0Given) {
            model->BSIM2nD0 = 0.0;
        }
        if( ! model->BSIM2nDLGiven) {
            model->BSIM2nDL = 0.0;
        }
        if( ! model->BSIM2nDWGiven) {
            model->BSIM2nDW = 0.0;
        }
        if( ! model->BSIM2vof00Given) {
            model->BSIM2vof00 = 1.8;
        }
        if( ! model->BSIM2vof0LGiven) {
            model->BSIM2vof0L = 0.0;
        }
        if( ! model->BSIM2vof0WGiven) {
            model->BSIM2vof0W = 0.0;
        }
        if( ! model->BSIM2vofB0Given) {
            model->BSIM2vofB0 = 0.0;
        }
        if( ! model->BSIM2vofBLGiven) {
            model->BSIM2vofBL = 0.0;
        }
        if( ! model->BSIM2vofBWGiven) {
            model->BSIM2vofBW = 0.0;
        }
        if( ! model->BSIM2vofD0Given) {
            model->BSIM2vofD0 = 0.0;
        }
        if( ! model->BSIM2vofDLGiven) {
            model->BSIM2vofDL = 0.0;
        }
        if( ! model->BSIM2vofDWGiven) {
            model->BSIM2vofDW = 0.0;
        }
        if( ! model->BSIM2ai00Given) {
            model->BSIM2ai00 = 0.0;
        }
        if( ! model->BSIM2ai0LGiven) {
            model->BSIM2ai0L = 0.0;
        }
        if( ! model->BSIM2ai0WGiven) {
            model->BSIM2ai0W = 0.0;
        }
        if( ! model->BSIM2aiB0Given) {
            model->BSIM2aiB0 = 0.0;
        }
        if( ! model->BSIM2aiBLGiven) {
            model->BSIM2aiBL = 0.0;
        }
        if( ! model->BSIM2aiBWGiven) {
            model->BSIM2aiBW = 0.0;
        }
        if( ! model->BSIM2bi00Given) {
            model->BSIM2bi00 = 0.0;
        }
        if( ! model->BSIM2bi0LGiven) {
            model->BSIM2bi0L = 0.0;
        }
        if( ! model->BSIM2bi0WGiven) {
            model->BSIM2bi0W = 0.0;
        }
        if( ! model->BSIM2biB0Given) {
            model->BSIM2biB0 = 0.0;
        }
        if( ! model->BSIM2biBLGiven) {
            model->BSIM2biBL = 0.0;
        }
        if( ! model->BSIM2biBWGiven) {
            model->BSIM2biBW = 0.0;
        }
        if( ! model->BSIM2vghigh0Given) {
            model->BSIM2vghigh0 = 0.2;
        }
        if( ! model->BSIM2vghighLGiven) {
            model->BSIM2vghighL = 0.0;
        }
        if( ! model->BSIM2vghighWGiven) {
            model->BSIM2vghighW = 0.0;
        }
        if( ! model->BSIM2vglow0Given) {
            model->BSIM2vglow0 = -0.15;
        }
        if( ! model->BSIM2vglowLGiven) {
            model->BSIM2vglowL = 0.0;
        }
        if( ! model->BSIM2vglowWGiven) {
            model->BSIM2vglowW = 0.0;
        }
        if( ! model->BSIM2toxGiven) {
            model->BSIM2tox = 0.03;  /* um */
        }
        if( ! model->BSIM2tempGiven) {
            model->BSIM2temp = 27.0;
        }
        if( ! model->BSIM2vddGiven) {
            model->BSIM2vdd = 5.0;
        }
        if( ! model->BSIM2vggGiven) {
            model->BSIM2vgg = 5.0;
        }
        if( ! model->BSIM2vbbGiven) {
            model->BSIM2vbb = 5.0;
        }
        if( ! model->BSIM2gateDrainOverlapCapGiven) {
            model->BSIM2gateDrainOverlapCap = 0.0;
        }
        if( ! model->BSIM2gateSourceOverlapCapGiven) {
            model->BSIM2gateSourceOverlapCap = 0.0;
        }
        if( ! model->BSIM2gateBulkOverlapCapGiven) {
            model->BSIM2gateBulkOverlapCap = 0.0;
        }
        if( ! model->BSIM2channelChargePartitionFlagGiven) {
            model->BSIM2channelChargePartitionFlag = 0.0;
        }
        if( ! model->BSIM2sheetResistanceGiven) {
            model->BSIM2sheetResistance = 0.0;
        }
        if( ! model->BSIM2unitAreaJctCapGiven) {
            model->BSIM2unitAreaJctCap = 0.0;
        }
        if( ! model->BSIM2unitLengthSidewallJctCapGiven) {
            model->BSIM2unitLengthSidewallJctCap = 0.0;
        }
        if( ! model->BSIM2jctSatCurDensityGiven) {
            model->BSIM2jctSatCurDensity = 0.0;
        }
        if( ! model->BSIM2bulkJctPotentialGiven) {
            model->BSIM2bulkJctPotential = 0.0;
        }
        if( ! model->BSIM2sidewallJctPotentialGiven) {
            model->BSIM2sidewallJctPotential = 0.0;
        }
        if( ! model->BSIM2bulkJctBotGradingCoeffGiven) {
            model->BSIM2bulkJctBotGradingCoeff = 0.0;
        }
        if( ! model->BSIM2bulkJctSideGradingCoeffGiven) {
            model->BSIM2bulkJctSideGradingCoeff = 0.0;
        }
        if( ! model->BSIM2defaultWidthGiven) {
            model->BSIM2defaultWidth = 10.0;
        }
        if( ! model->BSIM2deltaLengthGiven) {
            model->BSIM2deltaLength = 0.0;
        }

        /* loop through all the instances of the model */
        for (here = model->BSIM2instances; here != NULL ;
                here=here->BSIM2nextInstance) {

            /* allocate a chunk of the state vector */
            here->BSIM2states = *states;
            *states += BSIM2numStates;

            /* perform the parameter defaulting */

            if(!here->BSIM2drainAreaGiven) {
                here->BSIM2drainArea = 0;
            }
            if(!here->BSIM2drainPerimeterGiven) {
                here->BSIM2drainPerimeter = 0;
            }
            if(!here->BSIM2drainSquaresGiven) {
                here->BSIM2drainSquares = 1;
            }
            if(!here->BSIM2icVBSGiven) {
                here->BSIM2icVBS = 0;
            }
            if(!here->BSIM2icVDSGiven) {
                here->BSIM2icVDS = 0;
            }
            if(!here->BSIM2icVGSGiven) {
                here->BSIM2icVGS = 0;
            }
            if(!here->BSIM2lGiven) {
                here->BSIM2l = 5e-6;
            }
            if(!here->BSIM2sourceAreaGiven) {
                here->BSIM2sourceArea = 0;
            }
            if(!here->BSIM2sourcePerimeterGiven) {
                here->BSIM2sourcePerimeter = 0;
            }
            if(!here->BSIM2sourceSquaresGiven) {
                here->BSIM2sourceSquares = 1;
            }
            if(!here->BSIM2vdsatGiven) {
                here->BSIM2vdsat = 0;
            }
            if(!here->BSIM2vonGiven) {
                here->BSIM2von = 0;
            }
            if(!here->BSIM2wGiven) {
                here->BSIM2w = 5e-6;
            }
                   
            /* process drain series resistance */
            if( (model->BSIM2sheetResistance != 0) && 
                    (here->BSIM2drainSquares != 0.0 ) &&
                    (here->BSIM2dNodePrime == 0) ) {
                error = CKTmkVolt(ckt,&tmp,here->BSIM2name,"drain");
                if(error) return(error);
                here->BSIM2dNodePrime = tmp->number;
            } else {
                    here->BSIM2dNodePrime = here->BSIM2dNode;
            }
                   
            /* process source series resistance */
            if( (model->BSIM2sheetResistance != 0) && 
                    (here->BSIM2sourceSquares != 0.0 ) &&
                    (here->BSIM2sNodePrime == 0) ) {
                if(here->BSIM2sNodePrime == 0) {
                    error = CKTmkVolt(ckt,&tmp,here->BSIM2name,"source");
                    if(error) return(error);
                    here->BSIM2sNodePrime = tmp->number;
                }
            } else  {
                here->BSIM2sNodePrime = here->BSIM2sNode;
            }
                   

        /* set Sparse Matrix Pointers */

/* macro to make elements with built in test for out of memory */
#define TSTALLOC(ptr,first,second) \
if((here->ptr = SMPmakeElt(matrix,here->first,here->second))==(double *)NULL){\
    return(E_NOMEM);\
}

            TSTALLOC(BSIM2DdPtr, BSIM2dNode, BSIM2dNode)
            TSTALLOC(BSIM2GgPtr, BSIM2gNode, BSIM2gNode)
            TSTALLOC(BSIM2SsPtr, BSIM2sNode, BSIM2sNode)
            TSTALLOC(BSIM2BbPtr, BSIM2bNode, BSIM2bNode)
            TSTALLOC(BSIM2DPdpPtr, BSIM2dNodePrime, BSIM2dNodePrime)
            TSTALLOC(BSIM2SPspPtr, BSIM2sNodePrime, BSIM2sNodePrime)
            TSTALLOC(BSIM2DdpPtr, BSIM2dNode, BSIM2dNodePrime)
            TSTALLOC(BSIM2GbPtr, BSIM2gNode, BSIM2bNode)
            TSTALLOC(BSIM2GdpPtr, BSIM2gNode, BSIM2dNodePrime)
            TSTALLOC(BSIM2GspPtr, BSIM2gNode, BSIM2sNodePrime)
            TSTALLOC(BSIM2SspPtr, BSIM2sNode, BSIM2sNodePrime)
            TSTALLOC(BSIM2BdpPtr, BSIM2bNode, BSIM2dNodePrime)
            TSTALLOC(BSIM2BspPtr, BSIM2bNode, BSIM2sNodePrime)
            TSTALLOC(BSIM2DPspPtr, BSIM2dNodePrime, BSIM2sNodePrime)
            TSTALLOC(BSIM2DPdPtr, BSIM2dNodePrime, BSIM2dNode)
            TSTALLOC(BSIM2BgPtr, BSIM2bNode, BSIM2gNode)
            TSTALLOC(BSIM2DPgPtr, BSIM2dNodePrime, BSIM2gNode)
            TSTALLOC(BSIM2SPgPtr, BSIM2sNodePrime, BSIM2gNode)
            TSTALLOC(BSIM2SPsPtr, BSIM2sNodePrime, BSIM2sNode)
            TSTALLOC(BSIM2DPbPtr, BSIM2dNodePrime, BSIM2bNode)
            TSTALLOC(BSIM2SPbPtr, BSIM2sNodePrime, BSIM2bNode)
            TSTALLOC(BSIM2SPdpPtr, BSIM2sNodePrime, BSIM2dNodePrime)

        }
    }
    return(OK);
}  



