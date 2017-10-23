#ifndef NETWORK_H
#define NETWORK_H

#include "parameters.hpp"
#include "network.hpp"
#include "neuron.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <list>
#include <array>


class Network
{
	public:
	Network();
	~Network();
	
	private:
	std::array<Neuron*, TOTAL_NUMBER_OF_NEURONS_N> neurons;
	
};


#endif
