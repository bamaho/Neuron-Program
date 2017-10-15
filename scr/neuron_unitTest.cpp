#include "neuron.hpp"
//#include "gtest/src/gtest-all.cc"
#include "gtest/gtest.h"
#include "parameters.hpp"
#include <vector>

TEST(neuron, ringBuffer) //tests if spikes arrive with the right delay
{
	Neuron n1;
	Neuron n2;
	
	n1.addTarget(&n2);	//establishing a connection between the neurons
	n2.addTarget(&n1);
	
	unsigned int simulationTime(INITIAL_TIME);	//initializing the simulation time
	
	while (simulationTime < FINAL_TIME)	// "<" because the time scale is defined as each interval step going from [t to t+h), t+h isn't in the interval otherwise I would account twice for certain points in time
	{
		n1.update(simulationTime);	//update neurons, a container will be required to simulate a network
		n2.update(simulationTime);
		
		simulationTime += NUMBER_OF_TIME_STEPS_PER_SIMULATION_CYCLE;
	}

	//std::vector<unsigned int> v1(n2.getArrivingSpikesTimes());
	//std::vector<unsigned int> v2(n1.getSpikeTime());
	
	for(size_t i(0); i < n2.getArrivingSpikesTimes().size() ; i++)
	{
		EXPECT_EQ((n2.getArrivingSpikesTimes()[i])-SIGNAL_DELAY_D, n1.getSpikeTime()[i]);//compares the arrival times of spikes with the emission times, there should be a fixed delay in between
	}
	
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
