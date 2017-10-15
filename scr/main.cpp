#include <iostream>

#include "neuron.hpp"
#include "parameters.hpp"
//#include <vector>

using namespace std;

int main()
{
	Neuron neuron;	//initialization of neuron
	Neuron neuron2;
	
	neuron.addTarget(&neuron2);	//establishing a connection between the neurons, temporary, non systematic solution, better means are required to simulate a network
	neuron2.addTarget(&neuron);
	
	unsigned int simulationTime(INITIAL_TIME);	//initializing the simulation time
	
	while (simulationTime < FINAL_TIME)	// "<" because the time scale is defined as each interval step going from [t to t+h), t+h isn't in the interval otherwise I would account twice for certain points in time
	{
		neuron.update(simulationTime);	//update neurons, a container will be required to simulate a network, is the simulation time still required as an argument?
		neuron2.update(simulationTime);
		//cerr << "DEBUG: membrane potential at time " << simulationTime << " is " << neuron.getMembranePotential() << endl;	//DEBUG: membrane potential developement
		simulationTime += NUMBER_OF_TIME_STEPS_PER_SIMULATION_CYCLE;
	}
	
	neuron.printSpikingTimes("spikes.txt"); //Printing the  spiking times into a file of name spikes.txt
	neuron2.printSpikingTimes("spikes.txt");
	
	cout << "DEBUG: End of Program"<< endl; //DEBUG

	
}
