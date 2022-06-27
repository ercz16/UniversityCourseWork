#include <iostream>
#include <vector>
#include "DynamicArray.h"

using namespace std;

int main() {
  vector<int> numbers;

  DynamicArray one(5);
  one.add(5);
  one.add(10);
  one.add(15);
  one.add(20);
  one.add(20);
  one.add(99999);

  one.Print();

  return 0;
} //EOM
//EOF

