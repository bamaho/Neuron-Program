#include "network.hpp"
#include "neuron.hpp"
#include "parameters.hpp"

using namespace std;

Network::Network()
{
	//creation of neurons
		for(size_t i(0);i < NUMBER_OF_EXCITATORY_NEURONS_Ne; i++)
		{
			neurons[i] = new Neuron;
		}
		
		for(size_t i(NUMBER_OF_EXCITATORY_NEURONS_Ne);i < TOTAL_NUMBER_OF_NEURONS_N; i++)
		{
			neurons[i] = new Neuron;
		}
	//establishing connections
		
}

Network::~Network() //neurons can't exist without a network
{
    for (auto& neuron : neurons) {
        delete neuron;
        neuron = nullptr;
    }
}
