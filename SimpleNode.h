#ifndef SIMPLENODE_H
#define SIMPLENODE_H
#include <stdbool.h>

typedef struct SimpleNode{
	char* _name;
	double _x;
	double _y;
	double _z;
	int _numberOfEmitters;
	int _numberOfReceivers;
}SimpleNode;
void init_SimpleNode1D(SimpleNode *, char* name, double x, int numberOfEmitters, int numberOfReceivers);
void init_SimpleNode2D(SimpleNode *, char* name, double x, double y, int numberOfEmitters, int numberOfReceivers);
void init_SimpleNode3D(SimpleNode *, char* name, double x, double y, double z, int numberOfEmitters, int numberOfReceivers);

#endif