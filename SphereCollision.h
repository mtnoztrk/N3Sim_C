#ifndef SPHERECOLLISION_H
#define SPHERECOLLISION_H
#include <stdlib.h>
#include "Sphere.h"
#include "VerticalBoundary.h"
#include "HorizontalBoundary.h"


typedef struct SphereCollision{
	//particle collision
	double _time; // -1
	Sphere _sphere;
	int _sphereTag;
	Sphere _sphere2;
	int _sphere2Tag;
	//1: SphereSphere 2: SphereVertical 3: SphereHorizontal
	int _type;

	VerticalBoundary _vb;
	HorizontalBoundary _hb;

}SphereCollision;

void init_SphereSphereCollision(SphereCollision *c, Sphere *s, Sphere *s2);
void init_SphereVerticalBoundaryCollision(SphereCollision *c, Sphere *s, VerticalBoundary *s2);
void init_SphereHorizontalBoundaryCollision(SphereCollision *c, Sphere *s, HorizontalBoundary *s2);
double getTime(SphereCollision*);
#endif