#ifndef SIMULATION_CUSTOMER_H_
#define SIMULATION_CUSTOMER_H_

// Class that represents a single customer
class Customer {
public:
	Customer(double arrival_time);
	~Customer();

private:
	//const int ID; //commented because the constructor is not defined
	double arrival_time;
};

#endif
