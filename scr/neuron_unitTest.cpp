#include "neuron.hpp"
#include "gtest/gtest.h"
#include "parameters.hpp"

#include <vector>
#include <cmath>

TEST(neuron, ringBuffer) //tests if a spike arrive with the right delay and amplitude, tests that the order in which the neurons are updated is incidetal
{
	//part one - spiking neuron gets updated before receiving one, one spike
	Neuron n1;
	Neuron n2;
	
	n1.addTarget(&n2);	//establishing a connection between the neurons
	n1.spike();	//neuron_1 spikes and thus sends a signal to the second
		
	for(size_t i(0);i < SIGNAL_DELAY_D;i++)
	{
		n2.update();
	}
	EXPECT_DOUBLE_EQ(n2.readRingBuffer(),SPIKE_AMPLITUDE_J);
	
	//part two - receiving neuron gets updated before receiving one, n spikes
	Neuron n3;
	Neuron n4;
	constexpr unsigned int n(100);
	
	n3.addTarget(&n4);
	n4.update();
	
	for(size_t i(0); i < n; i++) //spiking n times
	{
		n3.spike();
	}
	
	for(size_t i(0); i < (SIGNAL_DELAY_D-1); i++)
	{
		n4.update();
	}
	EXPECT_DOUBLE_EQ(n4.readRingBuffer(),SPIKE_AMPLITUDE_J*n);
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
