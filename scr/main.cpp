#include "simulation.hpp"
#include "network.hpp"
#include "neuron.hpp"
#include "parameters.hpp"


#include <cassert>
#include <iostream>

using namespace std;

int main()
{
	//return system("python ../scr/pyscript.py");
	Simulation simulation;
	return(simulation.runBrunel());
	
	//The first uncommented reproduction gets excecuted.
	/*
	
	////////////////// Reproduction of Figure A ////////////////////////
	simulation.printDataForBrunelFigureToFile(3,2,5000,6000);
	return system("python ../scr/pyscript.py"); //Displays the graphs and leaves the program
	
	////////////////// Reproduction of Figure B ////////////////////////
	simulation.printDataForBrunelFigureToFile(6,4);
	cout << "The neurons have a mean firing frequency of " << simulation.printDataForBrunelFigureToFileWithMeanSpikingRate(6,4) <<
	 " Hz." << endl << "The corresponding value for this setting from Brunel is in Theory: 55.8 Hz and in Simulation: 60.7 Hz." << endl;
	return system("python ../scr/pyscript.py");	
	
	////////////////// Reproduction of Figure C ////////////////////////
	cout << "The neurons have a mean firing frequency of " << simulation.printDataForBrunelFigureToFileWithMeanSpikingRate(5,2) <<
	 " Hz." << endl << "The corresponding value for this setting from Brunel is in Theory: 38.0 Hz and in Simulation: 37.7 Hz." << endl;
	//simulation.printDataForBrunelFigureToFile(5,2);
	return system("python ../scr/pyscript.py"); 
	*/
	////////////////// Reproduction of Figure D ////////////////////////
	/*cout << "The neurons have a mean firing frequency of " << simulation.printDataForBrunelFigureToFileWithMeanSpikingRate(4.5,0.9) <<
	 " Hz." << endl << "The corresponding value for this setting from Brunel is in Theory: 6.5 Hz and in Simulation: 5.5 Hz." << endl;
	//simulation.printDataForBrunelFigureToFile(4.5,0.9);
	return system("python ../scr/pyscript.py");*/
}
