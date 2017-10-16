#include "neuron.hpp"
#include "gtest/gtest.h"
#include "parameters.hpp"

#include <vector>
#include <cmath>

TEST(neuron, ringBuffer) //tests if spikes arrive with the right delay
{
	Neuron n1;
	Neuron n2;
	
	n1.addTarget(&n2);	//establishing a connection between the neurons
	n2.addTarget(&n1);
	
	unsigned int simulationTime(INITIAL_TIME);	//initializing the simulation time
	
	while (simulationTime < FINAL_TIME)	// "<" because the time scale is defined as each interval step going from [t to t+h), t+h isn't in the interval otherwise I would account twice for certain points in time
	{
		 double inputCurrent(0);
				
				if ( BEGINN_EXTERNAL_CURRENT <= simulationTime and simulationTime < END_EXTERNAL_CURRENT ) //if the time is in the interval in which an external current is applied, the current is non zero, might come from the main
				{
					inputCurrent = EXTERNAL_CURRENT;
				}
		n1.setInputCurrent(inputCurrent);
		
		n1.update();	//update neurons, a container will be required to simulate a network
		n2.update();
		
		simulationTime += NUMBER_OF_TIME_STEPS_PER_SIMULATION_CYCLE;
	}
	
	for(size_t i(0); i < n2.getArrivingSpikesTimes().size() ; i++)
	{
		EXPECT_EQ((n2.getArrivingSpikesTimes()[i])-SIGNAL_DELAY_D, n1.getSpikeTime()[i]);//compares the arrival times of spikes with the emission times, there should be a fixed delay in between
	}
	
}

TEST(neuron, updateMembranePotentialWithExternalCurrent) //tests if the membrane potential is correctly updated if the neuron doesn't receive any spike but with stimulation through an external current after one time step
{
	Neuron neuron;
	neuron.setInputCurrent(EXTERNAL_CURRENT);
	neuron.update();
	
	EXPECT_DOUBLE_EQ(exp(-MIN_TIME_INTERVAL_H/TIME_CONSTANT_TAU)*INITIAL_MEMBRANE_POTENTIAL + (TIME_CONSTANT_TAU/NUMBER_OF_CONNECTIONS_FROM_NEURONS_C)*EXTERNAL_CURRENT*(1-exp(-MIN_TIME_INTERVAL_H/TIME_CONSTANT_TAU)),neuron.getMembranePotential());
	
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
