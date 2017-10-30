#include "neuron.hpp"
//#include "network.hpp"
#include "gtest/gtest.h"
#include "parameters.hpp"

#include <vector>
#include <cmath>
#include <iostream>



 
 void updateNeuronNTimes(Neuron& neuron, const unsigned int n) //auxilliary function that allows to update a neuron n times
{
	
	for(size_t i(0);i < n;++i)
	{
		neuron.update();
	}
	
}
 
 /*
 * Tests that require certain parameters to have precisely the indicated values:
 * - initial membrane potential = 0 mV
 * - membrane potential threshold = 20 mV
 * - reset membrane potential = 0 mV
 * - refraction period = 2 ms
 * - time constant tau = 20 ms
 * - number of connections from neurons C = 1
 * - and thus the membrane resistance R = 20 GΩ (=tau/C)
 * */
 
 TEST(oneNeuron, spikeTimes)	//with an external input current of 1.01 mV neuron spikes after 92.4ms
 {
	Neuron neuron;
	neuron.setInputCurrent(1.01);
	
	updateNeuronNTimes(neuron, 924);
	EXPECT_TRUE(neuron.getSpikeTime().empty());
	neuron.update();
	updateNeuronNTimes(neuron, 1);
	EXPECT_FALSE(neuron.getSpikeTime().empty());
	updateNeuronNTimes(neuron, 3000);
	
	std::vector<unsigned int> calculatedSpikeTimes({924,1868,2812,3756});//to verify!!
	EXPECT_EQ(calculatedSpikeTimes,neuron.getSpikeTime());
	
}
 
 
 TEST(oneNeuron, membranePotentialTendsToVthr)	//with an external input current of 1 mV the membrane potential tends asymtotically to V_Threshold without reaching it
 {
	Neuron neuron;
	neuron.setInputCurrent(1);
	neuron.update();
	
	EXPECT_DOUBLE_EQ( (TIME_CONSTANT_TAU/NUMBER_OF_CONNECTIONS_FROM_NEURONS_C)*(1-exp(-MIN_TIME_INTERVAL_H/TIME_CONSTANT_TAU)),neuron.getMembranePotential()); //tests if the first update of the membrane potential one correct
	
	updateNeuronNTimes(neuron, 10000);
	EXPECT_EQ(0,neuron.getNumberOfSpikes());
	EXPECT_NEAR (MEMBRANE_POTENTIAL_THRESHOLD, neuron.getMembranePotential(), 0.1);
	
	
}
 
 /*
  * Tests of more general nature, independent of parameter
  * */
TEST(oneNeuron, updateMembranePotentialWithPosExternalCurrent) //tests if the membrane potential is correctly updated after one step if the neuron doesn't receive any spike but with stimulation through an external current after one time step
{
	Neuron neuron;
	neuron.setInputCurrent(EXTERNAL_CURRENT);
	neuron.update();
	
	EXPECT_DOUBLE_EQ(exp(-MIN_TIME_INTERVAL_H/TIME_CONSTANT_TAU)*INITIAL_MEMBRANE_POTENTIAL + (TIME_CONSTANT_TAU/NUMBER_OF_CONNECTIONS_FROM_NEURONS_C)*EXTERNAL_CURRENT*(1-exp(-MIN_TIME_INTERVAL_H/TIME_CONSTANT_TAU)),neuron.getMembranePotential());
	
}

TEST(twoNeurons, ringBuffer) //tests if a spike arrive with the right delay and amplitude, tests that the order in which the neurons are updated is incidental
{
	//part one - spiking neuron gets updated before receiving one, one spike
	Neuron n1;
	Neuron n2;
	
	n1.addTarget(&n2);	//establishing a connection between the neurons
	n1.spike();	//neuron_1 spikes and thus sends a signal to the second
		
	for(size_t i(0);i < SIGNAL_DELAY_D;i++)
	{
		EXPECT_NEAR(n2.readRingBuffer(),0,0.00001); //Verifies that the spike doesn't arrive before it is supposed to
		n2.update();
		
	}
	

	EXPECT_NEAR(n2.readRingBuffer(),SPIKE_AMPLITUDE_J,0.00001); //Verifies that the spike arrives when it should
	n2.update();
	EXPECT_NEAR(n2.readRingBuffer(),0,0.00001); //Verifies that the spike doesn't arrive later it is supposed to
	
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
	EXPECT_NEAR(n4.readRingBuffer(),SPIKE_AMPLITUDE_J*n,0.00001);
}

/*TEST(neuronalNetwork, initialisation) //tests if each neuron receives the correct number of spikes and is thus properly connected
{
	Network network;
}*/



int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
