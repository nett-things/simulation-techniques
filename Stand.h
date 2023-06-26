#ifndef SIMULATION_STAND_H_
#define SIMULATION_STAND_H_

#include <queue>
#include <random>

using namespace std;

/*class Meat {
p8ublic:
	//SlicedMeat();

private:
	float weight, timeOfSlicing;
};*/

// Class that represents a single meat stand that generates one type of meat
class Stand {
public:
	Stand();
	Stand(double mean, double variance);

	~Stand();

	void provideMeat();

private:
	const double MEAN, VARIANCE;

	double slicedMeat; //queue<Meat*> slicedMeat;
};


#endif