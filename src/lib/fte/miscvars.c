/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Wayne A. Christopher, U. C. Berkeley CAD Group
**********/

#include "spice.h"
#include "cpdefs.h"
#include "ftedefs.h"
#include "ftedata.h"
#include "fteinp.h"
#include "suffix.h"

bool ft_nopage = false;
bool ft_parsedb = false;
bool ft_vecdb = false;
bool ft_simdb = false;
bool ft_evdb = false;
bool ft_grdb = false;
bool ft_gidb = false;
bool ft_controldb = false;
bool ft_asyncdb = false;

char *ft_setkwords[] = {

    "abstol",
    "acct",
    "appendwrite",
    "bypass",
    "chgtol",
    "color<num>",
    "cpdebug",
    "cptime",
    "curplot",
    "curplotname",
    "curplottitle",
    "curplotdate",
    "debug",
    "defad",
    "defas",
    "defl",
    "defw",
    "device",
    "display",
    "dontplot",
    "editor",
    "filetype",
    "fourgridsize",
    "geometry",
    "geometry<num>",
    "gmin",
    "gridsize",
    "hcopydev",
    "height",
    "history",
    "ignoreeof",
    "itl1",
    "itl2",
    "itl3",
    "itl4",
    "itl5",
    "list",
    "maxwins",
    "modelcard",
    "nomoremode",
    "nfreqs",
    "noasciiplotvalue",
    "noaskquit",
    "nobjthack",
    "nobreak",
    "noclobber",
    "node",
    "noglob",
    "nogrid",
    "nonomatch",
    "nopage",
    "noparse",
    "noprintscale",
    "nosort",
    "nosubckt",
    "numdgt",
    "opts",
    "pivrel",
    "pivtol",
    "plots",
    "pointchars",
    "polydegree",
    "polysteps",
    "program",
    "prompt",
    "rawfile",
    "rawfileprec",
    "reltol",
    "renumber",
    "rhost",
    "rprogram",
    "slowplot",
    "sourcepath",
    "spicepath",
    "subend",
    "subinvoke",
    "substart",
    "term",
    "ticmarks",
    "tnom",
    "trtol",
    "units",
    "unixcom",
    "vntol",
    "width",
    "xbrushheight",
    "xbrushwidth",
    "xfont",

    NULL
} ;
