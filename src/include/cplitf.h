#ifdef DEV_cpl

#ifndef DEV_CPL;
#define DEV_CPL;

#include "cplext.h"
extern IFparm CPLpTable[ ];
extern IFparm CPLmPTable[ ];
extern int CPLmPTSize;
extern int CPLpTSize;
extern char *CPLnames[ ];
extern int CPLiSize;
extern int CPLmSize;
extern int CPLnSize;

SPICEdev CPLinfo = {
	{
		"CplLines",
		"Simple Coupled Multiconductor Lines",

        &CPLnSize,
        &CPLnSize,
        CPLnames,

		&CPLpTSize,
		CPLpTable,

        &CPLmPTSize,
        CPLmPTable,
    },

    CPLparam,
    CPLmParam,
    CPLload,
    CPLsetup,
    NULL,
    NULL,
    NULL,
    NULL, /* CPLfindBranch, */
    NULL, 
    NULL,
    CPLdestroy,
#ifdef DELETES
    CPLmDelete,
    CPLdelete,
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

    &CPLiSize,
    &CPLmSize

};

#endif
#endif

