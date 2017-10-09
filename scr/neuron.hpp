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
	//std::vector<double> getSpikeTime() const;	//Is this function necessary? 
	bool isRefractory(double currentSimulationTime) const; 	//returns as a function of the current simulation time if the neuron is in a refractory state by comparing it to the time of the last spike and the refraction time
	
	void spike(double currentSimulationTime);	//stores the spikeing time and sets the membrane potential to zero
	void updateMembranePotential(double inputCurrent);	//Calculates and alters the new membrane Potential as a function of the current membrane potential and the input current
	
	void update(double simulationTime);	//Could be invoked at each cycle of the simulation and makes the neutron evolve in the course of time, the code that is currently in the loop of the main should be reorganized within the body of ths function
	
	void printSpikingTimes(const std::string& nameOfFile) const;	//stores the values of hte spikes
	
	private:
	
	double membranePotential;
	std::vector<double> spikes; //a vector is not the appropriate choice...a list would provide the required functions as well

};


#endif
