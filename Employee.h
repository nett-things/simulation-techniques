#ifndef SIMULATION_EMPLOYEE_H_
#define SIMULATION_EMPLOYEE_H_

#include "Customer.h"

// Class that represents a single meat wrapping employee
class Employee {
public:
	Employee();
	~Employee();

	void makeBusy();
	void makeFree();
	bool ifBusy() const;

	void assignCustomer(Customer* customer);
	void removeCustomer();

private:
	bool busy;
	Customer* customer;
};

#endif