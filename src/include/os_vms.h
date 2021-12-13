
/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
**********/

/*
 *	DEC VMS
 */

#define     DIR_PATHSEP		" "
#define     DIR_TERM		']'
#define     DIR_CWD		"."
#define     TEMPFORMAT		"TEMP%s%d.TMP"
#define HAS_ASCII
#define HAS_VMSHACK
#define HAS_UNLINK
#define HAS_SYSTEM
#define HAS_SYSVTIME
#define HAS_EXIT1
#define HAS_VPERROR
#define index strchr
#define rindex strrchr

#define AVAIL_X11	/* Haven't tried vms with X11, but it should work */
#define AVAIL_MFB

