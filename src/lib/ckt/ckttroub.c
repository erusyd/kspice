/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
**********/

#include "spice.h"
#include "misc.h"
#include <stdio.h>
#include "trandefs.h"
#include "cktdefs.h"
#include "devdefs.h"
#include "util.h"
#include "suffix.h"

extern SPICEdev *DEVices[];

char *
CKTtrouble(ckt, optmsg)
    CKTcircuit	*ckt;
    char	*optmsg;
{
    char	msg_buf[513];
    char	*emsg;

    if (!ckt)
	return NULL;
    if (!optmsg)
	optmsg = "";
    if (ckt->CKTtroubleNode)
	sprintf(msg_buf, "%s%sTime: %g, Timestep %g: trouble with %s\n",
		optmsg, optmsg && *optmsg ? "; " : "",
		ckt->CKTtime, ckt->CKTdelta,
		CKTnodName(ckt, ckt->CKTtroubleNode));
    else if (ckt->CKTtroubleElt)
	sprintf(msg_buf, "Time: %g, Timestep %g: trouble with %s:%s:%s\n",
		optmsg, optmsg && *optmsg ? "; " : "",
		ckt->CKTtime, ckt->CKTdelta,
		DEVices[ckt->CKTtroubleElt->GENmodPtr->GENmodType]
			->DEVpublic.name,
		ckt->CKTtroubleElt->GENmodPtr->GENmodName,
		ckt->CKTtroubleElt->GENname);
    else
	sprintf(msg_buf,
		"Time: %g, Timestep %g: No convergence problem detected.\n",
		ckt->CKTtime, ckt->CKTdelta);

    emsg = MALLOC(strlen(msg_buf)+1);
    strcpy(emsg,msg_buf);

    return emsg;
}
