#include "Stand.h"

Stand::Stand()
	: Stand(1.0, 0.1) {
}

Stand::Stand(double mean, double variance)
	: MEAN(mean),
	VARIANCE(variance) {

	slicedMeat = 0.0;
}

Stand::~Stand() {
	
}

void Stand::provideMeat() {
	static random_device rd{};
	static mt19937 generator{rd()};

	static normal_distribution<> distribution{MEAN, VARIANCE};

	// if there is less than 1 of slicedMeat, slice the meat
	if(slicedMeat < 1)
		slicedMeat += distribution(generator);

	// remove a unit of meat
	slicedMeat -= 1;
}
