#include "neuron.hpp"
#include "parameters.hpp"

//#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include <array>
#include <cassert>

using namespace std;

	Neuron::Neuron()
	:membranePotential(INITIAL_MEMBRANE_POTENTIAL)
	,inputCurrent(0)
	,internalTime(INITIAL_TIME) //Might be more appropriate to use the time of creation as an argument by default. Otherwise the assumption is, that it gets created at the beginning of the simulation
	{ for (auto& element: incomingSpikes){element =0;} }	//Initialized the ring buffer entries to zero
	
	
	
	double Neuron::getMembranePotential() const
	{ return membranePotential; }
	
	size_t Neuron::getNumberOfSpikes() const
	{ return spikes.size(); }
	
	
	
	void Neuron::setInputCurrent(double externalCurrent)
	{inputCurrent = externalCurrent;}
	
	
	
	void Neuron::update()	//Is invoked at each cycle of the simulation and makes the neutron evolve in the course of time
	{
		if(not isRefractory())
		{
			if(getMembranePotential() >= MEMBRANE_POTENTIAL_THRESHOLD)
			{
				spike();
			}
			else
			{
				updateMembranePotential();
			}
		}
		reinitializeCurrentRingBufferElement();
		internalTime += NUMBER_OF_TIME_STEPS_PER_SIMULATION_CYCLE;
	}

	
	bool Neuron::isRefractory() const	//If there haven't occured any spikes yet or the latest spike took place and the neuron has in the meantime undergone a complete refractory state, then the neuron isn't refractory
	{	
		return not(spikes.empty() or ((internalTime - spikes.back())>=	REFRACTION_TIME));//do I account for one point in time twice? 
	}
	
	void Neuron::spike()	//stores the spiking time, sets the membrane potential to sends a signal to the connected neurons
	{
		//cerr << "Debug Ring Buffer: spike at time " << currentSimulationTime << endl;
		spikes.push_back(internalTime);
		membranePotential = RESET_MEMBRANE_POTENTIAL;
		if(not targets.empty())
		{
			for(auto& targetNeuron: targets)
			{
				if(targetNeuron != nullptr) {
                targetNeuron->receiveSpike(internalTime);
				}
			
			}
		}
	}
	
	void Neuron::receiveSpike(unsigned int localTimeOfSpikingNeuron)
	{	
		incomingSpikes[timeToRingBufferIndex(SIGNAL_DELAY_D+localTimeOfSpikingNeuron)] += 1;	//writes the incoming spike at curent time + the signal delay into the ring buffer, to be altered
	}	
		


	void Neuron::updateMembranePotential()	//adding a second argument "int numberOfSpikes" would be another option
	{
		//The following lines are useful for testing only, store the times of arriving spikes, that have an impact on membrane potential, testing functions should be implemented by getters
		for(size_t i(0); i<incomingSpikes[timeToRingBufferIndex(internalTime)]; i++)
		{
			arrivingSpikesTimes.push_back(internalTime);
		}
		//cerr << "Debug Ring Buffer : number of Spikes in the Ring Buffer element that is read " <<incomingSpikes[currentIndexRingBuffer] << " at time " << internalTime << endl;
		(membranePotential *= INTERMEDIATE_RESULT_UPDATE_POTENTIAL) += (inputCurrent*MEMBRANE_RESISTANCE_R*(1-INTERMEDIATE_RESULT_UPDATE_POTENTIAL)+SPIKE_AMPLITUDE_J*readRingBuffer());
	}
	
	unsigned int Neuron::readRingBuffer() const //reads the current entry
	{
		return incomingSpikes[timeToRingBufferIndex(internalTime)];
	}
	
	void Neuron::reinitializeCurrentRingBufferElement()
	{
		incomingSpikes[timeToRingBufferIndex(internalTime)] = 0;
	}
	
	size_t Neuron::timeToRingBufferIndex(unsigned int time) const
	{
		const size_t index((time)%(SIGNAL_DELAY_D+1));
		assert(index < incomingSpikes.size());
		return index;
	}
	
	
	void Neuron::printSpikingTimes(const string& nameOfFile) const //prints the registered times when spikes ocurred into a file with a name to indicate
	{
		ofstream out(nameOfFile);
		
		if(out.fail())
		{
			cerr << "Error: impossible to write in file " << nameOfFile << endl;//(Too) simplistic solution!
		}
		
		else
		{
			out << "Spikes: " << endl;
			
			for(auto const& spike: spikes)
			{
				out << spike*MIN_TIME_INTERVAL_H << endl; //prints the times, not in number of steps, but converted milliseconds
			}
		}
		out.close();
	}

	void Neuron:: addTarget(Neuron* target)	//not the most elegant of solutions, since with this conception it is the users oblication to allocate space in the memory, the usage of unique pointers might have been more appropriate
	{
		if(target != nullptr) {
			targets.push_back(target);
		}
	}
	
	//Testing
	
		std::vector<unsigned int> Neuron::getSpikeTime() const	//Vector is not the appropriate choice
	{	return spikes;	}
	
	std::vector<unsigned int> Neuron::getArrivingSpikesTimes() const	//registers when spikes arrive, has except forr testing no other pu
	{	return arrivingSpikesTimes;	}
	
