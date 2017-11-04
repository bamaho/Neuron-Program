#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <cmath>
#include <cassert>

//Parameters


	//Time
constexpr unsigned int INITIAL_TIME(0);	//starting time of the simulation, in steps
constexpr unsigned int FINAL_TIME(12000);	//time when the simulation ends, in steps
constexpr double MIN_TIME_INTERVAL_H(0.1);	//minimal time interval in milliseconds, duration of one time step, H*(number of steps) gives the actual time in milliseconds
constexpr unsigned int SIGNAL_DELAY_D(15); //delay that the signal undergoes between emission and reception, for the sake of convenience uniform, in steps


	//Current
constexpr double EXTERNAL_CURRENT(0); //current applied to the neuron from the outside in piktoampere
/*constexpr unsigned int BEGINN_EXTERNAL_CURRENT(100);	//begin of time interval in which the external current is applied
constexpr unsigned int END_EXTERNAL_CURRENT(1000);	//end of time interval in which the external current is applied	*/

constexpr int J_INHIBATORY_OVER_J_EXCITATORY_G(5); //J_INHIBATORY/J_EXCITATORY

constexpr double SPIKE_AMPLITUDE_J_EXCITATORY_NEURON(0.1);	//spike amplitude of an excitatory neuron
constexpr double SPIKE_AMPLITUDE_J_INHIBITORY_NEURON(SPIKE_AMPLITUDE_J_EXCITATORY_NEURON*J_INHIBATORY_OVER_J_EXCITATORY_G);	//spike amplitude of an inhibitory neuron

constexpr double SPIKE_AMPLITUDE_J(0.1); 	//PSP (spike response) amplitude, defines the impact of one received spike on the membrane potential, changed for later version

	

	//Network
constexpr unsigned int TOTAL_NUMBER_OF_NEURONS_N(12500);
constexpr unsigned int NUMBER_OF_EXCITATORY_NEURONS_Ne(10000);
constexpr unsigned int NUMBER_OF_INHIBITORY_NEURONS_Ni(2500);

constexpr unsigned int NUMBER_OF_CONNECTIONS_FROM_NEURONS_C(1);	//each neuron receives C randomly chosen connections from other neurons in the network //to be altered? Becomes important when a whole network is simulated , MUST NOT BE ZERO FOR THIS RESULTS IN UNDEFINED BEHAVIOUR, DIVISION BY ZERO!
constexpr unsigned int NUMBER_OF_CONNECTIONS_FROM_EXCITATORY_NEURONS_Ce(1000); // Ce = Cext, the number of connections from excitatory from the rest of the brain that fire arbitrarily at a given rate
constexpr unsigned int NUMBER_OF_CONNECTIONS_FROM_INHIBITORY_NEURONS_Ci(250);


//Membrane Potential
constexpr double INITIAL_MEMBRANE_POTENTIAL(0);	//initial membrane portential in mV
constexpr double MEMBRANE_POTENTIAL_THRESHOLD(20);	//value in mV of mambrane potential that, once reached, causes the neuron to spike
constexpr double RESET_MEMBRANE_POTENTIAL(0); //value in mV that the membrane potential takes just after the spike
constexpr unsigned int REFRACTION_PERIOD(20);	//period after spike during which the neuron is insenstitive to stimulation, in steps

constexpr unsigned int TIME_CONSTANT_TAU(20);	//Tau = membrane resistance * Number of Connections from neurons, in milliseconds (!), MUST NOT BE ZERO FOR THIS RESULTS IN UNDEFINED BEHAVIOUR, DIVISION BY ZERO WHEN THE MEMBRANE POTENTIAL IS UPDATED!

constexpr double MEMBRANE_RESISTANCE_R(TIME_CONSTANT_TAU/NUMBER_OF_CONNECTIONS_FROM_NEURONS_C);	//in GΩ, the neuron can be thought of as a simple electrical circuit
constexpr double INTERMEDIATE_RESULT_UPDATE_POTENTIAL(exp(-MIN_TIME_INTERVAL_H/TIME_CONSTANT_TAU));	//an expression which has to be calculated multiple times when updating the membrane potential and that is constant

//Activity of the rest of the brain
constexpr bool BACKGROUND_NOISE_ON(true); //regulates if there's a contribution from the rest of the brain. That this parameter is false is a prerequisite for certain tests to work
constexpr unsigned int RATIO_V_EXTERNAL_OVER_V_THRESHOLD(2);

//Fetch Data
constexpr unsigned int TIME_BEGIN_PRINT_TO_TXT_FILE(10000);//assert that it is than smaller
constexpr unsigned int TIME_END_PRINT_TO_TXT_FILE(12000);

#endif
