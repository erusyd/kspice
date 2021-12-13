/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1987
**********/

#include "spice.h"
#include <stdio.h>
#include "devdefs.h"
#include "ifsim.h"
#include "swdefs.h"
#include "suffix.h"

IFparm SWpTable[] = { /* parameters */ 
 IP("on",           SW_IC_ON,  IF_FLAG,"Switch initially closed"),
 IP("off",          SW_IC_OFF, IF_FLAG,"Switch initially open"),
 IOP("pos_node",    SW_POS_NODE,IF_INTEGER,"Positive node of switch"),
 IOP("neg_node",    SW_NEG_NODE,IF_INTEGER,"Negative node of switch"),
 OP("cont_p_node",SW_POS_CONT_NODE,IF_INTEGER,"Positive contr. node of switch"),
 OP("cont_n_node",SW_NEG_CONT_NODE,IF_INTEGER,"Positive contr. node of switch"),
 OP("c",            SW_CURRENT, IF_REAL,    "Switch current"),
 OP("p",            SW_POWER,   IF_REAL,    "Switch power")
};
IFparm SWmPTable[] = { /* model parameters */
 IOP( "sw",   SW_MOD_SW,   IF_FLAG,"Switch model"),
 IOP( "vt",   SW_MOD_VTH,  IF_REAL,"Threshold voltage"),
 IOP( "vh",   SW_MOD_VHYS, IF_REAL,"Hysteresis voltage"),
 IOP( "ron",  SW_MOD_RON,  IF_REAL,"Resistance when closed"),
 IOP( "roff", SW_MOD_ROFF, IF_REAL,"Resistance when open"),
 OP( "gon", SW_MOD_GON,  IF_REAL,"Conductance when closed"),
 OP( "goff", SW_MOD_GOFF, IF_REAL,"Conductance when open")
};

char *SWnames[] = {
    "S+",
    "S-",
    "SC+",
    "SC-"
};

int	SWnSize = NUMELEMS(SWnames);
int	SWpTSize = NUMELEMS(SWpTable);
int	SWmPTSize = NUMELEMS(SWmPTable);
int	SWiSize = sizeof(SWinstance);
int	SWmSize = sizeof(SWmodel);
