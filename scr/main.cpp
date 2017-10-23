#include <iostream>

#include "neuron.hpp"
#include "parameters.hpp"
#include "network.hpp"
//#include <vector>
#include <cassert>

using namespace std;

int main()
{
	Network network;
	network.update();
	/*assert(NUMBER_OF_CONNECTIONS_FROM_NEURONS_C !=0 and TIME_CONSTANT_TAU !=0);	//Beware division by zero in parameter file!
	
	Neuron neuron;	//initialization of neuron
	Neuron neuron2;
	
	neuron.addTarget(&neuron2);	//establishing a connection between the neurons, temporary, non systematic solution, better means are required to simulate a network
	neuron2.addTarget(&neuron);
	
	unsigned int simulationTime(INITIAL_TIME);	//initializing the simulation time
	
	while (simulationTime < FINAL_TIME)	// "<" because the time scale is defined as each interval step going from [t to t+h), t+h isn't in the interval otherwise I would account twice for certain points in time
	{
		 double inputCurrent(0);
				
				if ( BEGINN_EXTERNAL_CURRENT <= simulationTime and simulationTime < END_EXTERNAL_CURRENT ) //if the time is in the interval in which an external current is applied, the current is non zero, might come from the main
				{
					inputCurrent = EXTERNAL_CURRENT;
				}
		neuron.setInputCurrent(inputCurrent);
		
		
		
		neuron.update();	//update neurons, a container will be required to simulate a network, is the simulation time still required as an argument?
		neuron2.update();
		//cerr << "DEBUG: membrane potential at time " << simulationTime << " is " << neuron.getMembranePotential() << endl;	//DEBUG: membrane potential developement
		simulationTime += NUMBER_OF_TIME_STEPS_PER_SIMULATION_CYCLE;
	}
	
	neuron.printSpikingTimes("spikes.txt"); //Printing the  spiking times into a file of name spikes.txt
	neuron2.printSpikingTimes("spikes.txt");
	
	 */
cout << "DEBUG: End of Program"<< endl; //DEBUG
	
}
