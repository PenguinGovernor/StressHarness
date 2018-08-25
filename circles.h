#ifndef CIRCLE_H
#define CIRCLE_H

#include <stdbool.h>

#define MATH_ERR -987.401

typedef struct circle_obj circle_t;
typedef struct point_obj point_t;

point_t *newPoint(double x, double y);
bool delPoint(point_t **p);

circle_t *newCircle(double x, double y, double r);
bool delCircle(circle_t **c);

double distance(point_t *one, point_t *two);
bool inCircle(circle_t *circle, point_t *ref);

point_t* getOrigin(circle_t* c);
double getRadius(circle_t* c);

#endif