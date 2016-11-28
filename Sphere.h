#ifndef SPHERE_H
#define SPHERE_H
#include <stdlib.h>

typedef struct Sphere{
	//particle variables
	//private static final String _initialParticlesColor = "purple";
	//static Random _randomGaussianX = new Random(System.currentTimeMillis());
	//static Random _randomGaussianY = new Random(System.currentTimeMillis() / 3);
	const char* _initialParticlesColor;
	int _tag;
	double _x;
	double _y;
	double _z;
	double _nextX;
	double _nextY;
	double _nextZ;
	double _previousVx;
	double _previousVy;
	double _previousVz;
	char* _color;

	//sphere variables
	double _radius;
}Sphere;

void init_sphere1D(Sphere *s, double x, double radius, double initVx, char* color);
void init_sphere2D(Sphere *s, double x, double y, double radius, double initVx, double initVy, char* color);
double getMinX(Sphere *s);
double getMaxX(Sphere *s);
double getMinY(Sphere *s);
double getMaxY(Sphere *s);
double getRadius(Sphere *s);
double getVx(Sphere *s);
double getVy(Sphere *s);
double getX(Sphere *s);
double getY(Sphere *s);
double getNextX(Sphere *s);
double getNextY(Sphere *s);
void updatePosition(Sphere *s);


char* getInitialParticlesColor(Sphere *s);

#endif