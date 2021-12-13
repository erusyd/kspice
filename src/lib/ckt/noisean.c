/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1987 Gary W. Ng
**********/

#include "spice.h"
#include <stdio.h>
#include <math.h>
#include "strext.h"
#include "acdefs.h"
#include "cktdefs.h"
#include "fteconst.h"
#include "iferrmsg.h"
#include "isrcdefs.h"
#include "noisedef.h"
#include "sperror.h"
#include "vsrcdefs.h"
#include "util.h"
#include "suffix.h"

int
NOISEan (ckt, restart)

CKTcircuit *ckt;
int restart;

{
    register Ndata *data;
    double realVal;
    double imagVal;
    int error;
    int posOutNode;
    int negOutNode;
    int code;
    int step;
    register CKTnode *node;
    IFuid freqUid;
    double freqTol; /* tolerence parameter for finding final frequency; hack */

    register NOISEAN *job = (NOISEAN*) (ckt->CKTcurJob);
    static char *nodundef =   "noise output node is not defined";
    static char *noacinput =    "no AC input source for noise analysis";


    /* make sure all the nodes/sources referenced are actually in the circuit */

    posOutNode = -1;
    if (job->Noutput)
	for (node = ckt->CKTnodes; node; node = node->next) {
	    if (strcmp(node->name, job->Noutput) == 0) {
		posOutNode = node->number;
		break;
	    }
	}
    if (posOutNode == -1) {
        errMsg = MALLOC(strlen(nodundef)+1);
        strcpy(errMsg,nodundef);
	return (E_NODUNDEF);
    }
    if (job->NoutputRef) {     /* was an output reference specified? */
	negOutNode = -1;
	for (node = ckt->CKTnodes; node; node = node->next) {
	    if (strcmp(node->name, job->NoutputRef) == 0) {
		negOutNode = node->number;
		break;
	    }
	}
	if (negOutNode == -1) {
        errMsg = MALLOC(strlen(nodundef)+1);
        strcpy(errMsg,nodundef);
	    return (E_NODUNDEF);
        }
    } else {
	negOutNode = 0;     /* if no output reference node was specified, we assume ground */
    }

    /* see if the source specified is AC */

    code = CKTtypelook("Vsource");
    if (code >= 0) {        /* if Vsources are supported */
        register VSRCinstance *inst;
	register VSRCmodel *model;
	for (model=(VSRCmodel*)ckt->CKThead[code]; model != NULL; model=model->VSRCnextModel) {
	    for (inst=model->VSRCinstances; inst != NULL; inst=inst->VSRCnextInstance) {
		if (strcmp(inst->VSRCname,job->Ninput) == 0) {
		    if (inst->VSRCacGiven) {
			goto okay;
                    } else {
        errMsg = MALLOC(strlen(noacinput)+1);
        strcpy(errMsg,noacinput);
			return (E_NOACINPUT);
                    }
                }
            }
        }
    }
    code = CKTtypelook("Isource");
    if (code >= 0) {        /* if Isources are supported */
        register ISRCinstance *inst;
	register ISRCmodel *model;
	for (model=(ISRCmodel*)ckt->CKThead[code]; model != NULL; model=model->ISRCnextModel) {
	    for (inst=model->ISRCinstances; inst != NULL; inst=inst->ISRCnextInstance) {
		if (strcmp(inst->ISRCname,job->Ninput) == 0) {
		    if (inst->ISRCacGiven) {
			goto okay;
                    } else {
        errMsg = MALLOC(strlen(noacinput)+1);
        strcpy(errMsg,noacinput);
			return (E_NOACINPUT);
                    }
                }
            }
        }
    }
        errMsg = MALLOC(strlen(noacinput)+1);
        strcpy(errMsg,noacinput);
    return (E_NOACINPUT);

okay:
    if ( (job->NsavFstp == 0) || restart) {
	switch (job->NstpType) {


        case DECADE:
            job->NfreqDelta = exp(log(10.0)/
                            job->NnumSteps);
            break;

        case OCTAVE:
            job->NfreqDelta = exp(log(2.0)/
	                    job->NnumSteps);
            break;

        case LINEAR:
            job->NfreqDelta = (job->NstopFreq - 
                            job->NstartFreq)/
			    (job->NnumSteps+1);
            break;

        default:
            return(E_BADPARM);
        }

	/* error = DCop(ckt); */
	error = CKTop(ckt, (ckt->CKTmode & MODEUIC) | MODEDCOP | MODEINITJCT,
		(ckt->CKTmode & MODEUIC) | MODEDCOP | MODEINITFLOAT,
		ckt->CKTdcMaxIter);


	if (error) return(error);
        data = (Ndata*)MALLOC(sizeof(Ndata));
	step = 0;
	data->freq = job->NstartFreq;
	data->outNoiz = 0.0;
	data->inNoise = 0.0;


	/* the current front-end needs the namelist to be fully
		declared before an OUTpBeginplot */

	(*(SPfrontEnd->IFnewUid))((GENERIC *)ckt,&freqUid,(IFuid)NULL,
		"frequency", UID_OTHER,(GENERIC **)NULL);

	data->numPlots = 0;                /* we don't have any plots  yet */
        error = CKTnoise(ckt,N_DENS,N_OPEN,data);
        if (error) return(error);

	/*
	 * all names in the namelist have been declared. now start the
	 * plot
	 */

	(*(SPfrontEnd->OUTpBeginPlot))(ckt,(GENERIC *)(ckt->CKTcurJob),
	   "Noise Spectral Density Curves - (V^2 or A^2)/Hz",
	   freqUid,IF_REAL,data->numPlots,data->namelist,IF_REAL,
	   &(data->NplotPtr));

    } else {   /* we must have paused before.  pick up where we left off */
	step = job->NsavFstp;
	switch (job->NstpType) {

	case DECADE:
        case OCTAVE:
	    data->freq = job->NstartFreq * exp (step *
		     log (job->NfreqDelta));
            break;
            
        case LINEAR:
	    data->freq = job->NstartFreq + step *
		     job->NfreqDelta;
            break;

        default:
            return(E_BADPARM);

        }
	job->NsavFstp = 0;
	data->outNoiz = job->NsavOnoise;
	data->inNoise = job->NsavInoise;
    }

    switch (job->NstpType) {
    case DECADE:
    case OCTAVE:
        freqTol = job->NfreqDelta * job->NstopFreq * ckt->CKTreltol;
        break;
    case LINEAR:
        freqTol = job->NfreqDelta * ckt->CKTreltol;
        break;
    default:
        return(E_BADPARM);
    }

    data->lstFreq = data->freq;

    /* do the noise analysis over all frequencies */

    while (data->freq <= job->NstopFreq + freqTol) {
        if( (*(SPfrontEnd->IFpauseTest))() ) { 
	    job->NsavFstp = step;   /* save our results */
	    job->NsavOnoise = data->outNoiz; /* up until now     */
	    job->NsavInoise = data->inNoise;
	    return (E_PAUSE);
        }
	ckt->CKTomega = 2.0 * M_PI * data->freq;
	ckt->CKTmode = (ckt->CKTmode & MODEUIC) | MODEAC;

	/*
	 * solve the original AC system to get the transfer
	 * function between the input and output
	 */

	NIacIter(ckt);
	realVal = *((ckt->CKTrhsOld) + posOutNode)
		- *((ckt->CKTrhsOld) + negOutNode);
	imagVal = *((ckt->CKTirhsOld) + posOutNode)
		- *((ckt->CKTirhsOld) + negOutNode);
	data->GainSqInv = 1.0 / MAX(((realVal*realVal)
		+ (imagVal*imagVal)),N_MINGAIN);
	data->lnGainInv = log(data->GainSqInv);

	/* set up a block of "common" data so we don't have to
	 * recalculate it for every device
	 */

	data->delFreq = data->freq - data->lstFreq;
	data->lnFreq = log(MAX(data->freq,N_MINLOG));
	data->lnLastFreq = log(MAX(data->lstFreq,N_MINLOG));
        data->delLnFreq = data->lnFreq - data->lnLastFreq;

	if ((job->NStpsSm != 0) && ((step % (job->NStpsSm)) == 0)) {
	    data->prtSummary = TRUE;
        } else {
	    data->prtSummary = FALSE;
        }

	/*
	data->outNumber = 1;       
	*/

	data->outNumber = 0;
	/* the frequency will NOT be stored in array[0]  as before; instead,
	 * it will be given in refVal.rValue (see later)
	 */

	NInzIter(ckt,posOutNode,negOutNode);   /* solve the adjoint system */

	/* now we use the adjoint system to calculate the noise
	 * contributions of each generator in the circuit
	 */

	error = CKTnoise(ckt,N_DENS,N_CALC,data);
	if (error) return(error);
	data->lstFreq = data->freq;

	/* update the frequency */

	switch (job->NstpType) {

	case DECADE:
	case OCTAVE:
	    data->freq *= job->NfreqDelta;
	    break;

        case LINEAR:
	    data->freq += job->NfreqDelta;
	    break;
        
	default:
	    return(E_INTERN);
        }
	step++;
    }

    error = CKTnoise(ckt,N_DENS,N_CLOSE,data);
    if (error) return(error);

    data->numPlots = 0;
    data->outNumber = 0;

    if (job->NstartFreq != job->NstopFreq) {
	error = CKTnoise(ckt,INT_NOIZ,N_OPEN,data);

	if (error) return(error);

	(*(SPfrontEnd->OUTpBeginPlot))(ckt,(GENERIC *)(ckt->CKTcurJob),
	       "Integrated Noise - V^2 or A^2",
	       (IFuid)NULL,(int)0,data->numPlots,data->namelist,IF_REAL,
	       &(data->NplotPtr));

	error = CKTnoise(ckt,INT_NOIZ,N_CALC,data);
	if (error) return(error);

	error = CKTnoise(ckt,INT_NOIZ,N_CLOSE,data);
	if (error) return(error);
    }

    FREE(data);
    return(OK);
}
