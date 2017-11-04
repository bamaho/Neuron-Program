#include "simulation.hpp"
#include "parameters.hpp"
#include "network.hpp"
#include "inhibitoryNeuron.hpp"
#include "neuron.hpp"

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


	Simulation::Simulation()
	:network()
	{}
	
	void Simulation::setRatioJinoverJexG(double ratioJinoverJexG) const
	{
		InhibitoryNeuron::setRatioJinoverJexG(ratioJinoverJexG);
	}
	void Simulation::setRatioVextOverVthr(double ratioVextOverVthr)const
	{
		Neuron::setRatioVextOverVthr(ratioVextOverVthr);
	}
		
	//void Simulation::run(unsigned int durationOfSimulation, unsigned int timeBeginPrintData, unsigned int timeEndPrintData)
	void Simulation::run(unsigned int durationOfSimulation)
	{
		
		unsigned int simulationTime(INITIAL_TIME);	//initializing the simulation time
		
		while (simulationTime < durationOfSimulation)	// "<" because the time scale is defined as each interval step going from [t to t+h), t+h isn't in the interval otherwise I would account twice for certain points in time
		{
			network.update();
			simulationTime ++;
		}

		network.printSimulationDataWithinTimeInterval("simulationData.txt");
		network.getMeanSpikeRateInInterval(2000,12000);
		system("python ../scr/pyscript.py");
		
	}
	
void Simulation::run(double ratioJinoverJexG, double ratioVextOverVthr, unsigned int durationOfSimulation)
	{
		InhibitoryNeuron::setRatioJinoverJexG(ratioJinoverJexG);
		Neuron::setRatioVextOverVthr(ratioVextOverVthr);
		run(durationOfSimulation);
	}
	

