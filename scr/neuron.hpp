#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <vector>

class Neuron
{
	public:
	
	Neuron();
	
	void update();
	size_t getNumberOfSpike();
	
	private:
	
	double membranePotential;
	std::vector<double> spikes;
	
	//double 
};


#endif
