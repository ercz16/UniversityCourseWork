#pragma once

#include <string>
#include <vector>

class Vehicle {
  private:
    std::string make;
    std::string model;
    unsigned int year;
    float price;
    unsigned int mileage;

  public:
    Vehicle() {
      make = "COP3503";
      model = "Rust Bucket";
      year = 1900;
      price = 0;
      mileage = 0;
    };

    Vehicle(std::string make, std::string model, int year, float price, int mileage);

    void Display();

    std::string GetYearMakeModel();

    float GetPrice();
};
