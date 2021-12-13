/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
**********/
#ifdef DEV_bsim1

#ifndef DEV_BSIM1
#define DEV_BSIM1

#include "bsim1ext.h"
extern IFparm BSIM1pTable[ ];
extern IFparm BSIM1mPTable[ ];
extern char *BSIM1names[ ];
extern int BSIM1pTSize;
extern int BSIM1mPTSize;
extern int BSIM1nSize;
extern int BSIM1iSize;
extern int BSIM1mSize;

SPICEdev BSIM1info = {
    {   "BSIM1",
        "Berkeley Short Channel IGFET Model",

        &BSIM1nSize,
        &BSIM1nSize,
        BSIM1names,

        &BSIM1pTSize,
        BSIM1pTable,

        &BSIM1mPTSize,
        BSIM1mPTable,
    },

    BSIM1param,
    BSIM1mParam,
    BSIM1load,
    BSIM1setup,
    BSIM1setup,
    BSIM1temp,
    BSIM1trunc,
    NULL,
    BSIM1acLoad,
    NULL,
    BSIM1destroy,
#ifdef DELETES
    BSIM1mDelete,
    BSIM1delete, 
#else /* DELETES */
    NULL,
    NULL,
#endif /* DELETES */
    BSIM1getic,
    BSIM1ask,
    BSIM1mAsk,
#ifdef AN_pz
    BSIM1pzLoad,
#else /* AN_pz */
    NULL,
#endif /* AN_pz */
#ifdef NEWCONV
    BSIM1convTest,
#else /* NEWCONV */
    NULL,
#endif /* NEWCONV */
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
#ifdef AN_disto
    BSIM1disto,
#else
    NULL,
#endif
    NULL,	/* NOISE */

    &BSIM1iSize,
    &BSIM1mSize

};

#endif
#endif
