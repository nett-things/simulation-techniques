#ifndef SIMULATION_STAND_H_
#define SIMULATION_STAND_H_

#include <iostream>
#include <random>
#include <cmath>

using namespace std;

// Class that represents a single meat stand that generates one type of meat
class Stand {
public:
	enum MeatType {
		UNDEFINED, CHICKEN, BEEF
	};

	Stand();
	Stand(int number_of_stands, MeatType type_of_meat, double mean, double variance);

	~Stand();

	double getMeat() const;
	void provideMeat(double simulation_time, bool print);

private:
	const int NO_OF_STANDS;
	const MeatType TYPE_OF_MEAT;
	const double MEAN, VARIANCE;

	double sliced_meat, storage_time;
};


#endif