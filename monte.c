#include "monte.h"
#include "circles.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

static double calcPerecentDiff(double accepted, double experimental)
{
	double pecrent = ((accepted - experimental) / (accepted)) * 100.0;
	if (pecrent < 0)
	{
		pecrent *= -1.0;
	}
	return pecrent;
}

static double randomDouble(double min, double max)
{
	double r = (double)rand() / RAND_MAX;
	return min + r * (max - min);
}

static double percentRound(double in, int precision)
{
	int powerOfTen = 1;
	for (int i = 0; i < precision; i += 1)
	{
		powerOfTen *= 10;
	}

	int temp = in * powerOfTen;
	return (double)temp / (double)powerOfTen;
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
	printf("Performing Monte Carlo pi approximation\n");

	// Make a circle with radius 'r'
	circle_t *c = newCircle(0, 0, r);
	long long pointsIn = 0, count = 0;
	point_t *p;
	double ratio, piApprox, percentDiff;

	// Generate random points
	for (long long i = 0; i < iterations; i += 1)
	{
		count += 1;
		printf("VERBOSE: Iteration %lld\n", i + 1);
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

		ratio = ((double)pointsIn) / ((double)count);
		piApprox = 4.0 * ratio;
		percentDiff = ((MONTE_PI - piApprox) / MONTE_PI) * 100.0;
		percentDiff = percentDiff < 0 ? percentDiff * -1 : percentDiff;
		printf("VERBOSE: Current ratio (%lld/%lld): %lf\n", pointsIn, count, ratio);
		printf("VERBOSE: Current pi approximation (ratio * 4) : %lf\n", piApprox);
		printf("VERBOSE: Current error rate: %lf%%\n", percentDiff);
		printf("-----------------------\n");
		delPoint(&p);
	}

	printf("Finished Monte Carlo pi approximation\n");

	printf("Final Points in circle: %lld\n", pointsIn);
	printf("Total points: %lld\n", iterations);
	printf("Final ratio (%lld/%lld): %lf\n", pointsIn, iterations, ratio);
	printf("Final pi approximation (ratio * 4) : %lf\n", piApprox);
	printf("Final error rate: %lf%%\n", percentDiff);
	printf("-----------------------\n");
	delCircle(&c);
	return piApprox;
}

double monteApproxPi(long long iterations, double r)
{
	printf("Performing Monte Carlo pi approximation\n");

	// Make a circle with radius 'r'
	circle_t *c = newCircle(0, 0, r);
	long long pointsIn = 0;
	point_t *p;
	double ratio, piApprox, percentDiff;

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

	printf("Finished Monte Carlo pi approximation\n");

	printf("Final Points in circle: %lld\n", pointsIn);
	printf("Total points: %lld\n", iterations);

	// Do monte carlo math -> pi = 4 * (pointIn/iteration)
	ratio = ((double)pointsIn) / ((double)iterations);
	piApprox = 4.0 * ratio;
	percentDiff = ((MONTE_PI - piApprox) / MONTE_PI) * 100.0;
	percentDiff = percentDiff < 0 ? percentDiff * -1 : percentDiff;
	printf("Final ratio (%lld/%lld): %lf\n", pointsIn, iterations, ratio);
	printf("Final pi approximation (ratio * 4): %lf\n", piApprox);
	printf("Final error rate: %lf%%\n", percentDiff);
	printf("-----------------------\n");
	delCircle(&c);
	return piApprox;
}

double quietMonteApprox(long long iterations, double r)
{
	// Make a circle with radius 'r'
	circle_t *c = newCircle(0, 0, r);
	long long pointsIn = 0;
	point_t *p;
	double ratio, piApprox, percentDiff;

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

	// Do monte carlo math -> pi = 4 * (pointIn/iteration)
	ratio = ((double)pointsIn) / ((double)iterations);
	piApprox = 4.0 * ratio;
	percentDiff = ((MONTE_PI - piApprox) / MONTE_PI) * 100.0;
	percentDiff = percentDiff < 0 ? percentDiff * -1 : percentDiff;
	delCircle(&c);
	return piApprox;
}

double perfectMonteApproxPi(double r, double target, int places)
{
	printf("Performing Monte Carlo Pi Approximation\nWill run until an error rate of %lf%% is reached or surpassed\n", target);
	// Make a circle with radius 'r'
	circle_t *c = newCircle(0, 0, r);
	long long pointsIn = 0;
	point_t *p;
	double ratio, piApprox, percentDiff;
	long long count = 0;
	percentDiff = 10000000;

	while (percentDiff > target)
	{
		count += 1;
		p = genRandomPoint(-1 * r, r, -1 * r, r);
		// Check if they're in the circle
		if (inCircle(c, p) == true)
		{
			pointsIn += 1;
		}
		delPoint(&p);
		ratio = ((double)pointsIn) / ((double)count);
		piApprox = 4.0 * ratio;
		percentDiff = percentRound(calcPerecentDiff(MONTE_PI, piApprox), places);
	}

	printf("Took %lld iterations\n", count);
	printf("Final ratio (%lld/%lld): %lf\n", pointsIn, count, ratio);
	printf("Final pi approximation (ratio * 4): %lf\n", piApprox);
	printf("Final error rate: %lf%%\n", percentDiff);
	printf("-----------------------\n");
	delCircle(&c);
	return piApprox;
}

double qPerfectMonteApproxPi(double r, double target, int places)
{
	// Make a circle with radius 'r'
	circle_t *c = newCircle(0, 0, r);
	long long pointsIn = 0;
	point_t *p;
	double ratio, piApprox, percentDiff;
	long long count = 0;
	percentDiff = 10000000;

	while (percentDiff > target)
	{
		count += 1;
		p = genRandomPoint(-1 * r, r, -1 * r, r);
		// Check if they're in the circle
		if (inCircle(c, p) == true)
		{
			pointsIn += 1;
		}
		delPoint(&p);
		ratio = ((double)pointsIn) / ((double)count);
		piApprox = 4.0 * ratio;
		percentDiff = percentRound(calcPerecentDiff(MONTE_PI, piApprox), places);
	}

	delCircle(&c);
	return piApprox;
}

double vPerfectMonteApproxPi(double r, double target, int places)
{
	printf("Performing Monte Carlo Pi Approximation\nWill run until an error rate of %lf%% is reached or surpassed\n", target);
	// Make a circle with radius 'r'
	circle_t *c = newCircle(0, 0, r);
	long long pointsIn = 0;
	point_t *p;
	double ratio, piApprox, percentDiff;
	long long count = 0;
	percentDiff = 10000000;

	while (percentDiff > target)
	{
		count += 1;
		printf("VERBOSE: Iteration %lld\n", count);
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

		delPoint(&p);
		ratio = ((double)pointsIn) / ((double)count);
		piApprox = 4.0 * ratio;
		percentDiff = percentRound(calcPerecentDiff(MONTE_PI, piApprox), places);
		printf("VERBOSE: Current ratio (%lld/%lld): %lf\n", pointsIn, count, ratio);
		printf("VERBOSE: Current pi approximation (ratio * 4) : %lf\n", piApprox);
		printf("VERBOSE: Current error rate: %lf%%\n", percentDiff);
		printf("-----------------------\n");
	}

	printf("Took %lld iterations\n", count);
	printf("Final ratio (%lld/%lld): %lf\n", pointsIn, count, ratio);
	printf("Final pi approximation (ratio * 4): %lf\n", piApprox);
	printf("Final error rate: %lf%%\n", percentDiff);
	printf("-----------------------\n");
	delCircle(&c);
	return piApprox;
}
