#include "Node.h"
#include <stdlib.h>

void init_SimpleNode1D(Node *s, char* name, double x, int numberOfEmitters, int numberOfReceivers){
	s->_name = name;
	s->_x = x;
	s->_y = -1;
	s->_z = -1;
	s->_numberOfEmitters = numberOfEmitters;
	s->_numberOfReceivers = numberOfReceivers;

	s->_emitterLen = 0;
	s->_emitterTotal = 4;
	s->_emitters = (Emitter*)malloc(sizeof(Emitter)*s->_emitterTotal);

	s->_receiverLen = 0;
	s->_receiverTotal = 4;
	s->_receivers = (Receiver*)malloc(sizeof(Receiver)*s->_receiverTotal);

	s->_type = 1;
}
void init_SimpleNode2D(Node *s, char* name, double x, double y, int numberOfEmitters, int numberOfReceivers){
	s->_name = name;
	s->_x = x;
	s->_y = y;
	s->_z = -1;
	s->_numberOfEmitters = numberOfEmitters;
	s->_numberOfReceivers = numberOfReceivers;

	s->_emitterLen = 0;
	s->_emitterTotal = 4;
	s->_emitters = (Emitter*)malloc(sizeof(Emitter)*s->_emitterTotal);

	s->_receiverLen = 0;
	s->_receiverTotal = 4;
	s->_receivers = (Receiver*)malloc(sizeof(Receiver)*s->_receiverTotal);

	s->_type = 1;
}
void init_SimpleNode3D(Node *s, char* name, double x, double y, double z, int numberOfEmitters, int numberOfReceivers){
	s->_name = name;
	s->_x = x;
	s->_y = y;
	s->_z = z;
	s->_numberOfEmitters = numberOfEmitters;
	s->_numberOfReceivers = numberOfReceivers;

	s->_emitterLen = 0;
	s->_emitterTotal = 4;
	s->_emitters = (Emitter*)malloc(sizeof(Emitter)*s->_emitterTotal);

	s->_receiverLen = 0;
	s->_receiverTotal = 4;
	s->_receivers = (Receiver*)malloc(sizeof(Receiver)*s->_receiverTotal);

	s->_type = 1;
}

void init_ImmediatelyReleasingNode1D(Node *s, char* name, double x, int initialSupply, int maxCapacity, int numberOfEmitters, int numberOfReceivers,
	double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, char* color, int harvesterIndex){
	s->_name = name;
	s->_x = x;
	s->_y = -1;
	s->_z = -1;
	s->_numberOfEmitters = 1;//numberOfEmitters is always 1
	s->_numberOfReceivers = numberOfReceivers;
	s->_initialSupply = initialSupply;
	s->_reservoir = initialSupply;
	s->_reservoirCapacity = maxCapacity;
	s->_harvesterIndex = harvesterIndex;
	s->_emitted = 0;
	s->_e = (Emitter*)malloc(sizeof(Emitter));
	init_ImmediatelyReleasingEmitter1D(s->_e, x, 0, 0, 0, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color);

	s->_emitterLen = 0;
	s->_emitterTotal = 4;
	s->_emitters = (Emitter*)malloc(sizeof(Emitter)*s->_emitterTotal);

	s->_receiverLen = 0;
	s->_receiverTotal = 4;
	s->_receivers = (Receiver*)malloc(sizeof(Receiver)*s->_receiverTotal);

	s->_type = 2;
}
void init_ImmediatelyReleasingNode2D(Node *s, char* name, double x, double y, int initialSupply, int maxCapacity, int numberOfEmitters, int numberOfReceivers,
	double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, char* color, int harvesterIndex){
	s->_name = name;
	s->_x = x;
	s->_y = y;
	s->_z = -1;
	s->_numberOfEmitters = 1;//numberOfEmitters is always 1
	s->_numberOfReceivers = numberOfReceivers;
	s->_initialSupply = initialSupply;
	s->_reservoir = initialSupply;
	s->_reservoirCapacity = maxCapacity;
	s->_harvesterIndex = harvesterIndex;
	s->_emitted = 0;
	s->_e = (Emitter*)malloc(sizeof(Emitter));
	init_ImmediatelyReleasingEmitter2D(s->_e, x, y, 0, 0, 0, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color);

	s->_emitterLen = 0;
	s->_emitterTotal = 4;
	s->_emitters = (Emitter*)malloc(sizeof(Emitter)*s->_emitterTotal);

	s->_receiverLen = 0;
	s->_receiverTotal = 4;
	s->_receivers = (Receiver*)malloc(sizeof(Receiver)*s->_receiverTotal);

	s->_type = 2;
}
void init_ImmediatelyReleasingNode3D(Node *s, char* name, double x, double y, double z, int initialSupply, int maxCapacity, int numberOfEmitters, int numberOfReceivers,
	double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, char* color, int harvesterIndex){
	s->_name = name;
	s->_x = x;
	s->_y = y;
	s->_z = z;
	s->_numberOfEmitters = 1;//numberOfEmitters is always 1
	s->_numberOfReceivers = numberOfReceivers;
	s->_initialSupply = initialSupply;
	s->_reservoir = initialSupply;
	s->_reservoirCapacity = maxCapacity;
	s->_harvesterIndex = harvesterIndex;
	s->_emitted = 0;
	s->_e = (Emitter*)malloc(sizeof(Emitter));
	init_ImmediatelyReleasingEmitter3D(s->_e, x, y, z, 0, 0, 0, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color);

	s->_emitterLen = 0;
	s->_emitterTotal = 4;
	s->_emitters = (Emitter*)malloc(sizeof(Emitter)*s->_emitterTotal);

	s->_receiverLen = 0;
	s->_receiverTotal = 4;
	s->_receivers = (Receiver*)malloc(sizeof(Receiver)*s->_receiverTotal);

	s->_type = 2;
}

void init_ImmediatelyPulseReleasingNode1D(Node *s, char* name, double x, int initialSupply, int maxCapacity, int numberOfEmitters, int numberOfReceivers,
	double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, char* color, double amplitude, int harvesterIndex){
	s->_name = name;
	s->_x = x;
	s->_y = -1;
	s->_z = -1;
	s->_numberOfEmitters = 1;//numberOfEmitters is always 1
	s->_numberOfReceivers = numberOfReceivers;
	s->_initialSupply = initialSupply;
	s->_reservoir = initialSupply;
	s->_reservoirCapacity = maxCapacity;
	s->_harvesterIndex = harvesterIndex;
	s->_emitted = 0;
	s->_e = (Emitter*)malloc(sizeof(Emitter));
	init_ImmediatelyReleasingEmitter1D(s->_e, x, 0, 0, 0, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color);
	s->_amplitude = amplitude;

	s->_emitterLen = 0;
	s->_emitterTotal = 4;
	s->_emitters = (Emitter*)malloc(sizeof(Emitter)*s->_emitterTotal);

	s->_receiverLen = 0;
	s->_receiverTotal = 4;
	s->_receivers = (Receiver*)malloc(sizeof(Receiver)*s->_receiverTotal);

	s->_type = 3;
}

void init_ImmediatelyPulseReleasingNode2D(Node *s, char* name, double x, double y, int initialSupply, int maxCapacity, int numberOfEmitters, int numberOfReceivers,
	double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, char* color, double amplitude, int harvesterIndex){
	s->_name = name;
	s->_x = x;
	s->_y = y;
	s->_z = -1;
	s->_numberOfEmitters = 1;//numberOfEmitters is always 1
	s->_numberOfReceivers = numberOfReceivers;
	s->_initialSupply = initialSupply;
	s->_reservoir = initialSupply;
	s->_reservoirCapacity = maxCapacity;
	s->_harvesterIndex = harvesterIndex;
	s->_emitted = 0;
	s->_e = (Emitter*)malloc(sizeof(Emitter));
	init_ImmediatelyReleasingEmitter2D(s->_e, x, y, 0, 0, 0, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color);
	s->_amplitude = amplitude;

	s->_emitterLen = 0;
	s->_emitterTotal = 4;
	s->_emitters = (Emitter*)malloc(sizeof(Emitter)*s->_emitterTotal);

	s->_receiverLen = 0;
	s->_receiverTotal = 4;
	s->_receivers = (Receiver*)malloc(sizeof(Receiver)*s->_receiverTotal);

	s->_type = 3;
}

void init_ImmediatelyPulseReleasingNode3D(Node *s, char* name, double x, double y, double z, int initialSupply, int maxCapacity, int numberOfEmitters, int numberOfReceivers,
	double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, char* color, double amplitude, int harvesterIndex){
	s->_name = name;
	s->_x = x;
	s->_y = y;
	s->_z = z;
	s->_numberOfEmitters = 1;//numberOfEmitters is always 1
	s->_numberOfReceivers = numberOfReceivers;
	s->_initialSupply = initialSupply;
	s->_reservoir = initialSupply;
	s->_reservoirCapacity = maxCapacity;
	s->_harvesterIndex = harvesterIndex;
	s->_emitted = 0;
	s->_e = (Emitter*)malloc(sizeof(Emitter));
	init_ImmediatelyReleasingEmitter3D(s->_e, x, y, z, 0, 0, 0, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color);
	s->_amplitude = amplitude;

	s->_emitterLen = 0;
	s->_emitterTotal = 4;
	s->_emitters = (Emitter*)malloc(sizeof(Emitter)*s->_emitterTotal);

	s->_receiverLen = 0;
	s->_receiverTotal = 4;
	s->_receivers = (Receiver*)malloc(sizeof(Receiver)*s->_receiverTotal);

	s->_type = 3;
}

void addEmitter(Node *s, Emitter e){
	if (s->_emitterLen + 1 >= s->_emitterTotal){
		s->_emitterTotal *= 2;
		s->_emitters = (Emitter*)realloc(s->_emitters, sizeof(Emitter)* s->_emitterTotal);
	}
	s->_emitters[s->_emitterLen++] = e;
}
void addReceiver(Node *s, Receiver r){
	if (s->_receiverLen + 1 >= s->_receiverTotal){
		s->_receiverTotal *= 2;
		s->_receivers = (Receiver*)realloc(s->_receivers, sizeof(Receiver)* s->_receiverTotal);
	}
	s->_receivers[s->_receiverLen++] = r;
}