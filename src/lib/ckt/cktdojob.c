/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

#include "spice.h"
#include "cktdefs.h"
#include <stdio.h>
#include "sperror.h"
#include "trandefs.h"
#include "util.h"
#include "suffix.h"

extern SPICEanalysis *analInfo[];
extern int ANALmaxnum;

int
CKTdoJob(inCkt,reset,inTask)
    GENERIC *inCkt;
    int reset;
    GENERIC *inTask;
{
    CKTcircuit	*ckt = (CKTcircuit *)inCkt;
    TSKtask	*task = (TSKtask *)inTask;
    JOB		*job;
    double	startTime;
    int		senflag;
    int		error, i;

    static int	sens_num = -1;

    /* Sensitivity is special */
    if (sens_num < 0) {
	for (i = 0; !error && i <  ANALmaxnum; i++)
	    if (!strcmp("SEN", analInfo[i]->public.name))
		break;
	sens_num = i;
    }

    startTime = (*(SPfrontEnd->IFseconds))( );

    ckt->CKTtemp  = task->TSKtemp;
    ckt->CKTnomTemp  = task->TSKnomTemp;
    ckt->CKTmaxOrder  = task->TSKmaxOrder;
    ckt->CKTintegrateMethod  = task->TSKintegrateMethod;
    ckt->CKTbypass  = task->TSKbypass;
    ckt->CKTdcMaxIter  = task->TSKdcMaxIter;
    ckt->CKTdcTrcvMaxIter  = task->TSKdcTrcvMaxIter;
    ckt->CKTtranMaxIter  = task->TSKtranMaxIter;
    ckt->CKTnumSrcSteps  = task->TSKnumSrcSteps;
    ckt->CKTnumGminSteps  = task->TSKnumGminSteps;
    ckt->CKTminBreak  = task->TSKminBreak;
    ckt->CKTabstol  = task->TSKabstol;
    ckt->CKTpivotAbsTol  = task->TSKpivotAbsTol;
    ckt->CKTpivotRelTol  = task->TSKpivotRelTol;
    ckt->CKTreltol  = task->TSKreltol;
    ckt->CKTchgtol  = task->TSKchgtol;
    ckt->CKTvoltTol  = task->TSKvoltTol;
    ckt->CKTgmin  = task->TSKgmin;
    ckt->CKTdelmin  = task->TSKdelmin;
    ckt->CKTtrtol  = task->TSKtrtol;
    ckt->CKTdefaultMosL  = task->TSKdefaultMosL;
    ckt->CKTdefaultMosW  = task->TSKdefaultMosW;
    ckt->CKTdefaultMosAD  = task->TSKdefaultMosAD;
    ckt->CKTdefaultMosAS  = task->TSKdefaultMosAS;
    ckt->CKTfixLimit  = task->TSKfixLimit;
    ckt->CKTnoOpIter  = task->TSKnoOpIter;
    ckt->CKTtryToCompact = task->TSKtryToCompact;
    ckt->CKTtroubleNode  = 0;
    ckt->CKTtroubleElt  = NULL;
#ifdef NEWTRUNC
    ckt->CKTlteReltol = task->TSKlteReltol;
    ckt->CKTlteAbstol = task->TSKlteAbstol;
#endif /* NEWTRUNC */

    error = 0;

    if (reset) {

	ckt->CKTdelta = 0.0;
	ckt->CKTtime = 0.0;
	ckt->CKTcurrentAnalysis = 0;

	senflag = 0;
	if (sens_num < ANALmaxnum)
	    for (job = task->jobs; !error && job; job = job->JOBnextJob) {
		if (job->JOBtype == i) {
		    senflag = 1;
		    ckt->CKTcurJob = job;
		    ckt->CKTsenInfo = (SENstruct *) job;
		    error = (*(analInfo[sens_num]->an_func))(ckt, reset);
		}
	    }

	if (ckt->CKTsenInfo && (!senflag || error))
	    FREE(ckt->CKTsenInfo);

	/* normal reset */
	if (!error)
	    error = CKTsetup(ckt);
	if (!error)
	    error = CKTtemp(ckt);
    }

    /* Analysis order is important */
    for (i = 0; !error && i < ANALmaxnum; i++) {

	if (i == sens_num)
	    continue;

	for (job = task->jobs; !error && job; job = job->JOBnextJob) {
	    if (job->JOBtype == i) {
                ckt->CKTcurJob=job;
		if (analInfo[i]->an_init)
		    error = (*(analInfo[i]->an_init))(ckt, job);
		if (!error && analInfo[i]->do_ic)
		    error = CKTic(ckt);
		if (!error)
		    error = (*(analInfo[i]->an_func))(ckt, reset);
			/* txl, cpl addition */
			if (error == 1111) break;
	    }
	}
    }

    ckt->CKTstat->STATtotAnalTime += (*(SPfrontEnd->IFseconds))( ) - startTime;

    if (ckt->CKTsenInfo)
	SENdestroy(ckt->CKTsenInfo);

    return(error);
}

