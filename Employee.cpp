#include "Employee.h"

Employee::Employee() : busy(false), customer(nullptr) {

}

Employee::~Employee() {
	delete customer;
}

void Employee::makeBusy() { busy = true; }
void Employee::makeFree() { busy = false; }
bool Employee::ifBusy() const { return busy; }

void Employee::assignCustomer(Customer* customer) { this->customer = customer; }
void Employee::removeCustomer() { delete customer; }

