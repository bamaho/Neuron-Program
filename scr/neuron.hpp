#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class Neuron
{
	public:
	
	Neuron();
	
	double getMembranePotential() const;
	size_t getNumberOfSpikes() const;
	//std::vector<double> getSpikeTime() const;	//Is this function necessary? Vector is not the appropriate choice
	
	bool isRefractory(double currentSimulationTime) const;
	//void setInRefractoryState();
	
	void spike(double currentSimulationTime);	//stores the spikeing time and sets the membrane potential to zero
	
	void update();	//Is invoked at each cycle of the simulation and makes the neutron evolve in the course of time
	void updateMembranePotential(double inputCurrent);	//Calculates and alters the new membrane Potential as a function of the current membrane potential and the input current
	
	void printSpikingTimes(const std::string& nameOfFile) const;
	
	private:
	
	double membranePotential;
	std::vector<double> spikes;

};


#endif
