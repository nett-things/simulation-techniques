#ifndef SIMULATION_CUSTOMER_H_
#define SIMULATION_CUSTOMER_H_

// Class that represents a single customer
class Customer {
public:
	Customer();
	~Customer();

private:
	//const int ID; //commented because the constructor is not defined
	float arrivalTime;
};

#endif
