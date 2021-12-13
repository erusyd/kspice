/**********
Copyright 1990 Regents of the University of California.  All rights
reserved.
Author: 1990 Jaijeet S. Roychowdhury
**********/

/*
 * This file defines the LTRA data structures that are available to the
 * next level(s) up the calling hierarchy
 */

#include "spice.h"
#include <stdio.h>
#include <math.h>
#include "devdefs.h"
#include "ifsim.h"
#include "ltradefs.h"
#include "suffix.h"


IFparm LTRApTable[] = { /* parameters */ 
 IOP( "v1", LTRA_V1,   IF_REAL   , "Initial voltage at end 1"),
 IOP( "v2", LTRA_V2,   IF_REAL   , "Initial voltage at end 2"),
 IOP( "i1", LTRA_I1,   IF_REAL   , "Initial current at end 1"),
 IOP( "i2", LTRA_I2,   IF_REAL   , "Initial current at end 2"),
 IP("ic", LTRA_IC,   IF_REALVEC,"Initial condition vector:v1,i1,v2,i2"),
 OP( "pos_node1", LTRA_POS_NODE1,IF_INTEGER,"Positive node of end 1 of t. line"),
 OP( "neg_node1", LTRA_NEG_NODE1,IF_INTEGER,"Negative node of end 1 of t. line"),
 OP( "pos_node2", LTRA_POS_NODE2,IF_INTEGER,"Positive node of end 2 of t. line"),
 OP( "neg_node2", LTRA_NEG_NODE2,IF_INTEGER,"Negative node of end 2 of t. line"),
};

IFparm LTRAmPTable[] = { /* model parameters */
 IOP( "ltra",	LTRA_MOD_LTRA,	IF_FLAG,	"LTRA model"),
 IOP( "r", LTRA_MOD_R,   IF_REAL   , "Resistance per metre"),
 IOP( "l", LTRA_MOD_L,   IF_REAL   , "Inductance per metre"),
 IOP( "g", LTRA_MOD_G,   IF_REAL   , "Conductance per metre"),
 IOP( "c", LTRA_MOD_C,   IF_REAL   , "Capacitance per metre"),
 IOP( "len", LTRA_MOD_LEN,   IF_REAL   , "length of line"),
/*
 IOP( "f",  LTRA_MOD_FREQ, IF_REAL   , "Frequency"),
 IOP( "nl", LTRA_MOD_NL,   IF_REAL   , "Normalized length at frequency given"),
*/
 OP( "rel", LTRA_MOD_RELTOL,   IF_REAL   , "Rel. rate of change of deriv. for bkpt"),
 OP( "abs", LTRA_MOD_ABSTOL,   IF_REAL   , "Abs. rate of change of deriv. for bkpt"),
/*
 IOP( "fullcontrol",	LTRA_MOD_FULLCONTROL,	IF_FLAG,	"rigorous timestep control"),
 IOP( "halfcontrol",	LTRA_MOD_HALFCONTROL,	IF_FLAG,	"only the current step is considered for timestep control"),
*/
 IOP( "nocontrol",	LTRA_MOD_NOCONTROL,	IF_FLAG,	"No timestep control"),
/*
 IOP( "print",	LTRA_MOD_PRINT,	IF_FLAG,	"printing of debugging info on"),
 IOP( "noprint",	LTRA_MOD_NOPRINT,	IF_FLAG,	"printing of debugging info off"),
 IOP( "ronly",	LTRA_MOD_RONLY,	IF_FLAG,	"use special load routines for G=0"),
 */
 IOP( "steplimit",	LTRA_MOD_STEPLIMIT,	IF_FLAG,	"always limit timestep to 0.8*(delay of line)"),
 IOP( "nosteplimit",	LTRA_MOD_NOSTEPLIMIT,	IF_FLAG,	"don't always limit timestep to 0.8*(delay of line)"),
 IOP( "lininterp",	LTRA_MOD_LININTERP,	IF_FLAG,	"use linear interpolation"),
 IOP( "quadinterp",	LTRA_MOD_QUADINTERP,	IF_FLAG,	"use quadratic interpolation"),
 IOP( "mixedinterp",	LTRA_MOD_MIXEDINTERP,	IF_FLAG,	"use linear interpolation only if quadratic interpolation results look unacceptable"),
 IOP( "truncnr",	LTRA_MOD_TRUNCNR,	IF_FLAG,	"use N-R iterations for step calculation in LTRAtrunc"),
 IOP( "truncdontcut",	LTRA_MOD_TRUNCDONTCUT,	IF_FLAG,	"don't limit timestep to keep impulse response calculation  errors low"),
 IOP( "compactrel",	LTRA_MOD_STLINEREL,	IF_REAL,	"special reltol for straight line checking"),
 IOP( "compactabs",	LTRA_MOD_STLINEABS,	IF_REAL,	"special abstol for straight line checking"),
 /*
 IOP( "choprel",	LTRA_MOD_CHOPREL,	IF_REAL,	"special reltol for truncation of impulse responses"),
 IOP( "chopabs",	LTRA_MOD_CHOPABS,	IF_REAL,	"special abstol for truncation of impulse responses "),
*/
};/**/

char *LTRAnames[] = {
    "P1+",
    "P1-",
    "P2+",
    "P2-"
};

int	LTRAnSize = NUMELEMS(LTRAnames);
int	LTRApTSize = NUMELEMS(LTRApTable);
int	LTRAmPTSize = NUMELEMS(LTRAmPTable);
int	LTRAiSize = sizeof(LTRAinstance);
int	LTRAmSize = sizeof(LTRAmodel);
