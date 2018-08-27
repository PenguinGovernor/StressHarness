#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>

#include "flags.h"
#include "monte.h"

#ifndef NUM_ARGS
#define NUM_ARGS 6
#endif

typedef enum
{
	VERBOSE,
	NUM,
	MONTECARLO,
	MONTECARLO_RADIUS,
	QUIET,
	PERF_MONTE
} argflag_t;

void printFlags(flag_t *flag, long long n, double r, double errorRate);
void verifyFlags(flag_t **flags);
int placesAfterDecimal(char *str);

int main(int argc, char const *argv[])
{

	srand(time(NULL));

	long long iterations = 50;
	double monteRadius = 10.0;
	int precise;
	double targetPrecision;

	flag_t *flags = newFlag(NUM_ARGS);
	int option;

	while ((option = getopt(argc, (char **)argv, "vmn:r:qM:")) != -1)
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

		case 'M':
			setFlag(flags, PERF_MONTE, true);
			precise = placesAfterDecimal(optarg);
			precise -= 1;
			precise += 1;
			targetPrecision = (double)atof(optarg);
			targetPrecision += 1;
			targetPrecision -= 1;

			break;
		}
	}

	verifyFlags(&flags);

	if (checkFlag(flags, VERBOSE))
	{
		printFlags(flags, iterations, monteRadius, targetPrecision);
	}

	if (checkFlag(flags, MONTECARLO))
	{

		if (checkFlag(flags, VERBOSE))
		{
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

	if (checkFlag(flags, PERF_MONTE))
	{

		if (checkFlag(flags, VERBOSE))
		{
			vPerfectMonteApproxPi(monteRadius, targetPrecision, precise);
		}
		else if (checkFlag(flags, QUIET))
		{
			qPerfectMonteApproxPi(monteRadius, targetPrecision, precise);
		}
		else
		{
			perfectMonteApproxPi(monteRadius, targetPrecision, precise);
		}
	}

	delFlag(&flags);
	return 0;
}

void printFlags(flag_t *flag, long long n, double r, double errorRate)
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
	printf("VERBOSE: Flag \"PERF_MONTE\" is ");
	checkFlag(flag, PERF_MONTE) == true ? printf("on\n") : printf("off\n");
	printf("VERBOSE: Value for flag \"PERF_MONTE\" is %lf\n", errorRate);
	printf("-----------------------\n");
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

int placesAfterDecimal(char *str)
{
	if (str == NULL)
	{
		perror("Passed null ref to places after decimal");
		return -1;
	}

	int count = 1;
	bool seenDecimal = false;

	for (int i = 0; str[i] != '\0'; i += 1)
	{
		if (str[i] == '.')
		{
			seenDecimal = true;
		}
		if (seenDecimal)
		{
			count += 1;
		}
	}

	return count;
}
