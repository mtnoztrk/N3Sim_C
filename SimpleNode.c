#include "SimpleNode.h"

void init_SimpleNode1D(SimpleNode *s, char* name, double x, int numberOfEmitters, int numberOfReceivers){
	s->_name = name;
	s->_x = x;
	s->_numberOfEmitters = numberOfEmitters;
	s->_numberOfReceivers = numberOfReceivers;
}
void init_SimpleNode2D(SimpleNode *s, char* name, double x, double y, int numberOfEmitters, int numberOfReceivers){
	s->_name = name;
	s->_x = x;
	s->_y = y;
	s->_numberOfEmitters = numberOfEmitters;
	s->_numberOfReceivers = numberOfReceivers;
}
void init_SimpleNode3D(SimpleNode *s, char* name, double x, double y, double z, int numberOfEmitters, int numberOfReceivers){
	s->_name = name;
	s->_x = x;
	s->_y = y;
	s->_z = z;
	s->_numberOfEmitters = numberOfEmitters;
	s->_numberOfReceivers = numberOfReceivers;
}