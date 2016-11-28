#ifndef RECEIVER_H
#define RECEIVER_H
#include <stdbool.h>

typedef struct Receiver{

	//particle receiver variables
	char* _name;
	double _x;
	double _y;
	double _z;
	bool _absorb;
	bool _accumulate; //assign false
	int _totalCount;

	//square receiver variables
	double _halfSide;

	//spherical receiver variables
	double _radius;

	int _type;
}Receiver;
void init_SquareReceiver1D(Receiver *, char* name, double x, bool absorb, bool accumulate, double side);
void init_SquareReceiver2D(Receiver *, char* name, double x, double y, bool absorb, bool accumulate, double side);
void init_SquareReceiver3D(Receiver *, char* name, double x, double y, double z, bool absorb, bool accumulate, double side);

void init_SphericalReceiver1D(Receiver *p, char* name, double x, bool absorb, bool accumulate, double radius);
void init_SphericalReceiver2D(Receiver *p, char* name, double x, double y, bool absorb, bool accumulate, double radius);

void init_SphericalReceiver3D(Receiver *p, char* name, double x, double y, double z, bool absorb, bool accumulate, double radius);
#endif