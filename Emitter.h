#ifndef EMITTER_H
#define EMITTER_H
#include <stdbool.h>
#include "Sphere.h"

typedef struct Emitter{
	//particle emitter variables
	double _x, _y, _z;
	double _startTime;
	double _endTime;
	double _amplitude;
	double _emitterRadius;
	double _initV;
	bool _punctual;
	bool _concentrationEmitter;
	char *_color;

	//sphere emitter variables
	double _sphereRadius;

	//rectangular sphere emitter variables
	int _period;
	int _timeOn;

	//noise sphere emitter variables
	double _randomGaussianNoise;

	//immediately releasing emitter variables
	//TODO: int _amplitude = { 0 };

	int _type;
}Emitter;
void init_PulseSphereEmitter1D(Emitter *, double x, double startTime, double endTime, double amplitude, double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, char* color);
void init_PulseSphereEmitter2D(Emitter *, double x, double y, double startTime, double endTime, double amplitude, double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, char* color);
void init_PulseSphereEmitter3D(Emitter *, double x, double y, double z, double startTime, double endTime, double amplitude, double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, char* color);
void init_RectangularSphereEmitter1D(Emitter *, double x, double startTime, double endTime, double amplitude, double sphereRadius, double emitterRadius, double initV,
	bool punctual, bool concentrationEmitter, int period, int timeOn, char* color);
void init_RectangularSphereEmitter2D(Emitter *, double x, double y, double startTime, double endTime, double amplitude, double sphereRadius, double emitterRadius, double initV,
	bool punctual, bool concentrationEmitter, int period, int timeOn, char* color);
void init_RectangularSphereEmitter3D(Emitter *, double x, double y, double z, double startTime, double endTime, double amplitude, double sphereRadius, double emitterRadius, double initV,
	bool punctual, bool concentrationEmitter, int period, int timeOn, char* color);
void init_NoiseSphereEmitter1D(Emitter *, double x, double startTime, double endTime, double amplitude, double sphereRadius, double emitterRadius, double initV, 
	bool punctual, bool concentrationEmitter, char* color);
void init_NoiseSphereEmitter2D(Emitter *, double x, double y, double startTime, double endTime, double amplitude, double sphereRadius, double emitterRadius, double initV, 
	bool punctual, bool concentrationEmitter, char* color);
void init_NoiseSphereEmitter3D(Emitter *, double x, double y, double z, double startTime, double endTime, double amplitude, double sphereRadius, double emitterRadius, double initV, 
	bool punctual, bool concentrationEmitter, char* color);
void init_ImmediatelyReleasingEmitter1D(Emitter *, double x, double startTime, double endTime, double amplitude, double sphereRadius, double emitterRadius, double initV, 
	bool punctual, bool concentrationEmitter, char* color);
void init_ImmediatelyReleasingEmitter2D(Emitter *, double x, double y, double startTime, double endTime, double amplitude, double sphereRadius, double emitterRadius, double initV, 
	bool punctual, bool concentrationEmitter, char* color);
void init_ImmediatelyReleasingEmitter3D(Emitter *, double x, double y, double z, double startTime, double endTime, double amplitude, double sphereRadius, double emitterRadius, double initV, 
	bool punctual, bool concentrationEmitter, char* color);

void emitParticleFromEmitter(Emitter e, int emitterListLen, double time, Sphere *particlesList, int sizeParticlesList);
double getNumParticles(Emitter p, double time);
int deleteParticles(Emitter e, Sphere *particlesList, int sizeParticleList, int numParticles);
void addParticles(Emitter e, Sphere *particlesList, int sizeParticleList, int numParticles);

char* getDescription();
#endif