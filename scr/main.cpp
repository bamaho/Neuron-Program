#include "neuron.hpp"
#include <iostream>
#include <array>

using namespace std;

int main()
{
	constexpr double INITIAL_TIME(0);//
	constexpr double FINAL_TIME(1000);
	constexpr double h(20); //strep in time, milliseconds
	double simtime(INITIAL_TIME);
	
	constexpr double I_ext(20);//piktoampere//courrant
	const array<double, 2> timeInterval ({2,3});
	
	
	
	
	//Neuron neuron;
	
	
	while (simtime <= FINAL_TIME)
	{
		double inputCurrent;
		//If time is in the indicated interval
		//inputCurrent = 
		simtime += h;
	}
	
	
	cout << "End"<< endl;

	
}
