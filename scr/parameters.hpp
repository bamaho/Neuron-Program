#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <array>

//Parameters

	//Time
constexpr double INITIAL_TIME(0);	//starting time of the simulation
constexpr double FINAL_TIME(1000);	//time when the simulation ends
constexpr double MIN_TIME_INTERVAL(20);	//minimal time interval in milliseconds

	//Current
constexpr double EXTERNAL_CURRENT(20); //current applied to the neuron from the outside in piktoampere
const std::array<double, 2> TIME_INTERVAL_EXT_CURRENT({20,100});	//time interval in which the external current is applied

	//Membrane Potential
constexpr double INITIAL_MEMBRANE_POTENTIAL(20);

#endif
