/**********
Copyright 1991 Regents of the University of California.  All rights reserved.
**********/

/*
 * Missing math functions
 */

#include "spice.h"
#include "stdio.h"
#include "misc.h"
#include "suffix.h"

#ifdef HAS_NO_IEEE_LOGB

double
logb(x)
	double	x;
{
	double	y = 0.0;

	if (x != 0.0) {
		if (x < 0.0)
			x = - x;
		while (x > 2.0) {
			y += 1.0;
			x /= 2.0;
		}
		while (x < 1.0) {
			y -= 1.0;
			x *= 2.0;
		}
	} else
		y = 0.0;

	return y;
}

double
scalb(x, n)
	double	x;
	int	n;
{
	double	y, z = 1.0, k = 2.0;

	if (n < 0) {
		n = -n;
		k = 0.5;
	}

	if (x != 0.0)
		for (y = 1.0; n; n >>= 1) {
			y *= k;
			if (n & 1)
				z *= y;
		}

	return x * z;
}

#endif
