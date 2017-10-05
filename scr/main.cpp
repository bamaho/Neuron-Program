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
		if(not neuron.isRefractory(simulationTime))
		{
			if(neuron.getMembranePotential() >= MEMBRANE_POTENTIAL_THRESHOLD)
			{
				neuron.spike(simulationTime);
			}
			
			else
			{
				double inputCurrent(0);
				
				if ( BEGINN_EXTERNAL_CURRENT <= simulationTime and simulationTime < END_EXTERNAL_CURRENT ) //if the time is in the interval in which an external current is applied, the current is non zero
				{
					inputCurrent = EXTERNAL_CURRENT;
				}
				
				neuron.updateMembranePotential(inputCurrent);
				
			}
		}
		
		
		//If time is in the indicated interval
		//inputCurrent = 
		//cout << simulationTime << endl;
		cerr << "DEBUG: membrane potential at time " << simulationTime << " is " << neuron.getMembranePotential() << endl;
		simulationTime += MIN_TIME_INTERVAL;
	}
	
	neuron.printSpikingTimes("spikes.txt");
	
	cout << "End"<< endl;

	
}
