/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
**********/

/*
 * Memory alloction functions
 */

#include "spice.h"
#include "stdio.h"
#include "misc.h"
#include "suffix.h"

/* Malloc num bytes and initialize to zero. Fatal error if the space can't
 * be malloc'd.   Return NULL for a request for 0 bytes.
 */

char *
tmalloc(num)
    int num;
{
    char *s;
#ifdef MALLOCTRACE
    int i;
    static char *mem_alloc();
#endif

    if (!num)
	return NULL;

#ifdef MALLOCTRACE
    s = mem_alloc((unsigned) num, 1, &i);
#else
    s = malloc((unsigned) num);
#endif
    if (!s) {
        fprintf(stderr, 
		"malloc: Internal Error: can't allocate %d bytes.\n", num);
        exit(EXIT_BAD);
    }
    bzero(s, num);
    return(s);
}

char *
trealloc(str, num)
    char *str;
    int num;
{
    char *s;
#ifdef MALLOCTRACE
    int i;
    static char *mem_alloc();
#endif

    if (!num) {
	if (str)
		free(str);
	return NULL;
    }

#ifdef MALLOCTRACE
    s = mem_alloc((unsigned) num, 1, &i);
    if (s) {
        bcopy(str, s, num); /* Hope this won't cause a mem fault. */
        free(str);
    }
#else
    if (!str)
	s = tmalloc(num);
    else
        s = realloc(str, (unsigned) num);
#endif

    if (!s) {
        fprintf(stderr, 
		"realloc: Internal Error: can't allocate %d bytes.\n", num);
        exit(EXIT_BAD);
    }
    return(s);
}

void
txfree(ptr)
	char	*ptr;
{
	if (ptr)
		free(ptr);
}
