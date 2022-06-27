#include <iostream>
#include <string>

#include "Showroom.h"

Showroom::Showroom(std::string name, unsigned int capacity) {
	this->name = name;
	this->capacity = capacity;
}

std::vector<Vehicle> Showroom::GetVehicleList() {
	return this->vehicles;
}

void Showroom::AddVehicle(Vehicle v) {
	if (this->vehicles.size() == this->capacity)
		std::cout << "Showroom is full! Cannot add " << v.GetYearMakeModel() << std::endl;
	else
		this->vehicles.push_back(v);
}

void Showroom::ShowInventory() {
	if (this->vehicles.size() == 0)
		std::cout << "Unnamed Showroom is empty!" << std::endl;
	else if (this->vehicles.size() == this->capacity) {
		std::cout << "Vehicles in " << this->name << std::endl;
		for (Vehicle &v: this->vehicles) v.Display();
	}
	else {
		std::cout << "Vehicles in " << this->name << std::endl;
		for (Vehicle &v: this->vehicles) v.Display();
	}
}

float Showroom::GetInventoryValue() {
	float sum = 0;
	for(Vehicle &v: this->vehicles)
		sum += v.GetPrice();
	return sum;
}
