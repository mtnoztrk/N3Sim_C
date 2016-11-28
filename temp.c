static ifstream _configFile;

// if no argument is received, read values from file or standard input
// else read from config file
if (argc == 0){
	//obsolete
	// ConsoleUI.readFromStdIn(_names, _values);
}
else{
	FileUI::readFromFile(_names, _values, argv);
}

// create simulator and space
// simulator params
string outPath = getNextstring("outPath");
//create Data Interface asap so we can log errors
DataInterface::init(outPath);
bool graphics = getNextBoolean("graphics");
bool infoFile = getNextBoolean("infoFile");
bool activeCollision = getNextBoolean("activeCollision");
double BMFactor = getNextDouble("BMFactor");
double inertiaFactor = getNextDouble("inertiaFactor");
double time = getNextDouble("time");
double timeStep = getNextDouble("timeStep");

// space params
bool boundedSpace = getNextBoolean("boundedSpace");
bool constantBGConcentration = getNextBoolean("constantBGConcentration");
double constantBGConcentrationWidth = getNextDouble("constantBGConcentrationWidth");
int dimension = getNextInt("dimension");

int xSize = 0, ySize = 0, zSize = 0;

printf("dimension: %d \n", dimension);

if (dimension >= 1) xSize = getNextInt("xSize");
if (dimension >= 2) ySize = getNextInt("ySize");
if (dimension == 3) zSize = getNextInt("zSize");
if ((dimension < 1) || (dimension > 3)) throw new Error("dimensions mismatch...\n");

double D = getNextDouble("D");
double bgConcentration = getNextDouble("bgConcentration");
double sphereRadius = getNextDouble("sphereRadius");
/////////////////////////////////////////////////////////////////////////////////////////////////

if (dimension == 1)      _d.createSimulator(outPath, graphics, infoFile, activeCollision, BMFactor, inertiaFactor, time, timeStep, xSize, D, bgConcentration, sphereRadius, boundedSpace, constantBGConcentration, constantBGConcentrationWidth);
else if (dimension == 2) _d.createSimulator(outPath, graphics, infoFile, activeCollision, BMFactor, inertiaFactor, time, timeStep, xSize, ySize, D, bgConcentration, sphereRadius, boundedSpace, constantBGConcentration, constantBGConcentrationWidth);
// else if (dimension == 3) _d.createSimulator(outPath, graphics, infoFile, activeCollision, BMFactor, inertiaFactor, time, timeStep, xSize, ySize, zSize, D, bgConcentration, sphereRadius, boundedSpace, constantBGConcentration, constantBGConcentrationWidth);


// createEmitters
int numEmitters = getNextInt("emitters");
double emitterRadius;
double x = -1, y = -1, z = -1;
double startTime;
double endTime;
double initV;
bool punctual;
bool concentrationEmitter;
string color;
int emitterType;
double amplitude;
int period;
int timeOn;
string file;
double scaleFactor;

for (int i = 0; i < numEmitters; i++){
	emitterRadius = getNextDouble("emitterRadius");
	if (dimension >= 1)  x = getNextDouble("x");
	if (dimension >= 2)  y = getNextDouble("y");
	if (dimension == 3)  z = getNextDouble("z");
	startTime = getNextDouble("startTime");
	endTime = getNextDouble("endTime");
	initV = getNextDouble("initV");
	punctual = getNextBoolean("punctual");
	concentrationEmitter = getNextBoolean("concentrationEmitter");
	color = getNextstring("color");

	emitterType = getNextInt("emitterType");
	switch (emitterType){
	case(1) :
		amplitude = getNextDouble("amplitude");
		amplitude = amplitude * timeStep / 100; //change to amplitude per timeStep
		_d.createPulseSphereEmitter(x, y, startTime, endTime, amplitude, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color);
		break;
	case(2) :
		amplitude = getNextDouble("amplitude");
		amplitude = amplitude * timeStep / 100; //change to amplitude per timeStep
		period = getNextInt("period");
		timeOn = getNextInt("timeOn");
		_d.createRectangularSphereEmitter(x, y, startTime, endTime, amplitude, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, period, timeOn, color);
		break;
	case(3) :
		amplitude = getNextDouble("amplitude");
		amplitude = amplitude * timeStep / 100; //change to amplitude per timeStep
		_d.createNoiseSphereEmitter(x, y, startTime, endTime, amplitude, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color);
		break;
	case(4) :
		file = getNextstring("file");
		scaleFactor = getNextDouble("scaleFactor");
		int size = (int)((double)(endTime - startTime) / timeStep);
		_d.createWaveFromFileSphereEmitter(x, y, startTime, endTime, scaleFactor, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, file, size, color);
		break;
	case(5) :
		// double z    = getNextDouble("z");
		z = getNextDouble("z");
		file = getNextstring("file");
		scaleFactor = getNextDouble("scaleFactor");
		int size4 = (int)((double)(endTime - startTime) / timeStep);
		_d.createPunctualWaveFromFile3DSphereEmitter(x, y, z, startTime, endTime, scaleFactor, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, file, size4, color);
		break;
	default: error("Wrong type of emitter. Emitter not created. Try again"); i--;
	}
}


// createReceivers		
int numReceivers = getNextInt("receivers");
string name;
int receiverType;
bool absorb;
bool accumulate;
double side;
double rradius;

for (int i = 0; i < numReceivers; i++){
	name = getNextstring("name");
	if (dimension >= 1) x = getNextDouble("x");
	if (dimension >= 2) y = getNextDouble("y");
	if (dimension == 3) z = getNextDouble("z");
	absorb = getNextBoolean("absorb");
	accumulate = getNextBoolean("accumulate");
	receiverType = getNextInt("receiverType");

	switch (receiverType){
	case(1) :
		side = getNextDouble("side");
		if (dimension == 1) _d.createSquareReceiver(name, x, absorb, accumulate, side);
		else if (dimension == 2) _d.createSquareReceiver(name, x, y, absorb, accumulate, side);
		else if (dimension == 3) _d.createSquareReceiver(name, x, y, z, absorb, accumulate, side);
		break;
	case(2) :
		rradius = getNextDouble("rradius");
		if (dimension == 1) _d.createSphericalReceiver(name, x, absorb, accumulate, rradius);
		else if (dimension == 2) _d.createSphericalReceiver(name, x, y, absorb, accumulate, rradius);
		break;
	case(3) :
		// double z    = getNextDouble("z");
		z = getNextDouble("z");
		rradius = getNextDouble("rradius");
		_d.create3DSphericalReceiver(name, x, y, z, absorb, accumulate, rradius);
		break;
	default: error("Wrong type of receiver. Receiver not created. Try again"); i--;
	} // switch

} // for i < numReceivers


// createNodes
int nodeType;
int numNodes = getNextInt("nodes");
int numberOfEmitters = -1, numberOfReceivers = -1;
int initialSupply = -1, reservoirCapacity = -1;
int harvesterIndex = -1;

for (int i = 0; i < numNodes; i++) {

	// node specific
	nodeType = getNextInt("nodeType");
	name = getNextstring("name");

	if (dimension >= 1) x = getNextDouble("x");
	if (dimension >= 2) y = getNextDouble("y");
	if (dimension == 3) z = getNextDouble("z");

	// simple node is not using the information below
	if (nodeType != 1) {
		initialSupply = getNextInt("initialSupply");
		reservoirCapacity = getNextInt("reservoirCapacity");
		numberOfEmitters = getNextInt("numberOfEmitters");
		numberOfReceivers = getNextInt("numberOfReceivers");
		harvesterIndex = getNextInt("harvesterIndex");
	}

	switch (nodeType) {

	case(1) : // simpleNode
		if (dimension == 1)      _d.createSimpleNode(name, x, numberOfEmitters, numberOfReceivers);
		else if (dimension == 2) _d.createSimpleNode(name, x, y, numberOfEmitters, numberOfReceivers);
		else if (dimension == 3) _d.createSimpleNode(name, x, y, z, numberOfEmitters, numberOfReceivers);
		break;

	case(2) : // immediatelyReleasingNode

		emitterRadius = getNextDouble("emitterRadius");
		initV = getNextDouble("initV");
		punctual = getNextBoolean("punctual");
		concentrationEmitter = getNextBoolean("concentrationEmitter");
		color = getNextstring("color");

		if (dimension == 1)_d.createImmediatelyReleasingNode(name, x, initialSupply, reservoirCapacity, numberOfEmitters,
			numberOfReceivers, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color, harvesterIndex);
		else if (dimension == 2)_d.createImmediatelyReleasingNode(name, x, y, initialSupply, reservoirCapacity, numberOfEmitters,
			numberOfReceivers, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color, harvesterIndex);
		else if (dimension == 3)_d.createImmediatelyReleasingNode(name, x, y, z, initialSupply, reservoirCapacity, numberOfEmitters,
			numberOfReceivers, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color, harvesterIndex);
		break;

	case(3) : // immediatelyPulseReleasingNode

		emitterRadius = getNextDouble("emitterRadius");
		initV = getNextDouble("initV");
		punctual = getNextBoolean("punctual");
		concentrationEmitter = getNextBoolean("concentrationEmitter");
		color = getNextstring("color");
		amplitude = getNextDouble("amplitude");

		if (dimension == 1) _d.createImmediatelyPulseReleasingNode(name, x, initialSupply, reservoirCapacity, numberOfEmitters,
			numberOfReceivers, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color, amplitude, harvesterIndex);
		else if (dimension == 2) _d.createImmediatelyPulseReleasingNode(name, x, y, initialSupply, reservoirCapacity, numberOfEmitters,
			numberOfReceivers, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color, amplitude, harvesterIndex);
		else if (dimension == 3) _d.createImmediatelyPulseReleasingNode(name, x, y, z, initialSupply, reservoirCapacity, numberOfEmitters,
			numberOfReceivers, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color, amplitude, harvesterIndex);
		break;

	default: error("Wrong type of node. Node not created. Try again");

	} // switch nodeType

	// emitter specific
	for (int j = 0; j < numberOfEmitters; j++) {

		emitterRadius = getNextDouble("emitterRadius");
		startTime = getNextDouble("startTime");
		endTime = getNextDouble("endTime");
		initV = getNextDouble("initV");
		punctual = getNextBoolean("punctual");
		concentrationEmitter = getNextBoolean("concentrationEmitter");
		color = getNextstring("color");
		emitterType = getNextInt("emitterType");

		switch (emitterType){

		case(1) :

			amplitude = getNextDouble("amplitude");
			amplitude = amplitude * timeStep / 100; //change to amplitude per timeStep

			if (dimension == 1) _d.addPulseSphereEmitterToNode(name, x, startTime, endTime, amplitude, sphereRadius,
				emitterRadius, initV, punctual, concentrationEmitter, color);
			else if (dimension == 2) _d.addPulseSphereEmitterToNode(name, x, y, startTime, endTime, amplitude, sphereRadius,
				emitterRadius, initV, punctual, concentrationEmitter, color);
			else if (dimension == 3) _d.addPulseSphereEmitterToNode(name, x, y, z, startTime, endTime, amplitude, sphereRadius,
				emitterRadius, initV, punctual, concentrationEmitter, color);
			break;

		case(2) :

			amplitude = getNextDouble("amplitude");
			amplitude = amplitude * timeStep / 100; //change to amplitude per timeStep
			period = getNextInt("period");
			timeOn = getNextInt("timeOn");

			if (dimension == 1) _d.addRectangularSphereEmitterToNode(name, x, startTime, endTime, amplitude, sphereRadius,
				emitterRadius, initV, punctual, concentrationEmitter, period, timeOn, color);
			else if (dimension == 2) _d.addRectangularSphereEmitterToNode(name, x, y, startTime, endTime, amplitude, sphereRadius,
				emitterRadius, initV, punctual, concentrationEmitter, period, timeOn, color);
			else if (dimension == 3) _d.addRectangularSphereEmitterToNode(name, x, y, startTime, endTime, amplitude, sphereRadius,
				emitterRadius, initV, punctual, concentrationEmitter, period, timeOn, color);
			break;

		case(3) :

			amplitude = getNextDouble("amplitude");
			amplitude = amplitude * timeStep / 100; //change to amplitude per timeStep

			if (dimension == 1) _d.addNoiseSphereEmitterToNode(name, x, startTime, endTime, amplitude, sphereRadius,
				emitterRadius, initV, punctual, concentrationEmitter, color);
			else if (dimension == 2) _d.addNoiseSphereEmitterToNode(name, x, y, startTime, endTime, amplitude, sphereRadius,
				emitterRadius, initV, punctual, concentrationEmitter, color);
			else if (dimension == 3) _d.addNoiseSphereEmitterToNode(name, x, y, z, startTime, endTime, amplitude, sphereRadius,
				emitterRadius, initV, punctual, concentrationEmitter, color);
			break;

		case(4) :

			file = getNextstring("file");
			scaleFactor = getNextDouble("scaleFactor");
			int size = (int)((double)(endTime - startTime) / timeStep);

			if (dimension == 1) _d.addWaveFromFileSphereEmitterToNode(name, x, startTime, endTime, scaleFactor, sphereRadius,
				emitterRadius, initV, punctual, concentrationEmitter, file, size, color);
			else if (dimension == 2) _d.addWaveFromFileSphereEmitterToNode(name, x, y, startTime, endTime, scaleFactor, sphereRadius,
				emitterRadius, initV, punctual, concentrationEmitter, file, size, color);
			else if (dimension == 3) _d.addWaveFromFileSphereEmitterToNode(name, x, y, z, startTime, endTime, scaleFactor, sphereRadius,
				emitterRadius, initV, punctual, concentrationEmitter, file, size, color);
			break;

		case(5) :
			// double z    = getNextDouble("z");
			z = getNextDouble("z");
			file = getNextstring("file");
			scaleFactor = getNextDouble("scaleFactor");
			int size4 = (int)((double)(endTime - startTime) / timeStep);
			_d.addPunctualWaveFromFile3DSphereEmitterToNode(name, x, y, z, startTime, endTime, scaleFactor, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, file, size4, color);
			break;

			/* case(6):
			_d.addImmediatelyReleasingEmitterToNode(name, x, y, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color);
			break;  */

		default: error("Wrong type of emitter. Emitter not created. Try again"); j--;

		} // end of switch emitterType	

	} // end of for j  < numberOfEmitters    

	// receiver specific
	for (int j = 0; j < numberOfReceivers; j++) {

		absorb = getNextBoolean("absorb");
		accumulate = getNextBoolean("accumulate");
		receiverType = getNextInt("receiverType");

		switch (receiverType){

		case(1) : // square receiver
			side = getNextDouble("side");
			_d.addSquareReceiverToNode(name, x, y, absorb, accumulate, side);
			break;

		case(2) : // spherical receiver
			rradius = getNextDouble("rradius");
			_d.addSphericalReceiverToNode(name, x, y, absorb, accumulate, rradius);
			break;

		case(3) : // 3D spherical receiver
			// double z        = getNextDouble("z");
			z = getNextDouble("z");
			rradius = getNextDouble("rradius");
			_d.add3DSphericalReceiverToNode(name, x, y, z, absorb, accumulate, rradius);
			break;

		case(4) : // harvesting spherical receiver
			int maxHarvestPerIteration = 0;
			rradius = getNextDouble("rradius");
			maxHarvestPerIteration = getNextInt("maxHarvestPerIteration");
			_d.addHarvestingSphericalReceiverToNode(name, x, y, accumulate, rradius, maxHarvestPerIteration);
			break;

		case(5) : // unlimited harvesting spherical receiver
			rradius = getNextDouble("rradius");
			_d.addUnlimitedHarvestingSphericalReceiverToNode(name, x, y, accumulate, rradius);
			break;

		case(6) : // ratio limited harvesting spherical receiver
			double harvestRatio = getNextDouble("harvestRatio");
			rradius = getNextDouble("rradius");
			_d.addRatioLimitedHarvestingSphericalReceiverToNode(name, x, y, accumulate, rradius, harvestRatio);
			break;

		default: error("Wrong type of receiver. Receiver not created. Try again");

		} //  end of switch receiverType   
	} // end of for j < numberOfReceivers

} // end of for i < numNodes


//start simulation
cout << endl << "Simulation starts..." << endl;
_d.startSimulation();
cout << endl << "Simulation finished!" << endl;

t = clock() - t;
long elapsedTime = t;

cout << "Total runtime: " << elapsedTime << endl;