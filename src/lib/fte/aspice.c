/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Wayne A. Christopher, U. C. Berkeley CAD Group
**********/

/*
 * Stuff for asynchronous spice runs, and also rspice.
 */

#include "spice.h"
#include "cpdefs.h"
#include "ftedefs.h"

#ifdef HAS_BSDSOCKETS


#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <netdb.h>

#ifdef HAS_GETPW
#include <pwd.h>
#endif

#ifdef HAS_UNIX_SIGS
#include <signal.h>
#endif

#include "fteinp.h"
#include "ftedata.h"
#include "suffix.h"

static int sigchild();

struct proc {
    int pr_pid;     /* The pid of the spice job. */
    char *pr_rawfile;   /* The temporary raw file. */
    char *pr_name;      /* The name of the spice run. */
    char *pr_inpfile;   /* The name of the input file. */
    char *pr_outfile;   /* The name of the (tmp) output file. */
    bool pr_saveout;    /* Don't (void) unlink the output file */
    struct proc *pr_next;   /* Link. */
} ;

static struct proc *running = NULL;
static int numchanged = 0;  /* How many children have changed in state. */

void
com_aspice(wl)
    wordlist *wl;
{
    char *deck, *output = NULL, spicepath[BSIZE_SP], s[BSIZE_SP];
    char *raw, *t;
    FILE *inp;
    struct proc *p;
    int pid;
    bool saveout = false;

    if (!Spice_Path) {
        fprintf(cp_err,
	    "No spice-3 binary is available for the aspice command.\n");
	return;
    }

    deck = wl->wl_word;
    if (!cp_getvar("spicepath", VT_STRING, spicepath))
        (void) strcpy(spicepath, Spice_Path);

    if (wl->wl_next) {
        output = wl->wl_next->wl_word;
        saveout = true;
    } else {
        output = smktemp("spout");
    }

    if ((inp = fopen(deck, "r")) == NULL) {
        perror(deck);
        return;
    }
    if (!fgets(s, BSIZE_SP, inp)) {
        fprintf(cp_err, "Error: bad deck %s\n", deck);
        (void) fclose(inp);
        return;
    }
    for (t = s; *t && (*t != '\n'); t++)
        ;
    *t = '\0';
    fprintf(cp_out, "Starting spice run for:\n%s\n", s);
    (void) fclose(inp);
    raw = smktemp("raw");
    (void) fclose(fopen(raw, "w")); /* So there isn't a race condition. */
    pid = fork();
    if (pid == 0) {
        if (!(freopen(deck, "r", stdin))) {
            perror(deck);
            exit (EXIT_BAD);
        }
        if (!(freopen(output, "w", stdout))) {
            perror(output);
            exit (EXIT_BAD);
        }
        (void) dup2(fileno(stdout), fileno(stderr));

        (void) execl(spicepath, spicepath, "-r", raw, 0);

        /* Screwed up. */
        perror(spicepath);
        exit(EXIT_BAD);
    }

    /* Add this one to the job list. */
    p = alloc(struct proc);
    p->pr_pid = pid;
    p->pr_name = copy(s);
    p->pr_rawfile = copy(raw);
    p->pr_inpfile = copy(deck);
    p->pr_outfile = copy(output);
    p->pr_saveout = saveout;
    if (running)
        p->pr_next = running;
    running = p;
#ifdef SIGCHLD
    (void) signal(SIGCHLD, sigchild);
#else
#ifdef SIGCLD
    (void) signal(SIGCLD, sigchild);
#endif
#endif
    return;
}

/* ARGSUSED */
void
com_jobs(wl)
    wordlist *wl;
{
    struct proc *p;

    for (p = running; p; p = p->pr_next)
        fprintf(cp_out, "%d\t%.70s\n", p->pr_pid, p->pr_name);
    return;
}

static int
sigchild()
{
    numchanged++;
    if (ft_asyncdb)
        fprintf(cp_err, "%d jobs done now\n", numchanged);
    if (cp_cwait) {
        ft_checkkids();
    }
    return;
}

/* This gets called every once in a while, and checks to see if any
 * jobs have finished. If they have it gets the data.  The problem is
 * that wait(0) is probably more portable, but it can't tell
 * whether the exit was normal or not.
 */

void
ft_checkkids()
{
    struct proc *p, *lp;
    char buf[BSIZE_SP];
    FILE *fp;
    int pid;
    static bool here = false;   /* Don't want to be re-entrant. */

    if (!numchanged || here)
        return;

    here = true;

    while (numchanged > 0) {
        pid = wait((union wait *) NULL);
        if (pid == -1) {
            fprintf(cp_err, 
"ft_checkkids: Internal Error: should be %d jobs done but there aren't any.\n",
                numchanged);
            numchanged = 0;
            running = NULL;
            here = false;
            return;
        }
        for (p = running; p; p = p->pr_next) {
            if (p->pr_pid == pid)
                break;
            lp = p;
        }
        if (p == NULL) {
            fprintf(cp_err,
            "ft_checkkids: Internal Error: Process %d not a job!\n",
                    pid);
            here = false;
            return;
        }
        if (p == running)
            running = p->pr_next;
        else
            lp->pr_next = p->pr_next;
        fprintf(cp_out, "Job finished: %.60s\n", p->pr_name);
        numchanged--;
        ft_loadfile(p->pr_rawfile);
        (void) unlink(p->pr_rawfile);
        out_init();
        if (!(fp = fopen(p->pr_outfile, "r"))) {
            perror(p->pr_outfile);
            here = false;
            return;
        }
        while (fgets(buf, BSIZE_SP, fp))
            out_send(buf);
        (void) fclose(fp);
        if (!p->pr_saveout)
            (void) unlink(p->pr_outfile);
        printf("\n-----\n");
    }
    printf("\n");
#ifdef TIOCSTI
    (void) ioctl(0, TIOCSTI, "\022");   /* Reprint the line. */
#endif
    here = false;
    return;
}

/* Run a spice job remotely. See the description of the spice daemon for
 * the protocol. This is 4.2 specific.
 */

void
com_rspice(wl)
    wordlist *wl;
{
    char rhost[64], *user, host[64], program[128], buf[BSIZE_SP];
    char *outfile;
    struct servent *sp;
    struct protoent *pp;
    struct hostent *hp;
    struct sockaddr_in server;
    FILE *inp, *serv, *out;
    struct passwd *pw;
    struct plot *pl;
    int s, i;

    /* Figure out where the spicedaemon is and connect to it. */
    if (!cp_getvar("rhost", VT_STRING, rhost))
        (void) strcpy(rhost, Spice_Host);
    if (!cp_getvar("rprogram", VT_STRING, program))
        *program = '\0';
    if (*rhost == '\0') {
        fprintf(cp_err,
        "Error: there is no remote spice host for this site.\n");
    }
    pw = getpwuid(getuid());
    if (pw == NULL) {
        fprintf(cp_err, "Who the heck are you, anyway??\n");
        return;
    }
    user = pw->pw_name;
    if (gethostname(host, 64) > 0) {
        perror("gethostname");
        return;
    }

    sp = getservbyname("spice", "tcp");
    if (sp == NULL) {
        fprintf(cp_err, "Error: spice/tcp: unknown service\n");
        return;
    }
    pp = getprotobyname("tcp");
    if (pp == NULL) {
        fprintf(cp_err, "Error: tcp: unknown protocol\n");
        return;
    }
    hp = gethostbyname(rhost);
    if (hp == NULL) {
        fprintf(cp_err, "Error: unknown host %s\n", rhost);
        return;
    }
    bzero((char *) &server, sizeof (struct sockaddr_in));
    bcopy(hp->h_addr, (char *) &server.sin_addr, hp->h_length);
    server.sin_family = hp->h_addrtype;
    server.sin_port = sp->s_port;

    /* Create the socket. */
    s = socket(AF_INET, SOCK_STREAM, pp->p_proto);
    if (s < 0) {
        perror("socket");
        return;
    }

    if (connect(s, (struct sockaddr *) &server, 
            sizeof (struct sockaddr)) < 0) {
        perror("connect");
        return;
    }

    /* Now we are ready to do the stuff. */
    if (*program)
        (void) sprintf(buf, "%s %s %s", user, host, program);
    else
        (void) sprintf(buf, "%s %s", user, host);
    (void) write(s, buf, strlen(buf) + 1);      /* Get the trailing \0. */
    if (read(s, buf, BSIZE_SP) <= 0) {
        fprintf(cp_err, "Connection (void) closed\n");
        (void) close(s);
        return;
    }

    if (eq(buf, "toomany")) {
        fprintf(cp_err, 
    "\nSorry, %s is too loaded now -- please try another machine\n",
            rhost);
        fprintf(cp_err, 
    "\tthat has a spice server running, or try again later.\n");
        (void) close(s);
        return;
    } else if (!eq(buf, "ok")) {
        fprintf(cp_err, "Error: remote spiced says %s\n", buf);
        (void) close(s);
        return;
    }

    /* Send the circuit over. */
    if (wl) {
        while (wl) {
            if (!(inp = fopen(wl->wl_word, "r"))) {
                perror(wl->wl_word);
                wl = wl->wl_next;
                continue;   /* Should be careful */
            }
            while ((i = fread(buf, 1, BSIZE_SP, inp)) > 0)
                (void) write(s, buf, i);
            wl = wl->wl_next;
        }
        (void) write(s, "@\n", 3);
    } else {
        if (ft_nutmeg || !ft_curckt) {
            fprintf(cp_err, "Error: no circuits loaded\n");
            (void) close(s);
            return;
        }
            
        /* We have to make a FILE struct for the socket. */
        inp = fdopen(s, "w");
        inp_list(inp, ft_curckt->ci_deck, ft_curckt->ci_options,
                LS_DECK);
        fputs("@\n", inp);
        (void) fflush(inp);
    }

    /* Now wait for things to come through */
    serv = fdopen(s, "r");
    while (fgets(buf, BSIZE_SP, serv) != NULL) {
        if (*buf == '@')
            break;
        fputs(buf, cp_out);
    }
    outfile = smktemp("rsp");
    if (!(out = fopen(outfile, "w"))) {
        perror(outfile);
        (void) fclose(serv);
        return;
    }
    while (i = fread(buf, 1, BSIZE_SP, serv))
        (void) fwrite(buf, 1, i, out);
    (void) fclose(out);
    (void) fclose(serv);
    pl = raw_read(outfile);
    if (pl)
        plot_add(pl);
    (void) unlink(outfile);
    return;
}

#else	/* if ! HAS_BSDSOCKETS */

/* ARGSUSED */
void
com_aspice(wl)
    wordlist *wl;
{
    fprintf(cp_err, "Asynchronous spice jobs are not available.\n");
    return;
}

/* ARGSUSED */
void
com_jobs(wl)
    wordlist *wl;
{
    fprintf(cp_err, "Asynchronous spice jobs are not available.\n");
    return;
}

#ifdef HAS_SYSTEM

#define SUBMIT "/bin/csh /usr/bin/rspice"

void
com_rspice(wl)
    wordlist *wl;
{
    char *output, *raw;
    char *input, buf[BSIZE_SP];
    FILE *fp;

    if (wl && !wl->wl_next) {
        input = wl->wl_word;
    } else {
        fprintf(cp_err, "Error: you must supply the input deck name.\n");
        return;
    }
    output = smktemp("out");
    raw = smktemp("raw");

    fprintf(cp_out, "Running job, please wait. ");
    (void) fflush(cp_out);
    (void) sprintf(buf, "%s %s %s %s", SUBMIT, input, output, raw);
    if (system(buf) != 0)
        return;
    
    fprintf(cp_out, "done.\n\n");
    
    if (!(fp = fopen(output, "r"))) {
        perror(output);
        return;
    }
    while (fgets(buf, BSIZE_SP, fp))
        fputs(buf, cp_out);
    (void) fclose(fp);
    (void) unlink(output);

    ft_loadfile(raw);
    (void) unlink(raw);
    return;
}

#else

/* ARGSUSED */
void
com_rspice(wl)
    wordlist *wl;
{
    fprintf(cp_err, "Remote spice runs are not available.\n");
    return;
}

#endif

void ft_checkkids() {}

#endif

