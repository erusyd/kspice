/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Hong J. Park, Thomas L. Quarles
**********/
/*
 */

#include "spice.h"
#include <stdio.h>
#include <math.h>
#include "util.h"
#include "cktdefs.h"
#include "bsim2def.h"
#include "trandefs.h"
#include "const.h"
#include "sperror.h"
#include "devdefs.h"
#include "suffix.h"


int
BSIM2load(inModel,ckt)

    GENmodel *inModel;
    register CKTcircuit *ckt;

        /* actually load the current value into the 
         * sparse matrix previously provided 
         */
{
    register BSIM2model *model = (BSIM2model*)inModel;
    register BSIM2instance *here;
    double DrainSatCurrent;
    double EffectiveLength;
    double GateBulkOverlapCap;
    double GateDrainOverlapCap;
    double GateSourceOverlapCap;
    double SourceSatCurrent;
    double DrainArea;
    double SourceArea;
    double DrainPerimeter;
    double SourcePerimeter;
    double arg;
    double capbd;
    double capbs;
    double cbd;
    double cbhat;
    double cbs;
    double cd;
    double cdrain;
    double cdhat;
    double cdreq;
    double ceq;
    double ceqbd;
    double ceqbs;
    double ceqqb;
    double ceqqd;
    double ceqqg;
    double czbd;
    double czbdsw;
    double czbs;
    double czbssw;
    double delvbd;
    double delvbs;
    double delvds;
    double delvgd;
    double delvgs;
    double evbd;
    double evbs;
    double gbd;
    double gbs;
    double gcbdb;
    double gcbgb;
    double gcbsb;
    double gcddb;
    double gcdgb;
    double gcdsb;
    double gcgdb;
    double gcggb;
    double gcgsb;
    double gcsdb;
    double gcsgb;
    double gcssb;
    double gds;
    double geq;
    double gm;
    double gmbs;
    double sarg;
    double sargsw;
    double tol;
    double vbd;
    double vbs;
    double vcrit;
    double vds;
    double vdsat;
    double vgb;
    double vgd;
    double vgdo;
    double vgs;
    double von;
    double xfact;
    double xnrm;
    double xrev;
    int Check;
    double cgdb;
    double cgsb;
    double cbdb;
    double cdgb;
    double cddb;
    double cdsb;
    double cggb;
    double cbgb;
    double cbsb;
    double csgb;
    double cssb;
    double csdb;
    double PhiB;
    double PhiBSW;
    double MJ;
    double MJSW;
    double argsw;
    double qgate;
    double qbulk;
    double qdrn;
    double qsrc;
    double cqgate;
    double cqbulk;
    double cqdrn;
    double vt0;
    int    ByPass;
#ifndef NOBYPASS
    double tempv;
#endif /*NOBYPASS*/
    int error;


    /*  loop through all the BSIM2 device models */
    for( ; model != NULL; model = model->BSIM2nextModel ) {

        /* loop through all the instances of the model */
        for (here = model->BSIM2instances; here != NULL ;
                here=here->BSIM2nextInstance) {
            EffectiveLength=here->BSIM2l - model->BSIM2deltaL * 1.e-6;/* m */
            DrainArea = here->BSIM2drainArea;
            SourceArea = here->BSIM2sourceArea;
            DrainPerimeter = here->BSIM2drainPerimeter;
            SourcePerimeter = here->BSIM2sourcePerimeter;
            if( (DrainSatCurrent=DrainArea*model->BSIM2jctSatCurDensity) 
                    < 1e-15){
                DrainSatCurrent = 1.0e-15;
            }
            if( (SourceSatCurrent=SourceArea*model->BSIM2jctSatCurDensity)
                    <1.0e-15){
                SourceSatCurrent = 1.0e-15;
            }
            GateSourceOverlapCap = model->BSIM2gateSourceOverlapCap *here->BSIM2w;
            GateDrainOverlapCap = model->BSIM2gateDrainOverlapCap * here->BSIM2w;
            GateBulkOverlapCap = model->BSIM2gateBulkOverlapCap *EffectiveLength;
            von = model->BSIM2type * here->BSIM2von;
            vdsat = model->BSIM2type * here->BSIM2vdsat;
            vt0 = model->BSIM2type * here->pParam->BSIM2vt0;

            Check=1;
            ByPass = 0;
            if((ckt->CKTmode & MODEINITSMSIG)) {
                vbs= *(ckt->CKTstate0 + here->BSIM2vbs);
                vgs= *(ckt->CKTstate0 + here->BSIM2vgs);
                vds= *(ckt->CKTstate0 + here->BSIM2vds);
            } else if ((ckt->CKTmode & MODEINITTRAN)) {
                vbs= *(ckt->CKTstate1 + here->BSIM2vbs);
                vgs= *(ckt->CKTstate1 + here->BSIM2vgs);
                vds= *(ckt->CKTstate1 + here->BSIM2vds);
            } else if((ckt->CKTmode & MODEINITJCT) && !here->BSIM2off) {
                vds= model->BSIM2type * here->BSIM2icVDS;
                vgs= model->BSIM2type * here->BSIM2icVGS;
                vbs= model->BSIM2type * here->BSIM2icVBS;
                if((vds==0) && (vgs==0) && (vbs==0) && 
                        ((ckt->CKTmode & 
                        (MODETRAN|MODEAC|MODEDCOP|MODEDCTRANCURVE)) ||
                        (!(ckt->CKTmode & MODEUIC)))) {
                    vbs = -1;
                    vgs = vt0;
                    vds = 0;
                }
            } else if((ckt->CKTmode & (MODEINITJCT | MODEINITFIX) ) && 
                    (here->BSIM2off)) {
                vbs=vgs=vds=0;
            } else {
#ifndef PREDICTOR
                if((ckt->CKTmode & MODEINITPRED)) {
                    xfact=ckt->CKTdelta/ckt->CKTdeltaOld[1];
                    *(ckt->CKTstate0 + here->BSIM2vbs) = 
                            *(ckt->CKTstate1 + here->BSIM2vbs);
                    vbs = (1+xfact)* (*(ckt->CKTstate1 + here->BSIM2vbs))
                            -(xfact * (*(ckt->CKTstate2 + here->BSIM2vbs)));
                    *(ckt->CKTstate0 + here->BSIM2vgs) = 
                            *(ckt->CKTstate1 + here->BSIM2vgs);
                    vgs = (1+xfact)* (*(ckt->CKTstate1 + here->BSIM2vgs))
                            -(xfact * (*(ckt->CKTstate2 + here->BSIM2vgs)));
                    *(ckt->CKTstate0 + here->BSIM2vds) = 
                            *(ckt->CKTstate1 + here->BSIM2vds);
                    vds = (1+xfact)* (*(ckt->CKTstate1 + here->BSIM2vds))
                            -(xfact * (*(ckt->CKTstate2 + here->BSIM2vds)));
                    *(ckt->CKTstate0 + here->BSIM2vbd) = 
                            *(ckt->CKTstate0 + here->BSIM2vbs)-
                            *(ckt->CKTstate0 + here->BSIM2vds);
                    *(ckt->CKTstate0 + here->BSIM2cd) = 
                            *(ckt->CKTstate1 + here->BSIM2cd);
                    *(ckt->CKTstate0 + here->BSIM2cbs) = 
                            *(ckt->CKTstate1 + here->BSIM2cbs);
                    *(ckt->CKTstate0 + here->BSIM2cbd) = 
                            *(ckt->CKTstate1 + here->BSIM2cbd);
                    *(ckt->CKTstate0 + here->BSIM2gm) = 
                            *(ckt->CKTstate1 + here->BSIM2gm);
                    *(ckt->CKTstate0 + here->BSIM2gds) = 
                            *(ckt->CKTstate1 + here->BSIM2gds);
                    *(ckt->CKTstate0 + here->BSIM2gmbs) = 
                            *(ckt->CKTstate1 + here->BSIM2gmbs);
                    *(ckt->CKTstate0 + here->BSIM2gbd) = 
                            *(ckt->CKTstate1 + here->BSIM2gbd);
                    *(ckt->CKTstate0 + here->BSIM2gbs) = 
                            *(ckt->CKTstate1 + here->BSIM2gbs);
                    *(ckt->CKTstate0 + here->BSIM2cggb) = 
                            *(ckt->CKTstate1 + here->BSIM2cggb);
                    *(ckt->CKTstate0 + here->BSIM2cbgb) = 
                            *(ckt->CKTstate1 + here->BSIM2cbgb);
                    *(ckt->CKTstate0 + here->BSIM2cbsb) = 
                            *(ckt->CKTstate1 + here->BSIM2cbsb);
                    *(ckt->CKTstate0 + here->BSIM2cgdb) = 
                            *(ckt->CKTstate1 + here->BSIM2cgdb);
                    *(ckt->CKTstate0 + here->BSIM2cgsb) = 
                            *(ckt->CKTstate1 + here->BSIM2cgsb);
                    *(ckt->CKTstate0 + here->BSIM2cbdb) = 
                            *(ckt->CKTstate1 + here->BSIM2cbdb);
                    *(ckt->CKTstate0 + here->BSIM2cdgb) = 
                            *(ckt->CKTstate1 + here->BSIM2cdgb);
                    *(ckt->CKTstate0 + here->BSIM2cddb) = 
                            *(ckt->CKTstate1 + here->BSIM2cddb);
                    *(ckt->CKTstate0 + here->BSIM2cdsb) = 
                            *(ckt->CKTstate1 + here->BSIM2cdsb);
                } else {
#endif /* PREDICTOR */
                    vbs = model->BSIM2type * ( 
                        *(ckt->CKTrhsOld+here->BSIM2bNode) -
                        *(ckt->CKTrhsOld+here->BSIM2sNodePrime));
                    vgs = model->BSIM2type * ( 
                        *(ckt->CKTrhsOld+here->BSIM2gNode) -
                        *(ckt->CKTrhsOld+here->BSIM2sNodePrime));
                    vds = model->BSIM2type * ( 
                        *(ckt->CKTrhsOld+here->BSIM2dNodePrime) -
                        *(ckt->CKTrhsOld+here->BSIM2sNodePrime));
#ifndef PREDICTOR
                }
#endif /* PREDICTOR */
                vbd=vbs-vds;
                vgd=vgs-vds;
                vgdo = *(ckt->CKTstate0 + here->BSIM2vgs) - 
                    *(ckt->CKTstate0 + here->BSIM2vds);
                delvbs = vbs - *(ckt->CKTstate0 + here->BSIM2vbs);
                delvbd = vbd - *(ckt->CKTstate0 + here->BSIM2vbd);
                delvgs = vgs - *(ckt->CKTstate0 + here->BSIM2vgs);
                delvds = vds - *(ckt->CKTstate0 + here->BSIM2vds);
                delvgd = vgd-vgdo;

                if (here->BSIM2mode >= 0) {
                    cdhat=
                        *(ckt->CKTstate0 + here->BSIM2cd) -
                        *(ckt->CKTstate0 + here->BSIM2gbd) * delvbd +
                        *(ckt->CKTstate0 + here->BSIM2gmbs) * delvbs +
                        *(ckt->CKTstate0 + here->BSIM2gm) * delvgs + 
                        *(ckt->CKTstate0 + here->BSIM2gds) * delvds ;
                } else {
                    cdhat=
                        *(ckt->CKTstate0 + here->BSIM2cd) -
                        ( *(ckt->CKTstate0 + here->BSIM2gbd) -
                          *(ckt->CKTstate0 + here->BSIM2gmbs)) * delvbd -
                        *(ckt->CKTstate0 + here->BSIM2gm) * delvgd +
                        *(ckt->CKTstate0 + here->BSIM2gds) * delvds;
                }
                cbhat=
                    *(ckt->CKTstate0 + here->BSIM2cbs) +
                    *(ckt->CKTstate0 + here->BSIM2cbd) +
                    *(ckt->CKTstate0 + here->BSIM2gbd) * delvbd +
                    *(ckt->CKTstate0 + here->BSIM2gbs) * delvbs ;

#ifndef NOBYPASS
                    /* now lets see if we can bypass (ugh) */

                /* following should be one big if connected by && all over
                 * the place, but some C compilers can't handle that, so
                 * we split it up here to let them digest it in stages
                 */
                tempv = MAX(FABS(cbhat),FABS(*(ckt->CKTstate0 + here->BSIM2cbs)
                        + *(ckt->CKTstate0 + here->BSIM2cbd)))+ckt->CKTabstol;
                if((!(ckt->CKTmode & MODEINITPRED)) && (ckt->CKTbypass) )
                if( (FABS(delvbs) < (ckt->CKTreltol * MAX(FABS(vbs),
                        FABS(*(ckt->CKTstate0+here->BSIM2vbs)))+
                        ckt->CKTvoltTol)) )
                if ( (FABS(delvbd) < (ckt->CKTreltol * MAX(FABS(vbd),
                        FABS(*(ckt->CKTstate0+here->BSIM2vbd)))+
                        ckt->CKTvoltTol)) )
                if( (FABS(delvgs) < (ckt->CKTreltol * MAX(FABS(vgs),
                        FABS(*(ckt->CKTstate0+here->BSIM2vgs)))+
                        ckt->CKTvoltTol)))
                if ( (FABS(delvds) < (ckt->CKTreltol * MAX(FABS(vds),
                        FABS(*(ckt->CKTstate0+here->BSIM2vds)))+
                        ckt->CKTvoltTol)) )
                if( (FABS(cdhat- *(ckt->CKTstate0 + here->BSIM2cd)) <
                        ckt->CKTreltol * MAX(FABS(cdhat),FABS(*(ckt->CKTstate0 +
                        here->BSIM2cd))) + ckt->CKTabstol) )
                if ( (FABS(cbhat-(*(ckt->CKTstate0 + here->BSIM2cbs) +
                        *(ckt->CKTstate0 + here->BSIM2cbd))) < ckt->CKTreltol *
                        tempv)) {
                    /* bypass code */
                    vbs = *(ckt->CKTstate0 + here->BSIM2vbs);
                    vbd = *(ckt->CKTstate0 + here->BSIM2vbd);
                    vgs = *(ckt->CKTstate0 + here->BSIM2vgs);
                    vds = *(ckt->CKTstate0 + here->BSIM2vds);
                    vgd = vgs - vds;
                    vgb = vgs - vbs;
                    cd = *(ckt->CKTstate0 + here->BSIM2cd);
                    cbs = *(ckt->CKTstate0 + here->BSIM2cbs);
                    cbd = *(ckt->CKTstate0 + here->BSIM2cbd);
                    cdrain = here->BSIM2mode * (cd + cbd);
                    gm = *(ckt->CKTstate0 + here->BSIM2gm);
                    gds = *(ckt->CKTstate0 + here->BSIM2gds);
                    gmbs = *(ckt->CKTstate0 + here->BSIM2gmbs);
                    gbd = *(ckt->CKTstate0 + here->BSIM2gbd);
                    gbs = *(ckt->CKTstate0 + here->BSIM2gbs);
                    if((ckt->CKTmode & (MODETRAN | MODEAC)) || 
                            ((ckt->CKTmode & MODETRANOP) && 
                            (ckt->CKTmode & MODEUIC))) {
                        cggb = *(ckt->CKTstate0 + here->BSIM2cggb);
                        cgdb = *(ckt->CKTstate0 + here->BSIM2cgdb);
                        cgsb = *(ckt->CKTstate0 + here->BSIM2cgsb);
                        cbgb = *(ckt->CKTstate0 + here->BSIM2cbgb);
                        cbdb = *(ckt->CKTstate0 + here->BSIM2cbdb);
                        cbsb = *(ckt->CKTstate0 + here->BSIM2cbsb);
                        cdgb = *(ckt->CKTstate0 + here->BSIM2cdgb);
                        cddb = *(ckt->CKTstate0 + here->BSIM2cddb);
                        cdsb = *(ckt->CKTstate0 + here->BSIM2cdsb);
                        capbs = *(ckt->CKTstate0 + here->BSIM2capbs);
                        capbd = *(ckt->CKTstate0 + here->BSIM2capbd);
                        ByPass = 1;
                        goto line755;
                    } else {
                        goto line850;
                    }
                }
#endif /*NOBYPASS*/

                von = model->BSIM2type * here->BSIM2von;
                if(*(ckt->CKTstate0 + here->BSIM2vds) >=0) {
                    vgs = DEVfetlim(vgs,*(ckt->CKTstate0 + here->BSIM2vgs)
                            ,von);
                    vds = vgs - vgd;
                    vds = DEVlimvds(vds,*(ckt->CKTstate0 + here->BSIM2vds));
                    vgd = vgs - vds;
                } else {
                    vgd = DEVfetlim(vgd,vgdo,von);
                    vds = vgs - vgd;
                    vds = -DEVlimvds(-vds,-(*(ckt->CKTstate0 + 
                            here->BSIM2vds)));
                    vgs = vgd + vds;
                }
                if(vds >= 0) {
                    vcrit = CONSTvt0 *log(CONSTvt0/(CONSTroot2*SourceSatCurrent));
                    vbs = DEVpnjlim(vbs,*(ckt->CKTstate0 + here->BSIM2vbs),
                            CONSTvt0,vcrit,&Check); /* BSIM2 test */
                    vbd = vbs-vds;
                } else {
                    vcrit = CONSTvt0 * log(CONSTvt0/(CONSTroot2*DrainSatCurrent));
                    vbd = DEVpnjlim(vbd,*(ckt->CKTstate0 + here->BSIM2vbd),
                            CONSTvt0,vcrit,&Check); /* BSIM2 test*/
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
                here->BSIM2mode = 1;
            } else {
                /* inverse mode */
                here->BSIM2mode = -1;
            }
            /* call BSIM2evaluate to calculate drain current and its 
             * derivatives and charge and capacitances related to gate
             * drain, and bulk
             */
           if( vds >= 0 )  {
                BSIM2evaluate(vds,vbs,vgs,here,model,&gm,&gds,&gmbs,&qgate,
                    &qbulk,&qdrn,&cggb,&cgdb,&cgsb,&cbgb,&cbdb,&cbsb,&cdgb,
                    &cddb,&cdsb,&cdrain,&von,&vdsat,ckt);
            } else {
                BSIM2evaluate(-vds,vbd,vgd,here,model,&gm,&gds,&gmbs,&qgate,
                    &qbulk,&qsrc,&cggb,&cgsb,&cgdb,&cbgb,&cbsb,&cbdb,&csgb,
                    &cssb,&csdb,&cdrain,&von,&vdsat,ckt);
            }
          
            here->BSIM2von = model->BSIM2type * von;
            here->BSIM2vdsat = model->BSIM2type * vdsat;  

        

            /*
             *  COMPUTE EQUIVALENT DRAIN CURRENT SOURCE
             */
            cd=here->BSIM2mode * cdrain - cbd;
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

                czbd  = model->BSIM2unitAreaJctCap * DrainArea;
                czbs  = model->BSIM2unitAreaJctCap * SourceArea;
                czbdsw= model->BSIM2unitLengthSidewallJctCap * DrainPerimeter;
                czbssw= model->BSIM2unitLengthSidewallJctCap * SourcePerimeter;
                PhiB = model->BSIM2bulkJctPotential;
                PhiBSW = model->BSIM2sidewallJctPotential;
                MJ = model->BSIM2bulkJctBotGradingCoeff;
                MJSW = model->BSIM2bulkJctSideGradingCoeff;

                /* Source Bulk Junction */
                if( vbs < 0 ) {  
                    arg = 1 - vbs / PhiB;
                    argsw = 1 - vbs / PhiBSW;
                    sarg = exp(-MJ*log(arg));
                    sargsw = exp(-MJSW*log(argsw));
                    *(ckt->CKTstate0 + here->BSIM2qbs) =
                        PhiB * czbs * (1-arg*sarg)/(1-MJ) + PhiBSW * 
                    czbssw * (1-argsw*sargsw)/(1-MJSW);
                    capbs = czbs * sarg + czbssw * sargsw ;
                } else {  
                    *(ckt->CKTstate0+here->BSIM2qbs) =
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
                    *(ckt->CKTstate0 + here->BSIM2qbd) =
                        PhiB * czbd * (1-arg*sarg)/(1-MJ) + PhiBSW * 
                    czbdsw * (1-argsw*sargsw)/(1-MJSW);
                    capbd = czbd * sarg + czbdsw * sargsw ;
                } else {  
                    *(ckt->CKTstate0+here->BSIM2qbd) =
                        vbd*(czbd+czbdsw)+ vbd*vbd*(czbd*MJ*0.5/PhiB 
                        + czbdsw * MJSW * 0.5/PhiBSW);
                    capbd = czbd + czbdsw + vbd *(czbd*MJ/PhiB+
                        czbdsw * MJSW / PhiBSW );
                }

            }




            /*
             *  check convergence
             */
            if ( (here->BSIM2off == 0)  || (!(ckt->CKTmode & MODEINITFIX)) ){
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
            *(ckt->CKTstate0 + here->BSIM2vbs) = vbs;
            *(ckt->CKTstate0 + here->BSIM2vbd) = vbd;
            *(ckt->CKTstate0 + here->BSIM2vgs) = vgs;
            *(ckt->CKTstate0 + here->BSIM2vds) = vds;
            *(ckt->CKTstate0 + here->BSIM2cd) = cd;
            *(ckt->CKTstate0 + here->BSIM2cbs) = cbs;
            *(ckt->CKTstate0 + here->BSIM2cbd) = cbd;
            *(ckt->CKTstate0 + here->BSIM2gm) = gm;
            *(ckt->CKTstate0 + here->BSIM2gds) = gds;
            *(ckt->CKTstate0 + here->BSIM2gmbs) = gmbs;
            *(ckt->CKTstate0 + here->BSIM2gbd) = gbd;
            *(ckt->CKTstate0 + here->BSIM2gbs) = gbs;

            *(ckt->CKTstate0 + here->BSIM2cggb) = cggb;
            *(ckt->CKTstate0 + here->BSIM2cgdb) = cgdb;
            *(ckt->CKTstate0 + here->BSIM2cgsb) = cgsb;

            *(ckt->CKTstate0 + here->BSIM2cbgb) = cbgb;
            *(ckt->CKTstate0 + here->BSIM2cbdb) = cbdb;
            *(ckt->CKTstate0 + here->BSIM2cbsb) = cbsb;

            *(ckt->CKTstate0 + here->BSIM2cdgb) = cdgb;
            *(ckt->CKTstate0 + here->BSIM2cddb) = cddb;
            *(ckt->CKTstate0 + here->BSIM2cdsb) = cdsb;

            *(ckt->CKTstate0 + here->BSIM2capbs) = capbs;
            *(ckt->CKTstate0 + here->BSIM2capbd) = capbd;

           /* bulk and channel charge plus overlaps */

            if((!(ckt->CKTmode & (MODETRAN | MODEAC))) &&
                    ((!(ckt->CKTmode & MODETRANOP)) ||
                    (!(ckt->CKTmode & MODEUIC)))  && (!(ckt->CKTmode 
                    &  MODEINITSMSIG))) goto line850; 
         
line755:
            if( here->BSIM2mode > 0 ) {
                BSIM2mosCap(ckt,vgd,vgs,vgb,GateDrainOverlapCap,
                        GateSourceOverlapCap,GateBulkOverlapCap,capbd,capbs
                        ,cggb,cgdb,cgsb,cbgb,cbdb,cbsb,cdgb,cddb,cdsb
                        ,&gcggb,&gcgdb,&gcgsb,&gcbgb,&gcbdb,&gcbsb,&gcdgb
                        ,&gcddb,&gcdsb,&gcsgb,&gcsdb,&gcssb,&qgate,&qbulk
                        ,&qdrn,&qsrc);
            } else {
                BSIM2mosCap(ckt,vgs,vgd,vgb,GateSourceOverlapCap,
                    GateDrainOverlapCap,GateBulkOverlapCap,capbs,capbd
                    ,cggb,cgsb,cgdb,cbgb,cbsb,cbdb,csgb,cssb,csdb
                    ,&gcggb,&gcgsb,&gcgdb,&gcbgb,&gcbsb,&gcbdb,&gcsgb
                    ,&gcssb,&gcsdb,&gcdgb,&gcdsb,&gcddb,&qgate,&qbulk
                    ,&qsrc,&qdrn);
            }
             
            if(ByPass) goto line860;
            *(ckt->CKTstate0 + here->BSIM2qg) = qgate;
            *(ckt->CKTstate0 + here->BSIM2qd) = qdrn -  
                    *(ckt->CKTstate0 + here->BSIM2qbd);
            *(ckt->CKTstate0 + here->BSIM2qb) = qbulk +  
                    *(ckt->CKTstate0 + here->BSIM2qbd) +  
                    *(ckt->CKTstate0 + here->BSIM2qbs); 

            /* store small signal parameters */
            if((!(ckt->CKTmode & (MODEAC | MODETRAN))) &&
                    (ckt->CKTmode & MODETRANOP ) && (ckt->CKTmode &
                    MODEUIC ))   goto line850;
            if(ckt->CKTmode & MODEINITSMSIG ) {  
                *(ckt->CKTstate0+here->BSIM2cggb) = cggb;
                *(ckt->CKTstate0+here->BSIM2cgdb) = cgdb;
                *(ckt->CKTstate0+here->BSIM2cgsb) = cgsb;
                *(ckt->CKTstate0+here->BSIM2cbgb) = cbgb;
                *(ckt->CKTstate0+here->BSIM2cbdb) = cbdb;
                *(ckt->CKTstate0+here->BSIM2cbsb) = cbsb;
                *(ckt->CKTstate0+here->BSIM2cdgb) = cdgb;
                *(ckt->CKTstate0+here->BSIM2cddb) = cddb;
                *(ckt->CKTstate0+here->BSIM2cdsb) = cdsb;     
                *(ckt->CKTstate0+here->BSIM2capbd) = capbd;
                *(ckt->CKTstate0+here->BSIM2capbs) = capbs;

                goto line1000;
            }
       
            if(ckt->CKTmode & MODEINITTRAN ) { 
                *(ckt->CKTstate1+here->BSIM2qb) =
                    *(ckt->CKTstate0+here->BSIM2qb) ;
                *(ckt->CKTstate1+here->BSIM2qg) =
                    *(ckt->CKTstate0+here->BSIM2qg) ;
                *(ckt->CKTstate1+here->BSIM2qd) =
                    *(ckt->CKTstate0+here->BSIM2qd) ;
            }
       
       
            error = NIintegrate(ckt,&geq,&ceq,0.0,here->BSIM2qb);
            if(error) return(error);
            error = NIintegrate(ckt,&geq,&ceq,0.0,here->BSIM2qg);
            if(error) return(error);
            error = NIintegrate(ckt,&geq,&ceq,0.0,here->BSIM2qd);
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
            cqgate = *(ckt->CKTstate0 + here->BSIM2iqg);
            cqbulk = *(ckt->CKTstate0 + here->BSIM2iqb);
            cqdrn = *(ckt->CKTstate0 + here->BSIM2iqd);
            ceqqg = cqgate - gcggb * vgb + gcgdb * vbd + gcgsb * vbs;
            ceqqb = cqbulk - gcbgb * vgb + gcbdb * vbd + gcbsb * vbs;
            ceqqd = cqdrn - gcdgb * vgb + gcddb * vbd + gcdsb * vbs;

            if(ckt->CKTmode & MODEINITTRAN ) {  
                *(ckt->CKTstate1 + here->BSIM2iqb) =  
                    *(ckt->CKTstate0 + here->BSIM2iqb);
                *(ckt->CKTstate1 + here->BSIM2iqg) =  
                    *(ckt->CKTstate0 + here->BSIM2iqg);
                *(ckt->CKTstate1 + here->BSIM2iqd) =  
                    *(ckt->CKTstate0 + here->BSIM2iqd);
            }

            /*
             *  load current vector
             */
line900:
   
            ceqbs = model->BSIM2type * (cbs-(gbs-ckt->CKTgmin)*vbs);
            ceqbd = model->BSIM2type * (cbd-(gbd-ckt->CKTgmin)*vbd);
     
            ceqqg = model->BSIM2type * ceqqg;
            ceqqb = model->BSIM2type * ceqqb;
            ceqqd =  model->BSIM2type * ceqqd;
            if (here->BSIM2mode >= 0) {
                xnrm=1;
                xrev=0;
                cdreq=model->BSIM2type*(cdrain-gds*vds-gm*vgs-gmbs*vbs);
            } else {
                xnrm=0;
                xrev=1;
                cdreq = -(model->BSIM2type)*(cdrain+gds*vds-gm*vgd-gmbs*vbd);
            }

            *(ckt->CKTrhs + here->BSIM2gNode) -= ceqqg;
            *(ckt->CKTrhs + here->BSIM2bNode) -=(ceqbs+ceqbd+ceqqb);
            *(ckt->CKTrhs + here->BSIM2dNodePrime) +=
                    (ceqbd-cdreq-ceqqd);
            *(ckt->CKTrhs + here->BSIM2sNodePrime) += 
                    (cdreq+ceqbs+ceqqg+ceqqb+ceqqd);

            /*
             *  load y matrix
             */

            *(here->BSIM2DdPtr) += (here->BSIM2drainConductance);
            *(here->BSIM2GgPtr) += (gcggb);
            *(here->BSIM2SsPtr) += (here->BSIM2sourceConductance);
            *(here->BSIM2BbPtr) += (gbd+gbs-gcbgb-gcbdb-gcbsb);
            *(here->BSIM2DPdpPtr) += 
                (here->BSIM2drainConductance+gds+gbd+xrev*(gm+gmbs)+gcddb);
            *(here->BSIM2SPspPtr) += 
                (here->BSIM2sourceConductance+gds+gbs+xnrm*(gm+gmbs)+gcssb);
            *(here->BSIM2DdpPtr) += (-here->BSIM2drainConductance);
            *(here->BSIM2GbPtr) += (-gcggb-gcgdb-gcgsb);
            *(here->BSIM2GdpPtr) += (gcgdb);
            *(here->BSIM2GspPtr) += (gcgsb);
            *(here->BSIM2SspPtr) += (-here->BSIM2sourceConductance);
            *(here->BSIM2BgPtr) += (gcbgb);
            *(here->BSIM2BdpPtr) += (-gbd+gcbdb);
            *(here->BSIM2BspPtr) += (-gbs+gcbsb);
            *(here->BSIM2DPdPtr) += (-here->BSIM2drainConductance);
            *(here->BSIM2DPgPtr) += ((xnrm-xrev)*gm+gcdgb);
            *(here->BSIM2DPbPtr) += (-gbd+(xnrm-xrev)*gmbs-gcdgb-gcddb-gcdsb);
            *(here->BSIM2DPspPtr) += (-gds-xnrm*(gm+gmbs)+gcdsb);
            *(here->BSIM2SPgPtr) += (-(xnrm-xrev)*gm+gcsgb);
            *(here->BSIM2SPsPtr) += (-here->BSIM2sourceConductance);
            *(here->BSIM2SPbPtr) += (-gbs-(xnrm-xrev)*gmbs-gcsgb-gcsdb-gcssb);
            *(here->BSIM2SPdpPtr) += (-gds-xrev*(gm+gmbs)+gcsdb);


line1000:  ;

        }   /* End of Mosfet Instance */

    }       /* End of Model Instance */
    return(OK);
}

