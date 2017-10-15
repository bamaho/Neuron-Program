#include "neuron.hpp"
#include "parameters.hpp"

//#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include <array>

using namespace std;

	Neuron::Neuron()
	:membranePotential(INITIAL_MEMBRANE_POTENTIAL)
	,internalTime(INITIAL_TIME) //Might be more appropriate to use the time of creation as an argument by default. Otherwise the assumption is, that it gets created at the beginning of the simulation
	//,numberOfSpikes(SIGNAL_DELAY_D + 1,0) //until the delay arrives it takes 1.5 milliseconds...and the time step of the simulation is 0.1
	,currentIndexRingBuffer(0)
	{for (auto& element: incomingSpikes)
		{element =0;}}
	
	double Neuron::getMembranePotential() const
	{	return membranePotential;	}
	
	size_t Neuron::getNumberOfSpikes() const
	{	return spikes.size();	}
	
	void Neuron::update(unsigned int simulationTime)	//Is invoked at each cycle of the simulation and makes the neutron evolve in the course of time
	{
		updateRingBuffer();
		if(not isRefractory(simulationTime))
		{
			if(getMembranePotential() >= MEMBRANE_POTENTIAL_THRESHOLD)
			{
				spike(simulationTime);
			}
			
			else
			{
				double inputCurrent(0);
				
				if ( BEGINN_EXTERNAL_CURRENT <= simulationTime and simulationTime < END_EXTERNAL_CURRENT ) //if the time is in the interval in which an external current is applied, the current is non zero, might come from the main
				{
					inputCurrent = EXTERNAL_CURRENT;
				}
				
				updateMembranePotential(inputCurrent);
				
			}
		}
		reinitializeCurrentRingBufferElement();
		internalTime += NUMBER_OF_TIME_STEPS_PER_SIMULATION_CYCLE;
		
	}
	
	bool Neuron::isRefractory(unsigned int currentSimulationTime) const	//If there haven't occured any spikes yet or the latest spike took place and the neuron has in the meantime undergone a complete refractory state, then the neuron isn't refractory
	{	if(spikes.empty() or ((currentSimulationTime - spikes.back())>=	REFRACTION_TIME))//do I account for one point in time twice? 
		{	return false;	}
		else { return true; }
	}
	
	void Neuron::spike(unsigned int currentSimulationTime)	//stores the spiking time, sets the membrane potential to sends a signal to the connected neurons
	{
		cerr << "Debug Ring Buffer: spike at time " << currentSimulationTime << endl;
		spikes.push_back(currentSimulationTime);
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
		/*auto temporaryIterator = numberOfSpikes.begin();
		if(not abs(localTimeOfSpikingNeuron-internalTime) < EPSILON_VERY_SMALL)
		{++temporaryIterator;}
		(*temporaryIterator)++;*/
		//cerr << "Debug receiving neuron : " << localTimeOfSpikingNeuron << " " << internalTime << "current element in ring buffer is : " << incomingSpikes[currentIndexRingBuffer] << endl;
		
		if(not abs(localTimeOfSpikingNeuron-internalTime) < EPSILON_VERY_SMALL)
		{	if(currentIndexRingBuffer == 0)
			{incomingSpikes.back()++;
				cerr << "Debug receiving neuron : " << localTimeOfSpikingNeuron << " " << internalTime << "current element -1 = end in ring buffer is : " << incomingSpikes[0] << endl;}
			else
			{incomingSpikes[currentIndexRingBuffer-1]++;
				cerr << "Debug receiving neuron : " << localTimeOfSpikingNeuron << " " << internalTime << "current element -1 in ring buffer is : " << incomingSpikes[currentIndexRingBuffer +1] << endl;}
		}
		else
		{
			incomingSpikes[currentIndexRingBuffer]++;
			cerr << "Debug receiving neuron : " << localTimeOfSpikingNeuron << " " << internalTime << "current element in ring buffer is : " << incomingSpikes[currentIndexRingBuffer] << endl;
		}
		
	}

	void Neuron::updateMembranePotential(double inputCurrent)	//adding a second argument "int numberOfSpikes" would be another option
	{
		cerr << "Debug Ring Buffer : number of Spikes in the Ring Buffer element that is read " <<incomingSpikes[currentIndexRingBuffer] << " at time " << internalTime << endl;
		(membranePotential *= INTERMEDIATE_RESULT_UPDATE_POTENTIAL) += (inputCurrent*MEMBRANE_RESISTANCE_R*(1-INTERMEDIATE_RESULT_UPDATE_POTENTIAL)+SPIKE_AMPLITUDE_J*incomingSpikes[currentIndexRingBuffer]);
	}

	
	void Neuron::updateRingBuffer() //deletes the last entry, adds new zero in the beginning, poor solution, one would only need to have a counter that gets updated
	{
		/*numberOfSpikes.pop_back();
		numberOfSpikes.push_front(0);*/
		

		
		if(indexReachedEndOfRingBuffer())
		{currentIndexRingBuffer = 0;}
		else
		{ currentIndexRingBuffer ++ ;}
	}
	
	void Neuron::reinitializeCurrentRingBufferElement()
	{
		incomingSpikes[currentIndexRingBuffer] = 0;
	}
	
	bool Neuron::indexReachedEndOfRingBuffer()
	{return (currentIndexRingBuffer + 2) > (incomingSpikes.size());}
	
	void Neuron::printSpikingTimes(const string& nameOfFile) const //prints the registered times when spikes ocurred into a file with a name to indicate
	{
		ofstream out(nameOfFile);	//.c_str()?
		
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

	void Neuron:: addTarget(Neuron* target)//not the most elegant solution, since with this conception it is the users oblication to allocate space in the memory, the usage of unique pointers might have been more appropriate
	{
		if(target != nullptr) {
			targets.push_back(target);
		}
	}
	
	/*	std::vector<double> Neuron::getSpikeTime() const	//Vector is not the appropriate choice
	{	return spikes;	}*/
	
