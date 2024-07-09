#include <iostream>
#include <fstream>
#include <vector>

#include "RestaurantSim.h"

using namespace std;

int main() {
	Simulation sim(10000);
	sim.sampleAverageEveryTimeAdvance(true);
	sim.setMode(Simulation::STEP_BY_STEP);
	sim.execute();
	sim.printResults();

	fstream data_out("output\\avg_data.txt", fstream::out);

	if(data_out.is_open())
		for(auto& i : sim.getAverageDataSet())
			data_out << i.simulation_time << "\t" << i.average_waiting_time << "\t" << i.average_meat_storage_time << "\t" << i.average_queue_length << "\t" << i.average_employee_time_utilization << endl;

	data_out.close(); 

	return 0;
}