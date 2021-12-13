/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985      Hong June Park, Thomas L. Quarles
**********/

#ifndef BSIM1
#define BSIM1

#include "ifsim.h"
#include "gendefs.h"
#include "cktdefs.h"
#include "complex.h"

    /* declarations for BSIM1 MOSFETs */

#define BSIM1numStates 35           
#define BSIM1NDCOEFFS	82

/* information needed for each instance */

typedef struct sBSIM1instance {
    struct sBSIM1model *BSIM1modPtr;      /* pointer to model */
    struct sBSIM1instance *BSIM1nextInstance;  /* pointer to next instance of 
                                              *current model*/
    IFuid BSIM1name; /* pointer to character string naming this instance */

    int BSIM1dNode;  /* number of the gate node of the mosfet */
    int BSIM1gNode;  /* number of the gate node of the mosfet */
    int BSIM1sNode;  /* number of the source node of the mosfet */
    int BSIM1bNode;  /* number of the bulk node of the mosfet */
    int BSIM1dNodePrime; /* number of the internal drain node of the mosfet */
    int BSIM1sNodePrime; /* number of the internal source node of the mosfet */

    double BSIM1l;   /* the length of the channel region */
    double BSIM1w;   /* the width of the channel region */
    double BSIM1drainArea;   /* the area of the drain diffusion */
    double BSIM1sourceArea;  /* the area of the source diffusion */
    double BSIM1drainSquares;    /* the length of the drain in squares */
    double BSIM1sourceSquares;   /* the length of the source in squares */
    double BSIM1drainPerimeter;
    double BSIM1sourcePerimeter;
    double BSIM1sourceConductance;   /*conductance of source(or 0):set in setup*/
    double BSIM1drainConductance;    /*conductance of drain(or 0):set in setup*/

    double BSIM1icVBS;   /* initial condition B-S voltage */
    double BSIM1icVDS;   /* initial condition D-S voltage */
    double BSIM1icVGS;   /* initial condition G-S voltage */
    double BSIM1von;
    double BSIM1vdsat;
    int BSIM1off;        /* non-zero to indicate device is off for dc analysis*/
    int BSIM1mode;       /* device mode : 1 = normal, -1 = inverse */

    double BSIM1vfb;      /* flat band voltage at given L and W */
    double BSIM1phi;      /* surface potential at strong inversion */
    double BSIM1K1;       /* bulk effect coefficient 1             */
    double BSIM1K2;       /* bulk effect coefficient 2             */
    double BSIM1eta;      /* drain induced barrier lowering        */
    double BSIM1etaB;     /* Vbs dependence of Eta                 */
    double BSIM1etaD;     /* Vds dependence of Eta                 */
    double BSIM1betaZero; /* Beta at vds = 0 and vgs = Vth         */
    double BSIM1betaZeroB; /* Vbs dependence of BetaZero           */
    double BSIM1betaVdd;  /* Beta at vds=Vdd and vgs=Vth           */
    double BSIM1betaVddB; /* Vbs dependence of BVdd             */
    double BSIM1betaVddD; /* Vds dependence of BVdd             */
    double BSIM1ugs;      /* Mobility degradation due to gate field*/
    double BSIM1ugsB;     /* Vbs dependence of Ugs                 */
    double BSIM1uds;      /* Drift Velocity Saturation due to Vds  */
    double BSIM1udsB;     /* Vbs dependence of Uds                 */
    double BSIM1udsD;     /* Vds dependence of Uds                 */
    double BSIM1subthSlope; /* slope of subthreshold current with Vgs*/
    double BSIM1subthSlopeB; /* Vbs dependence of Subthreshold Slope */
    double BSIM1subthSlopeD; /* Vds dependence of Subthreshold Slope */
    double BSIM1GDoverlapCap;/* Gate Drain Overlap Capacitance       */
    double BSIM1GSoverlapCap;/* Gate Source Overlap Capacitance      */
    double BSIM1GBoverlapCap;/* Gate Bulk Overlap Capacitance        */
    double BSIM1vt0;
    double BSIM1vdd;         /* Supply Voltage                       */
    double BSIM1temp;
    double BSIM1oxideThickness;
    double BSIM1channelChargePartitionFlag;


    unsigned BSIM1lGiven :1;
    unsigned BSIM1wGiven :1;
    unsigned BSIM1drainAreaGiven :1;
    unsigned BSIM1sourceAreaGiven    :1;
    unsigned BSIM1drainSquaresGiven  :1;
    unsigned BSIM1sourceSquaresGiven :1;
    unsigned BSIM1drainPerimeterGiven    :1;
    unsigned BSIM1sourcePerimeterGiven   :1;
    unsigned BSIM1dNodePrimeSet  :1;
    unsigned BSIM1sNodePrimeSet  :1;
    unsigned BSIM1icVBSGiven :1;
    unsigned BSIM1icVDSGiven :1;
    unsigned BSIM1icVGSGiven :1;
    unsigned BSIM1vonGiven   :1;
    unsigned BSIM1vdsatGiven :1;


    double *BSIM1DdPtr;      /* pointer to sparse matrix element at
                                     * (Drain node,drain node) */
    double *BSIM1GgPtr;      /* pointer to sparse matrix element at
                                     * (gate node,gate node) */
    double *BSIM1SsPtr;      /* pointer to sparse matrix element at
                                     * (source node,source node) */
    double *BSIM1BbPtr;      /* pointer to sparse matrix element at
                                     * (bulk node,bulk node) */
    double *BSIM1DPdpPtr;    /* pointer to sparse matrix element at
                                     * (drain prime node,drain prime node) */
    double *BSIM1SPspPtr;    /* pointer to sparse matrix element at
                                     * (source prime node,source prime node) */
    double *BSIM1DdpPtr;     /* pointer to sparse matrix element at
                                     * (drain node,drain prime node) */
    double *BSIM1GbPtr;      /* pointer to sparse matrix element at
                                     * (gate node,bulk node) */
    double *BSIM1GdpPtr;     /* pointer to sparse matrix element at
                                     * (gate node,drain prime node) */
    double *BSIM1GspPtr;     /* pointer to sparse matrix element at
                                     * (gate node,source prime node) */
    double *BSIM1SspPtr;     /* pointer to sparse matrix element at
                                     * (source node,source prime node) */
    double *BSIM1BdpPtr;     /* pointer to sparse matrix element at
                                     * (bulk node,drain prime node) */
    double *BSIM1BspPtr;     /* pointer to sparse matrix element at
                                     * (bulk node,source prime node) */
    double *BSIM1DPspPtr;    /* pointer to sparse matrix element at
                                     * (drain prime node,source prime node) */
    double *BSIM1DPdPtr;     /* pointer to sparse matrix element at
                                     * (drain prime node,drain node) */
    double *BSIM1BgPtr;      /* pointer to sparse matrix element at
                                     * (bulk node,gate node) */
    double *BSIM1DPgPtr;     /* pointer to sparse matrix element at
                                     * (drain prime node,gate node) */

    double *BSIM1SPgPtr;     /* pointer to sparse matrix element at
                                     * (source prime node,gate node) */
    double *BSIM1SPsPtr;     /* pointer to sparse matrix element at
                                     * (source prime node,source node) */
    double *BSIM1DPbPtr;     /* pointer to sparse matrix element at
                                     * (drain prime node,bulk node) */
    double *BSIM1SPbPtr;     /* pointer to sparse matrix element at
                                     * (source prime node,bulk node) */
    double *BSIM1SPdpPtr;    /* pointer to sparse matrix element at
                                     * (source prime node,drain prime node) */

    int BSIM1states;     /* index into state table for this device */

#ifndef NODISTO
	double BSIM1dCoeffs[BSIM1NDCOEFFS];
#else /* NODISTO */
	double *BSIM1dCoeffs;
#endif /* NODISTO */

} BSIM1instance ;

#ifndef CONFIG

#define BSIM1vbd BSIM1states+ 0
#define BSIM1vbs BSIM1states+ 1
#define BSIM1vgs BSIM1states+ 2
#define BSIM1vds BSIM1states+ 3
#define BSIM1cd BSIM1states+ 4
#define BSIM1id BSIM1states+ 4
#define BSIM1cbs BSIM1states+ 5
#define BSIM1ibs BSIM1states+ 5
#define BSIM1cbd BSIM1states+ 6
#define BSIM1ibd BSIM1states+ 6
#define BSIM1gm BSIM1states+ 7
#define BSIM1gds BSIM1states+ 8
#define BSIM1gmbs BSIM1states+ 9
#define BSIM1gbd BSIM1states+ 10
#define BSIM1gbs BSIM1states+ 11
#define BSIM1qb BSIM1states+ 12
#define BSIM1cqb BSIM1states+ 13
#define BSIM1iqb BSIM1states+ 13
#define BSIM1qg BSIM1states+ 14
#define BSIM1cqg BSIM1states+ 15
#define BSIM1iqg BSIM1states+ 15
#define BSIM1qd BSIM1states+ 16
#define BSIM1cqd BSIM1states+ 17
#define BSIM1iqd BSIM1states+ 17
#define BSIM1cggb BSIM1states+ 18
#define BSIM1cgdb BSIM1states+ 19
#define BSIM1cgsb BSIM1states+ 20
#define BSIM1cbgb BSIM1states+ 21
#define BSIM1cbdb BSIM1states+ 22
#define BSIM1cbsb BSIM1states+ 23
#define BSIM1capbd BSIM1states+ 24
#define BSIM1iqbd BSIM1states+ 25
#define BSIM1cqbd BSIM1states+ 25
#define BSIM1capbs BSIM1states+ 26
#define BSIM1iqbs BSIM1states+ 27
#define BSIM1cqbs BSIM1states+ 27
#define BSIM1cdgb BSIM1states+ 28
#define BSIM1cddb BSIM1states+ 29
#define BSIM1cdsb BSIM1states+ 30
#define BSIM1vono BSIM1states+ 31
#define BSIM1vdsato BSIM1states+ 32
#define BSIM1qbs  BSIM1states+ 33
#define BSIM1qbd  BSIM1states+ 34

/*
 * the following naming convention is used:
 * x = vgs
 * y = vbs
 * z = vds
 * DrC is the DrCur
 * therefore qg_xyz stands for the coefficient of the vgs*vbs*vds
 * term in the multidimensional Taylor expansion for qg; and DrC_x2y
 * for the coeff. of the vgs*vgs*vbs term in the DrC expansion.
 */

#define	qg_x		BSIM1dCoeffs[0]
#define	qg_y		BSIM1dCoeffs[1]
#define	qg_z		BSIM1dCoeffs[2]
#define	qg_x2		BSIM1dCoeffs[3]
#define	qg_y2		BSIM1dCoeffs[4]
#define	qg_z2		BSIM1dCoeffs[5]
#define	qg_xy		BSIM1dCoeffs[6]
#define	qg_yz		BSIM1dCoeffs[7]
#define	qg_xz		BSIM1dCoeffs[8]
#define	qg_x3		BSIM1dCoeffs[9]
#define	qg_y3		BSIM1dCoeffs[10]
#define	qg_z3		BSIM1dCoeffs[11]
#define	qg_x2z		BSIM1dCoeffs[12]
#define	qg_x2y		BSIM1dCoeffs[13]
#define	qg_y2z		BSIM1dCoeffs[14]
#define	qg_xy2		BSIM1dCoeffs[15]
#define	qg_xz2		BSIM1dCoeffs[16]
#define	qg_yz2		BSIM1dCoeffs[17]
#define	qg_xyz		BSIM1dCoeffs[18]
#define	qb_x		BSIM1dCoeffs[19]
#define	qb_y		BSIM1dCoeffs[20]
#define	qb_z		BSIM1dCoeffs[21]
#define	qb_x2		BSIM1dCoeffs[22]
#define	qb_y2		BSIM1dCoeffs[23]
#define	qb_z2		BSIM1dCoeffs[24]
#define	qb_xy		BSIM1dCoeffs[25]
#define	qb_yz		BSIM1dCoeffs[26]
#define	qb_xz		BSIM1dCoeffs[27]
#define	qb_x3		BSIM1dCoeffs[28]
#define	qb_y3		BSIM1dCoeffs[29]
#define	qb_z3		BSIM1dCoeffs[30]
#define	qb_x2z		BSIM1dCoeffs[31]
#define	qb_x2y		BSIM1dCoeffs[32]
#define	qb_y2z		BSIM1dCoeffs[33]
#define	qb_xy2		BSIM1dCoeffs[34]
#define	qb_xz2		BSIM1dCoeffs[35]
#define	qb_yz2		BSIM1dCoeffs[36]
#define	qb_xyz		BSIM1dCoeffs[37]
#define	qd_x		BSIM1dCoeffs[38]
#define	qd_y		BSIM1dCoeffs[39]
#define	qd_z		BSIM1dCoeffs[40]
#define	qd_x2		BSIM1dCoeffs[41]
#define	qd_y2		BSIM1dCoeffs[42]
#define	qd_z2		BSIM1dCoeffs[43]
#define	qd_xy		BSIM1dCoeffs[44]
#define	qd_yz		BSIM1dCoeffs[45]
#define	qd_xz		BSIM1dCoeffs[46]
#define	qd_x3		BSIM1dCoeffs[47]
#define	qd_y3		BSIM1dCoeffs[48]
#define	qd_z3		BSIM1dCoeffs[49]
#define	qd_x2z		BSIM1dCoeffs[50]
#define	qd_x2y		BSIM1dCoeffs[51]
#define	qd_y2z		BSIM1dCoeffs[52]
#define	qd_xy2		BSIM1dCoeffs[53]
#define	qd_xz2		BSIM1dCoeffs[54]
#define	qd_yz2		BSIM1dCoeffs[55]
#define	qd_xyz		BSIM1dCoeffs[56]
#define	DrC_x		BSIM1dCoeffs[57]
#define	DrC_y		BSIM1dCoeffs[58]
#define	DrC_z		BSIM1dCoeffs[59]
#define	DrC_x2		BSIM1dCoeffs[60]
#define	DrC_y2		BSIM1dCoeffs[61]
#define	DrC_z2		BSIM1dCoeffs[62]
#define	DrC_xy		BSIM1dCoeffs[63]
#define	DrC_yz		BSIM1dCoeffs[64]
#define	DrC_xz		BSIM1dCoeffs[65]
#define	DrC_x3		BSIM1dCoeffs[66]
#define	DrC_y3		BSIM1dCoeffs[67]
#define	DrC_z3		BSIM1dCoeffs[68]
#define	DrC_x2z		BSIM1dCoeffs[69]
#define	DrC_x2y		BSIM1dCoeffs[70]
#define	DrC_y2z		BSIM1dCoeffs[71]
#define	DrC_xy2		BSIM1dCoeffs[72]
#define	DrC_xz2		BSIM1dCoeffs[73]
#define	DrC_yz2		BSIM1dCoeffs[74]
#define	DrC_xyz		BSIM1dCoeffs[75]
#define	gbs1		BSIM1dCoeffs[76]
#define	gbs2		BSIM1dCoeffs[77]
#define	gbs3		BSIM1dCoeffs[78]
#define	gbd1		BSIM1dCoeffs[79]
#define	gbd2		BSIM1dCoeffs[80]
#define	gbd3		BSIM1dCoeffs[81]

#endif


/* per model data */

typedef struct sBSIM1model {       /* model structure for a resistor */
    int BSIM1modType;    /* type index of this device type */
    struct sBSIM1model *BSIM1nextModel;    /* pointer to next possible model 
                                          *in linked list */
    BSIM1instance * BSIM1instances; /* pointer to list of instances 
                                   * that have this model */
    IFuid BSIM1modName;       /* pointer to character string naming this model */
    int BSIM1type;       /* device type : 1 = nmos,  -1 = pmos */

    double BSIM1vfb0;
    double BSIM1vfbL;
    double BSIM1vfbW;
    double BSIM1phi0;
    double BSIM1phiL;
    double BSIM1phiW;
    double BSIM1K10;
    double BSIM1K1L;
    double BSIM1K1W;
    double BSIM1K20;
    double BSIM1K2L;
    double BSIM1K2W;
    double BSIM1eta0;
    double BSIM1etaL;
    double BSIM1etaW;
    double BSIM1etaB0;
    double BSIM1etaBl;
    double BSIM1etaBw;
    double BSIM1etaD0;
    double BSIM1etaDl;
    double BSIM1etaDw;
    double BSIM1deltaL;
    double BSIM1deltaW;
    double BSIM1mobZero;
    double BSIM1mobZeroB0;
    double BSIM1mobZeroBl;
    double BSIM1mobZeroBw ;
    double BSIM1mobVdd0;
    double BSIM1mobVddl;
    double BSIM1mobVddw;
    double BSIM1mobVddB0;
    double BSIM1mobVddBl;
    double BSIM1mobVddBw;
    double BSIM1mobVddD0;
    double BSIM1mobVddDl;
    double BSIM1mobVddDw;
    double BSIM1ugs0;
    double BSIM1ugsL;
    double BSIM1ugsW;
    double BSIM1ugsB0;
    double BSIM1ugsBL;
    double BSIM1ugsBW;
    double BSIM1uds0;
    double BSIM1udsL;
    double BSIM1udsW;
    double BSIM1udsB0;
    double BSIM1udsBL;
    double BSIM1udsBW;
    double BSIM1udsD0;
    double BSIM1udsDL;
    double BSIM1udsDW;
    double BSIM1subthSlope0;
    double BSIM1subthSlopeL;
    double BSIM1subthSlopeW;
    double BSIM1subthSlopeB0;
    double BSIM1subthSlopeBL;
    double BSIM1subthSlopeBW;
    double BSIM1subthSlopeD0;
    double BSIM1subthSlopeDL;
    double BSIM1subthSlopeDW;
    double BSIM1oxideThickness;              /* unit: micron  */
    double BSIM1Cox;                         /* unit: F/cm**2 */
    double BSIM1temp;
    double BSIM1vdd;
    double BSIM1gateSourceOverlapCap;
    double BSIM1gateDrainOverlapCap;
    double BSIM1gateBulkOverlapCap;
    double BSIM1channelChargePartitionFlag;

    double BSIM1sheetResistance;
    double BSIM1jctSatCurDensity;
    double BSIM1bulkJctPotential;
    double BSIM1bulkJctBotGradingCoeff;
    double BSIM1bulkJctSideGradingCoeff;
    double BSIM1sidewallJctPotential;
    double BSIM1unitAreaJctCap;
    double BSIM1unitLengthSidewallJctCap;
    double BSIM1defaultWidth;
    double BSIM1deltaLength;


    unsigned  BSIM1vfb0Given   :1;
    unsigned  BSIM1vfbLGiven   :1;
    unsigned  BSIM1vfbWGiven   :1;
    unsigned  BSIM1phi0Given   :1;
    unsigned  BSIM1phiLGiven   :1;
    unsigned  BSIM1phiWGiven   :1;
    unsigned  BSIM1K10Given   :1;
    unsigned  BSIM1K1LGiven   :1;
    unsigned  BSIM1K1WGiven   :1;
    unsigned  BSIM1K20Given   :1;
    unsigned  BSIM1K2LGiven   :1;
    unsigned  BSIM1K2WGiven   :1;
    unsigned  BSIM1eta0Given   :1;
    unsigned  BSIM1etaLGiven   :1;
    unsigned  BSIM1etaWGiven   :1;
    unsigned  BSIM1etaB0Given   :1;
    unsigned  BSIM1etaBlGiven   :1;
    unsigned  BSIM1etaBwGiven   :1;
    unsigned  BSIM1etaD0Given   :1;
    unsigned  BSIM1etaDlGiven   :1;
    unsigned  BSIM1etaDwGiven   :1;
    unsigned  BSIM1deltaLGiven   :1;
    unsigned  BSIM1deltaWGiven   :1;
    unsigned  BSIM1mobZeroGiven   :1;
    unsigned  BSIM1mobZeroB0Given   :1;
    unsigned  BSIM1mobZeroBlGiven   :1;
    unsigned  BSIM1mobZeroBwGiven   :1;
    unsigned  BSIM1mobVdd0Given   :1;
    unsigned  BSIM1mobVddlGiven   :1;
    unsigned  BSIM1mobVddwGiven   :1;
    unsigned  BSIM1mobVddB0Given   :1;
    unsigned  BSIM1mobVddBlGiven   :1;
    unsigned  BSIM1mobVddBwGiven   :1;
    unsigned  BSIM1mobVddD0Given   :1;
    unsigned  BSIM1mobVddDlGiven   :1;
    unsigned  BSIM1mobVddDwGiven   :1;
    unsigned  BSIM1ugs0Given   :1;
    unsigned  BSIM1ugsLGiven   :1;
    unsigned  BSIM1ugsWGiven   :1;
    unsigned  BSIM1ugsB0Given   :1;
    unsigned  BSIM1ugsBLGiven   :1;
    unsigned  BSIM1ugsBWGiven   :1;
    unsigned  BSIM1uds0Given   :1;
    unsigned  BSIM1udsLGiven   :1;
    unsigned  BSIM1udsWGiven   :1;
    unsigned  BSIM1udsB0Given   :1;
    unsigned  BSIM1udsBLGiven   :1;
    unsigned  BSIM1udsBWGiven   :1;
    unsigned  BSIM1udsD0Given   :1;
    unsigned  BSIM1udsDLGiven   :1;
    unsigned  BSIM1udsDWGiven   :1;
    unsigned  BSIM1subthSlope0Given   :1;
    unsigned  BSIM1subthSlopeLGiven   :1;
    unsigned  BSIM1subthSlopeWGiven   :1;
    unsigned  BSIM1subthSlopeB0Given   :1;
    unsigned  BSIM1subthSlopeBLGiven   :1;
    unsigned  BSIM1subthSlopeBWGiven   :1;
    unsigned  BSIM1subthSlopeD0Given   :1;
    unsigned  BSIM1subthSlopeDLGiven   :1;
    unsigned  BSIM1subthSlopeDWGiven   :1;
    unsigned  BSIM1oxideThicknessGiven   :1;
    unsigned  BSIM1tempGiven   :1;
    unsigned  BSIM1vddGiven   :1;
    unsigned  BSIM1gateSourceOverlapCapGiven   :1;
    unsigned  BSIM1gateDrainOverlapCapGiven   :1;
    unsigned  BSIM1gateBulkOverlapCapGiven   :1;
    unsigned  BSIM1channelChargePartitionFlagGiven   :1;
    unsigned  BSIM1sheetResistanceGiven   :1;
    unsigned  BSIM1jctSatCurDensityGiven   :1;
    unsigned  BSIM1bulkJctPotentialGiven   :1;
    unsigned  BSIM1bulkJctBotGradingCoeffGiven   :1;
    unsigned  BSIM1sidewallJctPotentialGiven   :1;
    unsigned  BSIM1bulkJctSideGradingCoeffGiven   :1;
    unsigned  BSIM1unitAreaJctCapGiven   :1;
    unsigned  BSIM1unitLengthSidewallJctCapGiven   :1;
    unsigned  BSIM1defaultWidthGiven   :1;
    unsigned  BSIM1deltaLengthGiven   :1;
    unsigned  BSIM1typeGiven   :1;

} BSIM1model;


#ifndef NMOS
#define NMOS 1
#define PMOS -1
#endif /*NMOS*/


/* device parameters */
#define BSIM1_W 1
#define BSIM1_L 2
#define BSIM1_AS 3
#define BSIM1_AD 4
#define BSIM1_PS 5
#define BSIM1_PD 6
#define BSIM1_NRS 7
#define BSIM1_NRD 8
#define BSIM1_OFF 9
#define BSIM1_IC_VBS 10
#define BSIM1_IC_VDS 11
#define BSIM1_IC_VGS 12
#define BSIM1_IC 13

/* model parameters */
#define BSIM1_MOD_VFB0 101
#define BSIM1_MOD_VFBL 102
#define BSIM1_MOD_VFBW 103
#define BSIM1_MOD_PHI0 104
#define BSIM1_MOD_PHIL 105
#define BSIM1_MOD_PHIW 106
#define BSIM1_MOD_K10 107
#define BSIM1_MOD_K1L 108
#define BSIM1_MOD_K1W 109
#define BSIM1_MOD_K20 110
#define BSIM1_MOD_K2L 111
#define BSIM1_MOD_K2W 112
#define BSIM1_MOD_ETA0 113
#define BSIM1_MOD_ETAL 114
#define BSIM1_MOD_ETAW 115
#define BSIM1_MOD_ETAB0 116
#define BSIM1_MOD_ETABL 117
#define BSIM1_MOD_ETABW 118
#define BSIM1_MOD_ETAD0 119
#define BSIM1_MOD_ETADL 120
#define BSIM1_MOD_ETADW 121
#define BSIM1_MOD_DELTAL 122
#define BSIM1_MOD_DELTAW 123
#define BSIM1_MOD_MOBZERO 124
#define BSIM1_MOD_MOBZEROB0 125
#define BSIM1_MOD_MOBZEROBL 126
#define BSIM1_MOD_MOBZEROBW 127
#define BSIM1_MOD_MOBVDD0 128
#define BSIM1_MOD_MOBVDDL 129
#define BSIM1_MOD_MOBVDDW 130
#define BSIM1_MOD_MOBVDDB0 131
#define BSIM1_MOD_MOBVDDBL 132
#define BSIM1_MOD_MOBVDDBW 133
#define BSIM1_MOD_MOBVDDD0 134
#define BSIM1_MOD_MOBVDDDL 135
#define BSIM1_MOD_MOBVDDDW 136
#define BSIM1_MOD_UGS0 137
#define BSIM1_MOD_UGSL 138
#define BSIM1_MOD_UGSW 139
#define BSIM1_MOD_UGSB0 140
#define BSIM1_MOD_UGSBL 141
#define BSIM1_MOD_UGSBW 142
#define BSIM1_MOD_UDS0 143
#define BSIM1_MOD_UDSL 144
#define BSIM1_MOD_UDSW 145
#define BSIM1_MOD_UDSB0 146
#define BSIM1_MOD_UDSBL 147
#define BSIM1_MOD_UDSBW 148
#define BSIM1_MOD_UDSD0 149
#define BSIM1_MOD_UDSDL 150
#define BSIM1_MOD_UDSDW 151
#define BSIM1_MOD_N00 152
#define BSIM1_MOD_N0L 153
#define BSIM1_MOD_N0W 154
#define BSIM1_MOD_NB0 155
#define BSIM1_MOD_NBL 156
#define BSIM1_MOD_NBW 157
#define BSIM1_MOD_ND0 158
#define BSIM1_MOD_NDL 159
#define BSIM1_MOD_NDW 160
#define BSIM1_MOD_TOX 161
#define BSIM1_MOD_TEMP 162
#define BSIM1_MOD_VDD 163
#define BSIM1_MOD_CGSO 164
#define BSIM1_MOD_CGDO 165
#define BSIM1_MOD_CGBO 166
#define BSIM1_MOD_XPART 167
#define BSIM1_MOD_RSH 168
#define BSIM1_MOD_JS 169
#define BSIM1_MOD_PB 170
#define BSIM1_MOD_MJ 171
#define BSIM1_MOD_PBSW 172
#define BSIM1_MOD_MJSW 173
#define BSIM1_MOD_CJ 174
#define BSIM1_MOD_CJSW 175
#define BSIM1_MOD_DEFWIDTH 176
#define BSIM1_MOD_DELLENGTH 177
#define BSIM1_MOD_NMOS 178
#define BSIM1_MOD_PMOS 179

/* device questions */
#define BSIM1_DNODE              201
#define BSIM1_GNODE              202
#define BSIM1_SNODE              203
#define BSIM1_BNODE              204
#define BSIM1_DNODEPRIME         205
#define BSIM1_SNODEPRIME         206
#define BSIM1_VBD                207
#define BSIM1_VBS                208
#define BSIM1_VGS                209
#define BSIM1_VDS                210
#define BSIM1_CD         211
#define BSIM1_CBS        212
#define BSIM1_CBD        213
#define BSIM1_GM         214
#define BSIM1_GDS        215
#define BSIM1_GMBS       216
#define BSIM1_GBD        217
#define BSIM1_GBS        218
#define BSIM1_QB         219
#define BSIM1_CQB        220
#define BSIM1_QG         221
#define BSIM1_CQG        222
#define BSIM1_QD         223
#define BSIM1_CQD        224
#define BSIM1_CGG        225
#define BSIM1_CGD        226
#define BSIM1_CGS        227
#define BSIM1_CBG        228
#define BSIM1_CAPBD      231
#define BSIM1_CQBD       232
#define BSIM1_CAPBS      233
#define BSIM1_CQBS       234
#define BSIM1_CDG        235
#define BSIM1_CDD        236
#define BSIM1_CDS        237
#define BSIM1_VON        238
#define BSIM1_QBS        239
#define BSIM1_QBD        240
#define BSIM1_SOURCECONDUCT      241
#define BSIM1_DRAINCONDUCT       242

/* model questions */

#include "bsim1ext.h"

#ifdef __STDC__
extern void BSIM1evaluate(double,double,double,BSIM1instance*,BSIM1model*,
	double*,double*,double*, double*, double*, double*, double*,
	double*, double*, double*, double*, double*, double*, double*,
	double*, double*, double*, double*, CKTcircuit*);
#else /* stdc */
extern void BSIM1evaluate();
#endif /* stdc */

#endif /*BSIM1*/
