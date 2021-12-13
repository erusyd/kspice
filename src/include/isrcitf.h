/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
**********/
#ifdef DEV_isrc

#ifndef DEV_ISRC
#define DEV_ISRC

#include "isrcext.h"
extern IFparm ISRCpTable[ ];
extern IFparm ISRCmPTable[ ];
extern char *ISRCnames[ ];
extern int ISRCpTSize;
extern int ISRCmPTSize;
extern int ISRCnSize;
extern int ISRCiSize;
extern int ISRCmSize;

SPICEdev ISRCinfo = {
    {
        "Isource",  
        "Independent current source",

        &ISRCnSize,
        &ISRCnSize,
        ISRCnames,

        &ISRCpTSize,
        ISRCpTable,

        0/*&ISRCmPTSize,
        NULL/*ISRCmPTable/**/,
    },

    ISRCparam,
    NULL,
    ISRCload,
    NULL,
    NULL,
    ISRCtemp,
    NULL,
    NULL,
    ISRCacLoad,
    ISRCaccept,
    ISRCdestroy,
#ifdef DELETES
    ISRCmDelete,
    ISRCdelete,
#else /* DELETES */
    NULL,
    NULL,
#endif /* DELETES */
    NULL,
    ISRCask,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,	/* DISTO */
    NULL,	/* NOISE */

    &ISRCiSize,
    &ISRCmSize
};


#endif
#endif
