#include <iostream>
#include <fstream>
#include <vector>

#include "RestaurantSim.h"

using namespace std;

int main() {
	Simulation sim(10000);
	sim.sampleAverageEveryTimeAdvance(true);
	sim.execute();
	sim.printResults();

	fstream data_out("avg.txt", fstream::out);

	if(data_out.is_open())
		for(auto& i : sim.getAverageDataSet())
			data_out << i.simulation_time << "\t" << i.average_waiting_time << endl;

	data_out.close(); 


	return 0;
}