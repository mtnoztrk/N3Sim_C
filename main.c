/*
N3Sim: A Simulation Framework for Diffusion-based Molecular Communication
Copyright (C) 2011 I‚àö¬±aki Pascual - N3CAT (UPC)
N3Cat (NaNoNetworking Center in Catalunya)
Universitat Polit‚àö¬Æcnica de Catalunya (UPC)
Jordi Girona, 1-3, Modul D6 (Campus Nord)
08034 Barcelona, Catalunya, Spain
acabello@ac.upc.edu

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
Original software has taken from www.n3cat.upc.edu/n3sim.

Migration from Java to C
Metin ÖZTÜRK
mtnoztrk@live.com
*/

#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include <stdbool.h>
#include <math.h>
#include "time.h"

#include "vector.h"
#include "QuickSort.h"
#include "GaussRand.h"
#include "PriorityQueue.h"

#include "VerticalBoundary.h"
#include "HorizontalBoundary.h"

#include "Sphere.h"
#include "Simulation.h"

#include "Emitter.h"
#include "Receiver.h"
#include "Node.h"


void readFromFile(char**, char**, char**);
void processLine(char*,char**, char**, char**, int);
int comparestrings(char*, char*);
char* getNextString(char*, char**, char**, int);
bool getNextBoolean(char*, char**, char**, int);
int getNextInt(char*, char**, char**, int);
double getNextDouble(char*, char**, char**, int);
void error(char*);
char* err_msg;
void writeOutputFile(int type, char* line);
void checkEmitterArraySize(Emitter*, int, int);
void checkReceiverArraySize(Receiver*e, int len, int total);
void checkNodeArraySize(Node*e, int len, int total);
void checkParticleArraySize(Sphere*e, int len, int total);
/*
void spaceSetInitialParticles(double, double, double, double, double, Sphere *);
void spaceInitialParticlesMove(double, double, double, double, bool, bool, Sphere *, int);
void spaceBrownianMotionAndInertiaStep(double , double , double , double , Sphere *, int);
void particleMakeBMAndInertiaStep(double k, double BMFactor, double inertiaFactor, Sphere *s);
double gaussRand();
void spaceCheckCollisions(bool _activeCollision, bool _boundedSpace, Sphere *, int);
*/

int main(int argc, char *argv[]) {
	//struct DomainInterface _d;

	clock_t t = clock();
	char **_names = malloc(sizeof(char*)*100);

	char **_values = malloc(sizeof(char*)*100);

	if (argc != 0)
		readFromFile(_names, _values, argv);
	
	int index = 0;

	char* outPath = malloc(sizeof(char));
	outPath = getNextString("outPath", _names, _values, index);

	bool graphics = getNextBoolean("graphics",_names, _values, ++index);
	bool infoFile = getNextBoolean("infoFile", _names, _values, ++index);
	bool activeCollision = getNextBoolean("activeCollision", _names, _values, ++index);
	double BMFactor = getNextDouble("BMFactor", _names, _values, ++index);
	double inertiaFactor = getNextDouble("inertiaFactor",_names, _values, ++index);
	double time = getNextDouble("time",_names, _values, ++index);
	double timeStep = getNextDouble("timeStep",_names, _values, ++index);

	// space params
	bool boundedSpace = getNextBoolean("boundedSpace", _names, _values, ++index);
	bool constantBGConcentration = getNextBoolean("constantBGConcentration", _names, _values, ++index);
	double constantBGConcentrationWidth = getNextDouble("constantBGConcentrationWidth", _names, _values, ++index);
	int dimension = getNextInt("dimension", _names, _values, ++index);

	int xSize = 0, ySize = 0, zSize = 0;

	printf("dimension: %d \n", dimension);

	if (dimension >= 1) 
		xSize = getNextInt("xSize", _names, _values, ++index);
	if (dimension >= 2) 
		ySize = getNextInt("ySize", _names, _values, ++index);
	if (dimension == 3) 
		zSize = getNextInt("zSize", _names, _values, ++index);
	if ((dimension < 1) || (dimension > 3)) 
		perror("dimensions mismatch...\n");

	double D = getNextDouble("D", _names, _values, ++index);
	double bgConcentration = getNextDouble("bgConcentration", _names, _values, ++index);
	double sphereRadius = getNextDouble("sphereRadius", _names, _values, ++index);

	//##################################################### SIMULATOR START ###################################################################################
	Simulation S;
	init_simulation(&S,0, time, timeStep, false,infoFile, D, bgConcentration, sphereRadius, xSize, ySize, zSize, activeCollision,BMFactor,inertiaFactor,
		boundedSpace,constantBGConcentration, constantBGConcentrationWidth,dimension);
	/*
	double _sim_time = 0;
	double _sim_endTime = time;
	double _sim_timeStep = timeStep;
	bool _sim_graphics = false; //TODO: grafik þimdilik çalýþmýyor
	bool _sim_infoFile = infoFile;

	//Space parameters
	double _space_D = D;                  // diffusion coefficient (nm^2/ns)
	double _space_bgConcentration = bgConcentration;    // initial concentration rate. Number spheres per 10000 nm2
	double _space_radius = sphereRadius;             // radius of the spheres of the initial concentration
	double _space_xSize = -1;
	double _space_ySize = -1;
	double _space_zSize = -1;
	if (dimension >= 1)
	_space_xSize = xSize;
	if (dimension >= 2)
	_space_ySize = ySize;
	if (dimension == 3)
	_space_zSize = zSize;
	bool _space_activeCollision = activeCollision;
	double _space_BMFactor = BMFactor;
	double _space_inertiaFactor = inertiaFactor;
	bool _space_boundedSpace = boundedSpace;
	bool _space_constantBGConcentration = constantBGConcentration;
	double _constantBGConcentrationWidth = constantBGConcentrationWidth;
	bool _space_infoFile = infoFile;

	//vector v;
	//vector_init(&v);

	VerticalBoundary left;
	VerticalBoundary right;

	if (_space_boundedSpace){
	init_verticalBoundary(&left, 0, 0, 0);			        // xMin == yMin == yMax == 0
	init_verticalBoundary(&right, _space_xSize, 0, 0);	    // yMin == yMax == 0
	//TODO: _verticalBoundariesList.add(left);
	//TODO: _verticalBoundariesList.add(right);
	}


	long _sim_simulationSystemTime;
	*/

	//###################################################### SIMULATOR END ####################################################################################




	// createEmitters
	int numEmitters = getNextInt("emitters", _names, _values, ++index);
	double emitterRadius;
	double x = -1, y = -1, z = -1;
	double startTime;
	double endTime;
	double initV;
	bool punctual;
	bool concentrationEmitter;
	char* color;
	int emitterType;
	double amplitude;
	int period;
	int timeOn;
	char* file;
	double scaleFactor;

	//bu dalga lazým olcak node to emitter and node to receiverda
	//int* arr[5][5];
	//arr[0][0] = &pulseEmitterArray[0];

	//declaring emitter arrays and allocating memory.
	//PulseSphereEmitter *pulseEmitterArray = (PulseSphereEmitter*)malloc(sizeof(PulseSphereEmitter)*numEmitters);
	
	//RectangularSphereEmitter *rectEmitterArray = (RectangularSphereEmitter*)malloc(sizeof(RectangularSphereEmitter)*numEmitters);
	//NoiseSphereEmitter *noiseEmitterArray = (NoiseSphereEmitter*)malloc(sizeof(NoiseSphereEmitter)*numEmitters);
	//Emitter *emitterArray = (Emitter*)malloc(sizeof(Emitter)*numEmitters);
	//WaveFromFileSphereEmitter *waveEmitterArray = (WaveFromFileSphereEmitter*)malloc(sizeof(WaveFromFileSphereEmitter)*numberOfEmitters);
	//PunctualWaveFromFile3DSphereEmitter *punctualEmitterArray = (PunctualWaveFromFile3DSphereEmitter*)malloc(sizeof(PunctualWaveFromFile3DSphereEmitter)*numberOfEmitters);

	for (int i = 0; i < numEmitters; i++){
		emitterRadius = getNextDouble("emitterRadius", _names, _values, ++index);
		if (dimension >= 1)  
			x = getNextDouble("x", _names, _values, ++index);
		if (dimension >= 2)  
			y = getNextDouble("y", _names, _values, ++index);
		if (dimension == 3)  
			z = getNextDouble("z", _names, _values, ++index);
		startTime = getNextDouble("startTime", _names, _values, ++index);
		endTime = getNextDouble("endTime", _names, _values, ++index);
		initV = getNextDouble("initV", _names, _values, ++index);
		punctual = getNextBoolean("punctual", _names, _values, ++index);
		concentrationEmitter = getNextBoolean("concentrationEmitter", _names, _values, ++index);
		color = getNextString("color", _names, _values, ++index);

		emitterType = getNextInt("emitterType", _names, _values, ++index);
		switch (emitterType){
		case(1) :
			amplitude = getNextDouble("amplitude", _names, _values, ++index);
			amplitude = amplitude * timeStep / 100; //change to amplitude per timeStep
			if (dimension == 1){
				checkEmitterArraySize(S._emitterList, S._emitterListLen, S._emitterListTotal);
				init_PulseSphereEmitter1D(&S._emitterList[i], x, startTime, endTime, amplitude, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color);
				S._emitterListLen++;
			}
			if (dimension == 2){
				checkEmitterArraySize(S._emitterList, S._emitterListLen, S._emitterListTotal);
				init_PulseSphereEmitter2D(&S._emitterList[i], x, y, startTime, endTime, amplitude, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color);
				S._emitterListLen++;
			}
			if (dimension == 3){
				checkEmitterArraySize(S._emitterList, S._emitterListLen, S._emitterListTotal);
				init_PulseSphereEmitter3D(&S._emitterList[i], x, y, z, startTime, endTime, amplitude, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color);
				S._emitterListLen++;
			}
			break;
		case(2) :
			amplitude = getNextDouble("amplitude", _names, _values, ++index);
			amplitude = amplitude * timeStep / 100; //change to amplitude per timeStep
			period = getNextInt("period", _names, _values, ++index);
			timeOn = getNextInt("timeOn", _names, _values, ++index);
			if (dimension == 1){
				checkEmitterArraySize(S._emitterList, S._emitterListLen, S._emitterListTotal);
				init_RectangularSphereEmitter1D(&S._emitterList[i], x, startTime, endTime, amplitude, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, period, timeOn, color);
				S._emitterListLen++;
			}
			if (dimension == 2){
				checkEmitterArraySize(S._emitterList, S._emitterListLen, S._emitterListTotal);
				init_RectangularSphereEmitter2D(&S._emitterList[i], x, y, startTime, endTime, amplitude, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, period, timeOn, color);
				S._emitterListLen++;
			}
			if (dimension == 3){
				checkEmitterArraySize(S._emitterList, S._emitterListLen, S._emitterListTotal);
				init_RectangularSphereEmitter3D(&S._emitterList[i], x, y, z, startTime, endTime, amplitude, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, period, timeOn, color);
				S._emitterListLen++;
			}
			
			break;
		case(3) :
			amplitude = getNextDouble("amplitude", _names, _values, ++index);
			amplitude = amplitude * timeStep / 100; //change to amplitude per timeStep0
			//_d.createNoiseSphereEmitter(x, y, startTime, endTime, amplitude, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color);
			if (dimension == 1){
				checkEmitterArraySize(S._emitterList, S._emitterListLen, S._emitterListTotal);
				init_NoiseSphereEmitter1D(&S._emitterList[i], x, startTime, endTime, amplitude, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color);
				S._emitterListLen++;
			}	
			if (dimension == 2){
				checkEmitterArraySize(S._emitterList, S._emitterListLen, S._emitterListTotal);
				init_NoiseSphereEmitter2D(&S._emitterList[i], x, y, startTime, endTime, amplitude, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color);
				S._emitterListLen++;
			}
			if (dimension == 3){
				checkEmitterArraySize(S._emitterList, S._emitterListLen, S._emitterListTotal);
				init_NoiseSphereEmitter3D(&S._emitterList[i], x, y, z, startTime, endTime, amplitude, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color);
				S._emitterListLen++;
			}
			break;
		case(4) :
			file = getNextString("file", _names, _values, ++index);
			scaleFactor = getNextDouble("scaleFactor", _names, _values, ++index);
			int size = (int)((double)(endTime - startTime) / timeStep);
			//_d.createWaveFromFileSphereEmitter(x, y, startTime, endTime, scaleFactor, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, file, size, color);
			break;
		case(5) :
			// double z    = getNextDouble("z");
			z = getNextDouble("z", _names, _values, ++index);
			file = getNextString("file", _names, _values, ++index);
			scaleFactor = getNextDouble("scaleFactor", _names, _values, ++index);
			int size4 = (int)((double)(endTime - startTime) / timeStep);
			//_d.createPunctualWaveFromFile3DSphereEmitter(x, y, z, startTime, endTime, scaleFactor, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, file, size4, color);
			break;
		default: error("Wrong type of emitter. Emitter not created. Try again"); i--;
		}
	}
	// createReceivers		
	int numReceivers = getNextInt("receivers", _names, _values, ++index);
	char* name;
	int receiverType;
	bool absorb;
	bool accumulate;
	double side;
	double rradius;


	//declaring receiver arrays

	//Receiver *receiverArray = (Receiver*)malloc(sizeof(Receiver)*numReceivers);
	//SquareReceiver *squareReceiverArray = (SquareReceiver*)malloc(sizeof(SquareReceiver)*numReceivers);
	//SphericalReceiver *sphericalReceiverArray = (SphericalReceiver*)malloc(sizeof(SphericalReceiver)*numReceivers);
	//SphericalReceiver3D *sphericalReceiver3DArray = (SphericalReceiver3D*)malloc(sizeof(SphericalReceiver3D)*numReceivers);

	for (int i = 0; i < numReceivers; i++){
		name = getNextString("name", _names, _values, ++index);
		if (dimension >= 1) 
			x = getNextDouble("x", _names, _values, ++index);
		if (dimension >= 2) 
			y = getNextDouble("y", _names, _values, ++index);
		if (dimension == 3) 
			z = getNextDouble("z", _names, _values, ++index);
		absorb = getNextBoolean("absorb", _names, _values, ++index);
		accumulate = getNextBoolean("accumulate", _names, _values, ++index);
		receiverType = getNextInt("receiverType", _names, _values, ++index);

		switch (receiverType){
		case(1) :
			side = getNextDouble("side", _names, _values, ++index);
			if (dimension == 1){
				checkReceiverArraySize(S._receiverList, S._receiverListLen, S._receiverListTotal);
				init_SquareReceiver1D(&S._receiverList[i], name, x, absorb, accumulate, side);
				S._receiverListLen++;
			}	
			else if (dimension == 2){
				checkReceiverArraySize(S._receiverList, S._receiverListLen, S._receiverListTotal);
				init_SquareReceiver2D(&S._receiverList[i], name, x, y, absorb, accumulate, side);
				S._receiverListLen++;
			}				
			else if (dimension == 3){
				checkReceiverArraySize(S._receiverList, S._receiverListLen, S._receiverListTotal);
				init_SquareReceiver3D(&S._receiverList[i], name, x, y, z, absorb, accumulate, side);
				S._receiverListLen++;
			}
			break;
		case(2) :
			rradius = getNextDouble("rradius", _names, _values, ++index);
			if (dimension == 1){
				checkReceiverArraySize(S._receiverList, S._receiverListLen, S._receiverListTotal);
				init_SphericalReceiver1D(&S._receiverList[i], name, x, absorb, accumulate, rradius);
				S._receiverListLen++;
			}
			else if (dimension == 2){
				checkReceiverArraySize(S._receiverList, S._receiverListLen, S._receiverListTotal);
				init_SphericalReceiver2D(&S._receiverList[i], name, x, y, absorb, accumulate, rradius);
				S._receiverListLen++;
			}
			break;
		case(3) :
			z = getNextDouble("z", _names, _values, ++index);
			rradius = getNextDouble("rradius", _names, _values, ++index);
			checkReceiverArraySize(S._receiverList, S._receiverListLen, S._receiverListTotal);
			init_SphericalReceiver3D(&S._receiverList[i], name, x, y, z, absorb, accumulate, rradius);
			S._receiverListLen++;
			
			break;
		default: error("Wrong type of receiver. Receiver not created. Try again"); i--;
		} // switch

	} // for i < numReceivers

	//######################################################################################
	//CONFIG DOSYASI BURDA BITIYOR
	//######################################################################################
	// createNodes
	int nodeType;
	int numNodes = getNextInt("nodes", _names, _values, ++index);
	int numberOfEmitters = -1, numberOfReceivers = -1;
	int initialSupply = -1, reservoirCapacity = -1;
	int harvesterIndex = -1;

	//SimpleNode *simpleNodeArray = (SimpleNode*)malloc(sizeof(SimpleNode)*numNodes);
	//ImmediatelyReleasingNode *immediatelyReleasingNodeArray = (ImmediatelyReleasingNode*)malloc(sizeof(ImmediatelyReleasingNode)*numNodes);4

	//Node *nodeArray = (Node*)malloc(sizeof(Node)*numNodes);

	for (int i = 0; i < numNodes; i++) {

		// node specific
		nodeType = getNextInt("nodeType", _names, _values, ++index);
		name = getNextString("name", _names, _values, ++index);

		if (dimension >= 1) 
			x = getNextDouble("x", _names, _values, ++index);
		if (dimension >= 2) 
			y = getNextDouble("y", _names, _values, ++index);
		if (dimension == 3) 
			z = getNextDouble("z", _names, _values, ++index);

		// simple node is not using the information below
		if (nodeType != 1) {
			initialSupply = getNextInt("initialSupply", _names, _values, ++index);
			reservoirCapacity = getNextInt("reservoirCapacity", _names, _values, ++index);
			numberOfEmitters = getNextInt("numberOfEmitters", _names, _values, ++index);
			numberOfReceivers = getNextInt("numberOfReceivers", _names, _values, ++index);
			harvesterIndex = getNextInt("harvesterIndex", _names, _values, ++index);
		}

		

		switch (nodeType) {

		case(1) : // simpleNode
			if (dimension == 1){
				checkNodeArraySize(S._nodeList, S._nodeListLen, S._nodeListTotal);
				init_SimpleNode1D(&S._nodeList[i], name, x, numberOfEmitters, numberOfEmitters);
				S._nodeListLen++;
			}
			else if (dimension == 2){
				checkNodeArraySize(S._nodeList, S._nodeListLen, S._nodeListTotal);
				init_SimpleNode2D(&S._nodeList[i], name, x, y, numberOfEmitters, numberOfEmitters);
				S._nodeListLen++;
			}
			else if (dimension == 3){
				checkNodeArraySize(S._nodeList, S._nodeListLen, S._nodeListTotal);
				init_SimpleNode3D(&S._nodeList[i], name, x, y, z, numberOfEmitters, numberOfEmitters);
				S._nodeListLen++;
			}
			break;

		case(2) : // immediatelyReleasingNode

			emitterRadius = getNextDouble("emitterRadius", _names, _values, ++index);
			initV = getNextDouble("initV", _names, _values, ++index);
			punctual = getNextBoolean("punctual", _names, _values, ++index);
			concentrationEmitter = getNextBoolean("concentrationEmitter", _names, _values, ++index);
			color = getNextString("color", _names, _values, ++index);

			if (dimension == 1){
				checkNodeArraySize(S._nodeList, S._nodeListLen, S._nodeListTotal);
				init_ImmediatelyReleasingNode1D(&S._nodeList[i], name, x, initialSupply, reservoirCapacity, numberOfEmitters,
					numberOfReceivers, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color, harvesterIndex);
				S._nodeListLen++;
			}
				
			else if (dimension == 2){
				checkNodeArraySize(S._nodeList, S._nodeListLen, S._nodeListTotal);
				init_ImmediatelyReleasingNode2D(&S._nodeList[i], name, x, y, initialSupply, reservoirCapacity, numberOfEmitters,
					numberOfReceivers, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color, harvesterIndex);
				S._nodeListLen++;
			}
			else if (dimension == 3){
				checkNodeArraySize(S._nodeList, S._nodeListLen, S._nodeListTotal);
				init_ImmediatelyReleasingNode3D(&S._nodeList[i], name, x, y, z, initialSupply, reservoirCapacity, numberOfEmitters,
					numberOfReceivers, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color, harvesterIndex);
				S._nodeListLen++;
			}
			break;

		case(3) : // immediatelyPulseReleasingNode

			emitterRadius = getNextDouble("emitterRadius", _names, _values, ++index);
			initV = getNextDouble("initV", _names, _values, ++index);
			punctual = getNextBoolean("punctual", _names, _values, ++index);
			concentrationEmitter = getNextBoolean("concentrationEmitter", _names, _values, ++index);
			color = getNextString("color", _names, _values, ++index);
			amplitude = getNextDouble("amplitude", _names, _values, ++index);

			if (dimension == 1); //_d.createImmediatelyPulseReleasingNode(name, x, initialSupply, reservoirCapacity, numberOfEmitters,
				//numberOfReceivers, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color, amplitude, harvesterIndex);
			else if (dimension == 2); //_d.createImmediatelyPulseReleasingNode(name, x, y, initialSupply, reservoirCapacity, numberOfEmitters,
				//numberOfReceivers, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color, amplitude, harvesterIndex);
			else if (dimension == 3); //_d.createImmediatelyPulseReleasingNode(name, x, y, z, initialSupply, reservoirCapacity, numberOfEmitters,
				//numberOfReceivers, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color, amplitude, harvesterIndex);
			break;

		default: error("Wrong type of node. Node not created. Try again");

		} // switch nodeType

		// emitter specific
		for (int j = 0; j < numberOfEmitters; j++) {

			emitterRadius = getNextDouble("emitterRadius", _names, _values, ++index);
			startTime = getNextDouble("startTime", _names, _values, ++index);
			endTime = getNextDouble("endTime", _names, _values, ++index);
			initV = getNextDouble("initV", _names, _values, ++index);
			punctual = getNextBoolean("punctual", _names, _values, ++index);
			concentrationEmitter = getNextBoolean("concentrationEmitter", _names, _values, ++index);
			color = getNextString("color", _names, _values, ++index);
			emitterType = getNextInt("emitterType", _names, _values, ++index);

			switch (emitterType){

			case(1) :

				amplitude = getNextDouble("amplitude", _names, _values, ++index);
				amplitude = amplitude * timeStep / 100; //change to amplitude per timeStep

				if (dimension == 1); //_d.addPulseSphereEmitterToNode(name, x, startTime, endTime, amplitude, sphereRadius,
					//emitterRadius, initV, punctual, concentrationEmitter, color);
				else if (dimension == 2); //_d.addPulseSphereEmitterToNode(name, x, y, startTime, endTime, amplitude, sphereRadius,
					//emitterRadius, initV, punctual, concentrationEmitter, color);
				else if (dimension == 3); //_d.addPulseSphereEmitterToNode(name, x, y, z, startTime, endTime, amplitude, sphereRadius,
					//emitterRadius, initV, punctual, concentrationEmitter, color);
				break;

			case(2) :

				amplitude = getNextDouble("amplitude", _names, _values, ++index);
				amplitude = amplitude * timeStep / 100; //change to amplitude per timeStep
				period = getNextInt("period", _names, _values, ++index);
				timeOn = getNextInt("timeOn", _names, _values, ++index);

				if (dimension == 1);//_d.addRectangularSphereEmitterToNode(name, x, startTime, endTime, amplitude, sphereRadius,
					//emitterRadius, initV, punctual, concentrationEmitter, period, timeOn, color);
				else if (dimension == 2); //_d.addRectangularSphereEmitterToNode(name, x, y, startTime, endTime, amplitude, sphereRadius,
					//emitterRadius, initV, punctual, concentrationEmitter, period, timeOn, color);
				else if (dimension == 3); //_d.addRectangularSphereEmitterToNode(name, x, y, startTime, endTime, amplitude, sphereRadius,
					//emitterRadius, initV, punctual, concentrationEmitter, period, timeOn, color);
				break;

			case(3) :

				amplitude = getNextDouble("amplitude", _names, _values, ++index);
				amplitude = amplitude * timeStep / 100; //change to amplitude per timeStep

				if (dimension == 1); //_d.addNoiseSphereEmitterToNode(name, x, startTime, endTime, amplitude, sphereRadius,
					//emitterRadius, initV, punctual, concentrationEmitter, color);
				else if (dimension == 2); //_d.addNoiseSphereEmitterToNode(name, x, y, startTime, endTime, amplitude, sphereRadius,
				//emitterRadius, initV, punctual, concentrationEmitter, color);
				else if (dimension == 3); //_d.addNoiseSphereEmitterToNode(name, x, y, z, startTime, endTime, amplitude, sphereRadius,
					//emitterRadius, initV, punctual, concentrationEmitter, color);
				break;

			case(4) :

				file = getNextString("file", _names, _values, ++index);
				scaleFactor = getNextDouble("scaleFactor", _names, _values, ++index);
				int size = (int)((double)(endTime - startTime) / timeStep);

				if (dimension == 1); //_d.addWaveFromFileSphereEmitterToNode(name, x, startTime, endTime, scaleFactor, sphereRadius,
					//emitterRadius, initV, punctual, concentrationEmitter, file, size, color);
				else if (dimension == 2); //_d.addWaveFromFileSphereEmitterToNode(name, x, y, startTime, endTime, scaleFactor, sphereRadius,
					//emitterRadius, initV, punctual, concentrationEmitter, file, size, color);
				else if (dimension == 3); //_d.addWaveFromFileSphereEmitterToNode(name, x, y, z, startTime, endTime, scaleFactor, sphereRadius,
					//emitterRadius, initV, punctual, concentrationEmitter, file, size, color);
				break;

			case(5) :
				// double z    = getNextDouble("z");
				z = getNextDouble("z", _names, _values, ++index);
				file = getNextString("file", _names, _values, ++index);
				scaleFactor = getNextDouble("scaleFactor", _names, _values, ++index);
				int size4 = (int)((double)(endTime - startTime) / timeStep);
				//_d.addPunctualWaveFromFile3DSphereEmitterToNode(name, x, y, z, startTime, endTime, scaleFactor, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, file, size4, color);
				break;

				/* case(6):
				_d.addImmediatelyReleasingEmitterToNode(name, x, y, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color);
				break;  */

			default: error("Wrong type of emitter. Emitter not created. Try again"); j--;

			} // end of switch emitterType	

		} // end of for j  < numberOfEmitters    

		// receiver specific
		for (int j = 0; j < numberOfReceivers; j++) {

			absorb = getNextBoolean("absorb", _names, _values, ++index);
			accumulate = getNextBoolean("accumulate", _names, _values, ++index);
			receiverType = getNextInt("receiverType", _names, _values, ++index);

			switch (receiverType){

			case(1) : // square receiver
				side = getNextDouble("side", _names, _values, ++index);
				//_d.addSquareReceiverToNode(name, x, y, absorb, accumulate, side);
				break;

			case(2) : // spherical receiver
				rradius = getNextDouble("rradius", _names, _values, ++index);
				//_d.addSphericalReceiverToNode(name, x, y, absorb, accumulate, rradius);
				break;

			case(3) : // 3D spherical receiver
				// double z        = getNextDouble("z");
				z = getNextDouble("z", _names, _values, ++index);
				rradius = getNextDouble("rradius", _names, _values, ++index);
				//_d.add3DSphericalReceiverToNode(name, x, y, z, absorb, accumulate, rradius);
				break;

			case(4) : ; // harvesting spherical receiver
				int maxHarvestPerIteration = 0;
				rradius = getNextDouble("rradius", _names, _values, ++index);
				maxHarvestPerIteration = getNextInt("maxHarvestPerIteration", _names, _values, ++index);
				//_d.addHarvestingSphericalReceiverToNode(name, x, y, accumulate, rradius, maxHarvestPerIteration);
				break;

			case(5) : // unlimited harvesting spherical receiver
				rradius = getNextDouble("rradius", _names, _values, ++index);
				//_d.addUnlimitedHarvestingSphericalReceiverToNode(name, x, y, accumulate, rradius);
				break;

			case(6) : ; // ratio limited harvesting spherical receiver
				double harvestRatio = getNextDouble("harvestRatio", _names, _values, ++index);
				rradius = getNextDouble("rradius", _names, _values, ++index);
				//_d.addRatioLimitedHarvestingSphericalReceiverToNode(name, x, y, accumulate, rradius, harvestRatio);
				break;

			default: error("Wrong type of receiver. Receiver not created. Try again");

			} //  end of switch receiverType   
		} // end of for j < numberOfReceivers

	} // end of for i < numNodes


	//start simulation
	printf("Simulation starts...\n");
	startSimulation(&S);
	//_d.startSimulation();

	//int sizeParticlesList = (int)((_space_bgConcentration*(double)(_space_xSize)*(double)(_space_ySize)) / 10000);
	//Sphere *particlesList = (Sphere*)malloc(sizeof(Sphere)*sizeParticlesList);
	//PriorityQueue<SphereCollision> _collisionsQueue;
	//ArrayList<ArrayList<SphereCollision>> _collisionsList;
	//Sphere s;
	//init_sphere2D(&s,12,14,123,12,12,"yesil");
	//heap_t *_collisionQueue = (heap_t *)calloc(1, sizeof (heap_t));;
	//pQueuePush(_collisionQueue,1,&s);
	//Sphere *a = (Sphere*)pQueuePop(_collisionQueue);
	//int _initialAllCollisions;
	//int _realCollisions;
	//int _totalCollisions;
	//spaceSetInitialParticles(_space_xSize, _space_ySize, _space_zSize, _space_bgConcentration, _space_radius, particlesList);
	//for (int i = 0; i < 2; i++)
		//spaceInitialParticlesMove(_sim_timeStep, _space_D, _space_BMFactor, _space_inertiaFactor, _space_activeCollision, _space_boundedSpace, particlesList, sizeParticlesList);

	printf("Simulation finished!\n");
	
	








	t = clock() - t;
	long elapsedTime = t;
	printf("Total runtime: %d \n", elapsedTime);
	
	//deallocationg memory
	free(outPath);
	free(_names);
	free(_values);
	//free(pulseEmitterArray);
	//free(noiseEmitterArray);
	//free(rectEmitterArray);
	//free(simpleNodeArray);
	//free(immediatelyReleasingNodeArray);
	//free(sphericalReceiver3DArray);
	//free(sphericalReceiverArray);
	//free(squareReceiverArray);
	//free(receiverArray);
	//free emitter and receiver list in nodes
	//free(nodeArray);
	exit_simulation(&S);
	//free(particlesList);
	return 0;
}//end of main

void readFromFile(char **names, char **values, char *argv[]){
	FILE *fp;
	int index = 0;
	fp = fopen(argv[1], "r");
	if (fp == NULL){
		perror("File could not be opened.");
		//return 1;
	}
	// read all lines 		
	char line[100];
	while (fgets(line, 100, fp) != 0){
		// do not read if blank line or begins with #
		while (line[0] == '#' || line[0] == '\n'){
			fgets(line, 100, fp);
		}
		processLine(line, names, values, argv, index);
		index++;
	}
	fclose(fp);
}

void processLine(char* line, char** names, char** values, char *argv[], int a){
	int _numParam = 1;
	int i = 0, j = 0;
	int len;
	len = strlen(line);
	for (i = 0; i < 50; i++){
		if (line[i] == '='){
			j = i;//find the location of equals sign
			break;
		}	
	}

	char *name = malloc(sizeof(char)*(j + 1));
	char *value = malloc(sizeof(char)*(len - j));



	for (i = 0; i < j; i++)
		name[i] = line[i];
	name[i] = '\0';

	for (i = j + 1; i < len; i++)
		value[i-j-1] = line[i];
	value[i - j - 2] = '\0';


	/* parameter value iþini çöz
	//if value is 'param', read the next value from args[]
	if (value == "param" || value == "Param"){
		value = argv[_numParam];
		_numParam++;
	}
	*/
	names[a] = name;
	values[a] = value;
	//free(name);
	//free(value);
};

char* getNextString(char* name, char** names, char** values, int index){
	char* foundName = names[index];
	char* value = values[index];
	if (comparestrings(foundName, name))
		return value;
	else {
		err_msg = malloc(sizeof(char)* 100);
		strcpy(err_msg, "ERROR : UI: expected parameter ");
		strcat(err_msg, name);
		strcat(err_msg, " , found ");
		strcat(err_msg, foundName);
		strcat(err_msg, ". Program terminates.");
		error(err_msg);
		return "1";
	}
	return NULL;
};

bool getNextBoolean(char* name, char** names, char** values, int index){
	char* foundName = names[index];
	char* strValue = values[index];
	bool value = false;

	if (comparestrings(foundName, name)){
		if (comparestrings(strValue, "y") || comparestrings(strValue, "yes") || comparestrings(strValue, "true")){
			value = true;
		}
		else if (comparestrings(strValue, "n") || comparestrings(strValue, "no") || comparestrings(strValue, "false")){
			value = false;
		}
		return value;
	}
	else {
		err_msg = malloc(sizeof(char)* 100);
		strcpy(err_msg, "ERROR : UI: expected parameter ");
		strcat(err_msg, name);
		strcat(err_msg, " , found ");
		strcat(err_msg, foundName);
		strcat(err_msg, ". Program terminates.");
		error(err_msg);
		return 1;
	}
	return value;
};

int getNextInt(char* name, char** names, char** values, int index){
	char* foundName = names[index];
	char* strValue = values[index];
	char* ptr;
	int value = 0;

	if (comparestrings(foundName, name)){
			value = strtol(strValue, &ptr, 10);
	}
	else {
		err_msg = malloc(sizeof(char)* 100);
		strcpy(err_msg, "ERROR : UI: expected parameter ");
		strcat(err_msg, name);
		strcat(err_msg, " , found ");
		strcat(err_msg, foundName);
		strcat(err_msg, ". Program terminates.");
		error(err_msg);
		return 1;
	}
	return value;
};

double getNextDouble(char* name, char** names, char** values, int index){
	char* foundName = names[index];
	char* strValue = values[index];
	int len = strlen(strValue);
	int i;
	for (i = 0; i < len; i++){
		if (strValue[i] == ','){
			strValue[i] = '.';
			break;
		}	
	}
	
	double value = 0;

	if (comparestrings(foundName, name)){
		value = atof(strValue);
	}
	else {
		err_msg = malloc(sizeof(char)*100);
		strcpy(err_msg, "ERROR : UI: expected parameter ");
		strcat(err_msg, name);
		strcat(err_msg, " , found ");
		strcat(err_msg, foundName);
		strcat(err_msg, ". Program terminates.");
		error(err_msg);
		return 1;
	}
	return value;
};

int comparestrings(char* a, char* b){
	int len;
	int ret_val = 1;
	int i;
	if (strlen(a) < strlen(b))
		return 0;
	else if (strlen(a) > strlen(b))
		return 0;
	else
		len = strlen(a);

	for (i = 0; i < len; i++){
		if (a[i] != b[i])
			ret_val = 0;
	}
	return ret_val;
};

void error(char* errorMsg) {
	//DataInterface::writeLineToFile(DataInterface::getErrorsFile(), errorMsg);
	printf("%s \n", errorMsg);
};

void checkEmitterArraySize(Emitter*e, int len, int total){
	if (len + 1 >= total){
		total *= 2; // double its size if its full
		e = (Emitter*)realloc(e, sizeof(Emitter)*total);
	}
}

void checkReceiverArraySize(Receiver*e, int len, int total){
	if (len + 1 >= total){
		total *= 2; // double its size if its full
		e = (Receiver*)realloc(e, sizeof(Receiver)*total);
	}
}

void checkNodeArraySize(Node*e, int len, int total){
	if (len + 1 >= total){
		total *= 2; // double its size if its full
		e = (Node*)realloc(e, sizeof(Node)*total);
	}
}

void checkParticleArraySize(Sphere*e, int len, int total){
	if (len + 1 >= total){
		total *= 2; // double its size if its full
		e = (Sphere*)realloc(e, sizeof(Sphere)*total);
	}
}


/*
void spaceSetInitialParticles(double _xSize, double _ySize, double _zSize, double _bgConcentration, double _radius, Sphere *_particlesList){
if (_bgConcentration > 0){

int numParticles = -1, xdiv = -1, ydiv = -1, i = -1;
double squareSide = -1, deltax = -1, x = -1, y = -1;
bool end = false;

// 1D
if (_ySize == -1) {

numParticles = (int)((_bgConcentration*(double)(_xSize)) / 100);
squareSide = _xSize / numParticles;
if (squareSide <= _radius)
printf("WARNING : initial concentration too high!");

// xdiv = (int)((double)(_xSize) / squareSide); // in 1D xdiv == numParticles
xdiv = numParticles;
deltax = (double)(_xSize) / (double)(xdiv);

i = 0;
x = deltax / 2;
end = false;
//TODO: Düzelt
while (x < _xSize && !end){
//Sphere s;
//init_sphere2D(&s, x, y, _radius, 0, 0, getInitialParticlesColor(&s));
//vector_add(_particlesList, &s);
x += deltax;
i++;
if (i >= numParticles) end = true;
}
} // end of 1D

//2D
if (_ySize != -1 && _zSize == -1) {

numParticles = (int)((_bgConcentration*(double)(_xSize)*(double)(_ySize)) / 10000);

double Area = _xSize * _ySize;
squareSide = sqrt(Area / numParticles);

if (squareSide <= _radius)
printf("WARNING : initial concentration too high!");

xdiv = (int)((double)(_xSize) / squareSide);
ydiv = (int)((double)(_ySize) / squareSide);

//TODO: buna efficient biþey koy bu ne
while (xdiv*ydiv<numParticles){
xdiv++;
if (xdiv*ydiv<numParticles)
ydiv++;
}

deltax = (double)(_xSize) / (double)(xdiv);
double deltay = (double)(_ySize) / (double)(ydiv);
// System.out.println("deltax : "+ deltax);
// System.out.println("deltay : "+ deltay);

i = 0;
x = deltax / 2;
y = deltay / 2;

end = false;
//Sphere *s = (Sphere *)malloc(sizeof(Sphere)*numParticles);
while (x < _xSize && !end){
y = deltay / 2;
while (y < _ySize  && !end){

init_sphere2D(&_particlesList[i], x, y, _radius, 0, 0, getInitialParticlesColor(&_particlesList[i]));
//vector_add(_particlesList, &s[i]);

printf("particle%d : \t %f \t %f \n",i,x,y);
y += deltay;
i++;
if (i >= numParticles) {
end = true;

}
}
x += deltax;
}
//free(s);
// System.out.println("particlesList size : "+ _particlesList.size());
} // end of 2D

}
};

void spaceInitialParticlesMove(double timeStep, double _D, double _BMFactor, double _inertiaFactor, bool _activeCollision, bool _boundedSpace, Sphere *_particlesList, int _sizeParticlesList){
if (_sizeParticlesList != 0){
spaceBrownianMotionAndInertiaStep(timeStep, _D, _BMFactor, _inertiaFactor, _particlesList, _sizeParticlesList);
spaceCheckCollisions(_activeCollision, _boundedSpace, _particlesList, _sizeParticlesList);
//for (int i = 0; i < 500; i++)
//	printf("%d Particle x: %f \n",i,_particlesList[i]._nextX);
//spaceUpdatePositions();
}
}

void spaceBrownianMotionAndInertiaStep(double timeStep, double _D, double _BMFactor, double _inertiaFactor, Sphere *_particlesList, int _sizeParticlesList){
double k = sqrt(2 * _D*timeStep);
for (int i = 0; i < _sizeParticlesList; i++){
//vector_get(_particlesList, i);
particleMakeBMAndInertiaStep(k, _BMFactor, _inertiaFactor, &_particlesList[i]);
}
}

void particleMakeBMAndInertiaStep(double k, double BMFactor, double inertiaFactor, Sphere *s){
double auxx = BMFactor * k * gaussRand();//_randomGaussianX.nextGaussian();
s->_nextX = s->_x + inertiaFactor * s->_previousVx + auxx;

if (s->_y != -1 && s->_z == -1) {
double auxy = BMFactor * k * gaussRand();// _randomGaussianY.nextGaussian();
s->_nextY = s->_y + inertiaFactor * s->_previousVy + auxy;
}

// TODO: randomGaussianZ isini cozunce alt kismi ac
// if (_z != -1) {
//     double auxz = BMFactor * k * _randomGaussianZ.nextGaussian();
//     _nextZ = _z + inertiaFactor * _previousVz + auxz;
// }
}

void spaceCheckCollisions(bool _activeCollision, bool _boundedSpace, Sphere *_particlesList, int _particlesListSize){
//Collections.sort(_particlesList, new ParticleMinXComparator());
quickSort(0,_particlesListSize,_particlesList);

if (_activeCollision || _boundedSpace)
//Collisions.modifySpace(this);
return;
}



*/