#include "neuron.hpp"
#include "parameters.hpp"

#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

	Neuron::Neuron()
	:membranePotential(INITIAL_MEMBRANE_POTENTIAL)
	{}
	
	double Neuron::getMembranePotential() const
	{	return membranePotential;	}
	
	size_t Neuron::getNumberOfSpikes() const
	{	return spikes.size();	}
	
/*	std::vector<double> Neuron::getSpikeTime() const	//Vector is not the appropriate choice
	{	return spikes;	}*/
	
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
		(membranePotential *= INTERMEDIATE_RESULT_UPDATE_POTENTIAL) += (inputCurrent*MEMBRANE_RESISTANCE_R*(1-INTERMEDIATE_RESULT_UPDATE_POTENTIAL));
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
				out << spike << endl;
			}
		}
		out.close();
	}
