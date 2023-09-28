#include "Stand.h"

Stand::Stand()
	: Stand(1, UNDEFINED, 1.0, 0.1) {
}

Stand::Stand(int number_of_stands, MeatType type_of_meat, double mean, double variance)
	: NO_OF_STANDS(number_of_stands),
	TYPE_OF_MEAT(type_of_meat),
	MEAN(mean),
	VARIANCE(variance),
	sliced_meat(0.0),
	storage_time(-1) { }

Stand::~Stand() {
	
}

double Stand::getMeat() const { return sliced_meat; }

void Stand::provideMeat(double simulation_time) {
	static random_device rd{};
	static mt19937 generator{rd()};

	static normal_distribution<> distribution{MEAN, VARIANCE};


	//if there is less than 1 unit of meat, slice it
	if(sliced_meat < 1) {
		do {
			for(int i = 0; i < NO_OF_STANDS; i++) {
				const double meat = distribution(generator);
				sliced_meat += (meat < 0.1) ? 0.1 : meat;
			}

		} while(sliced_meat < 1);

		//update the storage time
		storage_time = simulation_time;
	}

	// remove a unit of meat
	sliced_meat -= 1;
}