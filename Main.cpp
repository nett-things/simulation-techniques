#include <iostream>
#include <fstream>
#include <vector>

#include "RestaurantSim.h"

using namespace std;

void aggregateData(int num_of_runs) {
	vector<vector<Simulation::Data>> array_of_data;

	for(int i = 0; i < num_of_runs; i++) {
		Simulation sim(2000);
		sim.sampleAverageEveryTimeAdvance(true);
		sim.execute();

		array_of_data.push_back(sim.getAverageDataSet());
	}
	
	/*fstream data_out("data.txt", fstream::out);
	
	if(data_out.is_open())
		for(auto& m : array_of_data) {
			for(auto& n : m)
				data_out << n.average_waiting_time << "\t";

			data_out << "\n";
		}

	data_out.close();*/

	/*vector<double> sample_means;

	for(int i = 0; i < array_of_data[0].size(); i++) {
		double sample_mean = 0.0;

		for(int j = 0; j < num_of_runs; j++)
			sample_mean += array_of_data[j][i].average_waiting_time;

		sample_means.push_back(sample_mean / num_of_runs);
	}
		
	double overall_mean = 0.0;
	for(auto mean : sample_means)
		overall_mean += mean;
	overall_mean /= array_of_data[0].size();

	double standard_deviation = 0.0;*/
}

int main() {
	/*Simulation sim;
	sim.execute();
	sim.printResults();*/

	aggregateData(10);

	return 0;
}