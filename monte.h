#ifndef MONTE_H
#define MONTE_H

#include <stdlib.h>

#include "circles.h"

point_t *genRandomPoint(double xmin, double xmax, double ymin, double ymax);
double monteApproxPi(long long iterations, double r);
double monteApproxPiVerbose(long long iterations, double r);

#endif