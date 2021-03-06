/**********
Copyright 1991 Regents of the University of California.  All rights reserved.
**********/

/*
 *	SunOS
 */

#include "os_unix.h"

#define HAS_NO_ATRIGH_DECL	/* if asinh( ) is not in math.h		*/
#define HAS_ATRIGH		/* acosh( ), asinh( ), atanh( )         */
#define HAS_FTIME		/* ftime( ), <times.h>			*/
#define HAS_TERMCAP		/* tgetxxx( )				*/
#define HAS_VFORK		/* BSD-ism, should not be necessary	*/
#define HAS_INDEX		/* index( ) instead of strchr( )	*/
#define HAS_BCOPY		/* bcopy( ), bzero( )			*/
#define HAS_BSDRANDOM		/* srandom( ) and random( )		*/
#define HAS_POSIXTTY		/* <termios.h>				*/
#define HAS_BSDDIRS		/* <sys/dir.h>				*/
#define HAS_BSDRUSAGE		/* getrusage( )				*/
#define HAS_BSDRLIMIT		/* getrlimit( )				*/
#define HAS_BSDSOCKETS		/* <net/inet.h>, socket( ), etc.	*/
#define HAS_BSDTIME
#define HAS_DUP2
#define HAS_GETWD		/* getwd(buf)				*/
#define HAS_STRINGS		/* use <strings.h> instead of <string.h> */

#define AVAIL_X11
#define AVAIL_MFB
