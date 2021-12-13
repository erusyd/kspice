/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Wayne A. Christopher, U. C. Berkeley CAD Group
**********/

/*
 * Resource-related routines.
 */

#include "spice.h"
#include "cpdefs.h"
#include "ftedefs.h"

#ifdef HAS_BSDRLIMIT
#include <sys/time.h>
#include <sys/resource.h>
#endif
#ifdef HAS_BSDRUSAGE
#ifndef HAS_BSDRLIMIT
#include <sys/time.h>
#include <sys/resource.h>
#endif
#else
#ifdef HAS_SYSVRUSAGE
#include <sys/types.h>
#include <sys/times.h>
#include <sys/param.h>
#else
#ifdef HAS_FTIME
#include <sys/types.h>
#include <sys/timeb.h>
#endif
#endif
#endif

#include "suffix.h"

extern char *enddata;

static void printres();

void
com_rusage(wl)
    wordlist *wl;
{
    /* Fill in the SPICE accounting structure... */

    if (wl && (eq(wl->wl_word, "everything") || eq(wl->wl_word, "all"))) {
        printres((char *) NULL);
    } else if (wl) {
        for (; wl; wl = wl->wl_next) {
            printres(cp_unquote(wl->wl_word));
            if (wl->wl_next)
                (void) putc('\n', cp_out);
        }
    } else {
        printres("elapsed");
        (void) putc('\n', cp_out);
        printres("totaltime");
        (void) putc('\n', cp_out);
        printres("space");
    }
    return;
}

/* Find out if the user is approaching his maximum data size. */

#ifdef HAS_BSDRLIMIT
#define HAS_RLIMIT_
#endif
#ifdef HAS_SYSVRLIMIT
#define HAS_RLIMIT_
#endif

#ifdef HAS_BSDRUSAGE
#define HAS_RUSAGE_
#endif
#ifdef HAS_SYSVRUSAGE
#define HAS_RUSAGE_
#endif

void
ft_ckspace()
{
#ifdef HAS_RLIMIT_
    char *hi;
    long lim;

#ifdef HAS_DOSRLIMIT
    /* This is not very good here */
    extern unsigned int _memavl( );

    lim = _memavl( );
    if ((long) (enddata - lim) > ((long) enddata) * 0.9) {
        fprintf(cp_err, "Warning - approaching max data size: ");
        fprintf(cp_err, "cur size = %ld, hard limit = %ld.\n", 
                (long) (enddata - lim), (long) enddata);
    }
#else

#ifdef HAS_BSDRLIMIT
    struct rlimit rld;
    getrlimit(RLIMIT_DATA, &rld);
    if (rld.rlim_cur == RLIM_INFINITY)
        return;
    lim = rld.rlim_max;
#else
    /* SYSVRLIMIT */
    ulimit(3, 0L);
#endif
    hi = sbrk(0);
    if ((int) (hi - (char *) enddata) > lim * 0.9) {
        fprintf(cp_err, "Warning - approaching max data size: ");
        fprintf(cp_err, "cur size = %d, hard limit = %d.\n", 
                (int) hi, (int) lim);
    }
#ifdef HAS_BSDRLIMIT
    else if ((int) (hi - (char *) enddata) > rld.rlim_cur * 0.9) {
        fprintf(cp_err, "Warning - approaching max data size: ");
        fprintf(cp_err, "cur size = %d, soft limit = %d.\n", 
                (int) hi, (int) rld.rlim_cur);
    }
#endif

#endif
#endif
    return;
}

#ifdef HAS_SYSVRUSAGE

static long origrt = -1;
static long lastrt = -1;
static time_t lastut = -1, lastst = -1;

rset_time()
{
	struct tms dummy;
	long times();

	origrt = times(&dummy);
	lastut = dummy.tms_utime;
	lastst = dummy.tms_stime;
	lastrt = origrt;
}
#endif

/* Print out one piece of resource usage information. */

static void
printres(name)
    char *name;
{
    bool yy = false;
    static long lastsec = -1, lastusec = -1;
    struct variable *v;
    long   realt;
#ifndef HAS_BSDRUSAGE
#ifndef HAS_SYSVRUSAGE
#ifdef HAS_FTIME
    struct timeb timenow;
    extern struct timeb timebegin;
    int sec, msec;
#endif
#endif
#endif

    if (!name || eq(name, "totaltime")) {
#ifdef HAS_BSDRUSAGE
        struct rusage ruse;

        (void) getrusage(RUSAGE_SELF, &ruse);
        fprintf(cp_out, "Total run time: %lu.%03lu seconds.\n",
            ruse.ru_utime.tv_sec, ruse.ru_utime.tv_usec / 1000);
        lastsec = ruse.ru_utime.tv_sec;
        lastusec = ruse.ru_utime.tv_usec;
        yy = true;
#else
#ifdef HAS_SYSVRUSAGE
/*
 *  A system V time routine that works! (and has better resolution)
 */
	struct tms ruse;
	realt = times(&ruse);
	if( origrt != -1 )
           fprintf(cp_out, "Total real time  : %lu.%03lu seconds.\n",
		(realt - origrt)/HZ, ((realt - origrt)%HZ)*1000/HZ);
	else
		origrt = realt;
	fprintf(cp_out,
"Total user time  : %lu.%03lu seconds.\nTotal system time: %lu.%03lu seconds.\n",
		ruse.tms_utime/HZ, (ruse.tms_utime%HZ)*1000/HZ,
		ruse.tms_stime/HZ, (ruse.tms_stime%HZ)*1000/HZ);
/* If we havn't explicitly asked for totaltime then these variables
 *	shouldn't be reset untill the elapsed time section
 */
	if( eq(name, "totaltime")) {
		lastut = ruse.tms_utime;
		lastst = ruse.tms_stime;
		lastrt = realt;
	}
/*
        fprintf(cp_out, "Total run time: %lu seconds.\n", ruse.tms_utime);
        lastsec = ruse.tms_utime;
*/
        yy = true;
#else
#ifdef HAS_FTIME
	ftime(&timenow);
	timediff(&timenow, &timebegin, &sec, &msec);
	fprintf(cp_out, "Total run time: %u.%03u seconds.\n", sec, msec);
        yy = true;
#endif
#endif
#endif
    } 
    if (!name || eq(name, "space")) {
#ifdef HAS_BSDRLIMIT
        struct rlimit rld;
        char *hi;

        getrlimit(RLIMIT_DATA, &rld);
        hi = sbrk(0);
        fprintf(cp_out, "Current data size = %d,\n",
        (int) (hi - (char *) enddata));
        fprintf(cp_out, "Data limits: hard = %d, soft = %d.\n",
            rld.rlim_max, rld.rlim_cur);
        yy = true;
#else
#ifdef HAS_SYSVRLIMIT
	long	lim;
        char *hi;

	lim = ulimit(3, 0L);
        hi = sbrk(0);
        fprintf(cp_out, "Current data size = %d,\n",
	    (int) (hi - (char *) enddata));
        fprintf(cp_out, "Data limit = %d.\n", lim);
        yy = true;
#else
#ifdef HAS_DOSRLIMIT
	long	lim;
	lim = _memavl( );
        fprintf(cp_out,
	    "Dynamic memory space used (default data segment only) = %ld.\n",
	    (long) (enddata - lim));
        fprintf(cp_out, "Total space available = %ld.\n", (long) lim);
        yy = true;
#endif
#endif
#endif
    }
    if (!name || eq(name, "faults")) {
#ifdef HAS_BSDRUSAGE
        struct rusage ruse;

        (void) getrusage(RUSAGE_SELF, &ruse);
        fprintf(cp_out, 
        "%lu page faults, %lu vol + %lu invol = %lu context switches.\n",
                ruse.ru_majflt, ruse.ru_nvcsw, ruse.ru_nivcsw, 
                ruse.ru_nvcsw + ruse.ru_nivcsw);
        yy = true;
#endif
    } 
    if (!name || eq(name, "elapsed")) {
#ifdef HAS_BSDRUSAGE
        struct rusage ruse;

        (void) getrusage(RUSAGE_SELF, &ruse);
        if (lastsec >= 0) {
            if (ruse.ru_utime.tv_usec < lastusec) {
                ruse.ru_utime.tv_sec--;
                ruse.ru_utime.tv_usec += 1000000;
            }

            fprintf(cp_out,
                "Time since last call: %lu.%03lu seconds.\n",
                ruse.ru_utime.tv_sec - lastsec, 
                (ruse.ru_utime.tv_usec - lastusec) / 1000);
        }
        lastsec = ruse.ru_utime.tv_sec;
        lastusec = ruse.ru_utime.tv_usec;
        yy = true;
#else
#ifdef HAS_SYSVRUSAGE
	struct tms ruse;

	realt = times(&ruse);

	if( lastrt != -1 ) {
           fprintf(cp_out, "Real time since last call  : %lu.%03lu seconds.\n",
		(realt - lastrt)/HZ, ((realt - lastrt)%HZ)*1000/HZ);
	   fprintf(cp_out,
"User time since last call  : %lu.%03lu seconds.\nSystem time since last call: %lu.%03lu seconds.\n",
	(ruse.tms_utime - lastut)/HZ, ((ruse.tms_utime-lastut)%HZ)*1000/HZ,
	(ruse.tms_stime - lastst)/HZ, ((ruse.tms_stime-lastst)%HZ)*1000/HZ);
	}
	lastut = ruse.tms_utime;
	lastst = ruse.tms_stime;
	lastrt = realt;
/*
        fprintf(cp_out,
                "Time since last call: %lu seconds.\n",
		ruse.tms_utime - lastsec );
        lastsec = ruse.tms_utime;
*/
        yy = true;
#else
#ifdef HAS_FTIME
	ftime(&timenow);
	timediff(&timenow, &timebegin, &sec, &msec);
	fprintf(cp_out, "Time since last call: %u.03u seconds.\n", sec,
		msec);
        yy = true;
#endif
#endif
#endif
    } 

    /* Now get all the spice resource stuff. */
    if (ft_curckt && ft_curckt->ci_ckt) {
        v = if_getstat(ft_curckt->ci_ckt, name);
        if (name && v) {
            fprintf(cp_out, "%s = ", v->va_name);
            wl_print(cp_varwl(v), cp_out);
            (void) putc('\n', cp_out);
            yy = true;
        } else if (v) {
            (void) putc('\n', cp_out);
            while (v) {
                fprintf(cp_out, "%s = ", v->va_name);
                wl_print(cp_varwl(v), cp_out);
                (void) putc('\n', cp_out);
                v = v->va_next;
            }
            yy = true;
        }
    }

    if (!yy) {
        fprintf(cp_err, "Note: no resource usage information for '%s',\n",
		name);
        fprintf(cp_err, "\tor no active circuit available\n");
        
    }
    return;
}

