#include "network.hpp"
#include "neuron.hpp"
#include "excitatoryNeuron.hpp"
#include "inhibitoryNeuron.hpp"

#include "parameters.hpp"

#include <random>
#include <fstream>


#include <iostream>

using namespace std;

Network::Network()
{
	//creation of neurons
		for(size_t i(0); i < NUMBER_OF_EXCITATORY_NEURONS_Ne; i++)
		{
			neurons[i] = new ExcitatoryNeuron;
		}
		
		for(size_t i(NUMBER_OF_EXCITATORY_NEURONS_Ne);i < TOTAL_NUMBER_OF_NEURONS_N; i++)
		{
			neurons[i] = new InhibitoryNeuron;
		}
	//establishing connections
	
	default_random_engine randomGenerator;
	assert(neurons.size()>=NUMBER_OF_EXCITATORY_NEURONS_Ne);
	uniform_int_distribution<int> distributionExcitatoryNeurons(0,NUMBER_OF_EXCITATORY_NEURONS_Ne-1);
	assert(neurons.size()>=TOTAL_NUMBER_OF_NEURONS_N);
	uniform_int_distribution<int> distributionInhibitoryNeurons(NUMBER_OF_EXCITATORY_NEURONS_Ne,TOTAL_NUMBER_OF_NEURONS_N-1);
	
		for(const auto& neuron : neurons)
		{
			for(size_t i(0); i < NUMBER_OF_CONNECTIONS_FROM_EXCITATORY_NEURONS_Ce; i++)
			{
				neurons[distributionExcitatoryNeurons(randomGenerator)]->addTarget(neuron);	//Can stimulate itself???
			}
			
			for(size_t i(0); i < NUMBER_OF_CONNECTIONS_FROM_INHIBITORY_NEURONS_Ci; i++)
			{
				neurons[distributionInhibitoryNeurons(randomGenerator)]->addTarget(neuron);
			}
		}
}

Network::~Network() //neurons can't exist without a network
{
    for (auto& neuron : neurons) {
        delete neuron;
        neuron = nullptr;
    }
}

void Network::update()
{
	for(auto& neuron: neurons)
	{
		assert(neuron!=nullptr);
		neuron->update();
	}
	 cerr<< neurons[100]->readRingBuffer() << " " << neurons[100]->getBackgroundNoise() << endl;
}

vector<vector<unsigned int> > Network::getSpikeTimes()
{
	std::vector< std::vector<unsigned int> > spikeTimes;
	
	for(auto& neuron: neurons)
	{
		assert(neuron!=nullptr);
		spikeTimes.push_back(neuron->getSpikeTime());
	}
	return spikeTimes;
}

void Network::printSimulationData(const std::string& nameOfFile) const
{
	ofstream out(nameOfFile);
		
		if(out.fail())
		{
			cerr << "Error: impossible to write in file " << nameOfFile << endl;//(Too) simplistic solution!
		}
		
		else
		{
			
			for(size_t i(0); i < TOTAL_NUMBER_OF_NEURONS_N; i++)
			{
				for(auto const& spike: neurons[i]->getSpikeTime())
				{
					out << spike*MIN_TIME_INTERVAL_H << '\t'<< i << '\n' ; //prints the times, not in number of steps, but converted milliseconds
				}
			}
		}
		out.close();
}



