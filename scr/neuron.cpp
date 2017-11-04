#include "neuron.hpp"
#include "parameters.hpp"

//#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
//#include <list>
#include <array>
#include <cassert>
#include <random>

using namespace std;

	Neuron::Neuron()
	:membranePotential(INITIAL_MEMBRANE_POTENTIAL)
	,inputCurrent(0)
	,internalTime(INITIAL_TIME) //Might be more appropriate to use the time of creation as an argument by default. Otherwise the assumption is, that it gets created at the beginning of the simulation
	{ for (auto& element: incomingSpikes){element =0;} 
		
		}	//Initialized the ring buffer entries to zero
	
	Neuron:: ~Neuron(){}
	
	
	
	double Neuron::getMembranePotential() const
	{ return membranePotential; }
	
	size_t Neuron::getNumberOfSpikes() const
	{ return spikes.size(); }
	
	
	
	void Neuron::setInputCurrent(double externalCurrent)
	{inputCurrent = externalCurrent;}
	
	void Neuron::update(void (Neuron::*membranePotentialUpdate)() )
	{
		if(not isRefractory())
		{
			if(getMembranePotential() >= MEMBRANE_POTENTIAL_THRESHOLD)
			{
				spike();
			}
			else
			{
				(this->*membranePotentialUpdate)();
			}
		}
		reinitializeCurrentRingBufferElement();
		internalTime ++;
	}
	
	void Neuron::update()	//Is invoked at each cycle of the simulation and makes the neutron evolve in the course of time
	{
		update(&Neuron::updateMembranePotential);
		/*if(not isRefractory())
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
		internalTime ++;*/
	}
	void Neuron::updateWithoutBackgroundNoise()
	{update(&Neuron::updateMembranePotentialWithoutBackgroundNoise);}
	
	bool Neuron::isRefractory() const	//If there haven't occured any spikes yet or the latest spike took place and the neuron has in the meantime undergone a complete refractory state, then the neuron isn't refractory
	{	
		return not(spikes.empty() or ((internalTime - spikes.back())>=	REFRACTION_PERIOD));
	}
	
	void Neuron::spike()	//stores the spiking time, sets the membrane potential to sends a signal to the connected neurons
	{
		spikes.push_back(internalTime);
		membranePotential = RESET_MEMBRANE_POTENTIAL;
		if(not targets.empty())
		{
			for(auto& targetNeuron: targets)
			{
				if(targetNeuron != nullptr) {
                targetNeuron->receiveSpike(internalTime, getSpikeAmplitude()); //once two types of neurons are possible, this line isn't adequate anymore
				}
			
			}
		}
	}
	
	void Neuron::receiveSpike(unsigned int localTimeOfSpikingNeuron, double spikeAmplitude)
	{	
		incomingSpikes[timeToRingBufferIndex(SIGNAL_DELAY_D+localTimeOfSpikingNeuron)] += spikeAmplitude;	//writes the incoming spike at curent time + the signal delay into the ring buffer, to be altered, if one drops the simplification that D is uniform, d should be added by the spiking neuron
	}	
		
	void Neuron::updateMembranePotentialWithoutBackgroundNoise()
	{
		(membranePotential *= INTERMEDIATE_RESULT_UPDATE_POTENTIAL) += (inputCurrent*MEMBRANE_RESISTANCE_R*(1-INTERMEDIATE_RESULT_UPDATE_POTENTIAL)+readRingBuffer());
	}

	void Neuron::updateMembranePotential()	//adding a second argument "int numberOfSpikes" would be another option
	{
		updateMembranePotentialWithoutBackgroundNoise();
		membranePotential += getBackgroundNoise();
	}
	
	double Neuron::readRingBuffer() const //reads the current entry
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
	
	double Neuron::getSpikeAmplitude() const
	{
		return SPIKE_AMPLITUDE_J;
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
		if(target != nullptr) { //unpredictible
			targets.push_back(target);
		}
	}
	
	//Random Generator
	double Neuron::getBackgroundNoise() const
	{
		if (BACKGROUND_NOISE_ON)
		{static random_device randomDevice;
		 static mt19937 generator(randomDevice());
		 static poisson_distribution<> distribution(RATIO_V_EXTERNAL_OVER_V_THRESHOLD*MEMBRANE_POTENTIAL_THRESHOLD*MIN_TIME_INTERVAL_H/(SPIKE_AMPLITUDE_J_EXCITATORY_NEURON*TIME_CONSTANT_TAU));//V_EXT*J_EXT*h*Cext, "The number of connections from outside the network is taken to be equal to the number of recurrent excitatory ones, Cext = Ce"
		 return SPIKE_AMPLITUDE_J_EXCITATORY_NEURON*distribution(generator);}
		 else
		 {return 0;} //no contribution of the rest of the brain if background noise is not activated in the parameter file, for certain tests the activity must be turned off
	}
	
	//Testing
	
		const vector<unsigned int>& Neuron::getSpikeTime() const	//Vector is not the appropriate choice
	{	
		const vector<unsigned int> & sTimes(spikes);
		return sTimes;	}
