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
	
	//setters
	void setInputCurrent(double externalCurrent);
	
	//update, and related functions
	void update();	//Is invoked at each cycle of the simulation and makes the neutron evolve in the course of time
	
	bool isRefractory() const; 	//returns if the neuron is in a refractory state by comparing internal time to the time of the last spike and the refraction time
	void spike();	//stores the spikeing time and sets the membrane potential to zero
	void receiveSpike(unsigned int localTimeOfSpikingNeuron); //this function of a connected neuron is called, if the neuron spikes
	void updateMembranePotential();	//Calculates and sets the new membrane potential as a function of the current membrane potential and the input current
	void updateRingBuffer(); //updates the ring buffer, deletes the last element and adds an empty one in the front
	void reinitializeCurrentRingBufferElement(); //sets the current ring buffer element to zero
	bool indexReachedEndOfRingBuffer() const; //could be avoided by using a modulo
	
	
	//print data
	void printSpikingTimes(const std::string& nameOfFile) const;	//stores the values of the attribute "spikes" in a file
	
	//Network
	void addTarget(Neuron* target);	//allows to establish a connection between the neuron and another neuron, so that the other one receives its spikes
	
	//Testing, these function aren't necessary otherwise
	std::vector<unsigned int> getSpikeTime() const;
	std::vector<unsigned int> getArrivingSpikesTimes() const;
	
	private:
	
	double membranePotential;
	double inputCurrent; //is zero if not by means of the setter altered in the main
	std::vector<unsigned int> spikes; //a container to store the spiking times, a vector is not the appropriate choice...a list would provide the required functions as well
	std::vector<Neuron*> targets;	//Neurons on which an eventual spike of the current neuron has an impact
	
	unsigned int internalTime;	//second clock, allows to synchronize the times between the neurons, otherwise a problem arises when it comes to distinguishing between alrady updated and not yet updated neurons in neuron interactions
	
	std::array<unsigned int, SIGNAL_DELAY_D + 1> incomingSpikes; //ring buffer, one additional element is required for the neuron to arrive with the right delay, in this version J is always constant
	size_t currentIndexRingBuffer; // has to be always between 0 and (the signal delay in steps -1)
	
	//Testing of ring buffer, fulfills no other function
	std::vector<unsigned int> arrivingSpikesTimes;
};


#endif
