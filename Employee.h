#ifndef SIMULATION_EMPLOYEE_H_
#define SIMULATION_EMPLOYEE_H_

#include "Customer.h"

// Class that represents a single meat wrapping employee
class Employee {
public:
	Employee();
	~Employee();

	bool getStatus() const;
	double getServiceTime() const;

	void serveCustomer(double simulation_time, Customer* customer, double time);
	double finishService(double simulation_time);

private:
	bool busy;
	double service_time, started_service;
	Customer* serviced_customer;
};

#endif