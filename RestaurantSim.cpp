#include "RestaurantSim.h"

Restaurant::Restaurant() : Restaurant(1000) { }

Restaurant::Restaurant(double max_time)
	: SERVICE_TIME(0.6),
	NO_OF_EMPLOYEES(1),
	NO_OF_CHICKEN_STANDS(2),
	NO_OF_BEEF_STANDS(5),
	simulation_time(0),
	max_simulation_time(max_time),
	total_waiting_time(0.0),
	num_of_served_customers(0),
	total_chicken_queue(0),
	total_beef_queue(0),
	num_of_chicken_queue_changes(0),
	num_of_beef_queue_changes(0),
	chickenStands(NO_OF_CHICKEN_STANDS, Stand::MeatType::CHICKEN, 2.0, 0.3),
	beefStands(NO_OF_BEEF_STANDS, Stand::MeatType::BEEF,1.0, 1.1 ),
	sampling(false),
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

		if(simulation_time > 0.0 && sampling)
			data_set.push_back(encapsulateData());
		

		advanceSimulationTime();
	}
}

void Restaurant::sampleEveryTimeAdvance(bool if_sampling) {
	sampling = if_sampling;
}

double Restaurant::getAverageWaitingTime() const {
	return total_waiting_time / num_of_served_customers;
}

double Restaurant::getAverageChickenStorageTime() const {
	return chickenStands.getAverageStorageTime();
}
double Restaurant::getAverageBeefStorageTime() const {
	return beefStands.getAverageStorageTime();
}
double Restaurant::getAverageMeatStorageTime() const {
	return (chickenStands.getAverageStorageTime() + beefStands.getAverageStorageTime()) / 2;
}
double Restaurant::getAverageChickenQueueLength() const {
	return total_chicken_queue * 1.0 / num_of_chicken_queue_changes;
}
double Restaurant::getAverageBeefQueueLength() const {
	return total_beef_queue * 1.0 / num_of_beef_queue_changes;
}
double Restaurant::getAverageQueueLength() const {
	return (getAverageChickenQueueLength() + getAverageBeefQueueLength()) / 2;
}

double Restaurant::getAverageEmployeeTimeUtilization() const {
	double average_busy_time = 0;
	for(int i = 0; i < NO_OF_EMPLOYEES; i++)
		average_busy_time += employees[i]->getTotalBusyTime();
	average_busy_time /= NO_OF_EMPLOYEES;

	return average_busy_time / simulation_time * 100;
}

void Restaurant::printResults() const {
	cout << "Average customer waiting time: \t\t" << getAverageWaitingTime() << endl;
	cout << "Average storage time of chicken meat: \t" << getAverageChickenStorageTime() << endl;
	cout << "Average storage time of beef meat: \t" << getAverageBeefStorageTime() << endl;
	cout << "Average storage time of all meat: \t" << getAverageMeatStorageTime() << endl;
	cout << "Average chicken wrap queue length: \t" << getAverageChickenQueueLength() << endl;
	cout << "Average beef wrap queue length: \t" << getAverageBeefQueueLength() << endl;
	cout << "Average queue length: \t\t\t" << getAverageQueueLength() << endl;
	cout << "Average utilization of employee time: \t" << getAverageEmployeeTimeUtilization() << "%" << endl;
}

Restaurant::Data Restaurant::getData() const {
	return encapsulateData();
}

vector<Restaurant::Data> Restaurant::getDataSet() {
	return data_set;
}

void Restaurant::arrivalOfCustomer() {
	//generate a new customer
	auto const newCustomer = new Customer{next_arrival};

	//select a queue based on Bernoulli distribution with 𝑝=0.5
	//put a new customer in the selected queue

	static bernoulli_distribution distribution(0.5);

	if(distribution(generator)) {
		chickenWrapQueue.push(newCustomer);
		updateChickenQueueData();

	} else {
		beefWrapQueue.push(newCustomer);
		updateBeefQueueData();
	}

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

		chickenStands.provideMeat(simulation_time);

		updateChickenQueueData();

	} else {
		customer = beefWrapQueue.front();
		beefWrapQueue.pop();

		beefStands.provideMeat(simulation_time);

		updateBeefQueueData();
	}

	//const auto longest_queue = (chickenWrapQueue.size() > beefWrapQueue.size()) ? &chickenWrapQueue : &beefWrapQueue;

	//const auto customer = longest_queue->front();
	//longest_queue->pop();

	//assigning the customer to the employee and making the employee busy
	employees[id]->serveCustomer(simulation_time, customer, simulation_time + SERVICE_TIME);

	cerr << "[startOfService] \ttime: " << simulation_time << "; employee: " << id << endl;
}

void Restaurant::completionOfService(int id) {
	//complete the service and make the employee free
	total_waiting_time += employees[id]->finishService(simulation_time);
	num_of_served_customers++;

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

void Restaurant::updateChickenQueueData() {
	total_chicken_queue += chickenWrapQueue.size();
	num_of_chicken_queue_changes++;
}

void Restaurant::updateBeefQueueData() {
	total_beef_queue += beefWrapQueue.size();
	num_of_beef_queue_changes++;
}

Restaurant::Data Restaurant::encapsulateData() const {
	Data data = Data{};

	data.simulation_time = simulation_time;
	data.average_waiting_time = getAverageWaitingTime();
	data.average_chicken_storage_time = getAverageChickenStorageTime();
	data.average_beef_storage_time = getAverageBeefStorageTime();
	data.average_meat_storage_time = getAverageMeatStorageTime();
	data.average_chicken_queue_length = getAverageChickenQueueLength();
	data.average_beef_queue_length = getAverageBeefQueueLength();
	data.average_queue_length = getAverageQueueLength();
	data.average_employee_time_utilization = getAverageEmployeeTimeUtilization();

	return data;
}

