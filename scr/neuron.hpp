#ifndef NEURON_H
#define NEURON_H

#include "parameters.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <list>
#include <array>

class Neuron
{
	public:
	
	Neuron();
	
	//getters
	double getMembranePotential() const;
	size_t getNumberOfSpikes() const;
	
	//update
	void update();	//Is invoked at each cycle of the simulation and makes the neutron evolve in the course of time
	
	bool isRefractory(unsigned int currentSimulationTime) const; 	//returns, as a function of the current simulation time, if the neuron is in a refractory state by comparing it to the time of the last spike and the refraction time
	void spike(unsigned int currentSimulationTime);	//stores the spikeing time and sets the membrane potential to zero
	void receiveSpike(unsigned int localTimeOfSpikingNeuron); //this function of a connected neuron is called, if the neuron spikes
	void updateMembranePotential();	//Calculates and alters the new membrane Potential as a function of the current membrane potential and the input current
	void updateRingBuffer(); //updates the ring buffer, deletes the last element and adds an empty one in the front
	void reinitializeCurrentRingBufferElement();
	bool indexReachedEndOfRingBuffer() const;
	void setInputCurrent(double externalCurrent);
	
	//print data
	void printSpikingTimes(const std::string& nameOfFile) const;	//stores the values of the attribute "spikes" in a file
	
	//Network
	void addTarget(Neuron* target);	//allows to establish a connection between the neuron and another neuron, so that the other one receives its spikes
	
	//Testing
	std::vector<unsigned int> getSpikeTime() const;	//This function isn't necessary
	std::vector<unsigned int> getArrivingSpikesTimes() const;
	
	private:
	
	double membranePotential;
	double inputCurrent;
	std::vector<unsigned int> spikes; //a container to store the spiking times, a vector is not the appropriate choice...a list would provide the required functions as well
	std::vector<Neuron*> targets;	//Neurons on which an eventual spike of the current neuron has an impact
	
	unsigned int internalTime;	//second clock, allows to synchronize the times between the neurons, otherwise a problem arises when it comes to distinguishing between alrady updated and not yet updated neurons in neuron interactions
	
	//std::list<unsigned int> numberOfSpikes; //ring-buffer: the first element always corresponds to the current one and the last one to the least recent one, stores how many spikes arrive
	std::array<unsigned int, SIGNAL_DELAY_D + 1> incomingSpikes; //ring buffer, one additional element is required for the neuron to arrive with the right delay
	size_t currentIndexRingBuffer; // has to be always between 0 and (the signal delay in steps -1)
	
	//Testing of ring buffer
	std::vector<unsigned int> arrivingSpikesTimes;
};


#endif
