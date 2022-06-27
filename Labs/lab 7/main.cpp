#include <iostream>
#include <string>
#include <map>
#include <random>
#include <ctime>
#include <fstream>
using namespace std;

struct State {
  string name;
  int perCapita;
  int population;
  int median;
  int numHouseholds;

  State() {}
  State(string name, int perCapita, int population, int median, int numHouseholds);

  void print();
};

State::State(string name, int perCapita, int population, int median, int numHouseholds) {
  this->name = name;
  this->perCapita = perCapita;
  this->population = population;
  this->median = median;
  this->numHouseholds = numHouseholds;
}

void State::print() {
  cout << name << endl;
  cout << "Population: " << population << endl;
  cout << "Per Capita Income: " << perCapita << endl;
  cout << "Median Household Income: " << median << endl;
  cout << "Number of Households: " << numHouseholds << endl;
}

mt19937 random_mt;

int Random(int min, int max)
{
	uniform_int_distribution<int> dist(min, max);
	return dist(random_mt);
}

int main()
{
	cout << "1. Random Numbers\n";
	cout << "2. State Info\n";

	int option;
	cin >> option;

	if (option == 1)
	{
		int randomSeed;
		cout << "Random seed value: ";
		cin >> randomSeed;
		random_mt.seed(randomSeed);


		cout << "Number of times to roll the die: ";
      // user input
    int numRolls;
    cin >> numRolls;

		cout << "Number of sides on this die: ";
      // user input
    int numSides;
    cin >> numSides;

		// Roll Dice
    map<int, int> myMap;
    for(int i = 0; i < numRolls; ++i) {
      int outcome = Random(1, numSides);
      if (myMap.count(outcome) == 0)
       myMap.emplace(outcome, 1);
      else
       myMap[outcome] = myMap[outcome] + 1; 
    }

    for(int i = 0; i < numSides; ++i)
      cout << i+1 << ": " << myMap[i+1] << endl;

	}
	else if (option == 2)
	{
    map<string, State> myMap;
    // Load the states
    ifstream file("states.csv");
    string tmp;
    string num;
    getline(file, tmp);
    int arr[4];
    while(!file.eof()) {
      getline(file, tmp, ',');
      for(int i = 0; i < 3; i++) {
        getline(file, num, ',');
        arr[i] = stoi(num);
      }
      getline(file, num);
      arr[3] = stoi(num);
      myMap[tmp] = State(tmp, arr[0], arr[1], arr[2], arr[3]);
    }

    cout << "1. Print all states" << endl;
    cout << "2. Search for a state" << endl;
    cin >> option;
    if (option == 1) {
      for(auto iter = ++myMap.begin(); iter != myMap.end(); ++iter)
        iter->second.print();
    } else if (option == 2) {
      string query;
      cin.ignore();
      getline(cin, query);
      bool found = false;
      for (auto iter = myMap.begin(); iter != myMap.end(); ++iter) {
        if (iter->first == query) {
          found = true; 
          iter->second.print();
        }
      }
      if (!found) {
        cout << "No match found for " << query << endl;
      }
    }

  }

	return 0;
}

