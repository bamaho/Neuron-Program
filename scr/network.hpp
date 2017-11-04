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
	//std::vector< std::vector<unsigned int> > getSpikeTimes();
	
	//print data
	/**Prints each neuron's spike times and neuron id in a file of given name using the private function print simulation data.
	 * @param nameOfFile, a string*/
	void printSimulationData(const std::string& nameOfFile) const;
	/**Prints each neuron's spike times that are in an interval defined in the simulation's parameter file and neuron id in a file of given name using the private function print simulation data.
	 * @param nameOfFile, a string*/
	void printSimulationDataWithinTimeInterval(const std::string& nameOfFile) const;
	
	//void printSimulationDataWithinTimeInterval(const std::string& nameOfFile, unsigned int beginInterval, unsigned int endInterval) const;
		
	/**Calculates the mean spike rate of the network's neurons in an interval to indicate.
	 * @param begin of the interval to investigate in steps, an unsigned int
	 * @param begin of the interval to investigate in steps, an unsigned int*/ 
	double getMeanSpikeRateInInterval(unsigned int beginInterval, unsigned int endInterval) const;
	
	private:
	std::array<Neuron*, TOTAL_NUMBER_OF_NEURONS_N> neurons; ///< A container carrying the neurons forming the network, an array of pointers to neurons.
	
	/**An auxiliary function for printing the network's spike times to a file that allows to avoid the duplication of code.
	 * @see printSimulationData(const std::string& nameOfFile)
	 * @see printSimulationDataWithinTimeInterval
	 * @param nameOfFile, a string
	 * @param a member function that yields an iterator on a vector<unsigned int> pointing the first element that is printed
	 * @param a member function that yields an iterator on a vector<unsigned int> pointing the last element that is printed
	 */
	void printSimulationData(const std::string& nameOfFile, std::vector<unsigned int>::const_iterator (Network::*getIteratorBegin)(unsigned int) const , std::vector<unsigned int>::const_iterator (Network::*getIteratorEnd)(unsigned int) const ) const;
	
	/**An auxiliary function for printing the network's spike times to a file that returns an iterator pointing on neuron i's first spike time.
	 * @see printSimulationData(const std::string& nameOfFile)
	 * @param neuron identifier, an unsigned int */
	std::vector<unsigned int>::const_iterator getIteratorToBegin(unsigned int i) const;//change i
	
	/**An auxiliary function for printing the network's spike times to a file that returns an iterator pointing on neuron i's last spike time.
	 * @see printSimulationData(const std::string& nameOfFile)
	 * @param neuron identifier, an unsigned int */
	std::vector<unsigned int>::const_iterator getIteratorToEnd(unsigned int i) const;
	
	/**An auxiliary function for printing the network's spike times to a file that returns an iterator pointing on neuron i's first spike time that lies within an interval defined in the parameter file.
	 * @see printSimulationData(const std::string& nameOfFile)
	 * @param neuron identifier, an unsigned int */
	std::vector<unsigned int>::const_iterator getIteratorToBeginInterval(unsigned int i) const;
	std::vector<unsigned int>::const_iterator getIteratorToEndInterval(unsigned int i) const;
	
};


#endif
