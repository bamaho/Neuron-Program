#ifndef NETWORK_H
#define NETWORK_H

#include "parameters.hpp"
//#include "network.hpp"
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
	
	/// A constructor.
	/** Initializes a neuron network by creating 12'500 neurons among those 2'500 are inhibitory and the other 10'000 exitatory.
		Each one of them receives a fixed number of connections from both inhibitory and excitatory presynaptic neuron that are chosen randomly. */
	Network();
	
	/// A destructor which deletes all neurons of the network.
	~Network();
	
	/// A method updating all of the network's neuron by one step which is used in the main loop.
	void update();
	
	/// A getter of the spiking times of all neurons, allows to retreive data
	std::vector< std::vector<unsigned int> > getSpikeTimes();
	
	//print data
	/**Prints each neuron's spike times and neuron id in a file of given name. 
	 * @param nameOfFile, a string*/
	void printSimulationData(const std::string& nameOfFile) const;
	
	private:
	std::array<Neuron*, TOTAL_NUMBER_OF_NEURONS_N> neurons; ///< A container carrying the neurons forming the network, an array of pointers to neurons.
	
};


#endif
