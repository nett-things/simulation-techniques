#include "Employee.h"

Employee::Employee() : busy(false), service_time(-1), customer(nullptr) {

}

Employee::~Employee() {
	delete customer;
}

bool Employee::getStatus() const { return busy; }

double Employee::getServiceTime() const { return service_time; }

void Employee::serveCustomer(Customer* customer, double time) {
	this->customer = customer;
	service_time = time;
	busy = true;
}
void Employee::finishService() {
	//delete customer;
	service_time = -1;
	busy = false;
}

