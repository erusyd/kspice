/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/
/*
 */

    /* CKTdltNod
     *  delete the specified node - not yet supported in spice 
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
CKTdltNod(ckt,node)
    GENERIC *ckt;
    GENERIC *node;
{
    return(E_UNSUPP);
}
