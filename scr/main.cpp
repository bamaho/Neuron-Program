#include "simulation.hpp"
#include "network.hpp"
#include "neuron.hpp"
#include "parameters.hpp"


#include <cassert>
#include <iostream>

using namespace std;

int main()
{
	assert(PERCENT_EXCITATORY_NEURONS >=0); //Beware of negative number of neurons
	assert(NUMBER_OF_CONNECTIONS_FROM_NEURONS_C !=0 and TIME_CONSTANT_TAU !=0);	//Beware division by zero in parameter file
	
	//cout << NUMBER_OF_EXCITATORY_NEURONS_Ne << " " << NUMBER_OF_INHIBITORY_NEURONS_Ni << endl;
	//cout << NUMBER_OF_CONNECTIONS_FROM_EXCITATORY_NEURONS_Ce << " " << NUMBER_OF_CONNECTIONS_FROM_INHIBITORY_NEURONS_Ci << endl;
	Simulation simulation;
	simulation.run(6,4);
}
