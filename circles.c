#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "circles.h"

struct point_obj
{
	double x;
	double y;
};

struct circle_obj
{
	point_t *origin;
	double radius;
};

point_t *newPoint(double x, double y)
{
	point_t *p = malloc(sizeof(point_t));
	if (p == NULL)
	{
		perror("Failed to allocate space for point");
		return p;
	}
	p->x = x;
	p->y = y;
	return p;
}

bool delPoint(point_t **p)
{
	if (p == NULL || *p == NULL)
	{
		perror("Passed null ref to del point");
		return false;
	}
	free(*p);
	*p = NULL;
	return true;
}

circle_t *newCircle(double x, double y, double r)
{
	circle_t *c = malloc(sizeof(circle_t));
	if (c == NULL)
	{
		perror("Failed to alloc space for circle");
		return c;
	}
	c->origin = newPoint(x, y);
	c->radius = r;
	return c;
}

bool delCircle(circle_t **c)
{
	if (c == NULL || *c == NULL)
	{
		perror("Passed null ref to del circle");
		return false;
	}

	delPoint(&((*c)->origin));
	*c = NULL;
	free(*c);
	*c = NULL;
	return true;
}

double distance(point_t *one, point_t *two)
{
	if (one == NULL || two == NULL)
	{
		perror("Passed null ref to del point");
		return MATH_ERR;
	}
	return sqrt(pow(one->x - two->x, 2.0) + pow(one->y - two->y, 2));
}
bool inCircle(circle_t *circle, point_t *ref)
{
	if (circle == NULL || ref == NULL)
	{
		perror("Passed null ref to in cicrle");
		return false;
	}
	return distance(ref, circle->origin) < circle->radius;
}

point_t *getOrigin(circle_t *c)
{
	if (c == NULL)
	{
		perror("Passed null ref to get origin ");
		return NULL;
	}

	return c->origin;
}

double getRadius(circle_t *c)
{
	if (c == NULL)
	{
		perror("Passed null ref to get radius");
		return MATH_ERR;
	}

	return c->radius;
}