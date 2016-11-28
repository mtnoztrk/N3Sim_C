#ifndef NODE_H
#define NODE_H
#include <stdbool.h>
#include "Emitter.h"
#include "Receiver.h"

typedef struct Node{
	char* _name;
	double _x;
	double _y;
	double _z;
	int _numberOfEmitters;
	int _numberOfReceivers;

	Receiver *_receivers;
	int _receiverLen, _receiverTotal;
	Emitter *_emitters;
	int _emitterLen, _emitterTotal;
	

	//HarvestingNode variables
	int _initialSupply;         // TODO: long int?
	int _reservoirCapacity;     // TODO: long int?
	int _reservoir;             // TODO: long int?
	int _harvestedParticles;
	int _harvesterIndex;
	int _emitted;

	//ImmediatelyReleasingEmitter _e;
	Emitter *_e;

	//ImmediatelyPulseReleasingNode variables
	double _amplitude;

	int _type;
}Node;
void init_SimpleNode1D(Node *, char* name, double x, int numberOfEmitters, int numberOfReceivers);
void init_SimpleNode2D(Node *, char* name, double x, double y, int numberOfEmitters, int numberOfReceivers);
void init_SimpleNode3D(Node *, char* name, double x, double y, double z, int numberOfEmitters, int numberOfReceivers);

void init_ImmediatelyReleasingNode1D(Node *, char* name, double x, int initialSupply, int maxCapacity, int numberOfEmitters, int numberOfReceivers,
	double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, char* color, int harvesterIndex);
void init_ImmediatelyReleasingNode2D(Node *, char* name, double x, double y, int initialSupply, int maxCapacity, int numberOfEmitters, int numberOfReceivers,
	double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, char* color, int harvesterIndex);
void init_ImmediatelyReleasingNode3D(Node *, char* name, double x, double y, double z, int initialSupply, int maxCapacity, int numberOfEmitters, int numberOfReceivers,
	double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, char* color, int harvesterIndex);

void init_ImmediatelyPulseReleasingNode1D(Node *, char* name, double x, int initialSupply, int maxCapacity, int numberOfEmitters, int numberOfReceivers,
	double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, char* color, double amplitude, int harvesterIndex);
void init_ImmediatelyPulseReleasingNode2D(Node *, char* name, double x, double y, int initialSupply, int maxCapacity, int numberOfEmitters, int numberOfReceivers,
	double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, char* color, double amplitude, int harvesterIndex);
void init_ImmediatelyPulseReleasingNode3D(Node *, char* name, double x, double y, double z, int initialSupply, int maxCapacity, int numberOfEmitters, int numberOfReceivers,
	double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, char* color, double amplitude, int harvesterIndex);

void addEmitter(Node *, Emitter e);
void addReceiver(Node *, Receiver r);

#endif