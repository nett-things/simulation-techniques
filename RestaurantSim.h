#ifndef SIMULATION_RESTAURANTSIM_H_
#define SIMULATION_RESTAURANTSIM_H_

#include <iostream>
#include <queue>
#include <vector>
#include <random>
#include <cmath>

#include "Customer.h"
#include "Employee.h"
#include "Stand.h"

using namespace std;

// Main class of the simulation, it contains all the objects
class Restaurant {
public:
	struct Data {
		double simulation_time;
		double average_waiting_time;
		double average_chicken_storage_time;
		double average_beef_storage_time;
		double average_meat_storage_time;
		double average_chicken_queue_length;
		double average_beef_queue_length;
		double average_queue_length;
		double average_employee_time_utilization;
	};

	Restaurant();
	Restaurant(double max_time);
	~Restaurant();

	void execute();
	void sampleEveryTimeAdvance(bool if_sampling);

	double getAverageWaitingTime() const;
	double getAverageChickenStorageTime() const;
	double getAverageBeefStorageTime() const;
	double getAverageMeatStorageTime() const;
	double getAverageChickenQueueLength() const;
	double getAverageBeefQueueLength() const;
	double getAverageQueueLength() const;
	double getAverageEmployeeTimeUtilization() const;

	void printResults() const;
	Data getData() const;
	vector<Data> getDataSet();

private:
	const double SERVICE_TIME;
	const int NO_OF_EMPLOYEES, NO_OF_CHICKEN_STANDS, NO_OF_BEEF_STANDS;

	double simulation_time, max_simulation_time, next_arrival, total_waiting_time;
	int num_of_served_customers, total_chicken_queue, total_beef_queue, num_of_chicken_queue_changes, num_of_beef_queue_changes;
	
	queue<Customer*> chickenWrapQueue, beefWrapQueue;
	vector<Employee*> employees;

	Stand chickenStands, beefStands;

	bool sampling;
	vector<Data> data_set;

	random_device rd;
	mt19937 generator;

	void arrivalOfCustomer();
	void startOfService(int id);
	void completionOfService(int id);

	void advanceSimulationTime();
	void updateChickenQueueData();
	void updateBeefQueueData();

	Data encapsulateData() const;
};

using Simulation = Restaurant;

#endif
