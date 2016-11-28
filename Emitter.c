#include "Emitter.h"
#include <stdbool.h>
#include "GaussRand.h"
#include <math.h>
#include <stdio.h>
#include "Sphere.h"

void init_PulseSphereEmitter1D(Emitter *p, double x, double startTime, double endTime, double amplitude, double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, char* color){
	p->_x = x;
	p->_y = -1;
	p->_z = -1;
	p->_startTime = startTime;
	p->_endTime = endTime;
	p->_amplitude = amplitude;
	p->_sphereRadius = sphereRadius;
	p->_emitterRadius = emitterRadius;
	p->_initV = initV;
	p->_punctual = punctual;
	p->_concentrationEmitter = concentrationEmitter;
	p->_color = color;
	p->_type = 1;
}
void init_PulseSphereEmitter2D(Emitter *p, double x, double y, double startTime, double endTime, double amplitude, double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, char* color){
	p->_x = x;
	p->_y = y;
	p->_z = -1;
	p->_startTime = startTime;
	p->_endTime = endTime;
	p->_amplitude = amplitude;
	p->_sphereRadius = sphereRadius;
	p->_emitterRadius = emitterRadius;
	p->_initV = initV;
	p->_punctual = punctual;
	p->_concentrationEmitter = concentrationEmitter;
	p->_color = color;
	p->_type = 1;
}
void init_PulseSphereEmitter3D(Emitter *p, double x, double y, double z, double startTime, double endTime, double amplitude, double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, char* color){
	p->_x = x;
	p->_y = y;
	p->_z = z;
	p->_startTime = startTime;
	p->_endTime = endTime;
	p->_amplitude = amplitude;
	p->_sphereRadius = sphereRadius;
	p->_emitterRadius = emitterRadius;
	p->_initV = initV;
	p->_punctual = punctual;
	p->_concentrationEmitter = concentrationEmitter;
	p->_color = color;
	p->_type = 1;
}

void init_RectangularSphereEmitter1D(Emitter *p, double x, double startTime, double endTime, double amplitude, double sphereRadius, double emitterRadius, double initV,
	bool punctual, bool concentrationEmitter, int period, int timeOn, char* color){
	p->_x = x;
	p->_y = -1;
	p->_z = -1;
	p->_startTime = startTime;
	p->_endTime = endTime;
	p->_amplitude = amplitude;
	p->_sphereRadius = sphereRadius;
	p->_emitterRadius = emitterRadius;
	p->_initV = initV;
	p->_punctual = punctual;
	p->_concentrationEmitter = concentrationEmitter;
	p->_period = period;
	p->_timeOn = timeOn;
	p->_color = color;
	p->_type = 2;
}
void init_RectangularSphereEmitter2D(Emitter *p, double x, double y, double startTime, double endTime, double amplitude, double sphereRadius, double emitterRadius, double initV,
	bool punctual, bool concentrationEmitter, int period, int timeOn, char* color){
	p->_x = x;
	p->_y = y;
	p->_z = -1;
	p->_startTime = startTime;
	p->_endTime = endTime;
	p->_amplitude = amplitude;
	p->_sphereRadius = sphereRadius;
	p->_emitterRadius = emitterRadius;
	p->_initV = initV;
	p->_punctual = punctual;
	p->_concentrationEmitter = concentrationEmitter;
	p->_period = period;
	p->_timeOn = timeOn;
	p->_color = color;
	p->_type = 2;

}
void init_RectangularSphereEmitter3D(Emitter *p, double x, double y, double z, double startTime, double endTime, double amplitude, double sphereRadius, double emitterRadius, double initV,
	bool punctual, bool concentrationEmitter, int period, int timeOn, char* color){
	p->_x = x;
	p->_y = y;
	p->_z = z;
	p->_startTime = startTime;
	p->_endTime = endTime;
	p->_amplitude = amplitude;
	p->_sphereRadius = sphereRadius;
	p->_emitterRadius = emitterRadius;
	p->_initV = initV;
	p->_punctual = punctual;
	p->_concentrationEmitter = concentrationEmitter;
	p->_period = period;
	p->_timeOn = timeOn;
	p->_color = color;
	p->_type = 2;
}

void init_NoiseSphereEmitter1D(Emitter *p, double x, double startTime, double endTime, double amplitude, double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, char* color){
	p->_x = x;
	p->_y = -1;
	p->_z = -1;
	p->_startTime = startTime;
	p->_endTime = endTime;
	p->_amplitude = amplitude;
	p->_sphereRadius = sphereRadius;
	p->_emitterRadius = emitterRadius;
	p->_initV = initV;
	p->_punctual = punctual;
	p->_concentrationEmitter = concentrationEmitter;
	p->_color = color;
	p->_randomGaussianNoise = -1;
	p->_type = 3;
}
void init_NoiseSphereEmitter2D(Emitter *p, double x, double y, double startTime, double endTime, double amplitude, double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, char* color){
	p->_x = x;
	p->_y = y;
	p->_z = -1;
	p->_startTime = startTime;
	p->_endTime = endTime;
	p->_amplitude = amplitude;
	p->_sphereRadius = sphereRadius;
	p->_emitterRadius = emitterRadius;
	p->_initV = initV;
	p->_punctual = punctual;
	p->_concentrationEmitter = concentrationEmitter;
	p->_color = color;
	p->_randomGaussianNoise = -1;
	p->_type = 3;
}
void init_NoiseSphereEmitter3D(Emitter *p, double x, double y, double z, double startTime, double endTime, double amplitude, double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, char* color){
	p->_x = x;
	p->_y = y;
	p->_z = z;
	p->_startTime = startTime;
	p->_endTime = endTime;
	p->_amplitude = amplitude;
	p->_sphereRadius = sphereRadius;
	p->_emitterRadius = emitterRadius;
	p->_initV = initV;
	p->_punctual = punctual;
	p->_concentrationEmitter = concentrationEmitter;
	p->_color = color;
	p->_randomGaussianNoise = -1;
	p->_type = 3;
}

void init_ImmediatelyReleasingEmitter1D(Emitter *p, double x, double startTime, double endTime, double amplitude, double sphereRadius, double emitterRadius, double initV,
	bool punctual, bool concentrationEmitter, char* color){
	p->_x = x;
	p->_y = -1;
	p->_z = -1;
	p->_startTime = 0;
	p->_endTime = 0;
	p->_amplitude = 0;
	p->_sphereRadius = sphereRadius;
	p->_emitterRadius = emitterRadius;
	p->_initV = initV;
	p->_punctual = punctual;
	p->_concentrationEmitter = concentrationEmitter;
	p->_color = color;
	p->_type = 6;
}
void init_ImmediatelyReleasingEmitter2D(Emitter *p, double x, double y, double startTime, double endTime, double amplitude, double sphereRadius, double emitterRadius, double initV,
	bool punctual, bool concentrationEmitter, char* color){
	p->_x = x;
	p->_y = y;
	p->_z = -1;
	p->_startTime = 0;
	p->_endTime = 0;
	p->_amplitude = 0;
	p->_sphereRadius = sphereRadius;
	p->_emitterRadius = emitterRadius;
	p->_initV = initV;
	p->_punctual = punctual;
	p->_concentrationEmitter = concentrationEmitter;
	p->_color = color;
	p->_type = 6;
}
void init_ImmediatelyReleasingEmitter3D(Emitter *p, double x, double y, double z, double startTime, double endTime, double amplitude, double sphereRadius, double emitterRadius, double initV,
	bool punctual, bool concentrationEmitter, char* color){
	p->_x = x;
	p->_y = y;
	p->_z = z;
	p->_startTime = 0;
	p->_endTime = 0;
	p->_amplitude = 0;
	p->_sphereRadius = sphereRadius;
	p->_emitterRadius = emitterRadius;
	p->_initV = initV;
	p->_punctual = punctual;
	p->_concentrationEmitter = concentrationEmitter;
	p->_color = color;
	p->_type = 6;
}

void emitParticleFromEmitter(Emitter e, int emitterListLen, double time, Sphere *particlesList, int sizeParticlesList){
	//TODO: imediately için case ekle diðerleri ayný
	switch(e._type){
		case 1://pulseSphereEmitter
		{
			int n = (int)getNumParticles(e, time);
			int deleted = 0;
			if (n > 0){
				deleted = deleteParticles(e, particlesList, sizeParticlesList, sizeParticlesList);
				if (e._concentrationEmitter) 
					addParticles(e, particlesList, sizeParticlesList, n);
				else 
					addParticles(e, particlesList, sizeParticlesList, n + deleted);
			}
				else if (n < 0){
					n *= -1;
					deleteParticles(e, particlesList, sizeParticlesList, n);
				}
				break;
		}
		default:
			break;
	}
}

double getNumParticles(Emitter p, double time){
	//TODO: switchle dön bunlarý farklý çalýþýyo farklý emitörde
	if (time >= p._startTime && time < p._endTime) 
		return p._amplitude;
	return 0;
}

int deleteParticles(Emitter e, Sphere *particlesList, int sizeParticleList, int numParticles){

	//Collections.sort(particlesList, new ParticleXComparator());
	//TODO: sort particleslist
	//Iterator<Particle> it = particlesList.iterator();
	int iterator = 0;
	Sphere p;
	int count = 0;
	//ArrayList<Particle> toDeleteList = new ArrayList<Particle>();
	Sphere *toDeleteList;
	int totalToDeleteList = 4, lenToDeleteList = 0;
	toDeleteList = (Sphere*)malloc(sizeof(Sphere)*totalToDeleteList);


	while (iterator < sizeParticleList){
		p = particlesList[iterator + 1];
		if (getX(&p) > e._x + e._emitterRadius) 
			break;
		if (getX(&p) >= e._x - e._emitterRadius){
			if ((getX(&p) - e._x)*(getX(&p) - e._x) + (getY(&p) - e._y)*(getY(&p) - e._y) <= e._emitterRadius*e._emitterRadius){
				//allocating more space if needed.
				if (lenToDeleteList + 1 >= totalToDeleteList){
					totalToDeleteList *= 2;
					toDeleteList = (Sphere*)realloc(toDeleteList,sizeof(Sphere)*totalToDeleteList);
				}
				toDeleteList[lenToDeleteList++] = p;
			}
		}
	}
	// delete closer particles, so we sort them by distance to emitter
	//Collections.sort(toDeleteList, new ParticleDistanceComparator(_x, _y));
	//TODO: sort toDeleteList
	while (count < numParticles && count < lenToDeleteList){
		for (int i = 0; i < sizeParticleList; i++)
		{
			if (&particlesList[i] == &toDeleteList[count]){
				for (int j = i; j < sizeParticleList; j++)
				{
					particlesList[j] = particlesList[j + 1];
				}
				sizeParticleList--;
			}

		}
		//particlesList.remove(toDeleteList.get(count));
		count++;
	}
	return count;
}

void addParticles(Emitter e, Sphere *particlesList, int sizeParticleList, int numParticles){
	double maxDistance = e._emitterRadius*e._emitterRadius;
	//add particles in influence radius
	//TODO: swap this with pi constant
	double emitterArea = (3.14)*e._emitterRadius*e._emitterRadius;
	double squareSide = sqrt(emitterArea / numParticles);

	int xydiv = (int)(2 * e._emitterRadius / squareSide);
	xydiv++;
	squareSide = (2 * e._emitterRadius / xydiv);

	if (!e._punctual && squareSide <= e._sphereRadius * 2){
		//DataInterface.writeLineToFile(DataInterface.getErrorsFile(), "WARNING : emitting too many particles");
		printf("WARNING : emitting too many particles");
		squareSide = e._sphereRadius*2.1;
	}

	int i = 0;
	double x = e._x - e._emitterRadius + squareSide / 2;
	double y = e._y - e._emitterRadius + squareSide / 2;
	double maxx = e._x + e._emitterRadius - squareSide / 2;
	double maxy = e._y + e._emitterRadius - squareSide / 2;

	bool end = false;


	double deltaY = y - e._y;
	double deltaX = x - e._x;
	double vx = 0;
	double vy = 0;
	int sayac = 0;

	do {

		x = e._x - e._emitterRadius + squareSide / 2;
		y = e._y - e._emitterRadius + squareSide / 2;

		while ((x < maxx) && !end){
			y = e._y - e._emitterRadius + squareSide / 2;
			while ((y < maxy) && !end){
				deltaY = y - e._y;
				deltaX = x - e._x;
				if (deltaX*deltaX + deltaY*deltaY <= maxDistance){
					// we do not accept negative speed
					// if x == _x and y==_y, speed and angle are zero
					if (e._initV > 0){
						if (y == e._y){
							vx = e._initV; if (x < e._x) vx *= -1;
						}
						else if (x == e._x){
							vy = e._initV; if (y < e._y) vy *= -1;
						}
						else{
							vx = sqrt((e._initV*e._initV) / (1 + (deltaY*deltaY) / (deltaX*deltaX)));
							if ((deltaX)<0) vx *= -1;
							vy = vx*deltaY / deltaX;
						}
					}
					//TODO if punctual, the initial speed must be defined, in the meantime it will be zero 
					if (e._punctual)
						//TODO: bunlar exception atcak taþarsa düzelt.
						init_sphere2D(&particlesList[sizeParticleList++], e._x, e._y, e._sphereRadius, vx, vy, e._color);
						//particlesList.add(new Sphere(_x, _y, _sphereRadius, vx, vy, _color));
					else 
						init_sphere2D(&particlesList[sizeParticleList++], x, y, e._sphereRadius, vx, vy, e._color);
					i++;
					if (i >= numParticles) end = true;
				}
				y += squareSide;
			}
			x += squareSide;
		}

	} while (i < numParticles);
}

char* getDescription(){
	//string s = SphereEmitter::getDescription();
	//s += "amplitude (particle/timestep): " + std::to_string(_amplitude) + "\n";
	return "hello world\n";
}