#pragma once

#include <string>
#include <vector>

#include "Showroom.h"

class Dealership {
  private:
  	std::string name;
  	std::vector<Showroom> showrooms;
  	int capacity;

  public:
    //Constructor
    Dealership(std::string name = "Generic Dealership", unsigned int capacity = 0);

    // Behaviors
    void AddShowroom(Showroom s);
    float GetAveragePrice();
    void ShowInventory();
};
