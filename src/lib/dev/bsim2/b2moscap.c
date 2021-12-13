/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Hong J. Park, Thomas L. Quarles
**********/
/*
 */

#include "spice.h"
#include <stdio.h>
#include <math.h>
#include "cktdefs.h"
#include "bsim2def.h"
#include "suffix.h"


/* routine to calculate equivalent conductance and total terminal 
 * charges
 */

void
BSIM2mosCap(ckt,vgd,vgs,vgb,GateDrainOverlapCap,GateSourceOverlapCap,
        GateBulkOverlapCap,capbd,capbs,
        cggb,cgdb,cgsb,cbgb,cbdb,cbsb,cdgb,cddb,cdsb,
        gcggbPointer,gcgdbPointer,gcgsbPointer,gcbgbPointer,gcbdbPointer,
        gcbsbPointer,gcdgbPointer,gcddbPointer,gcdsbPointer,
        gcsgbPointer,gcsdbPointer,gcssbPointer,qGatePointer,qBulkPointer,
        qDrainPointer,qSourcePointer)
    register CKTcircuit *ckt;
    double vgd;
    double vgs;
    double vgb;
    double GateDrainOverlapCap;
    double GateSourceOverlapCap;
    double GateBulkOverlapCap;
    double capbd;
    double capbs;
    double cggb;
    double cgdb;
    double cgsb;
    double cbgb;
    double cbdb;
    double cbsb;
    double cdgb;
    double cddb;
    double cdsb;
    double *gcggbPointer;
    double *gcgdbPointer;
    double *gcgsbPointer;
    double *gcbgbPointer;
    double *gcbdbPointer;
    double *gcbsbPointer;
    double *gcdgbPointer;
    double *gcddbPointer;
    double *gcdsbPointer;
    double *gcsgbPointer;
    double *gcsdbPointer;
    double *gcssbPointer;
    double *qGatePointer;
    double *qBulkPointer;
    double *qDrainPointer;
    double *qSourcePointer;

{
    double qgd;
    double qgs;
    double qgb;
    double ag0;

    ag0 = ckt->CKTag[0];
    /* compute equivalent conductance */
    *gcdgbPointer = (cdgb - GateDrainOverlapCap) * ag0;
    *gcddbPointer = (cddb + capbd + GateDrainOverlapCap) * ag0;
    *gcdsbPointer = cdsb * ag0;
    *gcsgbPointer = -(cggb + cbgb + cdgb + GateSourceOverlapCap) * ag0;
    *gcsdbPointer = -(cgdb + cbdb + cddb ) * ag0;
    *gcssbPointer = (capbs + GateSourceOverlapCap - 
        (cgsb + cbsb + cdsb )) * ag0;
    *gcggbPointer = (cggb + GateDrainOverlapCap +
        GateSourceOverlapCap + GateBulkOverlapCap ) * ag0;
    *gcgdbPointer = (cgdb - GateDrainOverlapCap) * ag0;
    *gcgsbPointer = (cgsb - GateSourceOverlapCap) * ag0;
    *gcbgbPointer = (cbgb - GateBulkOverlapCap) * ag0;
    *gcbdbPointer = (cbdb - capbd) * ag0;
    *gcbsbPointer = (cbsb - capbs) * ag0;
 
    /* compute total terminal charge */
    qgd = GateDrainOverlapCap * vgd;
    qgs = GateSourceOverlapCap * vgs;
    qgb = GateBulkOverlapCap * vgb;
    *qGatePointer = *qGatePointer + qgd + qgs + qgb;
    *qBulkPointer = *qBulkPointer - qgb;
    *qDrainPointer = *qDrainPointer - qgd;
    *qSourcePointer = -(*qGatePointer + *qBulkPointer + *qDrainPointer);

}



