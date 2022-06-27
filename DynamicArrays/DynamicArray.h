#pragma once

class DynamicArray {
  int* data;
  int size;
  int capacity;

public:
  DynamicArray(int count);

  void Add(int newNumber);

  void Print();

  ~DynamicArray();

}
