/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Wayne A. Christopher, U. C. Berkeley CAD Group
**********/

/*
 * The signal routines for spice 3 and nutmeg.
 */

#include "spice.h"
#include "ifsim.h"
#include "iferrmsg.h"
#include "cpdefs.h"
#include "ftedefs.h"
#include "ftedev.h"
#include <setjmp.h>
#ifdef HAS_UNIX_SIGS
#include <signal.h>
#endif
#include "suffix.h"

#ifdef HAS_UNIX_SIGS
#ifdef HAS_LONGJUMP

extern jmp_buf jbuf;

/* The (void) signal handlers... SIGINT is the only one that gets reset (by
 * cshpar) so it is global. They are ifdef BSD because of the sigmask
 * stuff in sigstop. We set the interrupt flag and return if ft_setflag
 * is true.
 */

int
ft_sigintr()
{

    gr_clean();

    (void) signal( SIGINT, ft_sigintr );

    if (ft_intrpt)
        fprintf(cp_err, "Interrupt (ouch)\n");
    else {
        fprintf(cp_err, "Interrupt\n");
        ft_intrpt = true;
    }
    if (ft_setflag)
        return;
/* To restore screen after an interrupt to a plot for instance
 */
#ifdef HAS_MFB
	if( !strcmp( dispdev->name, "MFB" ))
		MFBHalt();
#endif
    cp_interactive = true;
    cp_resetcontrol();
    longjmp(jbuf, 1);
}

/* ARGSUSED */
int
sigfloat(sig, code)
{
    gr_clean();
    fperror("Error", code);
    rewind(cp_out);
    (void) signal( SIGFPE, sigfloat );
    longjmp(jbuf, 1);
}

/* This should give a new prompt if cshpar is waiting for input.  */

#ifdef SIGTSTP

int
sigstop( )
{
    gr_clean();
    cp_ccon(false);
    (void) signal(SIGTSTP, SIG_DFL);
    (void) kill(getpid(), SIGTSTP); /* This should stop us */
    return;
}

int
sigcont( )
{
    (void) signal(SIGTSTP, sigstop);
    if (cp_cwait)
        longjmp(jbuf, 1);
}

#endif

/* Special (void) signal handlers. */

int
sigill()
{
    fprintf(cp_err, "\ninternal error -- illegal instruction\n");
    fatal();
}

int
sigbus()
{
    fprintf(cp_err, "\ninternal error -- bus error\n");
    fatal();
}

int
sigsegv()
{
    fprintf(cp_err, "\ninternal error -- segmentation violation\n");
    fatal();
}

int
sig_sys()
{
    fprintf(cp_err, 
        "\ninternal error -- bad argument to system call\n");
    fatal();
}

#endif
#endif

