/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
**********/
#ifdef DEV_bsim2

#ifndef DEV_BSIM2
#define DEV_BSIM2

#include "bsim2ext.h"

extern IFparm BSIM2pTable[ ];
extern IFparm BSIM2mPTable[ ];
extern char *BSIM2names[ ];
extern int BSIM2pTSize;
extern int BSIM2mPTSize;
extern int BSIM2nSize;
extern int BSIM2iSize;
extern int BSIM2mSize;

SPICEdev BSIM2info = {
    {   "BSIM2",
        "Berkeley Short Channel IGFET Model",

        &BSIM2nSize,
        &BSIM2nSize,
        BSIM2names,

        &BSIM2pTSize,
        BSIM2pTable,

        &BSIM2mPTSize,
        BSIM2mPTable,
    },

    BSIM2param,
    BSIM2mParam,
    BSIM2load,
    BSIM2setup,
    BSIM2setup,
    BSIM2temp,
    BSIM2trunc,
    NULL,
    BSIM2acLoad,
    NULL,
    BSIM2destroy,
#ifdef DELETES
    BSIM2mDelete,
    BSIM2delete, 
#else /* DELETES */
    NULL,
    NULL,
#endif /* DELETES */
    BSIM2getic,
    BSIM2ask,
    BSIM2mAsk,
#ifdef AN_pz
    BSIM2pzLoad,
#else /* AN_pz */
    NULL,
#endif /* AN_pz */
#ifdef NEWCONV
    BSIM2convTest,
#else /* NEWCONV */
    NULL,
#endif /* NEWCONV */
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,

    &BSIM2iSize,
    &BSIM2mSize

};

#endif
#endif
