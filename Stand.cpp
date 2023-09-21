#include "Stand.h"

Stand::Stand()
	: Stand(1, MeatType::UNDEFINED, 1.0, 0.1) {
}

Stand::Stand(int number_of_stands, MeatType type_of_meat, double mean, double variance)
	: NO_OF_STANDS(number_of_stands),
	TYPE_OF_MEAT(type_of_meat),
	MEAN(mean),
	VARIANCE(variance),
	sliced_meat(0.0),
	storage_time(-1),
	total_storage_time(0.0),
	storage_units(0) { }

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
			for(int i = 0; i < NO_OF_STANDS; i++)
				sliced_meat += distribution(generator);

			//average storage time update
			total_storage_time += simulation_time - storage_time;
			storage_units++;

			//update the storage time
			storage_time = simulation_time;

		} while(sliced_meat < 1);

		cerr << "[slicingOfMeat] \ttime: " << simulation_time << "; meat: " << (TYPE_OF_MEAT == MeatType::CHICKEN ? "chicken" : (TYPE_OF_MEAT == MeatType::BEEF ? "beef" : "undefined")) << "; stored amount: " << sliced_meat << endl;
	}

	// remove a unit of meat
	sliced_meat -= 1;
}

double Stand::getAverageStorageTime() const {
	return total_storage_time/storage_units;
}
