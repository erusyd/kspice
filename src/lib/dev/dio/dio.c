/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

#include "spice.h"
#include <stdio.h>
#include "devdefs.h"
#include "diodefs.h"
#include "suffix.h"

IFparm DIOpTable[] = { /* parameters */ 
 IOP("off",    DIO_OFF,    IF_FLAG, "Initially off"),
 IOP("temp",   DIO_TEMP,   IF_REAL, "Instance temperature"),
 IOP("ic",     DIO_IC,     IF_REAL, "Initial device voltage"),
 IOP("area",   DIO_AREA,   IF_REAL, "Area factor"),
 IP("sens_area",DIO_AREA_SENS,IF_FLAG,"flag to request sensitivity WRT area"),
 OP("voltage",DIO_VOLTAGE,IF_REAL, "Diode voltage"),
 OP("current",DIO_CURRENT,IF_REAL, "Diode current"),
 OP("charge", DIO_CHARGE, IF_REAL, "Diode capacitor charge"),
 OP("capcur", DIO_CAPCUR, IF_REAL, "Diode capacitor current"),
 OP("cond",   DIO_CONDUCT,IF_REAL, "Diode conductance"),
 OP("p",      DIO_POWER,  IF_REAL, "Diode power"),
 OP("c",      DIO_CURRENT,IF_REAL, "Diode current"),
 OP("sens_dc",DIO_QUEST_SENS_DC,     IF_REAL,   "dc sensitivity "),
 OP("sens_real", DIO_QUEST_SENS_REAL,IF_REAL,   
        "dc sens. and real part of ac sensitivity"),
 OP("sens_imag", DIO_QUEST_SENS_IMAG,IF_REAL,   "imag part of ac sensitivity "),
 OP("sens_mag",  DIO_QUEST_SENS_MAG, IF_REAL,   "sensitivity of ac magnitude"),
 OP("sens_ph",   DIO_QUEST_SENS_PH,  IF_REAL,   "sensitivity of ac phase"),
 OP("sens_cplx", DIO_QUEST_SENS_CPLX,IF_COMPLEX,"ac sensitivity")
};
IFparm DIOmPTable[] = { /* model parameters */
 IOP( "is",  DIO_MOD_IS,  IF_REAL, "Saturation current"),
 IOP( "tnom",DIO_MOD_TNOM,IF_REAL, "Parameter measurement temperature"),
 IOP( "rs",  DIO_MOD_RS,  IF_REAL, "Ohmic resistance"),
 IOP( "n",   DIO_MOD_N,   IF_REAL, "Emission Coefficient"),
 IOP( "tt",  DIO_MOD_TT,  IF_REAL, "Transit Time"),
 IOP( "cjo", DIO_MOD_CJO, IF_REAL, "Junction capacitance"),
 IOP( "cj0", DIO_MOD_CJO, IF_REAL, "Junction capacitance"),
 IOP( "vj",  DIO_MOD_VJ,  IF_REAL, "Junction potential"),
 IOP( "m",   DIO_MOD_M,   IF_REAL, "Grading coefficient"),
 IOP( "eg",  DIO_MOD_EG,  IF_REAL, "Activation energy"),
 IOP( "xti", DIO_MOD_XTI, IF_REAL, "Saturation current temperature exp."),
 IOP( "fc",  DIO_MOD_FC,  IF_REAL, "Forward bias junction fit parameter"),
 IOP( "bv",  DIO_MOD_BV,  IF_REAL, "Reverse breakdown voltage"),
 IOP( "ibv", DIO_MOD_IBV, IF_REAL, "Current at reverse breakdown voltage"),
 OP( "cond", DIO_MOD_COND,IF_REAL, "Ohmic conductance"),
 IP( "d",    DIO_MOD_D,   IF_FLAG, "Diode model"),
 IP( "kf",   DIO_MOD_KF,  IF_REAL, "flicker noise coefficient"),
 IP( "af",   DIO_MOD_AF,  IF_REAL, "flicker noise exponent")
};

char *DIOnames[] = {
    "D+",
    "D-"
};

int	DIOnSize = NUMELEMS(DIOnames);
int	DIOpTSize = NUMELEMS(DIOpTable);
int	DIOmPTSize = NUMELEMS(DIOmPTable);
int	DIOiSize = sizeof(DIOinstance);
int	DIOmSize = sizeof(DIOmodel);
