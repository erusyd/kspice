/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

#include "spice.h"
#include "devdefs.h"
#include "ifsim.h"
#include <stdio.h>
#include "inddefs.h"
#include "suffix.h"

IFparm INDpTable[] = { /* parameters */ 
 IOP("inductance",IND_IND,    IF_REAL,"Inductance of inductor"),
 IOP("ic",        IND_IC,     IF_REAL,"Initial current through inductor"),
 IP( "sens_ind", IND_IND_SENS,IF_FLAG,
        "flag to request sensitivity WRT inductance"),
 OP( "flux",      IND_FLUX,   IF_REAL,"Flux through inductor"),
 OP( "volt",      IND_VOLT,   IF_REAL,"Terminal voltage of inductor"),
 OP( "current",   IND_CURRENT,IF_REAL,"Current through the inductor"),
 OP( "p",         IND_POWER,  IF_REAL,
        "instantaneous power dissipated by the inductor"),
 OP( "sens_dc", IND_QUEST_SENS_DC,     IF_REAL, "dc sensitivity sensitivity"),
 OP( "sens_real", IND_QUEST_SENS_REAL, IF_REAL, "real part of ac sensitivity"),
 OP( "sens_imag", IND_QUEST_SENS_IMAG, IF_REAL, 
        "dc sensitivity and imag part of ac sensitivty"),
 OP( "sens_mag",  IND_QUEST_SENS_MAG,  IF_REAL, "sensitivity of AC magnitude"),
 OP( "sens_ph",   IND_QUEST_SENS_PH,   IF_REAL, "sensitivity of AC phase"),
 OP( "sens_cplx", IND_QUEST_SENS_CPLX, IF_COMPLEX,    "ac sensitivity")
};

/*static IFparm INDmPTable[] = { /* model parameters */
/*}; /**/

char *INDnames[] = {
    "L+",
    "L-"
};


int	INDnSize = NUMELEMS(INDnames);
int	INDpTSize = NUMELEMS(INDpTable);
int	INDmPTSize = 0;
int	INDiSize = sizeof(INDinstance);
int	INDmSize = sizeof(INDmodel);

#ifdef MUTUAL

IFparm MUTpTable[] = { /* parameters */ 
 IOP( "coefficient", MUT_COEFF, IF_REAL    , "Mutual inductance"),
 IOP( "inductor1",   MUT_IND1,  IF_INSTANCE, "First coupled inductor"),
 IOP( "inductor2",   MUT_IND2,  IF_INSTANCE, "Second coupled inductor"),
 IP( "sens_coeff",   MUT_COEFF_SENS, IF_FLAG,    
        "flag to request sensitivity WRT coupling factor"),
 OP( "sens_dc",      MUT_QUEST_SENS_DC,   IF_REAL, "dc sensitivity "),
 OP( "sens_real",  MUT_QUEST_SENS_REAL, IF_REAL, "real part of ac sensitivity"),
 OP( "sens_imag",  MUT_QUEST_SENS_IMAG, IF_REAL, 
        "dc sensitivity and imag part of ac sensitivty"),
 OP( "sens_mag",   MUT_QUEST_SENS_MAG,  IF_REAL, "sensitivity of AC magnitude"),
 OP( "sens_ph",    MUT_QUEST_SENS_PH,   IF_REAL, "sensitivity of AC phase"),
 OP( "sens_cplx",  MUT_QUEST_SENS_CPLX, IF_COMPLEX,  "ac sensitivity")
};

/*static IFparm MUTmPTable[] = { /* model parameters */
/*}; /**/

int	MUTnSize = NUMELEMS(INDnames);
int	MUTpTSize = NUMELEMS(MUTpTable);
int	MUTmPTSize = 0;
int	MUTiSize = sizeof(INDinstance);
int	MUTmSize = sizeof(INDmodel);

#endif /*MUTUAL*/
