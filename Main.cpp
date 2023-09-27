#include <iostream>
#include <fstream>
#include <vector>

#include "RestaurantSim.h"

using namespace std;

void aggregateData(int num_of_runs) {
	vector<vector<double>> arrays_of_data;

	for(int i = 0; i < num_of_runs; i++) {
		Simulation sim(2000);
		sim.sampleWaitingTime(true);
		sim.execute();

		arrays_of_data.push_back(sim.getWaitingTimeDataSet());
	}


	/*
	//resize vectors to the shortest one
	int largest_size = 0;
	for(auto& array : arrays_of_data)
		if(array.size() > largest_size)
			largest_size = array.size();

	int smallest_size = largest_size;
	for(auto& array : arrays_of_data)
		if(array.size() < smallest_size)
			smallest_size = array.size();

	for(auto& array : arrays_of_data) {
		array.resize(smallest_size);
		array.shrink_to_fit();
	}

	fstream data_out("data.txt", fstream::out);
	
	if(data_out.is_open())
		for(auto& m : arrays_of_data[0]) {
			data_out << log10(m) << "\n";
		}

	data_out.close();

	//calculating the sample means
	vector<double> sample_means;
	for(int i = 0; i < smallest_size; i++) {
		double sample_mean = 0.0;

		for(int j = 0; j < num_of_runs; j++)
			sample_mean += arrays_of_data[j][i];

		sample_means.push_back(sample_mean / num_of_runs);
	}

	//calculating the overall mean
	double overall_mean = 0.0;
	for(auto mean : sample_means)
		overall_mean += mean;
	overall_mean /= smallest_size;

	//calculating the standard deviations
	double sum = 0.0;
	for(auto i : sample_means)
		sum += pow(i, 2);

	double standard_deviation = sqrt(1.0 / (smallest_size - 1) * (sum - (smallest_size * pow(overall_mean, 2))));
	cout << endl << standard_deviation;*/
	
}

int main() {
	/*Simulation sim;
	sim.execute();
	sim.printResults();*/

	//aggregateData(10);

	Simulation sim(5000);
	sim.sampleAverageEveryTimeAdvance(true);
	sim.execute();

	fstream data_out("avg.txt", fstream::out);

	if(data_out.is_open())
		for(auto& i : sim.getAverageDataSet())
			data_out << i.simulation_time << "\t" << i.average_waiting_time << endl;

	data_out.close();


	return 0;
}