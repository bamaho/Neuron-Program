#include "neuron.hpp"
#include "parameters.hpp"

#include <vector>

using namespace std;

	Neuron::Neuron()
	:membranePotential(INITIAL_MEMBRANE_POTENTIAL)
	{}
	
	double Neuron::getMembranePotential()
	{	return membranePotential;	}
	size_t Neuron::getNumberOfSpikes()
	{	return spikes.size();	}
	std::vector<double> Neuron::getSpikeTime()	//Vector is not the appropriate choice
	{	return spikes;	}
	void Neuron::update()	//Is invoked at each cycle of the simulation and makes the neutron evolve in the course of time
	{}
