/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
**********/
#ifdef DEV_ccvs

#ifndef DEV_CCVS
#define DEV_CCVS

#include "ccvsext.h"
extern IFparm CCVSpTable[ ];
extern IFparm CCVSmPTable[ ];
extern char *CCVSnames[ ];
extern int CCVSpTSize;
extern int CCVSmPTSize;
extern int CCVSnSize;
extern int CCVSiSize;
extern int CCVSmSize;

SPICEdev CCVSinfo = {
    {
        "CCVS",
        "Linear current controlled current source",

        &CCVSnSize,
        &CCVSnSize,
        CCVSnames,

        &CCVSpTSize,
        CCVSpTable,

        0/*&CCVSmPTSize,
        NULL/*CCVSmPTable*/,
    },

    CCVSparam,
    NULL,
    CCVSload,
    CCVSsetup,
    CCVSsetup,
    NULL,
    NULL,
    CCVSfindBr,
    CCVSload,   /* ac and normal load functions identical */
    NULL,
    CCVSdestroy,
#ifdef DELETES
    CCVSmDelete,
    CCVSdelete,
#else /* DELETES */
    NULL,
    NULL,
#endif /* DELETES */
    NULL,
    CCVSask,
    NULL,
#ifdef AN_pz
    CCVSpzLoad,
#else /* AN_pz */
    NULL,
#endif /* AN_pz */
    NULL,
#ifdef AN_sense
    CCVSsSetup,
    CCVSsLoad,
    NULL,
    CCVSsAcLoad,
    CCVSsPrint,
    NULL,
#else /* NOSENS */
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
#endif /* NOSENS */
    NULL,	/* DISTO */
    NULL,	/* NOISE */

    &CCVSiSize,
    &CCVSmSize

};

#endif
#endif
