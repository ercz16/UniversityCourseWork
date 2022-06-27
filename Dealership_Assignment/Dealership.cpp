#include <string>

#include "Dealership.h"

Dealership::Dealership(std::string name, unsigned int capacity) {
	this->name = name;
	this->capacity = capacity;
}

void Dealership::AddShowroom(Showroom s) {
	if (this->showrooms.size() == this->capacity)
		std::cout << "Dealership is full, can't add another showroom!" << std::endl;
	else
		this->showrooms.push_back(s);
}

float Dealership::GetAveragePrice() {
	if (this->showrooms.size() == 0) return 0.00;
	float sum = 0;
	int numShowRooms = 0;
	for(Showroom &s: this->showrooms) {
		sum += s.GetInventoryValue();
		numShowRooms += s.GetVehicleList().size();
	}
	return sum / numShowRooms;
}

void Dealership::ShowInventory() {
	if (this->showrooms.size() == 0)
		std::cout << "Generic Dealership is empty!" << std::endl;
	else
		for(Showroom s: this->showrooms) {
			s.ShowInventory();
			std::cout << std::endl;
		}

	std::cout << "Average car price: $" << this->GetAveragePrice();
}
