#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>

#include "flags.h"
#include "monte.h"

#ifndef NUM_ARGS
#define NUM_ARGS 4
#endif

#ifndef NUM_TESTS
#define NUM_TESTS 1
#endif

typedef enum
{
	VERBOSE,
	NUM,
	MONTECARLO,
	MONTECARLO_RADIUS
} argflag_t;

void printFlags(flag_t *flag, long long n, double r);

int main(int argc, char const *argv[])
{

	srand(time(NULL));

	long long iterations = 50;
	double monteRadius = 10.0;

	flag_t *flags = newFlag(NUM_ARGS);
	int option;

	while ((option = getopt(argc, (char **)argv, "vmn:r:")) != -1)
	{
		switch (option)
		{
		case 'n':
			setFlag(flags, NUM, true);
			iterations = atoi(optarg);
			break;

		case 'v':
			setFlag(flags, VERBOSE, true);
			break;

		case 'm':
			setFlag(flags, MONTECARLO, true);
			break;

		case 'r':
			setFlag(flags, MONTECARLO_RADIUS, true);
			monteRadius = atoi(optarg);
			break;
		}
	}

	if (checkFlag(flags, VERBOSE))
	{
		printFlags(flags, iterations, monteRadius);
	}

	if (checkFlag(flags, MONTECARLO))
	{
		printf("Performing montecarlo pi approximation\n");

		if (checkFlag(flags, VERBOSE))
		{
			monteApproxPiVerbose(iterations, monteRadius);
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
	printf("VERBOSE: Flag \"NUMITERATIONS\" is ");
	checkFlag(flag, NUM) == true ? printf("on\n") : printf("off\n");
	printf("VERBOSE: Value for flag \"NUMITERATIONS\" is %lld\n", n);
	printf("VERBOSE: Flag \"MONTECARLO\" is ");
	checkFlag(flag, MONTECARLO) == true ? printf("on\n") : printf("off\n");
	printf("VERBOSE: Flag \"MONTECARLO_RADIUS\" is ");
	checkFlag(flag, MONTECARLO_RADIUS) == true ? printf("on\n") : printf("off\n");
	printf("VERBOSE: Value for flag \"MONTECARLO_RADIUS\" is %lf\n", r);
}