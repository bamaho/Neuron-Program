#include "inhibitoryNeuron.hpp"
#include "parameters.hpp"


/*#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include <array>
#include <cassert>*/

using namespace std;

double InhibitoryNeuron::getSpikeAmplitude() const
{
	return -SPIKE_AMPLITUDE_J_INHIBITORY_NEURON;
}
