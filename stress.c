#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>

#include "flags.h"
#include "monte.h"

#ifndef NUM_ARGS
#define NUM_ARGS 5
#endif

typedef enum
{
	VERBOSE,
	NUM,
	MONTECARLO,
	MONTECARLO_RADIUS,
	QUIET
} argflag_t;

void printFlags(flag_t *flag, long long n, double r);
void verifyFlags(flag_t **flags);

int main(int argc, char const *argv[])
{

	srand(time(NULL));

	long long iterations = 50;
	double monteRadius = 10.0;

	flag_t *flags = newFlag(NUM_ARGS);
	int option;

	while ((option = getopt(argc, (char **)argv, "vmn:r:q")) != -1)
	{
		switch (option)
		{
		case 'n':
			setFlag(flags, NUM, true);
			iterations = (long long)atof(optarg);
			break;

		case 'v':
			setFlag(flags, VERBOSE, true);
			break;

		case 'm':
			setFlag(flags, MONTECARLO, true);
			break;

		case 'r':
			setFlag(flags, MONTECARLO_RADIUS, true);
			monteRadius = (double)atof(optarg);
			break;

		case 'q':
			setFlag(flags, QUIET, true);
			break;
		}
	}

	verifyFlags(&flags);

	if (checkFlag(flags, VERBOSE))
	{
		printFlags(flags, iterations, monteRadius);
	}

	if (checkFlag(flags, MONTECARLO))
	{

		if (checkFlag(flags, VERBOSE))
		{
			printf("Performing Monte Carlo pi approximation\n");
			monteApproxPiVerbose(iterations, monteRadius);
		}
		else if (checkFlag(flags, QUIET))
		{
			quietMonteApprox(iterations, monteRadius);
		}
		else
		{
			monteApproxPi(iterations, monteRadius);
		}
	}

	delFlag(&flags);
	return 0;
}

void printFlags(flag_t *flag, long long n, double r)
{
	printf("VERBOSE: Flag \"VERBOSE\" is on\n");
	printf("VERBOSE: Flag \"QUIET\" is off\n");
	printf("VERBOSE: Flag \"NUMITERATIONS\" is ");
	checkFlag(flag, NUM) == true ? printf("on\n") : printf("off\n");
	printf("VERBOSE: Value for flag \"NUMITERATIONS\" is %lld\n", n);
	printf("VERBOSE: Flag \"MONTECARLO\" is ");
	checkFlag(flag, MONTECARLO) == true ? printf("on\n") : printf("off\n");
	printf("VERBOSE: Flag \"MONTECARLO_RADIUS\" is ");
	checkFlag(flag, MONTECARLO_RADIUS) == true ? printf("on\n") : printf("off\n");
	printf("VERBOSE: Value for flag \"MONTECARLO_RADIUS\" is %lf\n", r);
}

void verifyFlags(flag_t **flags)
{
	// Can't have quiet and verbose on that's bad
	flag_t *f = *flags;
	if (checkFlag(f, QUIET) && checkFlag(f, VERBOSE))
	{
		perror("Invalid flags detected.\nFlag quiet and flag verbose are both on.\nExiting");
		delFlag(flags);
		exit(1);
	}
}
