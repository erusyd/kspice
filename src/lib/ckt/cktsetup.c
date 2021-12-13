/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/
/*
 */

    /* CKTsetup(ckt)
     * this is a driver program to iterate through all the various
     * setup functions provided for the circuit elements in the
     * given circuit 
     */

#include "spice.h"
#include <stdio.h>
#include "smpdefs.h"
#include "cktdefs.h"
#include "util.h"
#include "devdefs.h"
#include "sperror.h"
#include "suffix.h"


#define CKALLOC(var,size,type) \
    if(size && (!(var =(type *)MALLOC((size)*sizeof(type))))){\
            return(E_NOMEM);\
}

int
CKTsetup(ckt)
    register CKTcircuit *ckt;

{
    extern SPICEdev *DEVices[];

    register int i;
    int error;

    register SMPmatrix *matrix;
    ckt->CKTnumStates=0;


    if(ckt->CKTsenInfo){
        if (error = CKTsenSetup(ckt)) return(error);
    }

    matrix = ckt->CKTmatrix;

    for (i=0;i<DEVmaxnum;i++) {
        if ( ((*DEVices[i]).DEVsetup != NULL) && (ckt->CKThead[i] != NULL) ){
            error = (*((*DEVices[i]).DEVsetup))(matrix,ckt->CKThead[i],ckt,
                    &ckt->CKTnumStates);
            if(error) return(error);
        }
    }
    for(i=0;i<=ckt->CKTmaxOrder+1;i++) {
        CKALLOC(ckt->CKTstates[i],ckt->CKTnumStates,double);
    }
    if(ckt->CKTsenInfo){
        /* to allocate memory to sensitivity structures if 
         * it is not done before */

        error = NIsenReinit(ckt); 
        if(error) return(error);
    }
    if(ckt->CKTniState & NIUNINITIALIZED) {
        error = NIreinit(ckt);
        if(error) return(error);
    }

    return(OK);
}
