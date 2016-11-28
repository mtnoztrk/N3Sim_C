/*
N3Sim: A Simulation Framework for Diffusion-based Molecular Communication
Copyright (C) 2011 Iñaki Pascual - N3CAT (UPC)

N3Cat (NaNoNetworking Center in Catalunya)
Universitat Politècnica de Catalunya (UPC)
Jordi Girona, 1-3, Mòdul D6 (Campus Nord)
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

/*package domain.controller;

import data.DataInterface;
import domain.emitters.ParticleEmitter;
import domain.emitters.NoiseSphereEmitter;
import domain.emitters.PulseSphereEmitter;
import domain.emitters.FromFileSphereEmitter3D;
import domain.emitters.RectangularSphereEmitter;
import domain.emitters.FromFileSphereEmitter;
import domain.emitters.ImmediatelyReleasingEmitter;
import domain.receivers.ParticleReceiver;
import domain.receivers.SphericalReceiver;
import domain.receivers.SphericalReceiver3D;
import domain.receivers.SquareReceiver;
import domain.receivers.HarvestingReceiver;
import domain.receivers.HarvestingSphericalReceiver;
import domain.receivers.UnlimitedHarvestingSphericalReceiver;
import domain.receivers.RatioLimitedHarvestingSphericalReceiver;
import domain.nodes.SimpleNode;
import domain.nodes.ImmediatelyReleasingNode;
import domain.nodes.ImmediatelyPulseReleasingNode;
import domain.space.Simulator;
*/

#ifndef DOMAININTERFACE_H
#define DOMAININTERFACE_H


#include "DataInterface.h"
#include "ParticleEmitter.h"
#include "NoiseSphereEmitter.h"
#include "PulseSphereEmitter.h"
#include "FromFileSphereEmitter3D.h"
#include "RectangularSphereEmitter.h"
#include "FromFileSphereEmitter.h"
#include "ImmediatelyReleasingEmitter.h"
#include "ParticleReceiver.h"
#include "SphericalReceiver.h"
#include "SphericalReceiver3D.h"
#include "SquareReceiver.h"
#include "HarvestingReceiver.h"
#include "HarvestingSphericalReceiver.h"
#include "UnlimitedHarvestingSphericalReceiver.h"
#include "RatioLimitedHarvestingSphericalReceiver.h"
#include "SimpleNode.h"
#include "ImmediatelyReleasingNode.h"
#include "ImmediatelyPulseReleasingNode.h"
#include "Simulator.h"

#include <string>
using namespace std;
/*public final class domaininterface*/
class DomainInterface {

	Simulator _simulator;

public:
	void createSimulator(string, bool, bool, bool, double, double, double, double, int, double, double, double, bool, bool, double);
	void createSimulator(string, bool, bool, bool, double, double, double, double, int, int, double, double, double, bool, bool, double);
	void createPulseSphereEmitter(double, double, double, double, double, double, double, double, bool, bool, string);
	void createRectangularSphereEmitter(double, double, double, double, double, double, double, double, bool, bool, int, int, string);
	void createNoiseSphereEmitter(double, double, double, double, double, double, double, double, bool, bool, string);
	void createWaveFromFileSphereEmitter(double, double, double, double, double, double, double, double, bool, bool, string, int, string);
	void createPunctualWaveFromFile3DSphereEmitter(double, double, double, double, double, double, double, double, double, bool, bool, string, int, string);

	void createSquareReceiver(string, double, bool, bool, double);
	void createSquareReceiver(string, double, double, bool, bool, double);
	void createSquareReceiver(string, double, double, double, bool, bool, double);

	void createSphericalReceiver(string, double, bool, bool, double);
	void createSphericalReceiver(string, double, double, bool, bool, double);
	void create3DSphericalReceiver(string, double, double, double, bool, bool, double);

	void createSimpleNode(string, double, int, int);
	void createSimpleNode(string, double, double, int, int);
	void createSimpleNode(string, double, double, double, int, int);

	void createImmediatelyReleasingNode(string, double, int, int, int, int, double, double, double, bool, bool, string, int);
	void createImmediatelyReleasingNode(string, double, double, int, int, int, int, double, double, double, bool, bool, string, int);
	void createImmediatelyReleasingNode(string, double, double, double, int, int, int, int, double, double, double, bool, bool, string, int);

	void createImmediatelyPulseReleasingNode(string, double, int, int, int, int, double, double, double, bool, bool, string, double, int);
	void createImmediatelyPulseReleasingNode(string, double, double, int, int, int, int, double, double, double, bool, bool, string, double, int);
	void createImmediatelyPulseReleasingNode(string, double, double, double, int, int, int, int, double, double, double, bool, bool, string, double, int);

	void addPulseSphereEmitterToNode(string, double, double, double, double, double, double, double, bool, bool, string);
	void addPulseSphereEmitterToNode(string, double, double, double, double, double, double, double, double, bool, bool, string);
	void addPulseSphereEmitterToNode(string, double, double, double, double, double, double, double, double, double, bool, bool, string);

	void addRectangularSphereEmitterToNode(string, double, double, double, double, double, double, double, bool, bool, int, int, string);
	void addRectangularSphereEmitterToNode(string, double, double, double, double, double, double, double, double, bool, bool, int, int, string);
	void addRectangularSphereEmitterToNode(string, double, double, double, double, double, double, double, double, double, bool, bool, int, int, string);

	void addNoiseSphereEmitterToNode(string, double, double, double, double, double, double, double, bool, bool, string);
	void addNoiseSphereEmitterToNode(string, double, double, double, double, double, double, double, double, bool, bool, string);
	void addNoiseSphereEmitterToNode(string, double, double, double, double, double, double, double, double, double, bool, bool, string);

	void addWaveFromFileSphereEmitterToNode(string, double, double, double, double, double, double, double, bool, bool, string, int, string);
	void addWaveFromFileSphereEmitterToNode(string, double, double, double, double, double, double, double, double, bool, bool, string, int, string);
	void addWaveFromFileSphereEmitterToNode(string, double, double, double, double, double, double, double, double, double, bool, bool, string, int, string);

	void addPunctualWaveFromFile3DSphereEmitterToNode(string, double, double, double, double, double, double, double, double, double, bool, bool, string, int, string);
	void addSquareReceiverToNode(string, double, double, bool, bool, double);
	void addSphericalReceiverToNode(string, double, double, bool, bool, double);
	void add3DSphericalReceiverToNode(string, double, double, double, bool, bool, double);
	void addHarvestingSphericalReceiverToNode(string, double, double, bool, double, int);
	void addUnlimitedHarvestingSphericalReceiverToNode(string, double, double, bool, double);
	void addRatioLimitedHarvestingSphericalReceiverToNode(string, double, double, bool, double, double);
	void startSimulation();
	double getTime();
	void logError(string);

};

// 1D Simulator
void DomainInterface::createSimulator(string path, bool graphics, bool infoFile, bool activeCollision, double BMFactor, double inertiaFactor,
	double time, double timeStep, int xSize, double D, double bgConcentration, double radius, bool boundedSpace,
	bool constantBGConcentration, double constantBGConcentrationWidth)
{
	//_simulator = new Simulator(path, graphics, infoFile, time, timeStep);
	Simulator _simulator(path, graphics, infoFile, time, timeStep);
	_simulator.createSpace(xSize, D, bgConcentration, radius, activeCollision, BMFactor, inertiaFactor, boundedSpace,
		constantBGConcentration, constantBGConcentrationWidth, infoFile);
};


// 2D Simulator
void DomainInterface::createSimulator(string path, bool graphics, bool infoFile, bool activeCollision, double BMFactor, double inertiaFactor,
	double time, double timeStep, int xSize, int ySize, double D, double bgConcentration, double radius, bool boundedSpace,
	bool constantBGConcentration, double constantBGConcentrationWidth)
{
	Simulator _simulator(path, graphics, infoFile, time, timeStep);
	_simulator.createSpace(xSize, ySize, D, bgConcentration, radius, activeCollision, BMFactor, inertiaFactor, boundedSpace,
		constantBGConcentration, constantBGConcentrationWidth, infoFile);
};

// TODO: 3D simulatoru yazarken asagidaki kod blogunu ac
// 3D Simulator
// public void createSimulator(string path, bool graphics, bool infoFile, bool activeCollision, double BMFactor, double inertiaFactor, 
//        double time, double timeStep, int xSize, int ySize, int zSize, double D, double bgConcentration, double radius, bool boundedSpace, 
//        bool constantBGConcentration, double constantBGConcentrationWidth)
// {
//    _simulator = new Simulator(path, graphics, infoFile, time, timeStep);
// 	_simulator.createSpace(xSize, ySize, zSize, D, bgConcentration, radius, activeCollision, BMFactor, inertiaFactor, boundedSpace, 
//            constantBGConcentration, constantBGConcentrationWidth, infoFile);
// }    


void DomainInterface::createPulseSphereEmitter(double x, double y, double startTime, double endTime, double amplitude, double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, string color){
	ParticleEmitter *e;
	PulseSphereEmitter b(x, y, startTime, endTime, amplitude, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color);
	e = &b;
	_simulator.addEmitter(e);
};

void DomainInterface::createRectangularSphereEmitter(double x, double y, double startTime, double endTime, double amplitude, double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, int period, int timeOn, string color){
	ParticleEmitter e = new RectangularSphereEmitter(x, y, startTime, endTime, amplitude, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, period, timeOn, color);
	_simulator.addEmitter(e);
};

void DomainInterface::createNoiseSphereEmitter(double x, double y, double startTime, double endTime, double amplitude, double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, string color){
	ParticleEmitter e = new NoiseSphereEmitter(x, y, startTime, endTime, amplitude, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color);
	_simulator.addEmitter(e);
};

void DomainInterface::createWaveFromFileSphereEmitter(double x, double y, double startTime, double endTime, double amplitude, double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, string file, int size, string color){
	ParticleEmitter e = new FromFileSphereEmitter(x, y, startTime, endTime, amplitude, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, file, size, color);
	_simulator.addEmitter(e);
};

void DomainInterface::createPunctualWaveFromFile3DSphereEmitter(double x, double y, double z, double startTime, double endTime, double amplitude,
	double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, string file, int size4,
	string color) {
	ParticleEmitter e = new FromFileSphereEmitter3D(x, y, z, startTime, endTime, amplitude, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, file, size4, color);
	_simulator.addEmitter(e);
};

void DomainInterface::createSquareReceiver(string name, double x, bool absorb, bool accumulate, double side){
	ParticleReceiver r = new SquareReceiver(name, x, absorb, accumulate, side);
	_simulator.addReceiver(r);
}; // 1D    

void DomainInterface::createSquareReceiver(string name, double x, double y, bool absorb, bool accumulate, double side){
	ParticleReceiver r = new SquareReceiver(name, x, y, absorb, accumulate, side);
	_simulator.addReceiver(r);
}; // 2D

void DomainInterface::createSquareReceiver(string name, double x, double y, double z, bool absorb, bool accumulate, double side){
	ParticleReceiver r = new SquareReceiver(name, x, y, z, absorb, accumulate, side);
	_simulator.addReceiver(r);
}; // 3D    

void DomainInterface::createSphericalReceiver(string name, double x, bool absorb, bool accumulate, double radius){
	ParticleReceiver r = new SphericalReceiver(name, x, absorb, accumulate, radius);
	_simulator.addReceiver(r);
}; // 1D    

void DomainInterface::createSphericalReceiver(string name, double x, double y, bool absorb, bool accumulate, double radius){
	ParticleReceiver r = new SphericalReceiver(name, x, y, absorb, accumulate, radius);
	_simulator.addReceiver(r);
}; // 2D

void DomainInterface::create3DSphericalReceiver(string name, double x, double y, double z, bool absorb, bool accumulate, double rradius) {
	ParticleReceiver r = new SphericalReceiver3D(name, x, y, z, absorb, accumulate, rradius);
	_simulator.addReceiver(r);
};

void DomainInterface::createSimpleNode(string name, double x, int numberOfEmitters, int numberOfReceivers) {
	SimpleNode n = new SimpleNode(name, x, numberOfEmitters, numberOfReceivers);
	_simulator.addNode(n);
}; // 1D

void DomainInterface::createSimpleNode(string name, double x, double y, int numberOfEmitters, int numberOfReceivers) {
	SimpleNode n = new SimpleNode(name, x, y, numberOfEmitters, numberOfReceivers);
	_simulator.addNode(n);
}; // 2D

void DomainInterface::createSimpleNode(string name, double x, double y, double z, int numberOfEmitters, int numberOfReceivers) {
	SimpleNode n = new SimpleNode(name, x, y, z, numberOfEmitters, numberOfReceivers);
	_simulator.addNode(n);
}; // 3D

void DomainInterface::createImmediatelyReleasingNode(string name, double x, int initialSupply, int reservoirCapacity, int numberOfEmitters, int numberOfReceivers,
	double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, string color, int harvesterIndex)
{
	ImmediatelyReleasingNode n = new ImmediatelyReleasingNode(name, x, initialSupply, reservoirCapacity, numberOfEmitters, numberOfReceivers,
		sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color, harvesterIndex);
	ParticleEmitter e = new ImmediatelyReleasingEmitter(x, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color);
	_simulator.addNode(n);
	_simulator.addEmitterToNode(name, e);
}; // 1D

void DomainInterface::createImmediatelyReleasingNode(string name, double x, double y, int initialSupply, int reservoirCapacity, int numberOfEmitters, int numberOfReceivers,
	double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, string color, int harvesterIndex)
{
	ImmediatelyReleasingNode n = new ImmediatelyReleasingNode(name, x, y, initialSupply, reservoirCapacity, numberOfEmitters, numberOfReceivers,
		sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color, harvesterIndex);
	ParticleEmitter e = new ImmediatelyReleasingEmitter(x, y, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color);
	_simulator.addNode(n);
	_simulator.addEmitterToNode(name, e);
}; // 2D 

void DomainInterface::createImmediatelyReleasingNode(string name, double x, double y, double z, int initialSupply, int reservoirCapacity, int numberOfEmitters, int numberOfReceivers,
	double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, string color, int harvesterIndex)
{
	ImmediatelyReleasingNode n = new ImmediatelyReleasingNode(name, x, y, z, initialSupply, reservoirCapacity, numberOfEmitters, numberOfReceivers,
		sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color, harvesterIndex);
	ParticleEmitter e = new ImmediatelyReleasingEmitter(x, y, z, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color);
	_simulator.addNode(n);
	_simulator.addEmitterToNode(name, e);
}; // 3D

void DomainInterface::createImmediatelyPulseReleasingNode(string name, double x, int initialSupply, int reservoirCapacity, int numberOfEmitters, int numberOfReceivers,
	double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, string color, double amplitude, int harvesterIndex)
{
	ImmediatelyPulseReleasingNode n = new ImmediatelyPulseReleasingNode(name, x, initialSupply, reservoirCapacity, numberOfEmitters, numberOfReceivers,
		sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color, amplitude, harvesterIndex);
	// ImmediatelyReleasingEmitter e = new ImmediatelyReleasingEmitter(x, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color);
	_simulator.addNode(n);
	// _simulator.addEmitterToNode(name, e);

}; // 1D

void DomainInterface::createImmediatelyPulseReleasingNode(string name, double x, double y, int initialSupply, int reservoirCapacity, int numberOfEmitters, int numberOfReceivers,
	double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, string color, double amplitude, int harvesterIndex)
{
	ImmediatelyPulseReleasingNode n = new ImmediatelyPulseReleasingNode(name, x, y, initialSupply, reservoirCapacity, numberOfEmitters, numberOfReceivers,
		sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color, amplitude, harvesterIndex);
	ParticleEmitter e = new ImmediatelyReleasingEmitter(x, y, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color);
	_simulator.addNode(n);
	_simulator.addEmitterToNode(name, e);

}; // 2D

void DomainInterface::createImmediatelyPulseReleasingNode(string name, double x, double y, double z, int initialSupply, int reservoirCapacity, int numberOfEmitters, int numberOfReceivers,
	double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, string color, double amplitude, int harvesterIndex)
{
	ImmediatelyPulseReleasingNode n = new ImmediatelyPulseReleasingNode(name, x, y, z, initialSupply, reservoirCapacity, numberOfEmitters, numberOfReceivers,
		sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color, amplitude, harvesterIndex);
	// ParticleEmitter e = new ImmediatelyReleasingEmitter(x, y, z, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color);
	_simulator.addNode(n);
	// _simulator.addEmitterToNode(name, e);
}; // 3D

void DomainInterface::addPulseSphereEmitterToNode(string nodeName, double x, double startTime, double endTime, double amplitude, double sphereRadius,
	double emitterRadius, double initV, bool punctual, bool concentrationEmitter, string color)
{
	ParticleEmitter e = new PulseSphereEmitter(x, startTime, endTime, amplitude, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color);
	_simulator.addEmitterToNode(nodeName, e);
}; // 1D

void DomainInterface::addPulseSphereEmitterToNode(string nodeName, double x, double y, double startTime, double endTime, double amplitude, double sphereRadius,
	double emitterRadius, double initV, bool punctual, bool concentrationEmitter, string color)
{
	ParticleEmitter e = new PulseSphereEmitter(x, y, startTime, endTime, amplitude, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color);
	_simulator.addEmitterToNode(nodeName, e);
}; // 2D

void DomainInterface::addPulseSphereEmitterToNode(string nodeName, double x, double y, double z, double startTime, double endTime, double amplitude, double sphereRadius,
	double emitterRadius, double initV, bool punctual, bool concentrationEmitter, string color)
{
	ParticleEmitter e = new PulseSphereEmitter(x, y, z, startTime, endTime, amplitude, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color);
	_simulator.addEmitterToNode(nodeName, e);
}; // 3D

void DomainInterface::addRectangularSphereEmitterToNode(string nodeName, double x, double startTime, double endTime, double amplitude,
	double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, int period, int timeOn, string color)
{
	ParticleEmitter e = new RectangularSphereEmitter(x, startTime, endTime, amplitude, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, period, timeOn, color);
	_simulator.addEmitterToNode(nodeName, e);
}; // 1D

void DomainInterface::addRectangularSphereEmitterToNode(string nodeName, double x, double y, double startTime, double endTime, double amplitude,
	double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, int period, int timeOn, string color)
{
	ParticleEmitter e = new RectangularSphereEmitter(x, y, startTime, endTime, amplitude, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, period, timeOn, color);
	_simulator.addEmitterToNode(nodeName, e);
}; // 2D

void DomainInterface::addRectangularSphereEmitterToNode(string nodeName, double x, double y, double z, double startTime, double endTime, double amplitude,
	double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, int period, int timeOn, string color)
{
	ParticleEmitter e = new RectangularSphereEmitter(x, y, z, startTime, endTime, amplitude, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, period, timeOn, color);
	_simulator.addEmitterToNode(nodeName, e);
}; // 3D

void DomainInterface::addNoiseSphereEmitterToNode(string nodeName, double x, double startTime, double endTime, double amplitude,
	double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, string color)
{
	ParticleEmitter e = new NoiseSphereEmitter(x, startTime, endTime, amplitude, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color);
	_simulator.addEmitterToNode(nodeName, e);
}; // 1D

void DomainInterface::addNoiseSphereEmitterToNode(string nodeName, double x, double y, double startTime, double endTime, double amplitude,
	double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, string color)
{
	ParticleEmitter e = new NoiseSphereEmitter(x, y, startTime, endTime, amplitude, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color);
	_simulator.addEmitterToNode(nodeName, e);
}; // 2D

void DomainInterface::addNoiseSphereEmitterToNode(string nodeName, double x, double y, double z, double startTime, double endTime, double amplitude,
	double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, string color)
{
	ParticleEmitter e = new NoiseSphereEmitter(x, y, z, startTime, endTime, amplitude, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color);
	_simulator.addEmitterToNode(nodeName, e);
}; // 3D

void DomainInterface::addWaveFromFileSphereEmitterToNode(string nodeName, double x, double startTime, double endTime, double amplitude,
	double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, string file, int size, string color)
{
	ParticleEmitter e = new FromFileSphereEmitter(x, startTime, endTime, amplitude, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, file, size, color);
	_simulator.addEmitterToNode(nodeName, e);
}; // 1D

void DomainInterface::addWaveFromFileSphereEmitterToNode(string nodeName, double x, double y, double startTime, double endTime, double amplitude,
	double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, string file, int size, string color)
{
	ParticleEmitter e = new FromFileSphereEmitter(x, y, startTime, endTime, amplitude, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, file, size, color);
	_simulator.addEmitterToNode(nodeName, e);
}; // 2D

void DomainInterface::addWaveFromFileSphereEmitterToNode(string nodeName, double x, double y, double z, double startTime, double endTime, double amplitude,
	double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, string file, int size, string color)
{
	ParticleEmitter e = new FromFileSphereEmitter(x, y, z, startTime, endTime, amplitude, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, file, size, color);
	_simulator.addEmitterToNode(nodeName, e);
}; // 3D

void DomainInterface::addPunctualWaveFromFile3DSphereEmitterToNode(string nodeName, double x, double y, double z, double startTime, double endTime, double amplitude, double sphereRadius,
	double emitterRadius, double initV, bool punctual, bool concentrationEmitter, string file, int size4, string color) {
	ParticleEmitter e = new FromFileSphereEmitter3D(x, y, z, startTime, endTime, amplitude, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, file, size4, color);
	_simulator.addEmitterToNode(nodeName, e);
};
/*
public void addImmediatelyReleasingEmitterToNode (string nodeName, double x, double y, double sphereRadius, double emitterRadius,
double initV, bool punctual, bool concentrationEmitter, string color) {
ParticleEmitter e = new ImmediatelyReleasingEmitter(x, y, sphereRadius, emitterRadius, initV, punctual, concentrationEmitter, color);
_simulator.addEmitterToNode(nodeName, e);
}
*/
// TODO eger ileride bir node birden cok receiver icerirse, her receiverin kendi ismini de fonksiyonda gonder
void DomainInterface::addSquareReceiverToNode(string nodeName, double x, double y, bool absorb, bool accumulate, double side) {
	ParticleReceiver r = new SquareReceiver(nodeName, x, y, absorb, accumulate, side);
	_simulator.addReceiverToNode(nodeName, r);

};

void DomainInterface::addSphericalReceiverToNode(string nodeName, double x, double y, bool absorb, bool accumulate, double radius) {
	ParticleReceiver r = new SphericalReceiver(nodeName, x, y, absorb, accumulate, radius);
	_simulator.addReceiverToNode(nodeName, r);
};


void DomainInterface::add3DSphericalReceiverToNode(string nodeName, double x, double y, double z, bool absorb, bool accumulate, double rradius) {
	ParticleReceiver r = new SphericalReceiver3D(nodeName, x, y, z, absorb, accumulate, rradius);
	_simulator.addReceiverToNode(nodeName, r);
};


void DomainInterface::addHarvestingSphericalReceiverToNode(string nodeName, double x, double y, bool accumulate, double radius, int maxHarvestPerIteration) { // absorb already true for this receiver
	HarvestingReceiver r = new HarvestingSphericalReceiver(nodeName, x, y, accumulate, radius, maxHarvestPerIteration);
	_simulator.addReceiverToNode(nodeName, r);
};

void DomainInterface::addUnlimitedHarvestingSphericalReceiverToNode(string nodeName, double x, double y, bool accumulate, double radius) { //, int busyWaiting) { // absorb already true for this receiver
	HarvestingReceiver r = new UnlimitedHarvestingSphericalReceiver(nodeName, x, y, accumulate, radius); //, busyWaiting);
	_simulator.addReceiverToNode(nodeName, r);
};

void DomainInterface::addRatioLimitedHarvestingSphericalReceiverToNode(string nodeName, double x, double y, bool accumulate, double radius, double harvestRatio) { // absorb already true for this receiver
	HarvestingReceiver r = new RatioLimitedHarvestingSphericalReceiver(nodeName, x, y, accumulate, radius, harvestRatio);
	_simulator.addReceiverToNode(nodeName, r);
};

void DomainInterface::startSimulation() {
	_simulator.start();
};

// Deniz Demiray
double DomainInterface::getTime() {

	return _simulator.getTime();

};

void DomainInterface::logError(string errorMsg) {
	DataInterface.writeLineToFile(DataInterface.getErrorsFile(), errorMsg);
};

//WTF ?
//public void createImmediatelyReleasingNode(string name, double x, int initialSupply, int reservoirCapacity, int numberOfEmitters, int numberOfReceivers, double sphereRadius, double emitterRadius, double initV, bool punctual, bool concentrationEmitter, string color, int harvesterIndex) {
//    throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
//}



#endif