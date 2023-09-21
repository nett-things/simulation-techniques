#ifndef SIMULATION_CUSTOMER_H_
#define SIMULATION_CUSTOMER_H_

// Class that represents a single customer
class Customer {
public:
	Customer();
	Customer(double arrival_time);

	~Customer();

	void setArrivalTime(double time);
	double getArrivalTime() const;

private:
	//const int ID;
	double arrival_time;
};

#endif
