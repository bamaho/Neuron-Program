#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <list>

class Neuron
{
	public:
	
	Neuron();
	
	double getMembranePotential() const;
	size_t getNumberOfSpikes() const;
	//std::vector<double> getSpikeTime() const;	//Is this function necessary? 
	bool isRefractory(unsigned int currentSimulationTime) const; 	//returns as a function of the current simulation time if the neuron is in a refractory state by comparing it to the time of the last spike and the refraction time
	
	void spike(unsigned int currentSimulationTime);	//stores the spikeing time and sets the membrane potential to zero
	void updateMembranePotential(double inputCurrent);	//Calculates and alters the new membrane Potential as a function of the current membrane potential and the input current
	
	void update(unsigned int simulationTime);	//Could be invoked at each cycle of the simulation and makes the neutron evolve in the course of time, the code that is currently in the loop of the main should be reorganized within the body of ths function
	
	void printSpikingTimes(const std::string& nameOfFile) const;	//stores the values of hte spikes
	
	static void updateRingBuffer(); //updates the ring buffer, deletes the last element and adds an empty one in the front
	
	private:
	
	double membranePotential;
	std::vector<unsigned int> spikes; //a vector is not the appropriate choice...a list would provide the required functions as well
	
	static std::list<unsigned int> numberOfSpikes; //ring-buffer: the first element always corresponds to the current one..., last one to the least recent one, stores how many spikes arrive

};


#endif
