/**********
Copyright 1992 Regents of the University of California.  All rights
reserved.
Author: 1992 Charles Hough
**********/


#include "spice.h"
#include <stdio.h>
#include "util.h"
#include "txldefs.h"
#include "sperror.h"
#include "suffix.h"


int
TXLdelete(inModel,name,inst)
    GENmodel *inModel;
    IFuid name;
    GENinstance **inst;
{
    TXLmodel *model = (TXLmodel *)inModel;
    TXLinstance **fast = (TXLinstance **)inst;
    TXLinstance **prev = NULL;
    TXLinstance *here;

    for( ; model ; model = model->TXLnextModel) {
        prev = &(model->TXLinstances);
        for(here = *prev; here ; here = *prev) {
            if(here->TXLname == name || (fast && here==*fast) ) {
                *prev= here->TXLnextInstance;
                FREE(here);
                return(OK);
            }
            prev = &(here->TXLnextInstance);
        }
    }
    return(E_NODEV);
}
