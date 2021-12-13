/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1988 Min-Chie Jeng, Hong June Park, Thomas L. Quarles
**********/

#ifndef BSIM2
#define BSIM2

#include "ifsim.h"
#include "gendefs.h"
#include "cktdefs.h"
#include "complex.h"

    /* declarations for BSIM2 MOSFETs */

/* information needed for each instance */

typedef struct sBSIM2instance {
    struct sBSIM2model *BSIM2modPtr;      /* pointer to model */
    struct sBSIM2instance *BSIM2nextInstance;  /* pointer to next instance of 
                                              *current model*/
    IFuid BSIM2name; /* pointer to character string naming this instance */

    int BSIM2dNode;  /* number of the gate node of the mosfet */
    int BSIM2gNode;  /* number of the gate node of the mosfet */
    int BSIM2sNode;  /* number of the source node of the mosfet */
    int BSIM2bNode;  /* number of the bulk node of the mosfet */
    int BSIM2dNodePrime; /* number of the internal drain node of the mosfet */
    int BSIM2sNodePrime; /* number of the internal source node of the mosfet */

    double BSIM2l;   /* the length of the channel region */
    double BSIM2w;   /* the width of the channel region */
    double BSIM2drainArea;   /* the area of the drain diffusion */
    double BSIM2sourceArea;  /* the area of the source diffusion */
    double BSIM2drainSquares;    /* the length of the drain in squares */
    double BSIM2sourceSquares;   /* the length of the source in squares */
    double BSIM2drainPerimeter;
    double BSIM2sourcePerimeter;
    double BSIM2sourceConductance;   /* cond. of source (or 0): set in setup */
    double BSIM2drainConductance;    /* cond. of drain (or 0): set in setup */

    double BSIM2icVBS;   /* initial condition B-S voltage */
    double BSIM2icVDS;   /* initial condition D-S voltage */
    double BSIM2icVGS;   /* initial condition G-S voltage */
    double BSIM2von;
    double BSIM2vdsat;
    int BSIM2off;        /* non-zero to indicate device is off for dc analysis*/
    int BSIM2mode;       /* device mode : 1 = normal, -1 = inverse */

    struct bsim2SizeDependParam  *pParam;


    unsigned BSIM2lGiven :1;
    unsigned BSIM2wGiven :1;
    unsigned BSIM2drainAreaGiven :1;
    unsigned BSIM2sourceAreaGiven    :1;
    unsigned BSIM2drainSquaresGiven  :1;
    unsigned BSIM2sourceSquaresGiven :1;
    unsigned BSIM2drainPerimeterGiven    :1;
    unsigned BSIM2sourcePerimeterGiven   :1;
    unsigned BSIM2dNodePrimeSet  :1;
    unsigned BSIM2sNodePrimeSet  :1;
    unsigned BSIM2icVBSGiven :1;
    unsigned BSIM2icVDSGiven :1;
    unsigned BSIM2icVGSGiven :1;
    unsigned BSIM2vonGiven   :1;
    unsigned BSIM2vdsatGiven :1;


    double *BSIM2DdPtr;      /* pointer to sparse matrix element at
                                     * (Drain node,drain node) */
    double *BSIM2GgPtr;      /* pointer to sparse matrix element at
                                     * (gate node,gate node) */
    double *BSIM2SsPtr;      /* pointer to sparse matrix element at
                                     * (source node,source node) */
    double *BSIM2BbPtr;      /* pointer to sparse matrix element at
                                     * (bulk node,bulk node) */
    double *BSIM2DPdpPtr;    /* pointer to sparse matrix element at
                                     * (drain prime node,drain prime node) */
    double *BSIM2SPspPtr;    /* pointer to sparse matrix element at
                                     * (source prime node,source prime node) */
    double *BSIM2DdpPtr;     /* pointer to sparse matrix element at
                                     * (drain node,drain prime node) */
    double *BSIM2GbPtr;      /* pointer to sparse matrix element at
                                     * (gate node,bulk node) */
    double *BSIM2GdpPtr;     /* pointer to sparse matrix element at
                                     * (gate node,drain prime node) */
    double *BSIM2GspPtr;     /* pointer to sparse matrix element at
                                     * (gate node,source prime node) */
    double *BSIM2SspPtr;     /* pointer to sparse matrix element at
                                     * (source node,source prime node) */
    double *BSIM2BdpPtr;     /* pointer to sparse matrix element at
                                     * (bulk node,drain prime node) */
    double *BSIM2BspPtr;     /* pointer to sparse matrix element at
                                     * (bulk node,source prime node) */
    double *BSIM2DPspPtr;    /* pointer to sparse matrix element at
                                     * (drain prime node,source prime node) */
    double *BSIM2DPdPtr;     /* pointer to sparse matrix element at
                                     * (drain prime node,drain node) */
    double *BSIM2BgPtr;      /* pointer to sparse matrix element at
                                     * (bulk node,gate node) */
    double *BSIM2DPgPtr;     /* pointer to sparse matrix element at
                                     * (drain prime node,gate node) */

    double *BSIM2SPgPtr;     /* pointer to sparse matrix element at
                                     * (source prime node,gate node) */
    double *BSIM2SPsPtr;     /* pointer to sparse matrix element at
                                     * (source prime node,source node) */
    double *BSIM2DPbPtr;     /* pointer to sparse matrix element at
                                     * (drain prime node,bulk node) */
    double *BSIM2SPbPtr;     /* pointer to sparse matrix element at
                                     * (source prime node,bulk node) */
    double *BSIM2SPdpPtr;    /* pointer to sparse matrix element at
                                     * (source prime node,drain prime node) */

    int BSIM2states;     /* index into state table for this device */
#define BSIM2vbd BSIM2states+ 0
#define BSIM2vbs BSIM2states+ 1
#define BSIM2vgs BSIM2states+ 2
#define BSIM2vds BSIM2states+ 3
#define BSIM2cd BSIM2states+ 4
#define BSIM2id BSIM2states+ 4
#define BSIM2cbs BSIM2states+ 5
#define BSIM2ibs BSIM2states+ 5
#define BSIM2cbd BSIM2states+ 6
#define BSIM2ibd BSIM2states+ 6
#define BSIM2gm BSIM2states+ 7
#define BSIM2gds BSIM2states+ 8
#define BSIM2gmbs BSIM2states+ 9
#define BSIM2gbd BSIM2states+ 10
#define BSIM2gbs BSIM2states+ 11
#define BSIM2qb BSIM2states+ 12
#define BSIM2cqb BSIM2states+ 13
#define BSIM2iqb BSIM2states+ 13
#define BSIM2qg BSIM2states+ 14
#define BSIM2cqg BSIM2states+ 15
#define BSIM2iqg BSIM2states+ 15
#define BSIM2qd BSIM2states+ 16
#define BSIM2cqd BSIM2states+ 17
#define BSIM2iqd BSIM2states+ 17
#define BSIM2cggb BSIM2states+ 18
#define BSIM2cgdb BSIM2states+ 19
#define BSIM2cgsb BSIM2states+ 20
#define BSIM2cbgb BSIM2states+ 21
#define BSIM2cbdb BSIM2states+ 22
#define BSIM2cbsb BSIM2states+ 23
#define BSIM2capbd BSIM2states+ 24
#define BSIM2iqbd BSIM2states+ 25
#define BSIM2cqbd BSIM2states+ 25
#define BSIM2capbs BSIM2states+ 26
#define BSIM2iqbs BSIM2states+ 27
#define BSIM2cqbs BSIM2states+ 27
#define BSIM2cdgb BSIM2states+ 28
#define BSIM2cddb BSIM2states+ 29
#define BSIM2cdsb BSIM2states+ 30
#define BSIM2vono BSIM2states+ 31
#define BSIM2vdsato BSIM2states+ 32
#define BSIM2qbs  BSIM2states+ 33
#define BSIM2qbd  BSIM2states+ 34

#define BSIM2numStates 35           

} BSIM2instance ;

struct bsim2SizeDependParam
{
    double Width;
    double Length;
    double BSIM2vfb;      /* flat band voltage at given L and W */
    double BSIM2phi;      /* surface potential at strong inversion */
    double BSIM2k1;       /* bulk effect coefficient 1             */
    double BSIM2k2;       /* bulk effect coefficient 2             */
    double BSIM2eta0;      /* drain induced barrier lowering        */
    double BSIM2etaB;     /* Vbs dependence of Eta                 */
    double BSIM2beta0;    /* Beta at Vds = 0 and Vgs = Vth         */
    double BSIM2beta0B;   /* Vbs dependence of Beta0               */
    double BSIM2betas0;    /* Beta at Vds=Vdd and Vgs=Vth           */
    double BSIM2betasB;   /* Vbs dependence of Betas               */
    double BSIM2beta20;   /* Vds dependence of Beta in tanh term   */
    double BSIM2beta2B;   /* Vbs dependence of Beta2               */
    double BSIM2beta2G;   /* Vgs dependence of Beta2               */
    double BSIM2beta30;   /* Vds dependence of Beta in linear term */
    double BSIM2beta3B;   /* Vbs dependence of Beta3               */
    double BSIM2beta3G;   /* Vgs dependence of Beta3               */
    double BSIM2beta40;   /* Vds dependence of Beta in quadra term */
    double BSIM2beta4B;   /* Vbs dependence of Beta4               */
    double BSIM2beta4G;   /* Vgs dependence of Beta4               */
    double BSIM2ua0;      /* Linear Vgs dependence of Mobility     */
    double BSIM2uaB;      /* Vbs dependence of Ua                  */
    double BSIM2ub0;      /* Quadratic Vgs dependence of Mobility  */
    double BSIM2ubB;      /* Vbs dependence of Ub                  */
    double BSIM2u10;      /* Drift Velocity Saturation due to Vds  */
    double BSIM2u1B;      /* Vbs dependence of U1                  */
    double BSIM2u1D;      /* Vds dependence of U1                  */
    double BSIM2n0;       /* Subthreshold slope at Vds=0, Vbs=0    */
    double BSIM2nB;       /* Vbs dependence of n                   */
    double BSIM2nD;       /* Vds dependence of n                   */
    double BSIM2vof0;     /* Vth offset at Vds=0, Vbs=0            */
    double BSIM2vofB;     /* Vbs dependence of Vof                 */
    double BSIM2vofD;     /* Vds dependence of Vof                 */
    double BSIM2ai0;      /* Pre-factor in hot-electron effects    */
    double BSIM2aiB;      /* Vbs dependence of Ai                  */
    double BSIM2bi0;      /* Exp-factor in hot-electron effects    */
    double BSIM2biB;      /* Vbs dependence of Bi                  */
    double BSIM2vghigh;   /* Upper bound of cubic spline function  */
    double BSIM2vglow;    /* Lower bound of cubic spline function  */
    double BSIM2GDoverlapCap;/* Gate Drain Overlap Capacitance     */
    double BSIM2GSoverlapCap;/* Gate Source Overlap Capacitance    */
    double BSIM2GBoverlapCap;/* Gate Bulk Overlap Capacitance      */
    double SqrtPhi;
    double Phis3;
    double CoxWL;
    double One_Third_CoxWL;
    double Two_Third_CoxWL;
    double Arg;
    double BSIM2vt0;
    struct bsim2SizeDependParam  *pNext;
};


/* per model data */

typedef struct sBSIM2model {       	/* model structure for a resistor */
    int BSIM2modType;    		/* type index of this device type */
    struct sBSIM2model *BSIM2nextModel; /* pointer to next possible model 
                                         *in linked list */
    BSIM2instance * BSIM2instances;	/* pointer to list of instances 
                                   	 * that have this model */
    IFuid BSIM2modName;       		/* pointer to the name of this model */
    int BSIM2type;       		/* device type: 1 = nmos,  -1 = pmos */
    int pad;

    double BSIM2vfb0;
    double BSIM2vfbL;
    double BSIM2vfbW;
    double BSIM2phi0;
    double BSIM2phiL;
    double BSIM2phiW;
    double BSIM2k10;
    double BSIM2k1L;
    double BSIM2k1W;
    double BSIM2k20;
    double BSIM2k2L;
    double BSIM2k2W;
    double BSIM2eta00;
    double BSIM2eta0L;
    double BSIM2eta0W;
    double BSIM2etaB0;
    double BSIM2etaBL;
    double BSIM2etaBW;
    double BSIM2deltaL;
    double BSIM2deltaW;
    double BSIM2mob00;
    double BSIM2mob0B0;
    double BSIM2mob0BL;
    double BSIM2mob0BW ;
    double BSIM2mobs00;
    double BSIM2mobs0L;
    double BSIM2mobs0W;
    double BSIM2mobsB0;
    double BSIM2mobsBL;
    double BSIM2mobsBW;
    double BSIM2mob200;
    double BSIM2mob20L;
    double BSIM2mob20W;
    double BSIM2mob2B0;
    double BSIM2mob2BL;
    double BSIM2mob2BW;
    double BSIM2mob2G0;
    double BSIM2mob2GL;
    double BSIM2mob2GW;
    double BSIM2mob300;
    double BSIM2mob30L;
    double BSIM2mob30W;
    double BSIM2mob3B0;
    double BSIM2mob3BL;
    double BSIM2mob3BW;
    double BSIM2mob3G0;
    double BSIM2mob3GL;
    double BSIM2mob3GW;
    double BSIM2mob400;
    double BSIM2mob40L;
    double BSIM2mob40W;
    double BSIM2mob4B0;
    double BSIM2mob4BL;
    double BSIM2mob4BW;
    double BSIM2mob4G0;
    double BSIM2mob4GL;
    double BSIM2mob4GW;
    double BSIM2ua00;
    double BSIM2ua0L;
    double BSIM2ua0W;
    double BSIM2uaB0;
    double BSIM2uaBL;
    double BSIM2uaBW;
    double BSIM2ub00;
    double BSIM2ub0L;
    double BSIM2ub0W;
    double BSIM2ubB0;
    double BSIM2ubBL;
    double BSIM2ubBW;
    double BSIM2u100;
    double BSIM2u10L;
    double BSIM2u10W;
    double BSIM2u1B0;
    double BSIM2u1BL;
    double BSIM2u1BW;
    double BSIM2u1D0;
    double BSIM2u1DL;
    double BSIM2u1DW;
    double BSIM2n00;
    double BSIM2n0L;
    double BSIM2n0W;
    double BSIM2nB0;
    double BSIM2nBL;
    double BSIM2nBW;
    double BSIM2nD0;
    double BSIM2nDL;
    double BSIM2nDW;
    double BSIM2vof00;
    double BSIM2vof0L;
    double BSIM2vof0W;
    double BSIM2vofB0;
    double BSIM2vofBL;
    double BSIM2vofBW;
    double BSIM2vofD0;
    double BSIM2vofDL;
    double BSIM2vofDW;
    double BSIM2ai00;
    double BSIM2ai0L;
    double BSIM2ai0W;
    double BSIM2aiB0;
    double BSIM2aiBL;
    double BSIM2aiBW;
    double BSIM2bi00;
    double BSIM2bi0L;
    double BSIM2bi0W;
    double BSIM2biB0;
    double BSIM2biBL;
    double BSIM2biBW;
    double BSIM2vghigh0;
    double BSIM2vghighL;
    double BSIM2vghighW;
    double BSIM2vglow0;
    double BSIM2vglowL;
    double BSIM2vglowW;
    double BSIM2tox;              /* unit: micron  */
    double BSIM2Cox;                         /* unit: F/cm**2 */
    double BSIM2temp;
    double BSIM2vdd;
    double BSIM2vdd2;
    double BSIM2vgg;
    double BSIM2vgg2;
    double BSIM2vbb;
    double BSIM2vbb2;
    double BSIM2gateSourceOverlapCap;
    double BSIM2gateDrainOverlapCap;
    double BSIM2gateBulkOverlapCap;
    double BSIM2channelChargePartitionFlag;
    double BSIM2Vtm;

    double BSIM2sheetResistance;
    double BSIM2jctSatCurDensity;
    double BSIM2bulkJctPotential;
    double BSIM2bulkJctBotGradingCoeff;
    double BSIM2bulkJctSideGradingCoeff;
    double BSIM2sidewallJctPotential;
    double BSIM2unitAreaJctCap;
    double BSIM2unitLengthSidewallJctCap;
    double BSIM2defaultWidth;
    double BSIM2deltaLength;

    struct bsim2SizeDependParam  *pSizeDependParamKnot;


    unsigned  BSIM2vfb0Given   :1;
    unsigned  BSIM2vfbLGiven   :1;
    unsigned  BSIM2vfbWGiven   :1;
    unsigned  BSIM2phi0Given   :1;
    unsigned  BSIM2phiLGiven   :1;
    unsigned  BSIM2phiWGiven   :1;
    unsigned  BSIM2k10Given   :1;
    unsigned  BSIM2k1LGiven   :1;
    unsigned  BSIM2k1WGiven   :1;
    unsigned  BSIM2k20Given   :1;
    unsigned  BSIM2k2LGiven   :1;
    unsigned  BSIM2k2WGiven   :1;
    unsigned  BSIM2eta00Given   :1;
    unsigned  BSIM2eta0LGiven   :1;
    unsigned  BSIM2eta0WGiven   :1;
    unsigned  BSIM2etaB0Given   :1;
    unsigned  BSIM2etaBLGiven   :1;
    unsigned  BSIM2etaBWGiven   :1;
    unsigned  BSIM2deltaLGiven   :1;
    unsigned  BSIM2deltaWGiven   :1;
    unsigned  BSIM2mob00Given   :1;
    unsigned  BSIM2mob0B0Given   :1;
    unsigned  BSIM2mob0BLGiven   :1;
    unsigned  BSIM2mob0BWGiven   :1;
    unsigned  BSIM2mobs00Given   :1;
    unsigned  BSIM2mobs0LGiven   :1;
    unsigned  BSIM2mobs0WGiven   :1;
    unsigned  BSIM2mobsB0Given   :1;
    unsigned  BSIM2mobsBLGiven   :1;
    unsigned  BSIM2mobsBWGiven   :1;
    unsigned  BSIM2mob200Given   :1;
    unsigned  BSIM2mob20LGiven   :1;
    unsigned  BSIM2mob20WGiven   :1;
    unsigned  BSIM2mob2B0Given   :1;
    unsigned  BSIM2mob2BLGiven   :1;
    unsigned  BSIM2mob2BWGiven   :1;
    unsigned  BSIM2mob2G0Given   :1;
    unsigned  BSIM2mob2GLGiven   :1;
    unsigned  BSIM2mob2GWGiven   :1;
    unsigned  BSIM2mob300Given   :1;
    unsigned  BSIM2mob30LGiven   :1;
    unsigned  BSIM2mob30WGiven   :1;
    unsigned  BSIM2mob3B0Given   :1;
    unsigned  BSIM2mob3BLGiven   :1;
    unsigned  BSIM2mob3BWGiven   :1;
    unsigned  BSIM2mob3G0Given   :1;
    unsigned  BSIM2mob3GLGiven   :1;
    unsigned  BSIM2mob3GWGiven   :1;
    unsigned  BSIM2mob400Given   :1;
    unsigned  BSIM2mob40LGiven   :1;
    unsigned  BSIM2mob40WGiven   :1;
    unsigned  BSIM2mob4B0Given   :1;
    unsigned  BSIM2mob4BLGiven   :1;
    unsigned  BSIM2mob4BWGiven   :1;
    unsigned  BSIM2mob4G0Given   :1;
    unsigned  BSIM2mob4GLGiven   :1;
    unsigned  BSIM2mob4GWGiven   :1;
    unsigned  BSIM2ua00Given   :1;
    unsigned  BSIM2ua0LGiven   :1;
    unsigned  BSIM2ua0WGiven   :1;
    unsigned  BSIM2uaB0Given   :1;
    unsigned  BSIM2uaBLGiven   :1;
    unsigned  BSIM2uaBWGiven   :1;
    unsigned  BSIM2ub00Given   :1;
    unsigned  BSIM2ub0LGiven   :1;
    unsigned  BSIM2ub0WGiven   :1;
    unsigned  BSIM2ubB0Given   :1;
    unsigned  BSIM2ubBLGiven   :1;
    unsigned  BSIM2ubBWGiven   :1;
    unsigned  BSIM2u100Given   :1;
    unsigned  BSIM2u10LGiven   :1;
    unsigned  BSIM2u10WGiven   :1;
    unsigned  BSIM2u1B0Given   :1;
    unsigned  BSIM2u1BLGiven   :1;
    unsigned  BSIM2u1BWGiven   :1;
    unsigned  BSIM2u1D0Given   :1;
    unsigned  BSIM2u1DLGiven   :1;
    unsigned  BSIM2u1DWGiven   :1;
    unsigned  BSIM2n00Given   :1;
    unsigned  BSIM2n0LGiven   :1;
    unsigned  BSIM2n0WGiven   :1;
    unsigned  BSIM2nB0Given   :1;
    unsigned  BSIM2nBLGiven   :1;
    unsigned  BSIM2nBWGiven   :1;
    unsigned  BSIM2nD0Given   :1;
    unsigned  BSIM2nDLGiven   :1;
    unsigned  BSIM2nDWGiven   :1;
    unsigned  BSIM2vof00Given   :1;
    unsigned  BSIM2vof0LGiven   :1;
    unsigned  BSIM2vof0WGiven   :1;
    unsigned  BSIM2vofB0Given   :1;
    unsigned  BSIM2vofBLGiven   :1;
    unsigned  BSIM2vofBWGiven   :1;
    unsigned  BSIM2vofD0Given   :1;
    unsigned  BSIM2vofDLGiven   :1;
    unsigned  BSIM2vofDWGiven   :1;
    unsigned  BSIM2ai00Given   :1;
    unsigned  BSIM2ai0LGiven   :1;
    unsigned  BSIM2ai0WGiven   :1;
    unsigned  BSIM2aiB0Given   :1;
    unsigned  BSIM2aiBLGiven   :1;
    unsigned  BSIM2aiBWGiven   :1;
    unsigned  BSIM2bi00Given   :1;
    unsigned  BSIM2bi0LGiven   :1;
    unsigned  BSIM2bi0WGiven   :1;
    unsigned  BSIM2biB0Given   :1;
    unsigned  BSIM2biBLGiven   :1;
    unsigned  BSIM2biBWGiven   :1;
    unsigned  BSIM2vghigh0Given    :1;
    unsigned  BSIM2vghighLGiven    :1;
    unsigned  BSIM2vghighWGiven    :1;
    unsigned  BSIM2vglow0Given     :1;
    unsigned  BSIM2vglowLGiven     :1;
    unsigned  BSIM2vglowWGiven     :1;
    unsigned  BSIM2toxGiven   :1;
    unsigned  BSIM2tempGiven   :1;
    unsigned  BSIM2vddGiven   :1;
    unsigned  BSIM2vggGiven   :1;
    unsigned  BSIM2vbbGiven   :1;
    unsigned  BSIM2gateSourceOverlapCapGiven   :1;
    unsigned  BSIM2gateDrainOverlapCapGiven   :1;
    unsigned  BSIM2gateBulkOverlapCapGiven   :1;
    unsigned  BSIM2channelChargePartitionFlagGiven   :1;
    unsigned  BSIM2sheetResistanceGiven   :1;
    unsigned  BSIM2jctSatCurDensityGiven   :1;
    unsigned  BSIM2bulkJctPotentialGiven   :1;
    unsigned  BSIM2bulkJctBotGradingCoeffGiven   :1;
    unsigned  BSIM2sidewallJctPotentialGiven   :1;
    unsigned  BSIM2bulkJctSideGradingCoeffGiven   :1;
    unsigned  BSIM2unitAreaJctCapGiven   :1;
    unsigned  BSIM2unitLengthSidewallJctCapGiven   :1;
    unsigned  BSIM2defaultWidthGiven   :1;
    unsigned  BSIM2deltaLengthGiven   :1;
    unsigned  BSIM2typeGiven   :1;

} BSIM2model;


#ifndef NMOS
#define NMOS 1
#define PMOS -1
#endif /*NMOS*/


/* device parameters */
#define BSIM2_W 1
#define BSIM2_L 2
#define BSIM2_AS 3
#define BSIM2_AD 4
#define BSIM2_PS 5
#define BSIM2_PD 6
#define BSIM2_NRS 7
#define BSIM2_NRD 8
#define BSIM2_OFF 9
#define BSIM2_IC_VBS 10
#define BSIM2_IC_VDS 11
#define BSIM2_IC_VGS 12
#define BSIM2_IC 13

/* model parameters */
#define BSIM2_MOD_VFB0 101
#define BSIM2_MOD_VFBL 102
#define BSIM2_MOD_VFBW 103
#define BSIM2_MOD_PHI0 104
#define BSIM2_MOD_PHIL 105
#define BSIM2_MOD_PHIW 106
#define BSIM2_MOD_K10 107
#define BSIM2_MOD_K1L 108
#define BSIM2_MOD_K1W 109
#define BSIM2_MOD_K20 110
#define BSIM2_MOD_K2L 111
#define BSIM2_MOD_K2W 112
#define BSIM2_MOD_ETA00 113
#define BSIM2_MOD_ETA0L 114
#define BSIM2_MOD_ETA0W 115
#define BSIM2_MOD_ETAB0 116
#define BSIM2_MOD_ETABL 117
#define BSIM2_MOD_ETABW 118
#define BSIM2_MOD_DELTAL 119
#define BSIM2_MOD_DELTAW 120
#define BSIM2_MOD_MOB00 121
#define BSIM2_MOD_MOB0B0 122
#define BSIM2_MOD_MOB0BL 123
#define BSIM2_MOD_MOB0BW 124
#define BSIM2_MOD_MOBS00 125
#define BSIM2_MOD_MOBS0L 126
#define BSIM2_MOD_MOBS0W 127
#define BSIM2_MOD_MOBSB0 128
#define BSIM2_MOD_MOBSBL 129
#define BSIM2_MOD_MOBSBW 130
#define BSIM2_MOD_MOB200 131
#define BSIM2_MOD_MOB20L 132
#define BSIM2_MOD_MOB20W 133
#define BSIM2_MOD_MOB2B0 134
#define BSIM2_MOD_MOB2BL 135
#define BSIM2_MOD_MOB2BW 136
#define BSIM2_MOD_MOB2G0 137
#define BSIM2_MOD_MOB2GL 138
#define BSIM2_MOD_MOB2GW 139
#define BSIM2_MOD_MOB300 140
#define BSIM2_MOD_MOB30L 141
#define BSIM2_MOD_MOB30W 142
#define BSIM2_MOD_MOB3B0 143
#define BSIM2_MOD_MOB3BL 144
#define BSIM2_MOD_MOB3BW 145
#define BSIM2_MOD_MOB3G0 146
#define BSIM2_MOD_MOB3GL 147
#define BSIM2_MOD_MOB3GW 148
#define BSIM2_MOD_MOB400 149
#define BSIM2_MOD_MOB40L 150
#define BSIM2_MOD_MOB40W 151
#define BSIM2_MOD_MOB4B0 152
#define BSIM2_MOD_MOB4BL 153
#define BSIM2_MOD_MOB4BW 154
#define BSIM2_MOD_MOB4G0 155
#define BSIM2_MOD_MOB4GL 156
#define BSIM2_MOD_MOB4GW 157
#define BSIM2_MOD_UA00 158
#define BSIM2_MOD_UA0L 159
#define BSIM2_MOD_UA0W 160
#define BSIM2_MOD_UAB0 161
#define BSIM2_MOD_UABL 162
#define BSIM2_MOD_UABW 163
#define BSIM2_MOD_UB00 164
#define BSIM2_MOD_UB0L 165
#define BSIM2_MOD_UB0W 166
#define BSIM2_MOD_UBB0 167
#define BSIM2_MOD_UBBL 168
#define BSIM2_MOD_UBBW 169
#define BSIM2_MOD_U100 170
#define BSIM2_MOD_U10L 171
#define BSIM2_MOD_U10W 172
#define BSIM2_MOD_U1B0 173
#define BSIM2_MOD_U1BL 174
#define BSIM2_MOD_U1BW 175
#define BSIM2_MOD_U1D0 176
#define BSIM2_MOD_U1DL 177
#define BSIM2_MOD_U1DW 178
#define BSIM2_MOD_N00 179
#define BSIM2_MOD_N0L 180
#define BSIM2_MOD_N0W 181
#define BSIM2_MOD_NB0 182
#define BSIM2_MOD_NBL 183
#define BSIM2_MOD_NBW 184
#define BSIM2_MOD_ND0 185
#define BSIM2_MOD_NDL 186
#define BSIM2_MOD_NDW 187
#define BSIM2_MOD_VOF00 188
#define BSIM2_MOD_VOF0L 189
#define BSIM2_MOD_VOF0W 190
#define BSIM2_MOD_VOFB0 191
#define BSIM2_MOD_VOFBL 192
#define BSIM2_MOD_VOFBW 193
#define BSIM2_MOD_VOFD0 194
#define BSIM2_MOD_VOFDL 195
#define BSIM2_MOD_VOFDW 196
#define BSIM2_MOD_AI00 197
#define BSIM2_MOD_AI0L 198
#define BSIM2_MOD_AI0W 199
#define BSIM2_MOD_AIB0 200
#define BSIM2_MOD_AIBL 201
#define BSIM2_MOD_AIBW 202
#define BSIM2_MOD_BI00 203
#define BSIM2_MOD_BI0L 204
#define BSIM2_MOD_BI0W 205
#define BSIM2_MOD_BIB0 206
#define BSIM2_MOD_BIBL 207
#define BSIM2_MOD_BIBW 208
#define BSIM2_MOD_VGHIGH0 209
#define BSIM2_MOD_VGHIGHL 210
#define BSIM2_MOD_VGHIGHW 211
#define BSIM2_MOD_VGLOW0 212
#define BSIM2_MOD_VGLOWL 213
#define BSIM2_MOD_VGLOWW 214
#define BSIM2_MOD_TOX 215
#define BSIM2_MOD_TEMP 216
#define BSIM2_MOD_VDD 217
#define BSIM2_MOD_VGG 218
#define BSIM2_MOD_VBB 219
#define BSIM2_MOD_CGSO 220
#define BSIM2_MOD_CGDO 221
#define BSIM2_MOD_CGBO 222
#define BSIM2_MOD_XPART 223
#define BSIM2_MOD_RSH 224
#define BSIM2_MOD_JS 225
#define BSIM2_MOD_PB 226
#define BSIM2_MOD_MJ 227
#define BSIM2_MOD_PBSW 228
#define BSIM2_MOD_MJSW 229
#define BSIM2_MOD_CJ 230
#define BSIM2_MOD_CJSW 231
#define BSIM2_MOD_DEFWIDTH 232
#define BSIM2_MOD_DELLENGTH 233
#define BSIM2_MOD_NMOS 234
#define BSIM2_MOD_PMOS 235

/* device questions */
#define BSIM2_DNODE              241
#define BSIM2_GNODE              242
#define BSIM2_SNODE              243
#define BSIM2_BNODE              244
#define BSIM2_DNODEPRIME         245
#define BSIM2_SNODEPRIME         246
#define BSIM2_VBD                247
#define BSIM2_VBS                248
#define BSIM2_VGS                249
#define BSIM2_VDS                250
#define BSIM2_CD         251
#define BSIM2_CBS        252
#define BSIM2_CBD        253
#define BSIM2_GM         254
#define BSIM2_GDS        255
#define BSIM2_GMBS       256
#define BSIM2_GBD        257
#define BSIM2_GBS        258
#define BSIM2_QB         259
#define BSIM2_CQB        260
#define BSIM2_QG         261
#define BSIM2_CQG        262
#define BSIM2_QD         263
#define BSIM2_CQD        264
#define BSIM2_CGG        265
#define BSIM2_CGD        266
#define BSIM2_CGS        267
#define BSIM2_CBG        268
#define BSIM2_CAPBD      269
#define BSIM2_CQBD       270
#define BSIM2_CAPBS      271
#define BSIM2_CQBS       272
#define BSIM2_CDG        273
#define BSIM2_CDD        274
#define BSIM2_CDS        275
#define BSIM2_VON        276
#define BSIM2_QBS        277
#define BSIM2_QBD        278
#define BSIM2_SOURCECONDUCT      279
#define BSIM2_DRAINCONDUCT       280

/* model questions */

#include "bsim2ext.h"

#ifdef __STDC__
extern void BSIM2evaluate(double,double,double,BSIM2instance*,BSIM2model*,
        double*,double*,double*, double*, double*, double*, double*, 
        double*, double*, double*, double*, double*, double*, double*, 
        double*, double*, double*, double*, CKTcircuit*);
#else /* stdc */
extern void BSIM2evaluate();
#endif /* stdc */

#endif /*BSIM2*/

