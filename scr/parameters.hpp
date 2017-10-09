#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <cmath>

//Parameters

	//Time
constexpr unsigned int INITIAL_TIME(0);	//starting time of the simulation, in steps
constexpr unsigned int FINAL_TIME(1000);	//time when the simulation ends, in steps
constexpr double MIN_TIME_INTERVAL_H(0.1);	//minimal time interval in milliseconds, duration of one time step ...H*number of steps gives the real time in milliseconds
constexpr unsigned int NUMBER_OF_TIME_STEPS_PER_SIMULATION_CYCLE(1);

	//Current
constexpr double EXTERNAL_CURRENT(5); //current applied to the neuron from the outside in piktoampere
constexpr unsigned int BEGINN_EXTERNAL_CURRENT(100);	//time interval in which the external current is applied
constexpr unsigned int END_EXTERNAL_CURRENT(1000);

constexpr double SPIKE_AMPLITUDE_J(2);

	//Membrane Potential
constexpr double INITIAL_MEMBRANE_POTENTIAL(0);
constexpr double MEMBRANE_POTENTIAL_THRESHOLD(20);
constexpr unsigned int REFRACTION_TIME(2);//period after spike during which the neuron is insenstitive to stimulation, in steps

constexpr unsigned int TIME_CONSTANT_TAU(20);	//in milliseconds?
constexpr unsigned int NUMBER_OF_CONNECTIONS_FROM_NEURONS_C(1);//each neuron receives C randomly chosen connections from other neurons in the network //to be altered

constexpr double MEMBRANE_RESISTANCE_R(TIME_CONSTANT_TAU/NUMBER_OF_CONNECTIONS_FROM_NEURONS_C);//division by zero
constexpr double INTERMEDIATE_RESULT_UPDATE_POTENTIAL(exp(-MIN_TIME_INTERVAL_H/TIME_CONSTANT_TAU));//division by zero

#endif
