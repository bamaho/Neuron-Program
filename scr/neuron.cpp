#include "neuron.hpp"
#include "parameters.hpp"

#include <vector>
#include <cmath>

using namespace std;

	Neuron::Neuron()
	:membranePotential(INITIAL_MEMBRANE_POTENTIAL)
	{}
	
	double Neuron::getMembranePotential() const
	{	return membranePotential;	}
	
	size_t Neuron::getNumberOfSpikes() const
	{	return spikes.size();	}
	
	std::vector<double> Neuron::getSpikeTime() const	//Vector is not the appropriate choice
	{	return spikes;	}
	
	bool Neuron::isRefractory(double currentSimulationTime) const	//If there haven't occured any spikes yet or the latest spike took place and the neuron has in the meantime undergone a complete refractory state, then the neuron isn't refractory
	{	if(spikes.empty() or ((currentSimulationTime - spikes.back())>=	REFRACTION_TIME))//do I account for one time twice? 
		{	return false;	}
		else { return true; }
	}
	
	void Neuron::spike(double currentSimulationTime)
	{
		spikes.push_back(currentSimulationTime);
		membranePotential = 0;
	}
	
	void Neuron::update()	//Is invoked at each cycle of the simulation and makes the neutron evolve in the course of time
	{}

	void Neuron::updateMembranePotential(double inputCurrent)
	{
		double membraneResistance(TIME_CONSTANT_TAU/NUMBER_OF_CONNECTIONS_FROM_NEURONS_C);//Is this the right place?
	// inter
//membranePotential = //
	}
