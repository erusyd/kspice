/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
**********/

/*
 *	SYS-V and derivitive systems
 */

#include "os_unix.h"

#define HAS_SYSVTTY		/* <termio.h>				*/
#define HAS_SYSVDIRS		/* <dirent.h>				*/
#define HAS_SYSVRLIMIT
#define HAS_GETCWD
#define HAS_SYSVRUSAGE
#define HAS_SYSVTIME
#define HAS_STRCHR		/* strchr( ) instead of index( )	*/
#define HAS_FLOAT_H
#define HAS_ATRIGH		/* acosh( ), asinh( ), atanh( )         */

/* XXX This doesn't belong here */
#define index strchr
#define rindex strrchr
