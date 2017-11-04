#include "simulation.hpp"
#include "network.hpp"
#include "neuron.hpp"
#include "parameters.hpp"


#include <cassert>
#include <iostream>

using namespace std;

int main()
{
	assert(NUMBER_OF_CONNECTIONS_FROM_NEURONS_C !=0 and TIME_CONSTANT_TAU !=0);	//Beware division by zero in parameter file!
	
	Simulation simulation;
	simulation.run(6,4);

	
}
