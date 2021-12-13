/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1987 Thomas L. Quarles
**********/

#include "spice.h"
#include <stdio.h>
#include "ifsim.h"
#include "devdefs.h"
#include "cccsdefs.h"
#include "suffix.h"

IFparm CCCSpTable[] = { /* parameters */ 
 IOP("gain",    CCCS_GAIN,    IF_REAL    ,"Gain of source"),
 IOP("control", CCCS_CONTROL, IF_INSTANCE,"Name of controlling source"),
 IP("sens_gain",CCCS_GAIN_SENS,IF_FLAG, "flag to request sensitivity WRT gain"),
 OP("neg_node", CCCS_NEG_NODE,IF_INTEGER, "Negative node of source"),
 OP("pos_node", CCCS_POS_NODE,IF_INTEGER, "Positive node of source"),
 OP("c",        CCCS_CURRENT, IF_REAL,    "CCCS current"),
 OP("p",        CCCS_POWER,   IF_REAL,    "CCCS current"),
 OP("sens_dc",  CCCS_QUEST_SENS_DC,  IF_REAL,    "dc sensitivity "),
 OP("sens_real",CCCS_QUEST_SENS_REAL,IF_REAL,    "real part of ac sensitivity"),
 OP("sens_imag",CCCS_QUEST_SENS_IMAG,IF_REAL,    "imag part of ac sensitivity"),
 OP("sens_mag", CCCS_QUEST_SENS_MAG, IF_REAL,    "sensitivity of ac magnitude"),
 OP("sens_ph",  CCCS_QUEST_SENS_PH,  IF_REAL,    "sensitivity of ac phase"),
 OP("sens_cplx",CCCS_QUEST_SENS_CPLX,IF_COMPLEX, "ac sensitivity")

};

/* static IFparm CCCSmPTable[] = { /* model parameters */ 
/*};*/

char *CCCSnames[] = {
    "F+",
    "F-"
};

int	CCCSnSize = NUMELEMS(CCCSnames);
int	CCCSpTSize = NUMELEMS(CCCSpTable);
int	CCCSmPTSize = 0;
int	CCCSiSize = sizeof(CCCSinstance);
int	CCCSmSize = sizeof(CCCSmodel);
