/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
**********/
#ifdef DEV_asrc

#ifndef DEV_ASRC
#define DEV_ASRC

#include "asrcext.h"
extern IFparm ASRCpTable[ ];
extern IFparm ASRCmPTable[ ];
extern char *ASRCnames[ ];
extern int ASRCpTSize;
extern int ASRCmPTSize;
extern int ASRCnSize;
extern int ASRCiSize;
extern int ASRCmSize;

SPICEdev ASRCinfo = {
    {
        "ASRC",
        "Arbitrary Source ",

        &ASRCnSize,
        &ASRCnSize,
        ASRCnames,

        &ASRCpTSize,
        ASRCpTable,

        0/*&ASRCmPTSize,
        NULL/*ASRCmPTable*/,
    },

    ASRCparam,
    NULL,
    ASRCload,
    ASRCsetup,
    ASRCsetup,
    NULL,
    NULL,
    ASRCfindBr,
    ASRCacLoad,   /* ac and normal load functions NOT identical */
    NULL,
    ASRCdestroy,
#ifdef DELETES
    ASRCmDelete,
    ASRCdelete,
#else /* DELETES */
    NULL,
    NULL,
#endif /* DELETES */
    NULL,
    NULL,
    NULL,
#ifdef AN_pz
    ASRCpzLoad,
#else /* AN_pz */
    NULL,
#endif /* AN_pz */
#ifdef NEWCONV
    ASRCconvTest,
#else /* NEWCONV */
    NULL,
#endif /* NEWCONV */
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,	/* DISTO */
    NULL,	/* NOISE */

    &ASRCiSize,
    &ASRCmSize
};

#endif
#endif
