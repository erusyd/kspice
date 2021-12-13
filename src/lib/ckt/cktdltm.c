/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/
/*
 */

    /* CKTdltMod
     *  delete the specified model - not yet supported in spice 
     */

#include "spice.h"
#include <stdio.h>
#include "cktdefs.h"
#include "ifsim.h"
#include "sperror.h"
#include "util.h"
#include "suffix.h"


/* ARGSUSED */
int
CKTdltMod(ckt,modPtr)
    GENERIC *ckt;
    GENERIC *modPtr;
{
    return(E_UNSUPP);
}
