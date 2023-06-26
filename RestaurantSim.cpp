#include "RestaurantSim.h"

Restaurant::Restaurant()
	: SERVICE_TIME(0.6f),
	NO_OF_EMPLOYEES(1),
	NO_OF_CHICKEN_STANDS(2),
	NO_OF_BEEF_STANDS(5) {
}

Restaurant::~Restaurant() {
}

void Restaurant::init() {
	for(int i = 0; i < NO_OF_EMPLOYEES; i++)
		employees.push_back(new Employee());

	for(int i = 0; i < NO_OF_CHICKEN_STANDS; i++)
		chickenStands.push_back(new Stand(2.0, 0.3));

	for(int i = 0; i < NO_OF_BEEF_STANDS; i++)
		beefStands.push_back(new Stand(1.0, 1.1));
}

void Restaurant::execute() {
	do {
		//sim_time = nearest time event
		bool no_eventtrig;
		do {
			no_eventtrig = true;

			//if conditions met, start service and set no_eventtrig = false;
			
		} while(!no_eventtrig);
	} while((sim_time < 1000)); //limiting sim time

}

void Restaurant::arrivalOfCustomer() {
	//select a queue based on Bernoulli distribution with 𝑝=0.5
	//put a new customer in the selected queue

	auto newCustomer = Customer{};

	static random_device rd{};
	static mt19937 generator{rd()};
	static bernoulli_distribution distribution(0.5);

	if(distribution(generator))
		chickenWrapQueue.push(&newCustomer);
	else
		beefWrapQueue.push(&newCustomer);

	// TODO schedule the next arrival

	static exponential_distribution<> d(1);
}

void Restaurant::completionOfService() {
	// delete the customer and make the employee free

}

void Restaurant::startOfService() {
	//selecting the longest queue and removing a customer from it
	const auto longest_queue = (chickenWrapQueue.size() > beefWrapQueue.size()) ? &chickenWrapQueue : &beefWrapQueue;

	const auto customer = longest_queue->front();
	longest_queue->pop();

	//selecting a free employee
	Employee* free_employee = nullptr;

	for(auto i : employees)
		if(!i->ifBusy()) {
			free_employee = i;
			break;
		}

	//assigning the customer to the employee and making the employee busy
	free_employee->assignCustomer(customer);
	free_employee->makeBusy();

	// TODO calculating the completion of service
}

