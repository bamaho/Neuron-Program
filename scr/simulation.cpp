#include "simulation.hpp"
#include "parameters.hpp"

//#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
//#include <list>
#include <array>
#include <cassert>
#include <random>

using namespace std;

	Neuron::Neuron()
	:membranePotential(INITIAL_MEMBRANE_POTENTIAL)
	,inputCurrent(0)
	,internalTime(INITIAL_TIME) //Might be more appropriate to use the time of creation as an argument by default. Otherwise the assumption is, that it gets created at the beginning of the simulation
	{ for (auto& element: incomingSpikes){element =0;} 
		
		}	//Initialized the ring buffer entries to zero
	
	//Neuron:: ~Neuron(){}
	
	
	

