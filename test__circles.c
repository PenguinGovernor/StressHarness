#include <stdio.h>

#include "circles.h"

int main()
{
	circle_t *c = newCircle(0, 0, 4);
	point_t *p = newPoint(3, 0);

	if (distance(getOrigin(c), p) != 3.0)
	{
		fprintf(stderr, "Got %lf wanted %lf\n", distance(getOrigin(c), p), 3.0);
	}
	else
	{
		printf("SUCCESS GOT 3\n");
	}

	if (inCircle(c, p))
	{
		printf("SUCCESS IN CIRCLE\n");
	}
	else
	{
		fprintf(stderr, "Point should be in circle. Fail\n");
	}

	delPoint(&p);

	p = newPoint(4, 5);
	printf("Point (4,5) is%sin the circle centered at (0,0) with r=4\n", inCircle(c, p) ? " " : " not ");
	delPoint(&p);
	delCircle(&c);

	return 0;
}
