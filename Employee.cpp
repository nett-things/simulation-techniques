#include "Employee.h"

Employee::Employee() : busy(false), service_time(-1), serviced_customer(nullptr) {

}

Employee::~Employee() {
	delete serviced_customer;
}

bool Employee::getStatus() const { return busy; }

double Employee::getServiceTime() const { return service_time; }

void Employee::serveCustomer(Customer* customer, double time) {
	serviced_customer = customer;
	service_time = time;
	busy = true;
}
void Employee::finishService() {
	//delete serviced_customer;
	service_time = -1;
	busy = false;
}

