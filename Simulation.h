#ifndef SIMULATION_H
#define SIMULATION_H
#include <stdlib.h>
#include "Sphere.h"
#include "HorizontalBoundary.h"
#include "VerticalBoundary.h"
#include "GaussRand.h"
#include "QuickSort.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include "PriorityQueue.h"

#include "Emitter.h"
#include "Receiver.h"
#include "Node.h"

#include "SphereCollision.h"

typedef struct Simulation{
	//simulator variables
	double _time;
	double _endTime;
	double _timeStep;
	bool _graphics;
	bool _infoFile;
	long _simulationSystemTime;

	//space variables
	double _D;                  // diffusion coefficient (nm^2/ns)
	double _bgConcentration;    // initial concentration rate. Number spheres per 10000 nm2
	double _radius;             // radius of the spheres of the initial concentration
	double _xSize;
	double _ySize;
	double _zSize;
	bool _activeCollision;
	double _BMFactor;
	double _inertiaFactor;
	bool _boundedSpace;
	bool _constantBGConcentration;
	double _constantBGConcentrationWidth;

	//collisions variables
	//heap_t *_collisionsQueue;
	//vector _collisionsList;
	int _initialAllCollisions;
	int _realCollisions;
	int _totalCollisions;
	SphereCollision *_collisionsList;
	SphereCollision *_collisionsQueue;
	int _collisionsQueueLen, _collisionsListLen, _collisionsQueueTotal, _collisionsListTotal;

	Sphere *_particlesList;
	VerticalBoundary *_verticalBoundariesList;
	HorizontalBoundary *_horizontalBoundariesList;

	Emitter *_emitterList;
	int _emitterListLen, _emitterListTotal;
	Receiver *_receiverList;
	int _receiverListLen, _receiverListTotal;
	Node *_nodeList;
	int _nodeListLen, _nodeListTotal;

	int _dimension;
	int _sizeParticlesList;
	int _sizeVB;
	int _sizeHB;

}Simulation;

void init_simulation(Simulation *,double,double,double,bool,bool,double,double,double,double,double,double,bool,double,double,bool,bool,double, int);
void startSimulation(Simulation *);
void setInitialParticles(Simulation *);
void initialParticlesMove(Simulation *);
void brownianMotionAndInertiaStep(Simulation *);
void makeBMAndInertiaStep(double k, double BMFactor, double inertiaFactor, Sphere *s);
void checkCollisions(Simulation *);
void exit_simulation(Simulation *);
void createCollisionQueue(Simulation *);
void findParticleCollisions(Simulation *, int i, double time, SphereCollision *s, int, int);
void updatePositions(Simulation *);
int numParticlesToDelete(Simulation *);
void emit(Simulation *);
void updateReceivers(Simulation *);
char* simulatorToString(Simulation *);
void writeOutputFile(int type, char* line);
#endif