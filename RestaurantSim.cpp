#include "RestaurantSim.h"

Restaurant::Restaurant()
	: SERVICE_TIME(0.6),
	NO_OF_EMPLOYEES(1),
	NO_OF_CHICKEN_STANDS(2),
	NO_OF_BEEF_STANDS(5),
	simulation_time(0),
	max_simulation_time(10),
	generator{rd()} {

	for(int i = 0; i < NO_OF_EMPLOYEES; i++)
		employees.push_back(new Employee());

	for(int i = 0; i < NO_OF_CHICKEN_STANDS; i++)
		chickenStands.push_back(new Stand(2.0, 0.3));

	for(int i = 0; i < NO_OF_BEEF_STANDS; i++)
		beefStands.push_back(new Stand(1.0, 1.1));

	static exponential_distribution<> d(0.9);
	next_arrival = d(generator);
}

Restaurant::~Restaurant() {
	employees.clear();
	chickenStands.clear();
	beefStands.clear();
}

void Restaurant::execute() {
	while(simulation_time < max_simulation_time) {
		bool no_event_triggered = false;

		while(!no_event_triggered) {
			no_event_triggered = true;

			if(simulation_time == next_arrival) {
				arrivalOfCustomer();
				no_event_triggered = false;
			}

			for(int i = 0; i < NO_OF_EMPLOYEES; i++) {
				if(simulation_time == employees[i]->getServiceTime()) {
					completionOfService(i);
					no_event_triggered = false;
				}
				if(!employees[i]->getStatus() && (!chickenWrapQueue.empty() || !beefWrapQueue.empty())) {
					startOfService(i);
					no_event_triggered = false;
				}
			}
		}

		advanceSimulationTime();
	}
}

void Restaurant::arrivalOfCustomer() {
	//generate a new customer

	auto newCustomer = Customer{next_arrival};

	//select a queue based on Bernoulli distribution with 𝑝=0.5
	//put a new customer in the selected queue

	static bernoulli_distribution distribution(0.5);

	if(distribution(generator))
		chickenWrapQueue.push(&newCustomer);
	else
		beefWrapQueue.push(&newCustomer);

	cerr << "[arrivalOfCustomer] \ttime: " << simulation_time << "; \tchicken queue size: " << chickenWrapQueue.size() << "; beef queue size: " << beefWrapQueue.size() << endl;

	//schedule the next arrival
	static exponential_distribution<> d(0.9);

	next_arrival = simulation_time + d(generator);
}

void Restaurant::startOfService(int id) {
	//selecting the longest queue and removing a customer from it
	const auto longest_queue = (chickenWrapQueue.size() > beefWrapQueue.size()) ? &chickenWrapQueue : &beefWrapQueue;

	const auto customer = longest_queue->front();
	longest_queue->pop();

	//assigning the customer to the employee and making the employee busy
	employees[id]->serveCustomer(customer, simulation_time + SERVICE_TIME);

	cerr << "[startOfService] \ttime: " << simulation_time << "; \temployee: " << id << endl;
}

void Restaurant::completionOfService(int id) {
	//complete the service and make the employee free
	employees[id]->finishService();
	cerr << "[completionOfService] \ttime: " << simulation_time << "; \temployee: " << id << endl;
}

void Restaurant::advanceSimulationTime() {
	double min_time = next_arrival;

	for(int i = 0; i < NO_OF_EMPLOYEES; i++) {
		double departure_time = employees[i]->getServiceTime();
		min_time = ((departure_time > 0) && (departure_time < min_time)) ? departure_time : min_time;
	}

	simulation_time = min_time;
}

