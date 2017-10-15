#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <cmath>
#include <cassert>

//Parameters

	//Miscellaneous
constexpr double EPSILON_VERY_SMALL(0.000001);	//comparison of floating point numbers

	//Time
constexpr unsigned int INITIAL_TIME(0);	//starting time of the simulation, in steps
constexpr unsigned int FINAL_TIME(1000);	//time when the simulation ends, in steps
constexpr double MIN_TIME_INTERVAL_H(0.1);	//minimal time interval in milliseconds, duration of one time step, H*(number of steps) gives the actual time in milliseconds
constexpr unsigned int NUMBER_OF_TIME_STEPS_PER_SIMULATION_CYCLE(1);
constexpr unsigned int SIGNAL_DELAY_D(15); //delay that the signal undergoes between emission and reception, for the sake of convenience uniform, in steps


	//Current
constexpr double EXTERNAL_CURRENT(5); //current applied to the neuron from the outside in piktoampere
constexpr unsigned int BEGINN_EXTERNAL_CURRENT(100);	//begin of time interval in which the external current is applied
constexpr unsigned int END_EXTERNAL_CURRENT(1000);	//end of time interval in which the external current is applied

constexpr double SPIKE_AMPLITUDE_J(2); 	//defines the impact of one received spike on the membrane potential

	//Membrane Potential
constexpr double INITIAL_MEMBRANE_POTENTIAL(0);
constexpr double MEMBRANE_POTENTIAL_THRESHOLD(20);	//value of mambrane potential that, once reached, causes the neuron to spike
constexpr double RESET_MEMBRANE_POTENTIAL(0); //value that the membrane potential takes just after the spike
constexpr unsigned int REFRACTION_TIME(2);	//period after spike during which the neuron is insenstitive to stimulation, in steps

constexpr unsigned int TIME_CONSTANT_TAU(20);	//Tau = membrane resistance * Number of Connections from neurons, in milliseconds?
constexpr unsigned int NUMBER_OF_CONNECTIONS_FROM_NEURONS_C(1);	//each neuron receives C randomly chosen connections from other neurons in the network //to be altered? Becomes important when a whole network is simulated

//assert(NUMBER_OF_CONNECTIONS_FROM_NEURONS_C != 0);
constexpr double MEMBRANE_RESISTANCE_R(TIME_CONSTANT_TAU/NUMBER_OF_CONNECTIONS_FROM_NEURONS_C);	//the neuron can be thought of as a simple electrical circuit
//assert(TIME_CONSTANT_TAU != 0);
constexpr double INTERMEDIATE_RESULT_UPDATE_POTENTIAL(exp(-MIN_TIME_INTERVAL_H/TIME_CONSTANT_TAU));	//an expression that has to be calculated multiple times when updating the membrane potential that is constant

#endif
