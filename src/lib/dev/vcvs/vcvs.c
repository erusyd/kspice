/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1987 Thomas L. Quarles
**********/

#include "spice.h"
#include <stdio.h>
#include "ifsim.h"
#include "devdefs.h"
#include "vcvsdefs.h"
#include "suffix.h"

IFparm VCVSpTable[] = { /* parameters */ 
 IOP("gain", VCVS_GAIN, IF_REAL,"Voltage gain"),
 IP("sens_gain",VCVS_GAIN_SENS,IF_FLAG,"flag to request sensitivity WRT gain"),
 OP("pos_node", VCVS_POS_NODE, IF_INTEGER, "Positive node of source"),
 OP("neg_node", VCVS_NEG_NODE, IF_INTEGER, "Negative node of source"),
 OP("cont_p_node",VCVS_CONT_P_NODE,IF_INTEGER,"Positive node of contr. source"),
 OP("cont_n_node",VCVS_CONT_N_NODE,IF_INTEGER,"Negative node of contr. source"),
 IP("ic", VCVS_IC, IF_REAL, "Initial condition of controlling source"),
 OP("c",        VCVS_CURRENT,       IF_REAL,        "Current"),
 OP("p",        VCVS_POWER,         IF_REAL,        "Power"),
 OP("sens_dc",   VCVS_QUEST_SENS_DC,  IF_REAL, "dc sensitivity "),
 OP("sens_real", VCVS_QUEST_SENS_REAL,IF_REAL, "real part of ac sensitivity"),
 OP("sens_imag", VCVS_QUEST_SENS_IMAG,IF_REAL, "imag part of ac sensitivity"),
 OP("sens_mag",  VCVS_QUEST_SENS_MAG, IF_REAL, "sensitivity of ac magnitude"),
 OP("sens_ph",   VCVS_QUEST_SENS_PH,  IF_REAL, "sensitivity of ac phase"),
 OP("sens_cplx", VCVS_QUEST_SENS_CPLX,     IF_COMPLEX,    "ac sensitivity")
};

/*static IFparm VCVSmPTable[] = { /* model parameters */
/*};/**/

char *VCVSnames[] = {
    "V+",
    "V-",
    "VC+",
    "VC-"
};

int	VCVSnSize = NUMELEMS(VCVSnames);
int	VCVSpTSize = NUMELEMS(VCVSpTable);
int	VCVSmPTSize = 0;
int	VCVSiSize = sizeof(VCVSinstance);
int	VCVSmSize = sizeof(VCVSmodel);
