#include "monte.h"
#include "circles.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

static double randomDouble(double min, double max)
{
	double r = (double)rand() / RAND_MAX;
	return min + r * (max - min);
}

point_t *genRandomPoint(double xmin, double xmax, double ymin, double ymax)
{
	double psubx = randomDouble(xmin, xmax),
		   psuby = randomDouble(ymin, ymax);

	point_t *randPoint = newPoint(psubx, psuby);
	return randPoint;
}

double monteApproxPiVerbose(long long iterations, double r)
{
	// Make a circle with radius 'r'
	circle_t *c = newCircle(0, 0, r);
	long long pointsIn = 0;
	point_t *p;
	double ratio, piApprox;

	// Generate random points
	for (long long i = 0; i < iterations; i += 1)
	{
		printf("VERBOSE: Iteration %lld\n", i);
		p = genRandomPoint(-1 * r, r, -1 * r, r);
		// Check if they're in the circle

		printf("VERBOSE: Generated point: (%lf,%lf)\n", getXCor(p), getYCor(p));

		if (inCircle(c, p) == true)
		{
			printf("VERBOSE: Point (%lf,%lf) IS in the circle with radius %lf centered about (0,0)\n", getXCor(p), getYCor(p), r);
			pointsIn += 1;
		}
		else
		{
			printf("VERBOSE: Point (%lf,%lf) is NOT in the circle with radius %lf centered about (0,0)\n", getXCor(p), getYCor(p), r);
		}

		ratio = ((double)pointsIn) / ((double)iterations);
		piApprox = 4.0 * ratio;
		printf("VERBOSE: Current ratio (%lld/%lld): %lf\n", pointsIn, iterations, ratio);
		printf("VERBOSE: Current pi approximation: %lf\n", piApprox);
		printf("-----------------------\n");
		delPoint(&p);
	}

	printf("DONE WITH MONTE CARLO PI APPROXIMATION\n");

	printf("Final Points in circle: %lld\n", pointsIn);
	printf("Total points: %lld\n", iterations);

	// Do monte carlo math -> pi = 4 * (pointIn/iteration)
	ratio = ((double)pointsIn) / ((double)iterations);
	piApprox = 4.0 * ratio;
	printf("Final ratio (%lld/%lld): %lf\n", pointsIn, iterations, ratio);
	printf("Final pi approximation: %lf\n", piApprox);
	delCircle(&c);
	return piApprox;
}

double monteApproxPi(long long iterations, double r)
{
	// Make a circle with radius 'r'
	circle_t *c = newCircle(0, 0, r);
	long long pointsIn = 0;
	point_t *p;
	double ratio, piApprox;

	// Generate random points
	for (long long i = 0; i < iterations; i += 1)
	{
		p = genRandomPoint(-1 * r, r, -1 * r, r);
		// Check if they're in the circle

		if (inCircle(c, p) == true)
		{
			pointsIn += 1;
		}

		delPoint(&p);
	}

	printf("DONE WITH MONTE CARLO PI APPROXIMATION\n");

	printf("Final Points in circle: %lld\n", pointsIn);
	printf("Total points: %lld\n", iterations);

	// Do monte carlo math -> pi = 4 * (pointIn/iteration)
	ratio = ((double)pointsIn) / ((double)iterations);
	piApprox = 4.0 * ratio;
	printf("Final ratio (%lld/%lld): %lf\n", pointsIn, iterations, ratio);
	printf("Final pi approximation: %lf\n", piApprox);
	delCircle(&c);
	return piApprox;
}