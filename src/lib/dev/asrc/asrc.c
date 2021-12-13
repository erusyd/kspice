/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1987 Kanwar Jit Singh
**********/

#include "spice.h"
#include <stdio.h>
#include "ifsim.h"
#include "devdefs.h"
#include "asrcdefs.h"
#include "util.h"
#include "suffix.h"

/* Arbitrary source */
IFparm ASRCpTable[] = { /* parameters */ 
 IP( "i", ASRC_CURRENT, IF_PARSETREE, "Current source "),
 IP( "v", ASRC_VOLTAGE, IF_PARSETREE, "Voltage source"),
 OP( "pos_node", ASRC_POS_NODE, IF_INTEGER, "Positive Node"),
 OP( "neg_node", ASRC_NEG_NODE, IF_INTEGER, "Negative Node")
};

/*static IFparm ASRCmPTable[] = { /* model parameters */
/*}; /**/

char *ASRCnames[] = {
    "src+",
    "src-"
};

int	ASRCnSize = NUMELEMS(ASRCnames);
int	ASRCpTSize = NUMELEMS(ASRCpTable);
int	ASRCmPTSize = 0;
int	ASRCiSize = sizeof(ASRCinstance);
int	ASRCmSize = sizeof(ASRCmodel);
