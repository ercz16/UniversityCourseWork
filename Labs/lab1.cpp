#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

int main() {
  string title,
         col1,
         col2;

  string datapoint;
  vector<int> intComponents;
  vector<string> stringComponents;

  //part 1
  cout << "Enter a title for the data:" << endl;
  getline(cin, title);
  cout << "You entered: " << title << endl;

  //part 2
  cout << "Enter the column 1 header:" << endl;
  getline(cin, col1);
  cout << "You entered: " << col1 << endl;

  cout << "Enter the column 2 header:" << endl;
  getline(cin, col2);
  cout << "You entered: " << col2 << endl;

  //part 3
  int number;
  string name;
  while(true) {
    cout << "Enter a data point (-1 to stop input):" << endl;
    getline(cin, datapoint);

    if(datapoint == "-1") break;

    //part 4
    int pos = 0;
    int count = 0;
    for (int i = 0; i < datapoint.size(); i++)
      if(datapoint[i] == ',') {
        pos = i;
        count++;
      }

    if (count < 1)
      cout << "Error: No comma in string." << endl;
    else if (count > 1)
      cout << "Error: Too many commas in input." << endl;
    else {
      try {
        number = stoi(datapoint.substr(pos+1));
        name = datapoint.substr(0, pos);
        stringComponents.push_back(name);
        intComponents.push_back(number);
        cout << "Data string: " << name << endl;
        cout << "Data integer: " << number << endl;
      } catch (const exception& e) {
        cout << "Error: Comma not followed by an integer." << endl;
      }
    }
  }

  //part 5
  cout << endl << right << setw(33) << title << endl;
  cout << left << setw(20) << col1 << "|" << right << setw(23) << col2 << endl;
  for(int i = 0; i < 44; ++i) cout << '-';
  cout << endl;
  for(int i = 0; i < intComponents.size(); ++i) {
    cout << left << setw(20) << stringComponents[i] << "|" << right << setw(23) << intComponents[i] << endl;
  }
  cout << endl;

  //part 6
  for(int i = 0; i < intComponents.size(); ++i) {
    cout << right << setw(20) << stringComponents[i] << " ";
    for(int j = 0; j < intComponents[i]; ++j) cout << "*";
    cout << endl;
  }

  return 0;
} //EOM
//EOF

