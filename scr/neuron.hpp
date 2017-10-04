#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <vector>

class Neuron
{
	public:
	
	Neuron();
	
	double getMembranePotential();
	size_t getNumberOfSpikes();
	std::vector<double> getSpikeTime();	//Vector is not the appropriate choice
	
	void update();	//Is invoked at each cycle of the simulation and makes the neutron evolve in the course of time
	
	
	
	private:
	
	double membranePotential;
	std::vector<double> spikes;
	
	//double 
};


#endif
