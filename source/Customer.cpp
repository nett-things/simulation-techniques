#include "Customer.h"

Customer::Customer() : Customer(-1) { }
Customer::Customer(double arrival_time) : arrival_time(arrival_time) { }

Customer::~Customer() { }

void Customer::setArrivalTime(double time) {
	arrival_time = time;
}

double Customer::getArrivalTime() const {
	return arrival_time;
}



