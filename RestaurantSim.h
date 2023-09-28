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
	Restaurant();
	Restaurant(double max_time);
	~Restaurant();

	void execute();

private:
	const double SERVICE_TIME;
	const int NO_OF_EMPLOYEES, NO_OF_CHICKEN_STANDS, NO_OF_BEEF_STANDS;

	double simulation_time, max_simulation_time, next_arrival;
	
	queue<Customer*> chickenWrapQueue, beefWrapQueue;
	vector<Employee*> employees;

	Stand chickenStands, beefStands;

	random_device rd;
	mt19937 generator;

	void arrivalOfCustomer();
	void startOfService(int id);
	void completionOfService(int id);

	void advanceSimulationTime();
};

using Simulation = Restaurant;

#endif
