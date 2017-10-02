#include "neuron.hpp"
#include <iostream>

using namespace std;

int main()
{
	constexpr double INITIAL_TIME(0);//
	constexpr double FINAL_TIME(1000);
	constexpr double h(20); //strep in time, milliseconds
	double simtime(INITIAL_TIME);
	
	constexpr double I_ext(20);//piktoampere
	
	//Neuron neuron;
	
	
	while (simtime <= FINAL_TIME)
	{
		simtime += h;
	}
	
	
	cout << "End"<< endl;

	
}
