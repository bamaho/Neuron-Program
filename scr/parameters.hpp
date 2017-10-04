#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <cmath>

//Parameters

	//Time
constexpr double INITIAL_TIME(0);	//starting time of the simulation
constexpr double FINAL_TIME(1000);	//time when the simulation ends
constexpr double MIN_TIME_INTERVAL(20);	//minimal time interval in milliseconds

	//Current
constexpr double EXTERNAL_CURRENT(20); //current applied to the neuron from the outside in piktoampere
constexpr double BEGINN_EXTERNAL_CURRENT(60);	//time interval in which the external current is applied
constexpr double END_EXTERNAL_CURRENT(100);


	//Membrane Potential
constexpr double INITIAL_MEMBRANE_POTENTIAL(0);
constexpr double MEMBRANE_POTENTIAL_THRESHOLD(-20);
constexpr double REFRACTION_TIME(2);//period after spike during which the neuron is insenstitive to stimulation, in milliseconds

constexpr double TIME_CONSTANT_TAU(20);	//in milliseconds
constexpr double NUMBER_OF_CONNECTIONS_FROM_NEURONS_C(1);//each neuron receives C randomly chosen connections from other neurons in the network

constexpr double INTERMEDIATE_RESULT_UPDATE_POTENTIAL(0);

#endif
