#include <string>
#include <iostream>

#include "Vehicle.h"

Vehicle::Vehicle(std::string make, std::string model, int year, float price, int mileage) {
  this->make = make;
  this->model = model;
  this->year = year;
  this->price = price;
  this->mileage = mileage;
}

void Vehicle::Display() {
  std::cout << this->year << " " << this->make << " " << this->model << " " << "$" << this->price << " " << this->mileage << std::endl;
}

std::string Vehicle::GetYearMakeModel() {
  return std::to_string(this->year) + " " + this->make + " " + this->model;
}

float Vehicle::GetPrice() {
  return this->price;
}
