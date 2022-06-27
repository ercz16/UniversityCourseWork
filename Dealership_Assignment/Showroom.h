#pragma once

#include <string>
#include <iostream>

#include "Vehicle.h"

class Showroom {
  private:
    std::string name;
    std::vector<Vehicle> vehicles;
    int capacity;

  public:
    Showroom(std::string name = "Unnamed Showroom", unsigned int capacity = 0);
    
    std::vector<Vehicle> GetVehicleList();

    void AddVehicle(Vehicle v);
    void ShowInventory();
    float GetInventoryValue();
};
