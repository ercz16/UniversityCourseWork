#include <iostream>
#include <string>

using namespace std;

template <typename T>
T GetNumericValue(T min, T max) {
  T value;
  std::cin >> value;
  return value;
}

/*
int GetNumericValue(int min, int max) {
  int value;
  return value;
}

float GetNumericValue(float min, float max) {
  float value;
  return value;
}
*/

int main() {
  string var = GetNumericValue("this", "that");
  cout << var << endl;

  return 0;
} //EOM
//EOF

