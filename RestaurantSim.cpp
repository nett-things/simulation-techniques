#include "RestaurantSim.h"
#include "RestaurantSim.h"

Restaurant::Restaurant() : Restaurant(1000) { }

Restaurant::Restaurant(double max_time)
	: SERVICE_TIME(0.6),
	NO_OF_EMPLOYEES(1),
	NO_OF_CHICKEN_STANDS(2),
	NO_OF_BEEF_STANDS(5),
	simulation_time(0),
	max_simulation_time(max_time),
	chickenStands(NO_OF_CHICKEN_STANDS, Stand::MeatType::CHICKEN, 2.0, 0.3),
	beefStands(NO_OF_BEEF_STANDS, Stand::MeatType::BEEF, 1.0, 1.1),
	generator{rd()} {

	for(int i = 0; i < NO_OF_EMPLOYEES; i++)
		employees.push_back(new Employee());

	static exponential_distribution<> d(0.9);
	next_arrival = d(generator);
}

Restaurant::~Restaurant() {
	employees.clear();
}

void Restaurant::execute() {
	while(simulation_time < max_simulation_time) {

	}
}


void Restaurant::arrivalOfCustomer() {
	//generate a new customer
	auto const newCustomer = new Customer{next_arrival};

	//select a queue based on Bernoulli distribution with 𝑝=0.5
	//put a new customer in the selected queue

	static bernoulli_distribution distribution(0.5);

	if(distribution(generator))
		chickenWrapQueue.push(newCustomer);
	else
		beefWrapQueue.push(newCustomer);

	//schedule the next arrival
	static exponential_distribution<> d(0.9);

	next_arrival = simulation_time + d(generator);
}

void Restaurant::startOfService(int id) {
	//selecting the longest queue, removing a customer from it and providing meat from a stand
	Customer* customer = nullptr;

	if(chickenWrapQueue.size() > beefWrapQueue.size()) {
		customer = chickenWrapQueue.front();
		chickenWrapQueue.pop();

		chickenStands.provideMeat(simulation_time);

	} else {
		customer = beefWrapQueue.front();
		beefWrapQueue.pop();

		beefStands.provideMeat(simulation_time);
	}

	//assigning the customer to the employee and making the employee busy
	employees[id]->serveCustomer(simulation_time, customer, simulation_time + SERVICE_TIME);
}

void Restaurant::completionOfService(int id) {
	//complete the service and make the employee free
	employees[id]->finishService(simulation_time);
}

void Restaurant::advanceSimulationTime() {

}