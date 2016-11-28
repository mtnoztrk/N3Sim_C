#include "Simulation.h"
#include <string.h>

void init_simulation(Simulation *S,double time, double endTime, double timeStep, bool graphics, bool infoFile, double D, double bgConcentration, double radius, double xSize, double ySize, double zSize,
	bool activeCollision, double BMFactor, double inertiaFactor, bool boundedSpace, bool constantBGConcentration, double constantBGConcentrationWidth, int dimension){
	S->_time = time;
	S->_endTime = endTime;
	S->_timeStep = timeStep;
	S->_graphics = false; //TODO: graphics ekle
	S->_infoFile = infoFile;
	S->_simulationSystemTime;

	//space variables
	S->_D = D;                  // diffusion coefficient (nm^2/ns)
	S->_bgConcentration = bgConcentration;    // initial concentration rate. Number spheres per 10000 nm2
	S->_radius = radius;             // radius of the spheres of the initial concentration
	S->_xSize = dimension >= 1 ? xSize : -1;
	S->_ySize = dimension >= 2 ? ySize : -1;
	S->_zSize = dimension == 3 ? zSize : -1;
	S->_activeCollision = activeCollision;
	S->_BMFactor = BMFactor;
	S->_inertiaFactor = inertiaFactor;
	S->_boundedSpace = boundedSpace;
	S->_constantBGConcentration = constantBGConcentration;
	S->_constantBGConcentrationWidth = constantBGConcentrationWidth;
	S->_dimension = dimension;
	S->_sizeParticlesList = 5000;//default value
	
	if (S->_boundedSpace){
		S->_sizeVB = 2;
		S->_verticalBoundariesList = (VerticalBoundary*)malloc(sizeof(VerticalBoundary)*S->_sizeVB);
		init_verticalBoundary(&S->_verticalBoundariesList[0], 0, 0, 0);			        // xMin == yMin == yMax == 0 //left
		init_verticalBoundary(&S->_verticalBoundariesList[1], S->_xSize, 0, 0);	    // yMin == yMax == 0 //right
		//TODO: _verticalBoundariesList.add(left);
		//TODO: _verticalBoundariesList.add(right);
	}
	S->_sizeHB = 0;
	S->_collisionsListLen = 0;
	S->_collisionsQueueLen = 0; 
	S->_collisionsListTotal = 0;
	S->_collisionsQueueTotal = 0;
	//initializing variables for lists
	S->_emitterListLen = 0;
	S->_receiverListLen = 0;
	S->_nodeListLen = 0;
	S->_emitterListTotal = 4;
	S->_receiverListTotal = 4;
	S->_nodeListTotal = 4;
	S->_emitterList = (Emitter*)malloc(sizeof(Emitter)*S->_emitterListTotal);
	S->_receiverList = (Receiver*)malloc(sizeof(Receiver)*S->_receiverListTotal);
	S->_nodeList = (Node*)malloc(sizeof(Node)*S->_nodeListTotal);
}

void startSimulation(Simulation *S){
	//writeOutputFile(3,simulatorToString(S));
	clock_t iniTime, lastTime;
	iniTime = clock();
	setInitialParticles(S);
	for (int i = 0; i < 2; i++)
		initialParticlesMove(S);
	lastTime = clock();

	
	while (S->_time < S->_endTime){
	printf(".");
	if (S->_infoFile)
	;// DataInterface.writeLineToFile(DataInterface.getInfoFile(), "time:" + strPre(_time));

	//emission
	emit(S);

	if (S->_infoFile);// DataInterface.writeLineToFile(DataInterface.getInfoFile(), "emission time:" + (clock() - lastTime));
	//}
	//receivers
	if (S->_infoFile) lastTime = clock();
		updateReceivers(S);
	if (S->_infoFile);// DataInterface.writeLineToFile(DataInterface.getInfoFile(), "receivers counting time:" + (clock() - lastTime));
	//graphics
	if (S->_infoFile) lastTime = clock();
	if (S->_graphics){
	//_space.spaceToGraphics(_time);
	printf("GRAPHICS FEATURE HAS NOT IMPLEMENTED YET.");
	}
	if (S->_infoFile);// DataInterface.writeLineToFile(DataInterface.getInfoFile(), "graphics time:" + (clock() - lastTime));
	//motion
	if (S->_infoFile) lastTime = clock();
	brownianMotionAndInertiaStep(S);
	if (S->_infoFile);// DataInterface.writeLineToFile(DataInterface.getInfoFile(), "motion time:" + (clock() - lastTime));
	//collisions
	if (S->_infoFile) lastTime = clock();
	checkCollisions(S);

	if (S->_infoFile);// DataInterface.writeLineToFile(DataInterface.getInfoFile(), "collisions time:" + (clock() - lastTime));

	//			//velocity file
	//			line = strPre(_time) + DataInterface.getCsvSeparator() + _space.calculateVelocity();
	//			DataInterface.writeLineToFile(DataInterface.getVelocityFile(), line);

	//update positions
	if (S->_infoFile) lastTime = clock();
	updatePositions(S);
	if (S->_infoFile);// DataInterface.writeLineToFile(DataInterface.getInfoFile(), "update positions time:" + (System.currentTimeMillis() - lastTime));
	//calculate D
	if (S->_infoFile) lastTime = clock();
	//			calculatedD = _space.calculateD(_time);
	//			DataInterface.writeLineToFile(_DFile, calculatedD);
	//end
	S->_time += S->_timeStep;
	}
	

	S->_simulationSystemTime =(long)(clock() - iniTime);
}

void setInitialParticles(Simulation *S){
	if (S->_bgConcentration > 0){

		int numParticles = -1, xdiv = -1, ydiv = -1, i = -1;
		double squareSide = -1, deltax = -1, x = -1, y = -1;
		bool end = false;

		// 1D
		if (S->_ySize == -1) {

			numParticles = (int)((S->_bgConcentration*(double)(S->_xSize)) / 100);
			squareSide = S->_xSize / numParticles;
			if (squareSide <= S->_radius)
				printf("WARNING : initial concentration too high!");

			// xdiv = (int)((double)(_xSize) / squareSide); // in 1D xdiv == numParticles
			xdiv = numParticles;
			deltax = (double)(S->_xSize) / (double)(xdiv);

			i = 0;
			x = deltax / 2;
			end = false;
			//TODO: Düzelt 
			while (x < S->_xSize && !end){
				//Sphere s;
				//init_sphere2D(&s, x, y, _radius, 0, 0, getInitialParticlesColor(&s));
				//vector_add(_particlesList, &s);
				x += deltax;
				i++;
				if (i >= numParticles) end = true;
			}
		} // end of 1D

		//2D
		if (S->_ySize != -1 && S->_zSize == -1) {

			numParticles = (int)((S->_bgConcentration*(double)(S->_xSize)*(double)(S->_ySize)) / 10000);
			S->_sizeParticlesList = numParticles;

			double Area = S->_xSize * S->_ySize;
			squareSide = sqrt(Area / numParticles);

			if (squareSide <= S->_radius)
				printf("WARNING : initial concentration too high!");

			xdiv = (int)((double)(S->_xSize) / squareSide);
			ydiv = (int)((double)(S->_ySize) / squareSide);

			//TODO: buna efficient biþey koy bu ne
			while (xdiv*ydiv<numParticles){
				xdiv++;
				if (xdiv*ydiv<numParticles)
					ydiv++;
			}

			deltax = (double)(S->_xSize) / (double)(xdiv);
			double deltay = (double)(S->_ySize) / (double)(ydiv);
			// System.out.println("deltax : "+ deltax);	
			// System.out.println("deltay : "+ deltay);	

			i = 0;
			x = deltax / 2;
			y = deltay / 2;

			end = false;
			//Sphere *s = (Sphere *)malloc(sizeof(Sphere)*numParticles);
			S->_particlesList = (Sphere*)malloc(sizeof(Sphere)*S->_sizeParticlesList*2); //*2 emitter.c'de addParticle fonksiyonu taþmasýn diye belki yine taþabilir :D
			while (x < S->_xSize && !end){
				y = deltay / 2;
				while (y < S->_ySize  && !end){

					init_sphere2D(&S->_particlesList[i], x, y, S->_radius, 0, 0, getInitialParticlesColor(&S->_particlesList[i]));
					printf("particle%d : \t %f \t %f \n", i, x, y);
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
}

void initialParticlesMove(Simulation *S){
	if (S->_sizeParticlesList != 0){
		brownianMotionAndInertiaStep(S);
		checkCollisions(S);
		//for (int i = 0; i < 500; i++)
		//	printf("%d Particle x: %f \n",i,_particlesList[i]._nextX);
		updatePositions(S);
	}
}

void brownianMotionAndInertiaStep(Simulation *S){
	double k = sqrt(2 * S->_D*S->_timeStep);
	for (int i = 0; i < S->_sizeParticlesList; i++){
		//vector_get(_particlesList, i);
		makeBMAndInertiaStep(k, S->_BMFactor, S->_inertiaFactor, &S->_particlesList[i]);
	}
}

void makeBMAndInertiaStep(double k, double BMFactor, double inertiaFactor, Sphere *s){
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

void checkCollisions(Simulation *S){
	//Collections.sort(_particlesList, new ParticleMinXComparator());
	quickSort(0, S->_sizeParticlesList, S->_particlesList);

	if (S->_activeCollision || S->_boundedSpace){
		//Collisions.modifySpace(this);
		S->_realCollisions = 0;
		S->_initialAllCollisions = 0;
		clock_t lastTime = clock();
		createCollisionQueue(S);
		

	}		
}

void createCollisionQueue(Simulation *S){
	//allocate memory for priority queue
	if (S->_collisionsQueueTotal == 0){
		S->_collisionsQueueTotal = 4; // initially 4
		S->_collisionsQueue = (SphereCollision*)malloc(sizeof(SphereCollision)*S->_collisionsQueueTotal);
	}
		

	if (S->_collisionsQueueLen > 0){
		for (int i = 0; i < S->_collisionsQueueLen; i++)
			S->_collisionsQueue->_sphereTag = -2; // -2 tag means null
		S->_collisionsQueueLen = 0;
	}

	//set vectorlist for collisions
	if (S->_collisionsListTotal == 0){
		S->_collisionsListTotal = 4; //initally 4
		S->_collisionsList = (SphereCollision*)malloc(sizeof(SphereCollision)* S->_collisionsListTotal);
	}	
	else{
		for (int i = 0; i < S->_collisionsListLen; i++)
			S->_collisionsList->_sphereTag = -2; // -2 tag means null
	}

	for (int i = 0; i < S->_sizeParticlesList; i++){
		//ArrayList<SphereCollision> aux = findParticleCollisions(i, particleList, -1, space);
		SphereCollision *aux;
		int len = 0;
		int total = 4;
		aux = (SphereCollision*)malloc(sizeof(SphereCollision)*total);
		findParticleCollisions(S,i,-1, aux, len, total);
		//TODO: findParticleCollisions(i, particleList, -1, space);
		if (len > 0){
			S->_initialAllCollisions += len;
			//S->_collisionsQueue.add(aux.remove(0));
			if (S->_collisionsQueueLen + 1 >= S->_collisionsQueueTotal){
				S->_collisionsQueueTotal *= 2;
				S->_collisionsQueue = (SphereCollision*)realloc(S->_collisionsQueue, sizeof(SphereCollision)*S->_collisionsQueueTotal);
			}	
			S->_collisionsQueue[S->_collisionsQueueLen++] = S->_collisionsList[0];//TODO: prioritysi nolcak bunun?
		}
		//_collisionsList.add(aux);
		//vector_add(&S->_collisionsList,&aux);
		for (int i = 0; i < len; i++){
			if (S->_collisionsListLen + 1 >= S->_collisionsListTotal){
				S->_collisionsListTotal *= 2;
				S->_collisionsList = (SphereCollision*)realloc(S->_collisionsList, sizeof(SphereCollision)*S->_collisionsListTotal);
			}
			S->_collisionsList[i + S->_collisionsListLen] = aux[i];
		}
		free(aux);
	}

}

void findParticleCollisions(Simulation *S, int i, double time, SphereCollision *aux, int len, int total){

	//check particle collisions against boundaries and other particles with higher list position
	// (particleList must be sorted with XMinComparator)
	//ArrayList<SphereCollision> collisions = new ArrayList<SphereCollision>();
	//SphereSphereCollision *collisions = (SphereSphereCollision*)malloc(sizeof(SphereSphereCollision)*100);
	//System.out.println("list size : " + particleList.size() + " ; index : " + i);
	//Particle particle = particleList.get(i);
	Sphere p = S->_particlesList[i];
	double pMaxX = getMaxX(&p);
	double pMaxY = getMaxY(&p);
	double pMinX = getMinX(&p);
	double pMinY = getMinY(&p);

	int index = i + 1;
	int numParticles = S->_sizeParticlesList;
	bool end = false;
	double t = time;

	// sphere sphere collisions
	if (S->_activeCollision){
		while (index < numParticles && !end){
			Sphere p2 = S->_particlesList[index];
			//Particle p2 = particleList.get(index);
			if (getMinX(&p2) > pMaxX) 
				end = true;
			else{
				if (getMinY(&p) < getMinY(&p2)){
					if (getMinY(&p2) <= getMaxY(&p)){
						//SphereCollision c = new SphereSphereCollision((Sphere)particle, (Sphere)p2);

						//initalizerý düzeltmen gerekcek yine........................................................................................


						SphereCollision c;
						init_SphereSphereCollision(&c,&p,&p2);
						//t = c.getTime();
						t = getTime(&c);
						if (t > time + 0.0000000000001){
							//collisions.add(c);
							if (len + 1 >= total){
								total *= 2;
								aux = (SphereCollision*)realloc(aux,sizeof(SphereCollision)*total);
							}
							aux[len++] = c;
						}
					}
				}
				else{
					if (getMinY(&p) <= getMaxY(&p2)){
						//SphereCollision c = new SphereSphereCollision((Sphere)particle, (Sphere)p2);
						SphereCollision c;
						init_SphereSphereCollision(&c, &p, &p2);
						t = getTime(&c);
						if (t > time + 0.0000000000001){
							if (len + 1 >= total){
								total *= 2;
								aux = (SphereCollision*)realloc(aux, sizeof(SphereCollision)*total);
							}
							aux[len++] = c;
						}
					}
				}
			}
			index++;
		}
	}

	// sphere-boundary collisions
	if (S->_boundedSpace){
		double bMinX;
		double bMaxX;
		double bMinY;
		double bMaxY;

		for (int i = 0; i < S->_sizeHB; i++){ //sizeof(S->_horizontalBoundariesList); i++){
			bMinY = S->_horizontalBoundariesList[i]._yMin;
			bMinX = S->_horizontalBoundariesList[i]._xMin;
			bMaxX = S->_horizontalBoundariesList[i]._xMax;
			if ((pMaxX >= bMinX) && (pMinX <= bMaxX) && (pMinY <= bMinY) && (pMaxY >= bMinY)){
				//SphereCollision c = new SphereHorizontalBoundaryCollision((Sphere)particle, hb);
				SphereCollision c;
				init_SphereHorizontalBoundaryCollision(&c, &p, &S->_horizontalBoundariesList[i]);
				//					c.checkCollision();
				t = getTime(&c);
				if (t > time + 0.0000000000001){
					if (len + 1 >= total){
						total *= 2;
						aux = (SphereCollision*)realloc(aux, sizeof(SphereCollision)*total);
					}
					aux[len++] = c;
					printf("sphere boundary collision added. Sphere 1 radius: %f Spheretag 1: %f",c._sphere._radius, c._sphereTag);
				}
			}
		}
		for (int i = 0; i < S->_sizeVB; i++){
			
			bMinY = S->_verticalBoundariesList[i]._yMin;
			bMaxY = S->_verticalBoundariesList[i]._yMax;
			bMinX = S->_verticalBoundariesList[i]._xMin;


			if ((pMaxY >= bMinY) && (pMinY <= bMaxY) && (pMinX <= bMinX) && (pMaxX >= bMinX)){
				//SphereCollision c = new SphereVerticalBoundaryCollision((Sphere)particle, vb);
				//					c.checkCollision();
				SphereCollision c;
				init_SphereVerticalBoundaryCollision(&c, &p, &S->_verticalBoundariesList[i]);
				t = getTime(&c);
				if (t> time + 0.0000000000001){
					if (len + 1 >= total){
						total *= 2;
						aux = (SphereCollision*)realloc(aux, sizeof(SphereCollision)*total);
					}
					aux[len++] = c;
				}
			}
		}
	}

	//Collections.sort(collisions, new CollisionComparator());
	//TODO: sort this
	//return collisions;
}

void updatePositions(Simulation *S){
	// Open this block to track particles
	/*
	for (Particle p: _particlesList)
	System.out.println(p.getX()) +" "+p.getY()+" "+p.getZ());
	*/

	/*
	// 1D
	if (S->_ySize == -1 && S->_zSize == -1) {

	// check no particles go out of space
	if (S->_boundedSpace){
	for (Particle p : _particlesList){

	// if particle go beyond X = 0, bounce back
	if (p.getNextX() < 0) {
	double old_NextX = p.getNextX();
	p.setNextX(old_NextX * -1);
	DataInterface.writeLineToFile(DataInterface.getErrorsFile(),
	"Particle bounced from X = 0 side: current x position =  "
	+ p.getX() + " old nextX = " + old_NextX + " new nextX = " + p.getNextX());
	}

	// if particle go beyond X = _xSize, bounce back
	if (p.getNextX() > S->_xSize) {
	double old_NextX = p.getNextX();
	p.setNextX((S->_xSize * 2) - old_NextX);
	DataInterface.writeLineToFile(DataInterface.getErrorsFile(),
	"Particle bounced from X = " + S->_xSize + " side: current x position =  "
	+ p.getX() + " old nextX = " + old_NextX + " new nextX = " + p.getNextX());
	}

	else p.updatePosition();
	} // end of for _particlesList
	} // end of if _boundedSpace

	// update positions
	for (Particle p : _particlesList) p.updatePosition();

	// if simulating infinite space, delete particles according Ficks Law
	if (S->_constantBGConcentration){
	ArrayList<Particle> auxToDeleteList = new ArrayList<Particle>();
	double maxX = S->_xSize - S->_constantBGConcentrationWidth;

	Random r = new Random();
	for (Particle p : _particlesList){
	if (p.getX() < _constantBGConcentrationWidth || p.getX() > maxX){
	auxToDeleteList.add(p);
	}
	}

	Particle pa;
	int n = numParticlesToDelete();
	if (n > auxToDeleteList.size()) n = auxToDeleteList.size();
	int i = 0;

	while (i < n){
	pa = auxToDeleteList.remove((int)(r.nextDouble()*auxToDeleteList.size()));
	_particlesList.remove(pa);
	i++;
	}
	} // end of if _constantBGConcentration

	}
	// end of 1D
	*/


	// 2D
	//else 
	
	if (S->_ySize != -1 && S->_zSize == -1) {
		// check no particles go out of space
		if (S->_boundedSpace){
			for (int i = 0; i < S->_sizeParticlesList; i++){
				if (getNextX(&S->_particlesList[i]) < 0 || getNextX(&S->_particlesList[i]) > S->_xSize || getNextY(&S->_particlesList[i]) < 0 || getNextY(&S->_particlesList[i]) > S->_ySize){
					//DataInterface.writeLineToFile(DataInterface.getErrorsFile(), "ERROR : Particle out of bounds!");
					printf("ERROR : Particle out of bounds!");
				}
			}
		}

		// update positions
		for (int i = 0; i < S->_sizeParticlesList; i++)
			updatePosition(&S->_particlesList[i]);

		// if simulating infinite space, delete particles according Ficks Law		
		if (S->_constantBGConcentration){
			//ArrayList<Particle> auxToDeleteList = new ArrayList<>();
			Sphere *auxToDeleteList;
			int len = 0, total = 4;
			auxToDeleteList = (Sphere*) malloc(sizeof(Sphere)*total);
			double maxX = S->_xSize - S->_constantBGConcentrationWidth;
			double maxY = S->_ySize - S->_constantBGConcentrationWidth;

			//Random r = new Random();
			for (int i = 0; i < S->_sizeParticlesList; i++){
				if (getX(&S->_particlesList[i]) < S->_constantBGConcentrationWidth || 
					getX(&S->_particlesList[i]) > maxX || 
					getY(&S->_particlesList[i]) < S->_constantBGConcentrationWidth || 
					getY(&S->_particlesList[i]) > maxY){
					if (len + 1 >= total){
						total *= 2;
						auxToDeleteList = (Sphere*)realloc(auxToDeleteList, sizeof(Sphere)*total);
					}
					auxToDeleteList[len++] = S->_particlesList[i];
				}
			}

			Sphere pa;
			int n = numParticlesToDelete(S);
			if (n > len) 
				n = len;
			int i = 0;

			while (i < n){
				int index = (int)(gaussRand()*len);
				pa = auxToDeleteList[index];
				for (int j = index; j < len; j++)
					auxToDeleteList[j] = auxToDeleteList[j + 1];
				len--;
				//_particlesList.remove(pa);
				for (int j = 0; j < S->_sizeParticlesList; j++){
					int k = -1;
					if (S->_particlesList[j]._color == pa._color && S->_particlesList[j]._initialParticlesColor == pa._initialParticlesColor && S->_particlesList[j]._nextX == pa._nextX
						&& S->_particlesList[j]._nextY == pa._nextY && S->_particlesList[j]._nextZ == pa._nextZ && S->_particlesList[j]._previousVx == pa._previousVx
						&& S->_particlesList[j]._previousVy == pa._previousVy && S->_particlesList[j]._previousVz == pa._previousVz && S->_particlesList[j]._radius == pa._radius && S->_particlesList[j]._tag == pa._tag
						&& S->_particlesList[j]._x == pa._x && S->_particlesList[j]._y == pa._y && S->_particlesList[j]._z == pa._z){
						k = j;
					}
					if (j > k)
						S->_particlesList[j] = S->_particlesList[j + 1];
				}
				S->_sizeParticlesList--;
				i++;
			}
		} // end of if _constantBGConcentation
	} // end of 2D
}

int numParticlesToDelete(Simulation *S){
	int n1 = 0; //number of particles in first boundary area
	int n2 = 0; //number of particles in second boundary area

	double area1 = -1, area2 = -1, maxX1 = -1, maxX2 = -1, maxY1 = -1, maxY2 = -1;
	double CR1 = -1, CR2 = -2, CRFinal = -1, timeStep = -1, nFick = -1;

	// 1D
	//if (_ySize == -1) {

	//}

	// 2D
	// else
	if (S->_ySize != -1 && S->_zSize == -1) {
		area1 = S->_xSize*S->_ySize - (S->_xSize - 2 * S->_constantBGConcentrationWidth)*(S->_ySize - 2 * S->_constantBGConcentrationWidth);
		area2 = S->_xSize*S->_ySize - (S->_xSize - 4 * S->_constantBGConcentrationWidth)*(S->_ySize - 4 * S->_constantBGConcentrationWidth);

		maxX2 = S->_xSize - 2 * S->_constantBGConcentrationWidth;
		maxY2 = S->_ySize - 2 * S->_constantBGConcentrationWidth;

		maxX1 = S->_xSize - S->_constantBGConcentrationWidth;
		maxY1 = S->_ySize - S->_constantBGConcentrationWidth;

		for (int i = 0; i < S->_sizeParticlesList; i++){
			if (getX(&S->_particlesList[i]) < 2 * S->_constantBGConcentrationWidth || getX(&S->_particlesList[i]) > maxX2 || 
				getY(&S->_particlesList[i]) < 2 * S->_constantBGConcentrationWidth || getY(&S->_particlesList[i]) > maxY2){
				n2++;
				if (getX(&S->_particlesList[i]) < S->_constantBGConcentrationWidth || getX(&S->_particlesList[i]) > maxX1 || 
					getY(&S->_particlesList[i]) < S->_constantBGConcentrationWidth || getY(&S->_particlesList[i]) > maxY1){
					n1++;
				}
			}
		}

		CR1 = ((double)(n1)) / area1;
		CR2 = ((double)(n2 - n1)) / (area2 - area1);
		if (CR2 <= CR1) 
			return 0;
		CRFinal = CR1 - (CR2 - CR1);
		if (CRFinal * 10000 <= S->_bgConcentration) 
			return 0;
		// TODO do not use Simulator.getTimeStep
		timeStep = S->_timeStep;
		nFick = 2 * (double)(S->_xSize + S->_ySize)*timeStep*S->_D*(CR2 - CR1) / S->_constantBGConcentrationWidth;
	}
	return (int)nFick;
}

void emit(Simulation *S){
	for (int i = 0; i < S->_emitterListLen; i++){
		emitParticleFromEmitter(S->_emitterList[i], S->_emitterListLen, S->_time, S->_particlesList, S->_sizeParticlesList);
		//e.emit(time, _particlesList);
	}
		

	for (int i = 0; i < S->_nodeListLen; i++) {
		int emittedParticles = 0;
		//TODO: bunu yap iþte
		//emittedParticles = emitParticleFromNode(S->_nodeList[i], S->_nodeListLen, S->_time, S->_particlesList, S->_sizeParticlesList);
		//n.emit(time, _particlesList);
		//TODO: emitter dosyasinin bos olmasini istemiyorsan, orjinal siniflarin geri donus degerlerini duzelt
		//DataInterface.writeLineToFile("emitter_" + n.getFileName(), strPre(time) + DataInterface.getCsvSeparator() + emittedParticles);
	}
}

void updateReceivers(Simulation *S){
	int numParticles;
	int numberOfReceivers;
	//int i;

	//Collections.sort(_particlesList, new ParticleXComparator());
	//TODO: SORT this
	// Updating receivers
	for (int i = 0; i < S->_receiverListLen; i++){
		numParticles = count(&S->_receiverList[i], S->_particlesList, S->_sizeParticlesList);
		//DataInterface.writeLineToFile(r.getFileName(), strPre(time) + DataInterface.getCsvSeparator() + numParticles);
	}

	// Updating nodes
	for (int j = 0; j < S->_nodeListLen; j++) {
		numberOfReceivers = S->_nodeList[j]._numberOfReceivers;

		for (int i = 0; i < numberOfReceivers; i++) {
			numParticles = countNode(&S->_nodeList[j],S->_particlesList, S->_sizeParticlesList, i);//n.count(i, _particlesList);
			//DataInterface.writeLineToFile("receiver_" + i + "_" + n.getFileName(), strPre(time) + DataInterface.getCsvSeparator() + numParticles);
		}
	}
}

char* simulatorToString(Simulation *S){
	char  buffer[100];
	
	char *s = (char*)malloc(sizeof(char)*1000);
	strcat(s, "SIMULATION PARAMS \n");
	strcat(s, "***************** \n");
	sprintf(buffer, "simulation time (ns): %f \n", S->_endTime);
	strcat(s, buffer);
	sprintf(buffer, "timestep (ns):  %f \n", S->_timeStep);
	strcat(s, buffer);
	sprintf(buffer, "activate collisions:   %f \n", S->_activeCollision);
	strcat(s, buffer);
	sprintf(buffer, "Brownian Motion Factor:  %f \n", S->_BMFactor);
	strcat(s, buffer);
	sprintf(buffer, "Inertia Factor:  %f \n", S->_inertiaFactor);
	strcat(s, buffer);
	strcat(s, "\n");
	strcat(s, "SPACE PARAMS");
	strcat(s, "***************** \n");
	//TODO: getdescriptionu yaz iþte
	//strcat(s, _space.getDescription());
	strcat(s, "EMITTERS PARAMS");
	strcat(s, "***************** \n");
	for (int i = 0; i < S->_emitterListLen; i++){
		sprintf(buffer, "Emitter %f data \n", i);
		strcat(s, buffer);
		switch (S->_emitterList[i]._type){
		case 1:
			strcat(s, "Type : PulseSphereEmitter \n");
			break;
		case 2:
			strcat(s, "Type : RectangularSphereEmitter \n");
			break;
		case 3:
			strcat(s, "Type : NoiseSphereEmitter \n");
			break;
		case 4:
			strcat(s, "Type : WaveFromFileSphereEmitter \n");
			break;
		case 5:
			strcat(s, "Type : PunctualWaveFromFile3DSphereEmitter \n");
			break;
		default:
			strcat(s, "Type : SOMETHING WENT REALLY WRONG IF YOU ARE SEEING THIS ERROR MESSAGE. Emitter \n");
			break;
		}
		//TODO: getdescriptionu yaz iþte
		//strcat(s, _space.getDescription());
		strcat(s, "\n");
	}
	strcat(s, "\n");
	strcat(s, "RECEIVERS PARAMS");
	strcat(s, "***************** \n");
	for (int i = 0; i < S->_receiverListLen; i++){
		sprintf(buffer, "Receiver %f data \n", i);
		strcat(s, buffer);
		switch (S->_receiverList[i]._type){
		case 1:
			strcat(s, "Type : SquareReceiver \n");
			break;
		case 2:
			strcat(s, "Type : SphericalReceiver \n");
			break;
		case 3:
			strcat(s, "Type : Spherical3DReceiver \n");
			break;
		default:
			strcat(s, "Type : SOMETHING WENT REALLY WRONG IF YOU ARE SEEING THIS ERROR MESSAGE. Receiver \n");
			break;
		}
		//TODO: getdescriptionu yaz iþte
		//strcat(s, S->_receiverList[i].getDescription());
		strcat(s, "\n");
	}
	strcat(s, "\n");
	strcat(s, "NODE PARAMS");
	strcat(s, "***************** \n");
	for (int i = 0; i < S->_nodeListLen; i++){
		sprintf(buffer, "Node %f data \n", i);
		strcat(s, buffer);
		switch (S->_nodeList[i]._type){
		case 1:
			strcat(s, "Type : SimpleNode \n");
			break;
		case 2:
			strcat(s, "Type : ImmediatelyReleasingNode \n");
			break;
		case 3:
			strcat(s, "Type : ImmediatelyPulseReleasingNode \n");
			break;
		default:
			strcat(s, "Type : SOMETHING WENT REALLY WRONG IF YOU ARE SEEING THIS ERROR MESSAGE. Node \n");
			break;
		}
		//TODO: getdescriptionu yaz iþte
		//strcat(s, S->_receiverList[i].getDescription());
		strcat(s, "\n");
	}

	return s;

}

void writeOutputFile(int type, char* line){
	FILE *output;
	switch (type){
	case 1://info file
		output = fopen("info.log", "a");
		break;
	case 2://error file
		output = fopen("error.log", "a");
		break;
	case 3://simulation file
		output = fopen("simulationData.txt", "a");
		break;
	default:
		output = fopen("wrongType.txt", "a");
		break;
	}

	if (!output){//check file if open.
		perror("File opening failed!");
		return EXIT_FAILURE;
	}

	//yazdýr burda

	fclose(output);
}

void addEmitterToNode(Simulation *S, char* nodeName, Emitter e){
	for (int i = 0; i < S->_nodeListLen; i++){
		if (S->_nodeList[i]._name == nodeName)
			addEmitter(&S->_nodeList[i],e);
	}
}

void addReceiverToNode(Simulation *S, char* nodeName, Receiver e){
	for (int i = 0; i < S->_nodeListLen; i++){
		if (S->_nodeList[i]._name == nodeName)
			addReceiver(&S->_nodeList[i], e);
	}
}
//TODO: debug this
void addPulseSphereEmitterToNode1D(Simulation *S, char* nodeName, double x, double startTime, double endTime, double amplitude, double sphereRadius,
	double emitterRadius, double initV, bool punctual, bool concentrationEmitter, char* color)
{
	Emitter e;
	init_PulseSphereEmitter1D(&e, x, startTime, endTime, amplitude, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color);
	//ParticleEmitter e = new PulseSphereEmitter(x, startTime, endTime, amplitude, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color);
	addEmitterToNode(S, nodeName, e);
} // 1D

void exit_simulation(Simulation *S){
	free(S->_verticalBoundariesList);
	//for (int i = 0; i < S->_emitterListLen; i++){
	//	free(S->_emitterList[i].)
	//}
	free(S->_emitterList);
	free(S->_receiverList);
	free(S->_nodeList);
	//if (S->_horizontalBoundariesList != NULL)
	//	free(S->_horizontalBoundariesList);
	//free(S->_particlesList);
	//free(S->_collisionsQueue);
	
	
	//free(S->_collisionsList);
}

