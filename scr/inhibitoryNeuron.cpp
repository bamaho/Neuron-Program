#include "inhibitoryNeuron.hpp"
#include "parameters.hpp"



using namespace std;

InhibitoryNeuron::InhibitoryNeuron()
:Neuron()
{}

double InhibitoryNeuron::getSpikeAmplitude() const
{
	return -SPIKE_AMPLITUDE_J_INHIBITORY_NEURON;
}
