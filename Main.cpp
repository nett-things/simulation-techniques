#include <iostream>
#include <fstream>
#include <vector>

#include "RestaurantSim.h"

using namespace std;

int main() {
	Simulation sim(10);
	sim.setMode(Simulation::Mode::STEP_BY_STEP);
	sim.execute();

	return 0;
}