#include <iostream>

#include "neuron.hpp"
#include "parameters.hpp"

using namespace std;

int main()
{
	Neuron neuron;	//initialization of neuron
	double simulationTime(INITIAL_TIME);	//initializing the simulation time
	
	while (simulationTime < FINAL_TIME)	// "<" because the time scale is defined as each interval step going from [t to t+h), t+h isn't in the interval otherwise I would account twice for certain points in time
	{
		neuron.update(simulationTime);
		
		cerr << "DEBUG: membrane potential at time " << simulationTime << " is " << neuron.getMembranePotential() << endl;	//DEBUG: membrane potential developement
		simulationTime += MIN_TIME_INTERVAL;
	}
	
	neuron.printSpikingTimes("spikes.txt"); //Printing the  spiking times into a file of name spikes.txt
	
	cout << "DEBUG: End of Program"<< endl; //DEBUG

	
}
