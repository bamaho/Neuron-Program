#include "network.hpp"
#include "neuron.hpp"
#include "excitatoryNeuron.hpp"
#include "inhibitoryNeuron.hpp"

#include "parameters.hpp"

#include <random>

using namespace std;

Network::Network()
{
	//creation of neurons
		for(size_t i(0); i < NUMBER_OF_EXCITATORY_NEURONS_Ne; i++)
		{
			neurons[i] = new Neuron;
		}
		
		for(size_t i(NUMBER_OF_EXCITATORY_NEURONS_Ne);i < TOTAL_NUMBER_OF_NEURONS_N; i++)
		{
			neurons[i] = new Neuron;
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
				neurons[distributionExcitatoryNeurons(randomGenerator)]->addTarget(neuron);
			}
			
			for(size_t i(0); i < NUMBER_OF_CONNECTIONS_FROM_INHIBITORY_NEURONS_Ci; i++)
			{
				neurons[distributionInhibitoryNeurons(randomGenerator)]->addTarget(neuron);
			}
		}
}

void Network::update()
{
	for(auto& neuron: neurons)
	{
		assert(neuron!=nullptr);
		neuron->update();
	}
}

Network::~Network() //neurons can't exist without a network
{
    for (auto& neuron : neurons) {
        delete neuron;
        neuron = nullptr;
    }
}
