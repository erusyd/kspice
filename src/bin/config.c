/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
**********/

#include "spice.h"

#ifdef DEVICES_USED
static char *devs = DEVICES_USED;
#endif
#ifdef ANALYSES_USED
static char *ans = ANALYSES_USED;
#endif

#define CONFIG

#include <stdio.h>
#include "noisedef.h"
#include "devdefs.h"
#include "suffix.h"

#include "asrcitf.h"
#include "bjtitf.h"
#include "capitf.h"
#include "cccsitf.h"
#include "ccvsitf.h"
#include "cswitf.h"
#include "dioitf.h"
#include "inditf.h"
#include "isrcitf.h"
#include "mos1itf.h"
#include "mos6itf.h"
#include "resitf.h"
#include "switf.h"
#include "vccsitf.h"
#include "vcvsitf.h"
#include "vsrcitf.h"

#include "bsim1itf.h"
#include "bsim2itf.h"
#include "mos2itf.h"
#include "mos3itf.h"
#include "jfetitf.h"
#include "mesitf.h"
#include "ltraitf.h"
#include "traitf.h"
#include "txlitf.h"
#include "cplitf.h"
#include "urcitf.h"

#ifndef AN_dc

#ifdef AN_ac
#define AN_dc
#endif
#ifdef AN_pz
#define AN_dc
#endif
#ifdef AN_tran
#define AN_dc
#endif
#ifdef AN_noise
#define AN_dc
#endif
#ifdef AN_disto
#define AN_dc
#endif
#ifdef AN_sense
#define AN_dc
#endif

#endif

extern SPICEanalysis OPTinfo;
extern SPICEanalysis ACinfo;
extern SPICEanalysis DCTinfo;
extern SPICEanalysis DCOinfo;
extern SPICEanalysis TRANinfo;
extern SPICEanalysis PZinfo;
extern SPICEanalysis SENinfo;
extern SPICEanalysis TFinfo;
extern SPICEanalysis DISTOinfo;
extern SPICEanalysis NOISEinfo;

SPICEanalysis *analInfo[] = {
    &OPTinfo,
#ifdef AN_ac
    &ACinfo,
#endif
#ifdef AN_dc
    &DCTinfo,
#endif
#ifdef AN_op
    &DCOinfo,
#endif
#ifdef AN_tran
    &TRANinfo,
#endif
#ifdef AN_pz
    &PZinfo,
#endif
#ifdef AN_sense
    &SENinfo,
#endif
#ifdef AN_tf
    &TFinfo,
#endif
#ifdef AN_disto
    &DISTOinfo,
#endif
#ifdef AN_noise
    &NOISEinfo,
#endif
};

int ANALmaxnum = sizeof(analInfo)/sizeof(SPICEanalysis*);
SPICEdev *DEVices[] = {

#ifdef DEV_asrc
        &ASRCinfo,
#endif
#ifdef DEV_bjt
        &BJTinfo,
#endif
#ifdef DEV_bsim1
        &BSIM1info,
#endif
#ifdef DEV_bsim2
        &BSIM2info,
#endif
#ifdef DEV_cap
        &CAPinfo,
#endif
#ifdef DEV_cccs
        &CCCSinfo,
#endif
#ifdef DEV_ccvs
        &CCVSinfo,
#endif
#ifdef DEV_csw
        &CSWinfo,
#endif
#ifdef DEV_dio
        &DIOinfo,
#endif
#ifdef DEV_ind
        &INDinfo,
        &MUTinfo,
#endif
#ifdef DEV_isrc
        &ISRCinfo,
#endif
#ifdef DEV_jfet
        &JFETinfo,
#endif
#ifdef DEV_ltra
        &LTRAinfo,
#endif
#ifdef DEV_mes
        &MESinfo,
#endif
#ifdef DEV_mos1
        &MOS1info,
#endif
#ifdef DEV_mos2
        &MOS2info,
#endif
#ifdef DEV_mos3
        &MOS3info,
#endif
#ifdef DEV_mos6
        &MOS6info,
#endif
#ifdef DEV_res
        &RESinfo,
#endif
#ifdef DEV_sw
        &SWinfo,
#endif
#ifdef DEV_tra
        &TRAinfo,
#endif
#ifdef DEV_cpl
        &CPLinfo,
#endif
#ifdef DEV_txl
        &TXLinfo,
#endif
#ifdef DEV_urc
        &URCinfo,
#endif
#ifdef DEV_vccs
        &VCCSinfo,
#endif
#ifdef DEV_vcvs
        &VCVSinfo,
#endif
#ifdef DEV_vsrc
        &VSRCinfo,
#endif
};

/* my internal global constant for number of device types */
int DEVmaxnum = sizeof(DEVices)/sizeof(SPICEdev *);
/* XXX Should be -1 ? There is always an extra null element at the end ? */
static char * specSigList[] = {
    "time"
};

static IFparm nodeParms[] = {
    IP( "nodeset",PARM_NS ,IF_REAL,"suggested initial voltage"),
    IP( "ic",PARM_IC ,IF_REAL,"initial voltage"),
    IP( "type",PARM_NODETYPE ,IF_INTEGER,"output type of equation")
};

IFsimulator SIMinfo = {
    "KSPICE",        /* name */
    "circuit level simulator with fast transmission line simulation",  /* more about me */
    Spice_Version,          /* version */

    CKTinit,        /* newCircuit function */
    CKTdestroy,     /* deleteCircuit function */

    CKTnewNode,     /* newNode function */
    CKTground,      /* groundNode function */
    CKTbindNode,    /* bindNode function */
    CKTfndNode,     /* findNode function */
    CKTinst2Node,   /* instToNode function */
    CKTsetNodPm,    /* setNodeParm function */
    CKTaskNodQst,   /* askNodeQuest function */
    CKTdltNod,      /* deleteNode function */

    CKTcrtElt,      /* newInstance function */
    CKTparam,       /* setInstanceParm function */
    CKTask,         /* askInstanceQuest function */
    CKTfndDev,      /* findInstance funciton */
    CKTdltInst,     /* deleteInstance function */

    CKTmodCrt,      /* newModel function */
    CKTmodParam,    /* setModelParm function */
    CKTmodAsk,      /* askModelQuest function */
    CKTfndMod,      /* findModel function */
    CKTdltMod,      /* deleteModel function */

    CKTnewTask,     /* newTask function */
    CKTnewAnal,     /* newAnalysis function */
    CKTsetAnalPm,   /* setAnalysisParm function */
    CKTaskAnalQ,    /* askAnalysisQuest function */
    CKTfndAnal,     /* findAnalysis function */
    CKTfndTask,     /* findTask function */
    CKTdelTask,     /* deleteTask function */

    CKTdoJob,       /* doAnalyses function */
    CKTtrouble,	    /* non-convergence message function */

    sizeof(DEVices)/sizeof(SPICEdev *),
    (IFdevice**)DEVices,

    sizeof(analInfo)/sizeof(SPICEanalysis *),
    (IFanalysis **)analInfo,

    sizeof(nodeParms)/sizeof(IFparm),
    nodeParms,

    sizeof(specSigList)/sizeof(char *),
    specSigList,

};
