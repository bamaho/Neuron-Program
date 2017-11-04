#ifndef SIMULATION_H
#define SIMULATION_H

#include "parameters.hpp"
#include "network.hpp"

#include <array>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <random>


class Simulation
{
	public:
	
	//constructor and deconstructor
	/// A constructor.
	Simulation();
	
	void setRatioJinoverJexG(double ratioJinoverJexG) const;
	void setRatioVextOverVthr(double ratioVextOverVthr)const;
	

	void run(unsigned int durationOfSimulation = FINAL_TIME);
	void run(double ratioJinoverJexG, double ratioVextOverVthr, unsigned int durationOfSimulation = FINAL_TIME);
	//void run(unsigned int durationOfSimulation = FINAL_TIME, unsigned int timeBeginPrintData = TIME_BEGIN_PRINT_TO_TXT_FILE, unsigned int timeEndPrintData = TIME_END_PRINT_TO_TXT_FILE);
	
	double getMeanSpikeRateInInterval(double ratioJinoverJexG, double ratioVextOverVthr, unsigned int timeBeginMeasurement, unsigned int timeEndMeasurement);
	
	private:
	
	//static unsigned int timeBeginPrintToTxtFile;
	//static unsigned int timeEndPrintToTxtFile;
	Network network;
	

};


#endif
