#include <iostream>
#include <iostream>

#include "DynamicArray.h"

using namespace std;

DynamicArray::DynamicArray(int count) {
  data = new int[count];
  size = count;
  capacity = 0;
}

DynamicArray::DynamicArray(const DynamicArray& other) {
  this->capacity = other.capacity;
  this->size = other.size;

  data = new int[capacity];
  for(int i = 0; i < size; ++i)
    data[i] = other.data[i];
}

DynamicArray::Add(int newNumber) {
  if(size == capacity) {
    int* newArray = new int[size + 1];

    for(int i = 0; i < size; ++i) 
      newArray[i] = data[i];

    newArray[size] = newNumber;

    delete[] data;

    data = newArray;
    capacity++;

  } else {
    data[size] = newNumber;
    size++;
  }

}

DynamicArray::Print() {
  for(int i = 0; i < size; ++i)
    cout << data[i] << endl;
}

//EOF

