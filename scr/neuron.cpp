#include "neuron.hpp"
#include "parameters.hpp"

#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <list>

using namespace std;

//std::list<unsigned int> Neuron::numberOfSpikes(15,0);//until the delay arrives it takes 1.5 milliseconds...and the time step of the simulation is 0.1

	Neuron::Neuron()
	:membranePotential(INITIAL_MEMBRANE_POTENTIAL)
	,internalTime(INITIAL_TIME)//Might be more appropriate to use the time of creation as an argument, by default the assumption is, that it gets created at the beginning of the simulation
	{}
	
	double Neuron::getMembranePotential() const
	{	return membranePotential;	}
	
	size_t Neuron::getNumberOfSpikes() const
	{	return spikes.size();	}
	
/*	std::vector<double> Neuron::getSpikeTime() const	//Vector is not the appropriate choice
	{	return spikes;	}*/
	
	bool Neuron::isRefractory(unsigned int currentSimulationTime) const	//If there haven't occured any spikes yet or the latest spike took place and the neuron has in the meantime undergone a complete refractory state, then the neuron isn't refractory
	{	if(spikes.empty() or ((currentSimulationTime - spikes.back())>=	REFRACTION_TIME))//do I account for one point in time twice? 
		{	return false;	}
		else { return true; }
	}
	
	void Neuron::spike(unsigned int currentSimulationTime)
	{
		spikes.push_back(currentSimulationTime);
		//numberOfSpikes.front() ++;//increments the number of spikes of the current time interval, loading buffer
		membranePotential = 0;
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
	
	void Neuron::updateMembranePotential(double inputCurrent)//, int numberOfSpikes)
	{
		(membranePotential *= INTERMEDIATE_RESULT_UPDATE_POTENTIAL) += (inputCurrent*MEMBRANE_RESISTANCE_R*(1-INTERMEDIATE_RESULT_UPDATE_POTENTIAL)+SPIKE_AMPLITUDE_J*numberOfSpikes.back());
	}

	void Neuron::update(unsigned int simulationTime)	//Not complete yet, will be invoked at each cycle of the simulation and makes the neutron evolve in the course of time
	{
		if(not isRefractory(simulationTime))
		{
			if(getMembranePotential() >= MEMBRANE_POTENTIAL_THRESHOLD)
			{
				spike(simulationTime);
				//return true;//does spike
			}
			
			else
			{
				double inputCurrent(0);
				
				if ( BEGINN_EXTERNAL_CURRENT <= simulationTime and simulationTime < END_EXTERNAL_CURRENT ) //if the time is in the interval in which an external current is applied, the current is non zero,//should come from the main
				{
					inputCurrent = EXTERNAL_CURRENT;
				}
				
				updateMembranePotential(inputCurrent);
				internalTime += NUMBER_OF_TIME_STEPS_PER_SIMULATION_CYCLE;
			}
		}
		
		//return false;//doesn't spike
		
	}
	
	void Neuron::updateRingBuffer() //deletes the last entry, adds new zero in the beginning
	{
		numberOfSpikes.pop_back();
		numberOfSpikes.push_front(0);
		
	}
	
	void Neuron::receiveSpike(unsigned int localTimeOfSpikingNeuron)
	{
		//numberOfSpikes[abs(localTimeOfSpikingNeuron-internalTime) < EPSILON_VERY_SMALL]	++;//tests if the current neuron has already ben updated in this cycle, could be made with positions in lists or vectors as well, identifier for each neuron
		//numberOfSpikes.front() ++;//increments the number of spikes of the current time interval, loading buffer
		auto temporaryIterator = numberOfSpikes.begin();
		if(not abs(localTimeOfSpikingNeuron-internalTime) < EPSILON_VERY_SMALL)
		{++temporaryIterator;}
		*temporaryIterator++;
		
	}

	
	void Neuron::printSpikingTimes(const string& nameOfFile) const //prints the registered times when spikes ocurred into a file with a name to indicate
	{
		ofstream out(nameOfFile); //out(nameOfFile);//.c_str()?
		
		if(out.fail())
		{
			cerr << "Error: impossible to write in file " << nameOfFile << endl;//Very simplistic solution!
		}
		
		else
		{
			out << "Spikes: " << endl;
			
			for(auto const& spike: spikes)
			{
				out << spike*MIN_TIME_INTERVAL_H << endl; //prints the time not in number of threps but in milliseconds
			}
		}
		out.close();
	}
