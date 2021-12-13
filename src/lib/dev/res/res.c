/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/
/*
 */

#include "spice.h"
#include <stdio.h>
#include "resdefs.h"
#include "devdefs.h"
#include "ifsim.h"
#include "suffix.h"


IFparm RESpTable[] = { /* parameters */ 
 IOP( "resistance", RES_RESIST, IF_REAL,"Resistance"),
 IOP( "w",          RES_WIDTH,  IF_REAL,"Width"),
 IOP( "l",          RES_LENGTH, IF_REAL,"Length"),
 IOP( "c",          RES_CURRENT,IF_REAL,"Current"),
 IOP( "p",          RES_POWER,  IF_REAL,"Power"),
 IP("sens_resist", RES_RESIST_SENS, IF_FLAG,   
        "flag to request sensitivity WRT resistance"),
 OP("sens_dc",  RES_QUEST_SENS_DC,  IF_REAL,    "dc sensitivity "),
 OP("sens_real",RES_QUEST_SENS_REAL,IF_REAL,    
        "dc sensitivity and real part of ac sensitivity"),
 OP("sens_imag",RES_QUEST_SENS_IMAG,IF_REAL,    
        "dc sensitivity and imag part of ac sensitivity"),
 OP("sens_mag", RES_QUEST_SENS_MAG, IF_REAL,    "ac sensitivity of magnitude"),
 OP("sens_ph",  RES_QUEST_SENS_PH,  IF_REAL,    "ac sensitivity of phase"),
 OP("sens_cplx",RES_QUEST_SENS_CPLX,IF_COMPLEX,    "ac sensitivity"),
 IOP("temp",        RES_TEMP,   IF_REAL,"Instance operating temperature"),
} ;
IFparm RESmPTable[] = { /* model parameters */
 IOP( "tc1",    RES_MOD_TC1,      IF_REAL,"First order temp. coefficient"),
 IOP( "tc2",    RES_MOD_TC2,      IF_REAL,"Second order temp. coefficient"),
 IOP( "rsh",    RES_MOD_RSH,      IF_REAL,"Sheet resistance"),
 IOP( "defw",   RES_MOD_DEFWIDTH, IF_REAL,"Default device width"),
 IP( "r",      RES_MOD_R,        IF_FLAG,"Device is a resistor model"),
 IOP( "narrow", RES_MOD_NARROW,   IF_REAL,"Narrowing of resistor"),
 IOP("tnom",    RES_MOD_TNOM,     IF_REAL,"Parameter measurement temperature"),
};

char *RESnames[] = {
    "R+",
    "R-"
};

int	RESnSize = NUMELEMS(RESnames);
int	RESpTSize = NUMELEMS(RESpTable);
int	RESmPTSize = NUMELEMS(RESmPTable);
int	RESiSize = sizeof(RESinstance);
int	RESmSize = sizeof(RESmodel);
