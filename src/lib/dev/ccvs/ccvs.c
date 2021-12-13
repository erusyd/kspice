/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1987 Thomas L. Quarles
**********/

#include "spice.h"
#include <stdio.h>
#include "ifsim.h"
#include "devdefs.h"
#include "ccvsdefs.h"
#include "suffix.h"

/* current controlled voltage source */
IFparm CCVSpTable[] = { /* parameters */ 
 IOP("gain",     CCVS_TRANS,   IF_REAL    ,"Transresistance (gain)"),
 IOP("control",  CCVS_CONTROL, IF_INSTANCE,"Controlling voltage source"),
 IP("sens_trans",CCVS_TRANS_SENS,IF_FLAG,  
        "flag to request sens. WRT transimpedance"),
 OP("pos_node", CCVS_POS_NODE,IF_INTEGER, "Positive node of source"),
 OP("neg_node", CCVS_NEG_NODE,IF_INTEGER, "Negative node of source"),
 OP("c",        CCVS_CURRENT, IF_REAL,    "Device current"),
 OP("p",        CCVS_POWER,   IF_REAL,    "Device power"),
 OP("sens_dc",   CCVS_QUEST_SENS_DC,  IF_REAL,   "dc sensitivity "),
 OP("sens_real", CCVS_QUEST_SENS_REAL,IF_REAL,   "real part of ac sensitivity"),
 OP("sens_imag", CCVS_QUEST_SENS_IMAG,IF_REAL,   "imag part of ac sensitivity"),
 OP("sens_mag",  CCVS_QUEST_SENS_MAG, IF_REAL,   "sensitivity of ac magnitude"),
 OP("sens_ph",   CCVS_QUEST_SENS_PH,  IF_REAL,   "sensitivity of ac phase"),
 OP("sens_cplx", CCVS_QUEST_SENS_CPLX,IF_COMPLEX,"ac sensitivity")
};

/*static IFparm CCVSmPTable[] = { /* model parameters */
/*}; /**/

char *CCVSnames[] = {
    "H+",
    "H-"
};

int	CCVSnSize = NUMELEMS(CCVSnames);
int	CCVSpTSize = NUMELEMS(CCVSpTable);
int	CCVSmPTSize = 0;
int	CCVSiSize = sizeof(CCVSinstance);
int	CCVSmSize = sizeof(CCVSmodel);
