#include "Sphere.h"
#include "GaussRand.h"

void init_sphere1D(Sphere *s, double x, double radius, double initVx, char* color){
	s->_tag = 0;
	s->_x = x;
	s->_y = -1;
	s->_z = -1;
	s->_radius = radius;
	s->_previousVx = initVx;
	s->_color = color;
	s->_nextX = -1;
	s->_nextY = -1;
	s->_nextZ = -1;
	s->_previousVy = -1;
	s->_previousVz = -1;
	s->_initialParticlesColor = "Purple";
	//s->_randomGaussianX = gaussRand();
	//s->_randomGaussianY = gaussRand();

}
void init_sphere2D(Sphere *s, double x, double y, double radius, double initVx, double initVy, char* color){
	s->_tag = 0;
	s->_x = x;
	s->_y = y;
	s->_z = -1;
	s->_radius = radius;
	s->_previousVx = initVx;
	s->_previousVy = initVy;
	s->_color = color;
	s->_nextX = -1;
	s->_nextY = -1;
	s->_nextZ = -1;
	s->_previousVy = -1;
	s->_previousVz = -1;
	s->_initialParticlesColor = "Purple";
	//s->_randomGaussianX = gaussRand();
	//s->_randomGaussianY = gaussRand();
}

double getMinX(Sphere *s) {
	return s->_x<s->_nextX ? s->_x - s->_radius : s->_nextX - s->_radius;
}

double getMaxX(Sphere *s) {
	return s->_x>s->_nextX ? s->_x + s->_radius : s->_nextX + s->_radius;
}

double getMinY(Sphere *s) {
	return s->_y<s->_nextY ? s->_y - s->_radius : s->_nextY - s->_radius;
}

double getMaxY(Sphere *s) {
	return s->_y>s->_nextY ? s->_y + s->_radius : s->_nextY + s->_radius;
}

double getRadius(Sphere *s) {
	return s->_radius;
}

double getVx(Sphere *s) {
	return s->_nextX - s->_x;
}

double getVy(Sphere *s) {
	return s->_nextY - s->_y;
}

double getX(Sphere *s) {
	return s->_x;
}

double getY(Sphere *s) {
	return s->_y;
}

double getNextX(Sphere *s){
	return s->_nextX;
}

double getNextY(Sphere *s){
	return s->_nextY;
}

void updatePosition(Sphere *s){
	s->_previousVx = s->_nextX - s->_x;
	s->_x = s->_nextX;

	if (s->_y != -1 && s->_z == -1) {
		s->_previousVy = s->_nextY - s->_y;
		s->_y = s->_nextY;
	}
	else if (s->_z != -1) {
		s->_previousVz = s->_nextZ - s->_z;
		s->_z = s->_nextZ;
	}
}

char* getInitialParticlesColor(Sphere *s){
	if (s->_initialParticlesColor != NULL)
		return s->_initialParticlesColor;
	else
		return "Purple";
}