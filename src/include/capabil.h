/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
**********/

/*
 *  #define-s that are always on
 */

#define CAPZEROBYPASS
#define NEWCONV
/* #define CAPBYPASS	Internal use only */

/*
 *  #define-s to identify common capabilities
 */

#ifdef WANT_X11

#ifdef AVAIL_X11
#define HAS_X11
#endif

#else
#ifdef WANT_X10

#ifdef AVAIL_X10
#define HAS_X10
#endif

#ifdef WANT_XT
#ifdef AVAIL_XT
#define HAS_XT
#endif
#endif

#endif	/* X10 */

#endif	/* !X11 */

#ifdef WANT_MFB
#ifdef AVAIL_MFB
#define HAS_MFB
#endif
#endif

#ifdef HAS_BSDDIRS
#define HAS_DIRS_
#endif
#ifdef HAS_SYSVDIRS
#define HAS_DIRS_
#endif
#ifdef HAS_DOSDIRS
#define HAS_DIRS_
#endif

#ifdef HAS_BSDTTY
#define HAS_TTY_
#endif
#ifdef HAS_SYSVTTY
#define HAS_TTY_
#endif

#ifdef HAS_BSDTIME
#define HAS_TIME_
#endif
#ifdef HAS_SYSVTIME
#define HAS_TIME_
#endif

#ifdef HAS_BSDRLIMIT
#define HAS_RLIMIT_
#endif
#ifdef HAS_SYSVRLIMIT
#define HAS_RLIMIT_
#endif
#ifdef HAS_DOSRLIMIT
#define HAS_RLIMIT_
#endif

#ifdef HAS_X10
#define HAS_X_
#endif
#ifdef HAS_X11
#define HAS_X_
#endif

#ifndef DIR_TERM
#define DIR_TERM	0
#endif

#ifndef DIR_PATHSEP
#define DIR_PATHSEP	0
#endif

#ifndef DIR_CWD
#define DIR_CWD		0
#endif

#ifdef HAS_NO_IEEE_LOGB
#  ifndef HAS_NO_IEEE_LOGB_DECL
#    define HAS_NO_IEEE_LOGB_DECL
#  endif
#endif

#ifdef HAS_NO_IEEE_LOGB_DECL
#ifdef __STDC__
extern double logb(double), scalb(double, int);
#else
extern double logb( ), scalb( );
#endif
#endif
