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

	void serveCustomer(Customer* customer, double time);
	void finishService();

private:
	bool busy;
	double service_time;
	Customer* serviced_customer;
};

#endif