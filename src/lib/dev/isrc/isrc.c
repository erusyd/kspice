/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1987 Thomas L. Quarles
**********/

#include "spice.h"
#include <stdio.h>
#include "ifsim.h"
#include "devdefs.h"
#include "isrcdefs.h"
#include "suffix.h"

IFparm ISRCpTable[] = { /* parameters */ 
 IOP( "dc",      ISRC_DC,        IF_REAL   ,"DC value of source"),
 IOP( "acmag",   ISRC_AC_MAG,    IF_REAL   ,"AC magnitude"),
 IOP( "acphase", ISRC_AC_PHASE,  IF_REAL   ,"AC phase"),
 IP ( "pulse",   ISRC_PULSE,     IF_REALVEC,"Pulse description"),
 IP ( "sine",    ISRC_SINE,      IF_REALVEC,"Sinusoidal source description"),
 IP ( "sin",     ISRC_SINE,      IF_REALVEC,"Sinusoidal source description"),
 IP ( "exp",     ISRC_EXP,       IF_REALVEC,"Exponential source description"),
 IP ( "pwl",     ISRC_PWL,       IF_REALVEC,"Piecewise linear description"),
 IP ( "sffm",    ISRC_SFFM,      IF_REALVEC,"single freq. FM description"),
 OP ( "neg_node",ISRC_NEG_NODE,  IF_INTEGER,"Negative node of source"),
 OP ( "pos_node",ISRC_POS_NODE,  IF_INTEGER,"Positive node of source"),
 OP ( "acreal",  ISRC_AC_REAL,   IF_REAL   ,"AC real part"),
 OP ( "acimag",  ISRC_AC_IMAG,   IF_REAL   ,"AC imaginary part"),
 OP ( "function",ISRC_FCN_TYPE,  IF_INTEGER,"Function of the source"),
 OP ( "order",   ISRC_FCN_ORDER, IF_INTEGER,"Order of the source function"),
 OP ( "coeffs",  ISRC_FCN_COEFFS,IF_REALVEC,"Coefficients of the source"),
 IP ( "ac",      ISRC_AC,        IF_REALVEC,"AC magnitude,phase vector"),
 IP ( "p",       ISRC_POWER,     IF_REAL,   "Power supplied by the source"),
 IP ( "c",       ISRC_DC,        IF_REAL,   "Current through current source"),
 IP ( "distof1", ISRC_D_F1,      IF_REALVEC,"f1 input for distortion"),
 IP ( "distof2", ISRC_D_F1,      IF_REALVEC,"f2 input for distortion"),
};

/*static IFparm ISRCmPTable[] = { /* model parameters */ 
/*}; /**/

char *ISRCnames[] = {
    "I+",
    "I-"
};

int	ISRCnSize = NUMELEMS(ISRCnames);
int	ISRCpTSize = NUMELEMS(ISRCpTable);
int	ISRCmPTSize = 0;
int	ISRCiSize = sizeof(ISRCinstance);
int	ISRCmSize = sizeof(ISRCmodel);
