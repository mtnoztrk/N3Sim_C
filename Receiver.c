#include "Receiver.h"

void init_SquareReceiver1D(Receiver *s, char* name, double x, bool absorb, bool accumulate, double side){
	s->_name = name;
	s->_x = x;
	s->_y = -1;
	s->_z = -1;
	s->_absorb = absorb;
	s->_accumulate = accumulate;
	s->_halfSide = side / 2;

	s->_type = 1;
}
void init_SquareReceiver2D(Receiver *s, char* name, double x, double y, bool absorb, bool accumulate, double side){
	s->_name = name;
	s->_x = x;
	s->_y = y;
	s->_z = -1;
	s->_absorb = absorb;
	s->_accumulate = accumulate;
	s->_halfSide = side / 2;

	s->_type = 1;
}
void init_SquareReceiver3D(Receiver *s, char* name, double x, double y, double z, bool absorb, bool accumulate, double side){
	s->_name = name;
	s->_x = x;
	s->_y = y;
	s->_z = z;
	s->_absorb = absorb;
	s->_accumulate = accumulate;
	s->_halfSide = side / 2;

	s->_type = 1;
}

void init_SphericalReceiver1D(Receiver *p, char* name, double x, bool absorb, bool accumulate, double radius){
	p->_name = name;
	p->_x = x;
	p->_y = -1;
	p->_z = -1;
	p->_absorb = absorb;
	p->_accumulate = accumulate;
	p->_radius = radius;
	p->_totalCount = 0;

	p->_type = 2;
}
void init_SphericalReceiver2D(Receiver *p, char* name, double x, double y, bool absorb, bool accumulate, double radius){
	p->_name = name;
	p->_x = x;
	p->_y = y;
	p->_z = -1;
	p->_absorb = absorb;
	p->_accumulate = accumulate;
	p->_radius = radius;
	p->_totalCount = 0;

	p->_type = 2;
}


void init_SphericalReceiver3D(Receiver *p, char* name, double x, double y, double z, bool absorb, bool accumulate, double radius){
	p->_name = name;
	p->_x = x;
	p->_y = y;
	p->_z = z;
	p->_absorb = absorb;
	p->_accumulate = accumulate;
	p->_radius = radius;
	p->_totalCount = 0;

	p->_type = 3;
}
