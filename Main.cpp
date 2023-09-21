#include <iostream>
#include <fstream>
#include <vector>

#include "RestaurantSim.h"

using namespace std;

void aggregateData(int num_of_runs) {
	vector<vector<Simulation::Data>> array_of_data;

	for(int i = 0; i < num_of_runs; i++) {
		Simulation sim(2000);
		sim.sampleEveryTimeAdvance(true);
		sim.execute();

		array_of_data.push_back(sim.getDataSet());
	}
	
	fstream data_out("data.txt", fstream::out);

	if(data_out.is_open())
		for(auto& m : array_of_data) {
			for(auto& n : m)
				data_out << n.average_waiting_time << "\t";

			data_out << "\n";
		}

	data_out.close();
}

int main() {
	/*Simulation sim;
	sim.execute();
	sim.printResults();*/

	aggregateData(10);

	return 0;
}