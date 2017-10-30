#ifndef EXCITATORY_NEURON_H
#define EXCITATORY_NEURON_H

#include "parameters.hpp"
#include "neuron.hpp"

//#include <array>
//#include <fstream>
//#include <iostream>
//#include <list>
//#include <string>
//#include <vector>


class ExcitatoryNeuron : public Neuron
{
	public:
	
	//constructor
	ExcitatoryNeuron();
	
	double getSpikeAmplitude() const;
	
	
	
	private:
	
	
	
};


#endif
