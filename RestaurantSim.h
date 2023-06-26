#ifndef SIMULATION_RESTAURANTSIM_H_
#define SIMULATION_RESTAURANTSIM_H_

#include <queue>
#include <vector>
#include <random>

#include "Customer.h"
#include "Employee.h"
#include "Stand.h"

using namespace std;

// Main class of the simulation, it contains all the objects
class Restaurant {
public:
	Restaurant();
	~Restaurant();

	void init();
	void execute();

	void arrivalOfCustomer();
	void completionOfService();

	void startOfService();


private:
	const float SERVICE_TIME;
	const int NO_OF_EMPLOYEES, NO_OF_CHICKEN_STANDS, NO_OF_BEEF_STANDS;

	double sim_time;
	
	queue<Customer*> chickenWrapQueue, beefWrapQueue;

	vector<Employee*> employees;
	vector<Stand*> chickenStands, beefStands;
};

using Simulation = Restaurant;

#endif
