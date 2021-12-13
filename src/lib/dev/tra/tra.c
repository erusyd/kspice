/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1987 Thomas L. Quarles
**********/

#include "spice.h"
#include <stdio.h>
#include "devdefs.h"
#include "ifsim.h"
#include "tradefs.h"
#include "suffix.h"

IFparm TRApTable[] = { /* parameters */ 
 IOP( "z0", TRA_Z0,   IF_REAL   , "Characteristic impedance"),
 IOP( "zo", TRA_Z0,   IF_REAL   , "Characteristic impedance"),
 IOP( "f",  TRA_FREQ, IF_REAL   , "Frequency"),
 IOP( "td", TRA_TD,   IF_REAL   , "Transmission delay"),
 IOP( "nl", TRA_NL,   IF_REAL   , "Normalized length at frequency given"),
 IOP( "v1", TRA_V1,   IF_REAL   , "Initial voltage at end 1"),
 IOP( "v2", TRA_V2,   IF_REAL   , "Initial voltage at end 2"),
 IOP( "i1", TRA_I1,   IF_REAL   , "Initial current at end 1"),
 IOP( "i2", TRA_I2,   IF_REAL   , "Initial current at end 2"),
 IP("ic", TRA_IC,   IF_REALVEC,"Initial condition vector:v1,i1,v2,i2"),
 OP( "rel", TRA_RELTOL,   IF_REAL   , "Rel. rate of change of deriv. for bkpt"),
 OP( "abs", TRA_ABSTOL,   IF_REAL   , "Abs. rate of change of deriv. for bkpt"),
 OP( "pos_node1", TRA_POS_NODE1,IF_INTEGER,"Positive node of end 1 of t. line"),
 OP( "neg_node1", TRA_NEG_NODE1,IF_INTEGER,"Negative node of end 1 of t. line"),
 OP( "pos_node2", TRA_POS_NODE2,IF_INTEGER,"Positive node of end 2 of t. line"),
 OP( "neg_node2", TRA_NEG_NODE2,IF_INTEGER,"Negative node of end 2 of t. line"),
 OP( "delays",TRA_DELAY, IF_REALVEC, "Delayed values of excitation")
};

/*static IFparm TRAmPTable[] = { /* model parameters */
/*};/**/

char *TRAnames[] = {
    "P1+",
    "P1-",
    "P2+",
    "P2-"
};

int	TRAnSize = NUMELEMS(TRAnames);
int	TRApTSize = NUMELEMS(TRApTable);
int	TRAmPTSize = 0;
int	TRAiSize = sizeof(TRAinstance);
int	TRAmSize = sizeof(TRAmodel);
