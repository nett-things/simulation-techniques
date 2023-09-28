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
	operation_mode(CONTINUOUS),
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
	if(operation_mode == STEP_BY_STEP)
		cerr << "[simulation] \t\tstarted at time: " << simulation_time << endl;

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

	if(operation_mode == STEP_BY_STEP)
		cerr << "[simulation] \t\tended at time: " << simulation_time << endl;
}

void Restaurant::setMode(Mode mode) {
	operation_mode = mode;

	if(operation_mode == STEP_BY_STEP)
		cerr << "[simulation] \t\tmode set to STEP_BY_STEP" << endl;
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

	if(operation_mode == STEP_BY_STEP)
		cerr << "[arrivalOfCustomer] \ttime: " << simulation_time << "; chicken queue size: " << chickenWrapQueue.size() << "; beef queue size: " << beefWrapQueue.size() << endl;

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

		chickenStands.provideMeat(simulation_time, (operation_mode == STEP_BY_STEP) ? true : false);

	} else {
		customer = beefWrapQueue.front();
		beefWrapQueue.pop();

		beefStands.provideMeat(simulation_time, (operation_mode == STEP_BY_STEP) ? true : false);
	}

	//assigning the customer to the employee and making the employee busy
	employees[id]->serveCustomer(simulation_time, customer, simulation_time + SERVICE_TIME);

	if(operation_mode == STEP_BY_STEP)
		cerr << "[startOfService] \ttime: " << simulation_time << "; employee: " << id << endl;
}

void Restaurant::completionOfService(int id) {
	//complete the service and make the employee free
	employees[id]->finishService(simulation_time);

	if(operation_mode == STEP_BY_STEP)
		cerr << "[completionOfService] \ttime: " << simulation_time << "; employee: " << id << endl;
}

void Restaurant::advanceSimulationTime() {
	double min_time = next_arrival;

	for(int i = 0; i < NO_OF_EMPLOYEES; i++) {
		double departure_time = employees[i]->getServiceTime();
		min_time = ((departure_time > 0) && (departure_time < min_time)) ? departure_time : min_time;
	}

	simulation_time = min_time;
}