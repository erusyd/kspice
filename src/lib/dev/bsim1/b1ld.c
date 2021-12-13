/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Hong J. Park, Thomas L. Quarles
**********/

#include "spice.h"
#include <stdio.h>
#include <math.h>
#include "util.h"
#include "cktdefs.h"
#include "bsim1def.h"
#include "trandefs.h"
#include "const.h"
#include "sperror.h"
#include "devdefs.h"
#include "suffix.h"


int
BSIM1load(inModel,ckt)

    GENmodel *inModel;
    register CKTcircuit *ckt;

        /* actually load the current value into the 
         * sparse matrix previously provided 
         */
{
    register BSIM1model *model = (BSIM1model*)inModel;
    register BSIM1instance *here;
    double DrainSatCurrent = 0.0;
    double EffectiveLength = 0.0;
    double GateBulkOverlapCap = 0.0;
    double GateDrainOverlapCap = 0.0;
    double GateSourceOverlapCap = 0.0;
    double SourceSatCurrent = 0.0;
    double DrainArea = 0.0;
    double SourceArea = 0.0;
    double DrainPerimeter = 0.0;
    double SourcePerimeter = 0.0;
    double arg = 0.0;
    double capbd = 0.0;
    double capbs = 0.0;
    double cbd = 0.0;
    double cbhat = 0.0;
    double cbs = 0.0;
    double cd = 0.0;
    double cdrain = 0.0;
    double cdhat = 0.0;
    double cdreq = 0.0;
    double ceq = 0.0;
    double ceqbd = 0.0;
    double ceqbs = 0.0;
    double ceqqb = 0.0;
    double ceqqd = 0.0;
    double ceqqg = 0.0;
    double czbd = 0.0;
    double czbdsw = 0.0;
    double czbs = 0.0;
    double czbssw = 0.0;
    double delvbd = 0.0;
    double delvbs = 0.0;
    double delvds = 0.0;
    double delvgd = 0.0;
    double delvgs = 0.0;
    double evbd = 0.0;
    double evbs = 0.0;
    double gbd = 0.0;
    double gbs = 0.0;
    double gcbdb = 0.0;
    double gcbgb = 0.0;
    double gcbsb = 0.0;
    double gcddb = 0.0;
    double gcdgb = 0.0;
    double gcdsb = 0.0;
    double gcgdb = 0.0;
    double gcggb = 0.0;
    double gcgsb = 0.0;
    double gcsdb = 0.0;
    double gcsgb = 0.0;
    double gcssb = 0.0;
    double gds = 0.0;
    double geq = 0.0;
    double gm = 0.0;
    double gmbs = 0.0;
    double sarg = 0.0;
    double sargsw = 0.0;
    double tol = 0.0;
    double vbd = 0.0;
    double vbs = 0.0;
    double vcrit = 0.0;
    double vds = 0.0;
    double vdsat = 0.0;
    double vgb = 0.0;
    double vgd = 0.0;
    double vgdo = 0.0;
    double vgs = 0.0;
    double von = 0.0;
    double xfact = 0.0;
    double xnrm = 0.0;
    double xrev = 0.0;
    int Check = 0;
    double cgdb = 0.0;
    double cgsb = 0.0;
    double cbdb = 0.0;
    double cdgb = 0.0;
    double cddb = 0.0;
    double cdsb = 0.0;
    double cggb = 0.0;
    double cbgb = 0.0;
    double cbsb = 0.0;
    double csgb = 0.0;
    double cssb = 0.0;
    double csdb = 0.0;
    double PhiB = 0.0;
    double PhiBSW = 0.0;
    double MJ = 0.0;
    double MJSW = 0.0;
    double argsw = 0.0;
    double qgate = 0.0;
    double qbulk = 0.0;
    double qdrn = 0.0;
    double qsrc = 0.0;
    double cqgate = 0.0;
    double cqbulk = 0.0;
    double cqdrn = 0.0;
    double vt0 = 0.0;
    int    ByPass = 0;
#ifndef NOBYPASS
    double tempv = 0.0;
#endif /*NOBYPASS*/
    int error = 0;


    /*  loop through all the BSIM1 device models */
    for( ; model != NULL; model = model->BSIM1nextModel ) {

        /* loop through all the instances of the model */
        for (here = model->BSIM1instances; here != NULL ;
                here=here->BSIM1nextInstance) {
            EffectiveLength=here->BSIM1l - model->BSIM1deltaL * 1.e-6;/* m */
            DrainArea = here->BSIM1drainArea;
            SourceArea = here->BSIM1sourceArea;
            DrainPerimeter = here->BSIM1drainPerimeter;
            SourcePerimeter = here->BSIM1sourcePerimeter;
            if( (DrainSatCurrent=DrainArea*model->BSIM1jctSatCurDensity) 
                    < 1e-15){
                DrainSatCurrent = 1.0e-15;
            }
            if( (SourceSatCurrent=SourceArea*model->BSIM1jctSatCurDensity)
                    <1.0e-15){
                SourceSatCurrent = 1.0e-15;
            }
            GateSourceOverlapCap = model->BSIM1gateSourceOverlapCap *here->BSIM1w;
            GateDrainOverlapCap = model->BSIM1gateDrainOverlapCap * here->BSIM1w;
            GateBulkOverlapCap = model->BSIM1gateBulkOverlapCap *EffectiveLength;
            von = model->BSIM1type * here->BSIM1von;
            vdsat = model->BSIM1type * here->BSIM1vdsat;
            vt0 = model->BSIM1type * here->BSIM1vt0;

            Check=1;
            ByPass = 0;
            if((ckt->CKTmode & MODEINITSMSIG)) {
                vbs= *(ckt->CKTstate0 + here->BSIM1vbs);
                vgs= *(ckt->CKTstate0 + here->BSIM1vgs);
                vds= *(ckt->CKTstate0 + here->BSIM1vds);
            } else if ((ckt->CKTmode & MODEINITTRAN)) {
                vbs= *(ckt->CKTstate1 + here->BSIM1vbs);
                vgs= *(ckt->CKTstate1 + here->BSIM1vgs);
                vds= *(ckt->CKTstate1 + here->BSIM1vds);
            } else if((ckt->CKTmode & MODEINITJCT) && !here->BSIM1off) {
                vds= model->BSIM1type * here->BSIM1icVDS;
                vgs= model->BSIM1type * here->BSIM1icVGS;
                vbs= model->BSIM1type * here->BSIM1icVBS;
                if((vds==0) && (vgs==0) && (vbs==0) && 
                        ((ckt->CKTmode & 
                        (MODETRAN|MODEAC|MODEDCOP|MODEDCTRANCURVE)) ||
                        (!(ckt->CKTmode & MODEUIC)))) {
                    vbs = -1;
                    vgs = vt0;
                    vds = 0;
                }
            } else if((ckt->CKTmode & (MODEINITJCT | MODEINITFIX) ) && 
                    (here->BSIM1off)) {
                vbs=vgs=vds=0;
            } else {
#ifndef PREDICTOR
                if((ckt->CKTmode & MODEINITPRED)) {
                    xfact=ckt->CKTdelta/ckt->CKTdeltaOld[1];
                    *(ckt->CKTstate0 + here->BSIM1vbs) = 
                            *(ckt->CKTstate1 + here->BSIM1vbs);
                    vbs = (1+xfact)* (*(ckt->CKTstate1 + here->BSIM1vbs))
                            -(xfact * (*(ckt->CKTstate2 + here->BSIM1vbs)));
                    *(ckt->CKTstate0 + here->BSIM1vgs) = 
                            *(ckt->CKTstate1 + here->BSIM1vgs);
                    vgs = (1+xfact)* (*(ckt->CKTstate1 + here->BSIM1vgs))
                            -(xfact * (*(ckt->CKTstate2 + here->BSIM1vgs)));
                    *(ckt->CKTstate0 + here->BSIM1vds) = 
                            *(ckt->CKTstate1 + here->BSIM1vds);
                    vds = (1+xfact)* (*(ckt->CKTstate1 + here->BSIM1vds))
                            -(xfact * (*(ckt->CKTstate2 + here->BSIM1vds)));
                    *(ckt->CKTstate0 + here->BSIM1vbd) = 
                            *(ckt->CKTstate0 + here->BSIM1vbs)-
                            *(ckt->CKTstate0 + here->BSIM1vds);
                    *(ckt->CKTstate0 + here->BSIM1cd) = 
                            *(ckt->CKTstate1 + here->BSIM1cd);
                    *(ckt->CKTstate0 + here->BSIM1cbs) = 
                            *(ckt->CKTstate1 + here->BSIM1cbs);
                    *(ckt->CKTstate0 + here->BSIM1cbd) = 
                            *(ckt->CKTstate1 + here->BSIM1cbd);
                    *(ckt->CKTstate0 + here->BSIM1gm) = 
                            *(ckt->CKTstate1 + here->BSIM1gm);
                    *(ckt->CKTstate0 + here->BSIM1gds) = 
                            *(ckt->CKTstate1 + here->BSIM1gds);
                    *(ckt->CKTstate0 + here->BSIM1gmbs) = 
                            *(ckt->CKTstate1 + here->BSIM1gmbs);
                    *(ckt->CKTstate0 + here->BSIM1gbd) = 
                            *(ckt->CKTstate1 + here->BSIM1gbd);
                    *(ckt->CKTstate0 + here->BSIM1gbs) = 
                            *(ckt->CKTstate1 + here->BSIM1gbs);
                    *(ckt->CKTstate0 + here->BSIM1cggb) = 
                            *(ckt->CKTstate1 + here->BSIM1cggb);
                    *(ckt->CKTstate0 + here->BSIM1cbgb) = 
                            *(ckt->CKTstate1 + here->BSIM1cbgb);
                    *(ckt->CKTstate0 + here->BSIM1cbsb) = 
                            *(ckt->CKTstate1 + here->BSIM1cbsb);
                    *(ckt->CKTstate0 + here->BSIM1cgdb) = 
                            *(ckt->CKTstate1 + here->BSIM1cgdb);
                    *(ckt->CKTstate0 + here->BSIM1cgsb) = 
                            *(ckt->CKTstate1 + here->BSIM1cgsb);
                    *(ckt->CKTstate0 + here->BSIM1cbdb) = 
                            *(ckt->CKTstate1 + here->BSIM1cbdb);
                    *(ckt->CKTstate0 + here->BSIM1cdgb) = 
                            *(ckt->CKTstate1 + here->BSIM1cdgb);
                    *(ckt->CKTstate0 + here->BSIM1cddb) = 
                            *(ckt->CKTstate1 + here->BSIM1cddb);
                    *(ckt->CKTstate0 + here->BSIM1cdsb) = 
                            *(ckt->CKTstate1 + here->BSIM1cdsb);
                } else {
#endif /* PREDICTOR */
                    vbs = model->BSIM1type * ( 
                        *(ckt->CKTrhsOld+here->BSIM1bNode) -
                        *(ckt->CKTrhsOld+here->BSIM1sNodePrime));
                    vgs = model->BSIM1type * ( 
                        *(ckt->CKTrhsOld+here->BSIM1gNode) -
                        *(ckt->CKTrhsOld+here->BSIM1sNodePrime));
                    vds = model->BSIM1type * ( 
                        *(ckt->CKTrhsOld+here->BSIM1dNodePrime) -
                        *(ckt->CKTrhsOld+here->BSIM1sNodePrime));
#ifndef PREDICTOR
                }
#endif /* PREDICTOR */
                vbd=vbs-vds;
                vgd=vgs-vds;
                vgdo = *(ckt->CKTstate0 + here->BSIM1vgs) - 
                    *(ckt->CKTstate0 + here->BSIM1vds);
                delvbs = vbs - *(ckt->CKTstate0 + here->BSIM1vbs);
                delvbd = vbd - *(ckt->CKTstate0 + here->BSIM1vbd);
                delvgs = vgs - *(ckt->CKTstate0 + here->BSIM1vgs);
                delvds = vds - *(ckt->CKTstate0 + here->BSIM1vds);
                delvgd = vgd-vgdo;

                if (here->BSIM1mode >= 0) {
                    cdhat=
                        *(ckt->CKTstate0 + here->BSIM1cd) -
                        *(ckt->CKTstate0 + here->BSIM1gbd) * delvbd +
                        *(ckt->CKTstate0 + here->BSIM1gmbs) * delvbs +
                        *(ckt->CKTstate0 + here->BSIM1gm) * delvgs + 
                        *(ckt->CKTstate0 + here->BSIM1gds) * delvds ;
                } else {
                    cdhat=
                        *(ckt->CKTstate0 + here->BSIM1cd) -
                        ( *(ckt->CKTstate0 + here->BSIM1gbd) -
                          *(ckt->CKTstate0 + here->BSIM1gmbs)) * delvbd -
                        *(ckt->CKTstate0 + here->BSIM1gm) * delvgd +
                        *(ckt->CKTstate0 + here->BSIM1gds) * delvds;
                }
                cbhat=
                    *(ckt->CKTstate0 + here->BSIM1cbs) +
                    *(ckt->CKTstate0 + here->BSIM1cbd) +
                    *(ckt->CKTstate0 + here->BSIM1gbd) * delvbd +
                    *(ckt->CKTstate0 + here->BSIM1gbs) * delvbs ;

#ifndef NOBYPASS
                    /* now lets see if we can bypass (ugh) */

                /* following should be one big if connected by && all over
                 * the place, but some C compilers can't handle that, so
                 * we split it up here to let them digest it in stages
                 */
                tempv = MAX(FABS(cbhat),FABS(*(ckt->CKTstate0 + here->BSIM1cbs)
                        + *(ckt->CKTstate0 + here->BSIM1cbd)))+ckt->CKTabstol;
                if((!(ckt->CKTmode & MODEINITPRED)) && (ckt->CKTbypass) )
                if( (FABS(delvbs) < (ckt->CKTreltol * MAX(FABS(vbs),
                        FABS(*(ckt->CKTstate0+here->BSIM1vbs)))+
                        ckt->CKTvoltTol)) )
                if ( (FABS(delvbd) < (ckt->CKTreltol * MAX(FABS(vbd),
                        FABS(*(ckt->CKTstate0+here->BSIM1vbd)))+
                        ckt->CKTvoltTol)) )
                if( (FABS(delvgs) < (ckt->CKTreltol * MAX(FABS(vgs),
                        FABS(*(ckt->CKTstate0+here->BSIM1vgs)))+
                        ckt->CKTvoltTol)))
                if ( (FABS(delvds) < (ckt->CKTreltol * MAX(FABS(vds),
                        FABS(*(ckt->CKTstate0+here->BSIM1vds)))+
                        ckt->CKTvoltTol)) )
                if( (FABS(cdhat- *(ckt->CKTstate0 + here->BSIM1cd)) <
                        ckt->CKTreltol * MAX(FABS(cdhat),FABS(*(ckt->CKTstate0 +
                        here->BSIM1cd))) + ckt->CKTabstol) )
                if ( (FABS(cbhat-(*(ckt->CKTstate0 + here->BSIM1cbs) +
                        *(ckt->CKTstate0 + here->BSIM1cbd))) < ckt->CKTreltol *
                        tempv)) {
                    /* bypass code */
                    vbs = *(ckt->CKTstate0 + here->BSIM1vbs);
                    vbd = *(ckt->CKTstate0 + here->BSIM1vbd);
                    vgs = *(ckt->CKTstate0 + here->BSIM1vgs);
                    vds = *(ckt->CKTstate0 + here->BSIM1vds);
                    vgd = vgs - vds;
                    vgb = vgs - vbs;
                    cd = *(ckt->CKTstate0 + here->BSIM1cd);
                    cbs = *(ckt->CKTstate0 + here->BSIM1cbs);
                    cbd = *(ckt->CKTstate0 + here->BSIM1cbd);
                    cdrain = here->BSIM1mode * (cd + cbd);
                    gm = *(ckt->CKTstate0 + here->BSIM1gm);
                    gds = *(ckt->CKTstate0 + here->BSIM1gds);
                    gmbs = *(ckt->CKTstate0 + here->BSIM1gmbs);
                    gbd = *(ckt->CKTstate0 + here->BSIM1gbd);
                    gbs = *(ckt->CKTstate0 + here->BSIM1gbs);
                    if((ckt->CKTmode & (MODETRAN | MODEAC)) || 
                            ((ckt->CKTmode & MODETRANOP) && 
                            (ckt->CKTmode & MODEUIC))) {
                        cggb = *(ckt->CKTstate0 + here->BSIM1cggb);
                        cgdb = *(ckt->CKTstate0 + here->BSIM1cgdb);
                        cgsb = *(ckt->CKTstate0 + here->BSIM1cgsb);
                        cbgb = *(ckt->CKTstate0 + here->BSIM1cbgb);
                        cbdb = *(ckt->CKTstate0 + here->BSIM1cbdb);
                        cbsb = *(ckt->CKTstate0 + here->BSIM1cbsb);
                        cdgb = *(ckt->CKTstate0 + here->BSIM1cdgb);
                        cddb = *(ckt->CKTstate0 + here->BSIM1cddb);
                        cdsb = *(ckt->CKTstate0 + here->BSIM1cdsb);
                        capbs = *(ckt->CKTstate0 + here->BSIM1capbs);
                        capbd = *(ckt->CKTstate0 + here->BSIM1capbd);
                        ByPass = 1;
                        goto line755;
                    } else {
                        goto line850;
                    }
                }
#endif /*NOBYPASS*/

                von = model->BSIM1type * here->BSIM1von;
                if(*(ckt->CKTstate0 + here->BSIM1vds) >=0) {
                    vgs = DEVfetlim(vgs,*(ckt->CKTstate0 + here->BSIM1vgs)
                            ,von);
                    vds = vgs - vgd;
                    vds = DEVlimvds(vds,*(ckt->CKTstate0 + here->BSIM1vds));
                    vgd = vgs - vds;
                } else {
                    vgd = DEVfetlim(vgd,vgdo,von);
                    vds = vgs - vgd;
                    vds = -DEVlimvds(-vds,-(*(ckt->CKTstate0 + here->BSIM1vds)));
                    vgs = vgd + vds;
                }
                if(vds >= 0) {
                    vcrit =CONSTvt0*log(CONSTvt0/(CONSTroot2*SourceSatCurrent));
                    vbs = DEVpnjlim(vbs,*(ckt->CKTstate0 + here->BSIM1vbs),
                            CONSTvt0,vcrit,&Check); /* BSIM1 test */
                    vbd = vbs-vds;
                } else {
                    vcrit = CONSTvt0*log(CONSTvt0/(CONSTroot2*DrainSatCurrent));
                    vbd = DEVpnjlim(vbd,*(ckt->CKTstate0 + here->BSIM1vbd),
                            CONSTvt0,vcrit,&Check); /* BSIM1 test*/
                    vbs = vbd + vds;
                }
            } 

             /* determine DC current and derivatives */
            vbd = vbs - vds;
            vgd = vgs - vds;
            vgb = vgs - vbs;


            if(vbs <= 0.0 ) {
                gbs = SourceSatCurrent / CONSTvt0 + ckt->CKTgmin;
                cbs = gbs * vbs ;
            } else {
                evbs = exp(vbs/CONSTvt0);
                gbs = SourceSatCurrent*evbs/CONSTvt0 + ckt->CKTgmin;
                cbs = SourceSatCurrent * (evbs-1) + ckt->CKTgmin * vbs ;
            }
            if(vbd <= 0.0) {
                gbd = DrainSatCurrent / CONSTvt0 + ckt->CKTgmin;
                cbd = gbd * vbd ;
            } else {
                evbd = exp(vbd/CONSTvt0);
                gbd = DrainSatCurrent*evbd/CONSTvt0 +ckt->CKTgmin;
                cbd = DrainSatCurrent *(evbd-1)+ckt->CKTgmin*vbd;
            }
            /* line 400 */
            if(vds >= 0) {
                /* normal mode */
                here->BSIM1mode = 1;
            } else {
                /* inverse mode */
                here->BSIM1mode = -1;
            }
            /* call BSIM1evaluate to calculate drain current and its 
             * derivatives and charge and capacitances related to gate
             * drain, and bulk
             */
           if( vds >= 0 )  {
                BSIM1evaluate(vds,vbs,vgs,here,model,&gm,&gds,&gmbs,&qgate,
                    &qbulk,&qdrn,&cggb,&cgdb,&cgsb,&cbgb,&cbdb,&cbsb,&cdgb,
                    &cddb,&cdsb,&cdrain,&von,&vdsat,ckt);
            } else {
                BSIM1evaluate(-vds,vbd,vgd,here,model,&gm,&gds,&gmbs,&qgate,
                    &qbulk,&qsrc,&cggb,&cgsb,&cgdb,&cbgb,&cbsb,&cbdb,&csgb,
                    &cssb,&csdb,&cdrain,&von,&vdsat,ckt);
            }
          
            here->BSIM1von = model->BSIM1type * von;
            here->BSIM1vdsat = model->BSIM1type * vdsat;  

        

            /*
             *  COMPUTE EQUIVALENT DRAIN CURRENT SOURCE
             */
            cd=here->BSIM1mode * cdrain - cbd;
            if ((ckt->CKTmode & (MODETRAN | MODEAC | MODEINITSMSIG)) ||
                    ((ckt->CKTmode & MODETRANOP ) && 
                    (ckt->CKTmode & MODEUIC))) {
                /*
                 *  charge storage elements
                 *
                 *   bulk-drain and bulk-source depletion capacitances
                 *  czbd : zero bias drain junction capacitance
                 *  czbs : zero bias source junction capacitance
                 * czbdsw:zero bias drain junction sidewall capacitance
                 * czbssw:zero bias source junction sidewall capacitance
                 */

                czbd  = model->BSIM1unitAreaJctCap * DrainArea;
                czbs  = model->BSIM1unitAreaJctCap * SourceArea;
                czbdsw= model->BSIM1unitLengthSidewallJctCap * DrainPerimeter;
                czbssw= model->BSIM1unitLengthSidewallJctCap * SourcePerimeter;
                PhiB = model->BSIM1bulkJctPotential;
                PhiBSW = model->BSIM1sidewallJctPotential;
                MJ = model->BSIM1bulkJctBotGradingCoeff;
                MJSW = model->BSIM1bulkJctSideGradingCoeff;

                /* Source Bulk Junction */
                if( vbs < 0 ) {  
                    arg = 1 - vbs / PhiB;
                    argsw = 1 - vbs / PhiBSW;
                    sarg = exp(-MJ*log(arg));
                    sargsw = exp(-MJSW*log(argsw));
                    *(ckt->CKTstate0 + here->BSIM1qbs) =
                        PhiB * czbs * (1-arg*sarg)/(1-MJ) + PhiBSW * 
                    czbssw * (1-argsw*sargsw)/(1-MJSW);
                    capbs = czbs * sarg + czbssw * sargsw ;
                } else {  
                    *(ckt->CKTstate0+here->BSIM1qbs) =
                        vbs*(czbs+czbssw)+ vbs*vbs*(czbs*MJ*0.5/PhiB 
                        + czbssw * MJSW * 0.5/PhiBSW);
                    capbs = czbs + czbssw + vbs *(czbs*MJ/PhiB+
                        czbssw * MJSW / PhiBSW );
                }

                /* Drain Bulk Junction */
                if( vbd < 0 ) {  
                    arg = 1 - vbd / PhiB;
                    argsw = 1 - vbd / PhiBSW;
                    sarg = exp(-MJ*log(arg));
                    sargsw = exp(-MJSW*log(argsw));
                    *(ckt->CKTstate0 + here->BSIM1qbd) =
                        PhiB * czbd * (1-arg*sarg)/(1-MJ) + PhiBSW * 
                    czbdsw * (1-argsw*sargsw)/(1-MJSW);
                    capbd = czbd * sarg + czbdsw * sargsw ;
                } else {  
                    *(ckt->CKTstate0+here->BSIM1qbd) =
                        vbd*(czbd+czbdsw)+ vbd*vbd*(czbd*MJ*0.5/PhiB 
                        + czbdsw * MJSW * 0.5/PhiBSW);
                    capbd = czbd + czbdsw + vbd *(czbd*MJ/PhiB+
                        czbdsw * MJSW / PhiBSW );
                }

            }




            /*
             *  check convergence
             */
            if ( (here->BSIM1off == 0)  || (!(ckt->CKTmode & MODEINITFIX)) ){
                if (Check == 1) {
                    ckt->CKTnoncon++;
#ifndef NEWCONV
                } else {
                    tol=ckt->CKTreltol*MAX(FABS(cdhat),FABS(cd))+ckt->CKTabstol;
                    if (FABS(cdhat-cd) >= tol) { 
                        ckt->CKTnoncon++;
                    } else {
                        tol=ckt->CKTreltol*MAX(FABS(cbhat),FABS(cbs+cbd))+
                            ckt->CKTabstol;
                        if (FABS(cbhat-(cbs+cbd)) > tol) {
                            ckt->CKTnoncon++;
                        }
                    }
#endif /* NEWCONV */
                }
            }
            *(ckt->CKTstate0 + here->BSIM1vbs) = vbs;
            *(ckt->CKTstate0 + here->BSIM1vbd) = vbd;
            *(ckt->CKTstate0 + here->BSIM1vgs) = vgs;
            *(ckt->CKTstate0 + here->BSIM1vds) = vds;
            *(ckt->CKTstate0 + here->BSIM1cd) = cd;
            *(ckt->CKTstate0 + here->BSIM1cbs) = cbs;
            *(ckt->CKTstate0 + here->BSIM1cbd) = cbd;
            *(ckt->CKTstate0 + here->BSIM1gm) = gm;
            *(ckt->CKTstate0 + here->BSIM1gds) = gds;
            *(ckt->CKTstate0 + here->BSIM1gmbs) = gmbs;
            *(ckt->CKTstate0 + here->BSIM1gbd) = gbd;
            *(ckt->CKTstate0 + here->BSIM1gbs) = gbs;

            *(ckt->CKTstate0 + here->BSIM1cggb) = cggb;
            *(ckt->CKTstate0 + here->BSIM1cgdb) = cgdb;
            *(ckt->CKTstate0 + here->BSIM1cgsb) = cgsb;

            *(ckt->CKTstate0 + here->BSIM1cbgb) = cbgb;
            *(ckt->CKTstate0 + here->BSIM1cbdb) = cbdb;
            *(ckt->CKTstate0 + here->BSIM1cbsb) = cbsb;

            *(ckt->CKTstate0 + here->BSIM1cdgb) = cdgb;
            *(ckt->CKTstate0 + here->BSIM1cddb) = cddb;
            *(ckt->CKTstate0 + here->BSIM1cdsb) = cdsb;

            *(ckt->CKTstate0 + here->BSIM1capbs) = capbs;
            *(ckt->CKTstate0 + here->BSIM1capbd) = capbd;

           /* bulk and channel charge plus overlaps */

            if((!(ckt->CKTmode & (MODETRAN | MODEAC))) &&
                    ((!(ckt->CKTmode & MODETRANOP)) ||
                    (!(ckt->CKTmode & MODEUIC)))  && (!(ckt->CKTmode 
                    &  MODEINITSMSIG))) goto line850; 
         
line755:
            if( here->BSIM1mode > 0 ) {
                BSIM1mosCap(ckt,vgd,vgs,vgb,GateDrainOverlapCap,
                        GateSourceOverlapCap,GateBulkOverlapCap,capbd,capbs
                        ,cggb,cgdb,cgsb,cbgb,cbdb,cbsb,cdgb,cddb,cdsb
                        ,&gcggb,&gcgdb,&gcgsb,&gcbgb,&gcbdb,&gcbsb,&gcdgb
                        ,&gcddb,&gcdsb,&gcsgb,&gcsdb,&gcssb,&qgate,&qbulk
                        ,&qdrn,&qsrc);
            } else {
                BSIM1mosCap(ckt,vgs,vgd,vgb,GateSourceOverlapCap,
                    GateDrainOverlapCap,GateBulkOverlapCap,capbs,capbd
                    ,cggb,cgsb,cgdb,cbgb,cbsb,cbdb,csgb,cssb,csdb
                    ,&gcggb,&gcgsb,&gcgdb,&gcbgb,&gcbsb,&gcbdb,&gcsgb
                    ,&gcssb,&gcsdb,&gcdgb,&gcdsb,&gcddb,&qgate,&qbulk
                    ,&qsrc,&qdrn);
            }
             
            if(ByPass) goto line860;
            *(ckt->CKTstate0 + here->BSIM1qg) = qgate;
            *(ckt->CKTstate0 + here->BSIM1qd) = qdrn -  
                    *(ckt->CKTstate0 + here->BSIM1qbd);
            *(ckt->CKTstate0 + here->BSIM1qb) = qbulk +  
                    *(ckt->CKTstate0 + here->BSIM1qbd) +  
                    *(ckt->CKTstate0 + here->BSIM1qbs); 

            /* store small signal parameters */
            if((!(ckt->CKTmode & (MODEAC | MODETRAN))) &&
                    (ckt->CKTmode & MODETRANOP ) && (ckt->CKTmode &
                    MODEUIC ))   goto line850;
            if(ckt->CKTmode & MODEINITSMSIG ) {  
                *(ckt->CKTstate0+here->BSIM1cggb) = cggb;
                *(ckt->CKTstate0+here->BSIM1cgdb) = cgdb;
                *(ckt->CKTstate0+here->BSIM1cgsb) = cgsb;
                *(ckt->CKTstate0+here->BSIM1cbgb) = cbgb;
                *(ckt->CKTstate0+here->BSIM1cbdb) = cbdb;
                *(ckt->CKTstate0+here->BSIM1cbsb) = cbsb;
                *(ckt->CKTstate0+here->BSIM1cdgb) = cdgb;
                *(ckt->CKTstate0+here->BSIM1cddb) = cddb;
                *(ckt->CKTstate0+here->BSIM1cdsb) = cdsb;     
                *(ckt->CKTstate0+here->BSIM1capbd) = capbd;
                *(ckt->CKTstate0+here->BSIM1capbs) = capbs;

                goto line1000;
            }
       
            if(ckt->CKTmode & MODEINITTRAN ) { 
                *(ckt->CKTstate1+here->BSIM1qb) =
                    *(ckt->CKTstate0+here->BSIM1qb) ;
                *(ckt->CKTstate1+here->BSIM1qg) =
                    *(ckt->CKTstate0+here->BSIM1qg) ;
                *(ckt->CKTstate1+here->BSIM1qd) =
                    *(ckt->CKTstate0+here->BSIM1qd) ;
            }
       
       
            error = NIintegrate(ckt,&geq,&ceq,0.0,here->BSIM1qb);
            if(error) return(error);
            error = NIintegrate(ckt,&geq,&ceq,0.0,here->BSIM1qg);
            if(error) return(error);
            error = NIintegrate(ckt,&geq,&ceq,0.0,here->BSIM1qd);
            if(error) return(error);
      
            goto line860;

line850:
            /* initialize to zero charge conductance and current */
            ceqqg = ceqqb = ceqqd = 0.0;
            gcdgb = gcddb = gcdsb = 0.0;
            gcsgb = gcsdb = gcssb = 0.0;
            gcggb = gcgdb = gcgsb = 0.0;
            gcbgb = gcbdb = gcbsb = 0.0;
            goto line900;
            
line860:
            /* evaluate equivalent charge current */
            cqgate = *(ckt->CKTstate0 + here->BSIM1iqg);
            cqbulk = *(ckt->CKTstate0 + here->BSIM1iqb);
            cqdrn = *(ckt->CKTstate0 + here->BSIM1iqd);
            ceqqg = cqgate - gcggb * vgb + gcgdb * vbd + gcgsb * vbs;
            ceqqb = cqbulk - gcbgb * vgb + gcbdb * vbd + gcbsb * vbs;
            ceqqd = cqdrn - gcdgb * vgb + gcddb * vbd + gcdsb * vbs;

            if(ckt->CKTmode & MODEINITTRAN ) {  
                *(ckt->CKTstate1 + here->BSIM1iqb) =  
                    *(ckt->CKTstate0 + here->BSIM1iqb);
                *(ckt->CKTstate1 + here->BSIM1iqg) =  
                    *(ckt->CKTstate0 + here->BSIM1iqg);
                *(ckt->CKTstate1 + here->BSIM1iqd) =  
                    *(ckt->CKTstate0 + here->BSIM1iqd);
            }

            /*
             *  load current vector
             */
line900:
   
            ceqbs = model->BSIM1type * (cbs-(gbs-ckt->CKTgmin)*vbs);
            ceqbd = model->BSIM1type * (cbd-(gbd-ckt->CKTgmin)*vbd);
     
            ceqqg = model->BSIM1type * ceqqg;
            ceqqb = model->BSIM1type * ceqqb;
            ceqqd =  model->BSIM1type * ceqqd;
            if (here->BSIM1mode >= 0) {
                xnrm=1;
                xrev=0;
                cdreq=model->BSIM1type*(cdrain-gds*vds-gm*vgs-gmbs*vbs);
            } else {
                xnrm=0;
                xrev=1;
                cdreq = -(model->BSIM1type)*(cdrain+gds*vds-gm*vgd-gmbs*vbd);
            }

            *(ckt->CKTrhs + here->BSIM1gNode) -= ceqqg;
            *(ckt->CKTrhs + here->BSIM1bNode) -=(ceqbs+ceqbd+ceqqb);
            *(ckt->CKTrhs + here->BSIM1dNodePrime) +=
                    (ceqbd-cdreq-ceqqd);
            *(ckt->CKTrhs + here->BSIM1sNodePrime) += 
                    (cdreq+ceqbs+ceqqg+ceqqb+ceqqd);

            /*
             *  load y matrix
             */

            *(here->BSIM1DdPtr) += (here->BSIM1drainConductance);
            *(here->BSIM1GgPtr) += (gcggb);
            *(here->BSIM1SsPtr) += (here->BSIM1sourceConductance);
            *(here->BSIM1BbPtr) += (gbd+gbs-gcbgb-gcbdb-gcbsb);
            *(here->BSIM1DPdpPtr) += 
                (here->BSIM1drainConductance+gds+gbd+xrev*(gm+gmbs)+gcddb);
            *(here->BSIM1SPspPtr) += 
                (here->BSIM1sourceConductance+gds+gbs+xnrm*(gm+gmbs)+gcssb);
            *(here->BSIM1DdpPtr) += (-here->BSIM1drainConductance);
            *(here->BSIM1GbPtr) += (-gcggb-gcgdb-gcgsb);
            *(here->BSIM1GdpPtr) += (gcgdb);
            *(here->BSIM1GspPtr) += (gcgsb);
            *(here->BSIM1SspPtr) += (-here->BSIM1sourceConductance);
            *(here->BSIM1BgPtr) += (gcbgb);
            *(here->BSIM1BdpPtr) += (-gbd+gcbdb);
            *(here->BSIM1BspPtr) += (-gbs+gcbsb);
            *(here->BSIM1DPdPtr) += (-here->BSIM1drainConductance);
            *(here->BSIM1DPgPtr) += ((xnrm-xrev)*gm+gcdgb);
            *(here->BSIM1DPbPtr) += (-gbd+(xnrm-xrev)*gmbs-gcdgb-gcddb-gcdsb);
            *(here->BSIM1DPspPtr) += (-gds-xnrm*(gm+gmbs)+gcdsb);
            *(here->BSIM1SPgPtr) += (-(xnrm-xrev)*gm+gcsgb);
            *(here->BSIM1SPsPtr) += (-here->BSIM1sourceConductance);
            *(here->BSIM1SPbPtr) += (-gbs-(xnrm-xrev)*gmbs-gcsgb-gcsdb-gcssb);
            *(here->BSIM1SPdpPtr) += (-gds-xrev*(gm+gmbs)+gcsdb);


line1000:  ;

        }   /* End of Mosfet Instance */

    }       /* End of Model Instance */
    return(OK);
}

