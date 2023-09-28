#include "Employee.h"

Employee::Employee() : busy(false), service_time(-1), started_service(0.0), serviced_customer(nullptr) {}

Employee::~Employee() {
	delete serviced_customer;
}

bool Employee::getStatus() const {
	return busy;
}

double Employee::getServiceTime() const {
	return service_time;
}

void Employee::serveCustomer(double simulation_time, Customer* customer, double time) {
	serviced_customer = customer;
	service_time = time;
	busy = true;

	started_service = simulation_time;
}

double Employee::finishService(double simulation_time) {
	const double waiting_time = simulation_time - serviced_customer->getArrivalTime();

	service_time = -1;
	busy = false;

	delete serviced_customer;

	return waiting_time;
}

