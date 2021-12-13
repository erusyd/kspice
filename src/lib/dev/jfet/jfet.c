/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

#include "spice.h"
#include <stdio.h>
#include "ifsim.h"
#include "devdefs.h"
#include "jfetdefs.h"
#include "suffix.h"

IFparm JFETpTable[] = { /* device parameters */ 
 IOP("off",         JFET_OFF,            IF_FLAG,   "Device initially off"),
 IOP("ic",          JFET_IC,             IF_REALVEC,"Initial VDS,VGS vector"),
 IOP("area",        JFET_AREA,           IF_REAL,   "Area factor"),
 IOP("ic-vds",      JFET_IC_VDS,         IF_REAL,   "Initial D-S voltage"),
 IOP("ic-vgs",      JFET_IC_VGS,         IF_REAL,   "Initial G-S volrage"),
 IOP("temp",        JFET_TEMP,           IF_REAL,   "Instance temperature"),
 OP("drain-node",   JFET_DRAINNODE,      IF_INTEGER,"Number of drain node"),
 OP("gate-node",    JFET_GATENODE,       IF_INTEGER,"Number of gate node"),
 OP("source-node",  JFET_SOURCENODE,     IF_INTEGER,"Number of source node"),
 OP("drain-prime-node", JFET_DRAINPRIMENODE, IF_INTEGER,"Internal drain node"),
 OP("source-prime-node",JFET_SOURCEPRIMENODE,IF_INTEGER,"Internal source node"),
 OP("vgs",          JFET_VGS,            IF_REAL,   "Voltage G-S"),
 OP("vgd",          JFET_VGD,            IF_REAL,   "Voltage G-D"),
 OP("cg",           JFET_CG,             IF_REAL,   "Current at gate node"),
 OP("cd",           JFET_CD,             IF_REAL,   "Current at drain node"),
 OP("cgd",          JFET_CGD,            IF_REAL,   "Current G-D"),
 OP("gm",           JFET_GM,             IF_REAL,   "Transconductance"),
 OP("gds",          JFET_GDS,            IF_REAL,   "Conductance D-S"),
 OP("ggs",          JFET_GGS,            IF_REAL,   "Conductance G-S"),
 OP("ggd",          JFET_GGD,            IF_REAL,   "Conductance G-D"),
 OP("qgs", JFET_QGS,  IF_REAL,"Charge storage G-S junction"),
 OP("cqgs",JFET_CQGS, IF_REAL,"Capacitance due to charge storage G-S junction"),
 OP("qgd", JFET_QGD,  IF_REAL,"Charge storage G-D junction"),
 OP("cqgd",JFET_CQGD, IF_REAL,"Capacitance due to charge storage G-D junction"),
 OP("cs",  JFET_CS,   IF_REAL,"Source current"),
 OP("p",   JFET_POWER,IF_REAL,"Power dissipated by the JFET"),
 OP("kf",  JFET_MOD_KF,IF_REAL,"Flicker Noise Coefficient"),
 OP("af",  JFET_MOD_KF,IF_REAL,"Flicker Noise Exponent")
};

IFparm JFETmPTable[] = { /* model parameters */
 IOP("vt0",     JFET_MOD_VTO,      IF_REAL,"Threshold voltage"),
 IOP("vto",     JFET_MOD_VTO,      IF_REAL,"Threshold voltage"),
 IOP("beta",    JFET_MOD_BETA,     IF_REAL,"Transconductance parameter"),
 IOP("lambda",  JFET_MOD_LAMBDA,   IF_REAL,"Channel length modulation param."),
 IOP("rd",      JFET_MOD_RD,       IF_REAL,"Drain ohmic resistance"),
 IOP("rs",      JFET_MOD_RS,       IF_REAL,"Source ohmic resistance"),
 IOP("cgs",     JFET_MOD_CGS,      IF_REAL,"G-S junction capactance"),
 IOP("cgd",     JFET_MOD_CGD,      IF_REAL,"G-D junction cap"),
 IOP("pb",      JFET_MOD_PB,       IF_REAL,"Gate junction potential"),
 IOP("is",      JFET_MOD_IS,       IF_REAL,"Gate junction saturation current"),
 IOP("fc",      JFET_MOD_FC,       IF_REAL,"Forward bias junction fir parm."),
 IOP("njf",     JFET_MOD_NJF,      IF_FLAG,"N type JFET model"),
 IOP("pjf",     JFET_MOD_PJF,      IF_FLAG,"P type JFET model"),
 IOP("tnom",    JFET_MOD_TNOM,     IF_REAL,"parameter measurement temperature"),
 OP("drainconduct", JFET_MOD_DRAINCONDUCT, IF_REAL,"Drain conductance"),
 OP("sourceconduct",JFET_MOD_SOURCECONDUCT,IF_REAL,"Source conductance")
};


char *JFETnames[] = {
    "Drain",
    "Gate",
    "Source"
};

int	JFETnSize = NUMELEMS(JFETnames);
int	JFETpTSize = NUMELEMS(JFETpTable);
int	JFETmPTSize = NUMELEMS(JFETmPTable);
int	JFETiSize = sizeof(JFETinstance);
int	JFETmSize = sizeof(JFETmodel);
