#include "GaussRand.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
//This uses the polar method of G. E. P. Box, M. E. Muller, and G. Marsaglia, as described by Donald E. Knuth in The Art of Computer Programming, 
//Volume 3: Seminumerical Algorithms, section 3.4.1, subsection C, algorithm P. Note that it generates two independent values at the cost of only one call to StrictMath.log and one call to StrictMath.sqrt.
double gaussRand()
{
	static double V1, V2, S;
	static int phase = 0;
	double X;

	if (phase == 0) {
		do {
			double U1 = (double)rand() / RAND_MAX;
			double U2 = (double)rand() / RAND_MAX;

			V1 = 2 * U1 - 1;
			V2 = 2 * U2 - 1;
			S = V1 * V1 + V2 * V2;
		} while (S >= 1 || S == 0);

		X = V1 * sqrt(-2 * log(S) / S);
	}
	else
		X = V2 * sqrt(-2 * log(S) / S);

	phase = 1 - phase;

	return X;
}
