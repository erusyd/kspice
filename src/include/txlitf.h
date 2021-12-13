/**********
Copyright 1992 Regents of the University of California.  All rights
reserved.
Author: 1992 Charles Hough
**********/
#ifdef DEV_txl

#ifndef DEV_TXL;
#define DEV_TXL;

#include "txlext.h"
extern IFparm TXLpTable[ ];
extern IFparm TXLmPTable[ ];
extern int TXLmPTSize;
extern int TXLpTSize;
extern char *TXLnames[ ];
extern int TXLiSize;
extern int TXLmSize;
extern int TXLnSize;

SPICEdev TXLinfo = {
	{
		"TransLine",
		"Simple Lossy Transmission Line",

        &TXLnSize,
        &TXLnSize,
        TXLnames,

		&TXLpTSize,
		TXLpTable,

        &TXLmPTSize,
        TXLmPTable,
    },

    TXLparam,
    TXLmParam,
    TXLload,
    TXLsetup,
    NULL,
    NULL,
    NULL,
    NULL, /* TXLfindBranch, */
    TXLload, /* ac load */
    NULL,
    TXLdestroy,
#ifdef DELETES
    TXLmDelete,
    TXLdelete,
#else /* DELETES */
    NULL,
    NULL,
#endif /* DELETES */
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
	NULL,
	NULL,

    &TXLiSize,
    &TXLmSize

};

#endif
#endif

