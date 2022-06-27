#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct LegoSet {
	int setNumber;
	string theme;
	string name;
	int numMinifigs;
	int numParts;
	double price;

	void print() {
		cout << "Name: " << name << endl;
		cout << "Number: " << setNumber << endl;
		cout << "Theme: " << theme << endl;
		cout << "Price: $" << price << endl;
		cout << "Minifigures: " << numMinifigs << endl;
		cout << "Piece count: " << numParts << endl;
	}
};

struct Collection {
	vector<LegoSet> sets;
	int maxPriceInd;
	int minPriceInd;

	int maxPartsInd;

	int numSets;

	Collection() {
		numSets = 0;
	}

	void setMaxMinPrice() {
		double maxPrice = 0;
		double minPrice = 10000000;
		int maxParts = 0;
		for (int i = 0; i < (int)sets.size(); ++i) {
			if (sets[i].price > maxPrice) {
				maxPrice = sets[i].price;
				maxPriceInd = i;
			}
			if (sets[i].price < minPrice) {
				minPrice = sets[i].price;
				minPriceInd = i;
			}
			if (sets[i].numParts > maxParts) {
				maxParts = sets[i].numParts;
				maxPartsInd = i;
			}
		}
	}

	void mostExpensive() {
		cout << "The most expensive set is: " << endl;
		sets[maxPriceInd].print();
	}

	void mostParts() {
		cout << "The set with the highest parts count: " << endl;
		sets[maxPartsInd].print();
	}

	void searchNames() {
		string keyphrase;
		getline(cin, keyphrase);

		bool found = false;
		for (int i = 0; i < (int)sets.size(); ++i) {
			if ((int)sets[i].name.find(keyphrase) != -1) {
				if(!found)
					cout << "Sets matching \"" << keyphrase << "\":" << endl;
				found = true;
				cout << sets[i].setNumber << " " << sets[i].name << " $" << sets[i].price << endl;
			}
		}
		if(!found)
			cout << "No sets found matching that search term" << endl;
	}

	void searchThemes() {
		string keyphrase;
		getline(cin, keyphrase);
		
		bool found = false;
		for (int i = 0; i < (int)sets.size(); ++i) {
			if ((int)sets[i].theme.find(keyphrase) != -1) {
				if(!found)
					cout << "Sets matching \"" << keyphrase << "\":" << endl;
				found = true;
				cout << sets[i].setNumber << " " << sets[i].name << " $" << sets[i].price << endl;
			}
		}
		if(!found)
			cout << "No sets found matching that search term" << endl;
	}

	void showAveragePartCount() {
		int total = 0;
		for (int i = 0; i < (int)sets.size(); ++i) {
			total += sets[i].numParts;
		}
		int average = total / sets.size();
		cout << "Average part count for " << sets.size() << " sets: " << average << endl;
	}

	void searchPriceInformation() {
		double total = 0;
		for (int i = 0; i < (int)sets.size(); ++i) {
			total += sets[i].price;
		}
		double average = (double)total / sets.size();
		cout << "Average price for " << sets.size() << " sets: $" << average << endl;
		cout << endl;
		cout << "Least expensive set: " << endl;
		sets[minPriceInd].print();

		cout << "Most expensive set: " << endl;
		sets[maxPriceInd].print();
	}	

	void searchMinifigure() {
		int largest = 0;;
		int largestInd = 0;
		int total = 0;
		for (int i = 0; i < (int)sets.size(); ++i) {
			if(sets[i].numMinifigs > largest) {
				largest = sets[i].numMinifigs;
				largestInd = i;
			}
			total += sets[i].numMinifigs;
		}
		int average = total / sets.size();
		cout << "Average number of minifigures: " << average << endl;
		cout << "Set with the most minifigures: " << endl;
		sets[largestInd].print();
	}

	void ifYouBoughtOneOfEverything() {
		double totalPrice = 0;
		int totalPieces = 0;
		int totalMinifigures = 0;

		for (int i = 0; i < (int)sets.size(); ++i) {
			totalPrice += sets[i].price;
			totalPieces += sets[i].numParts;
			totalMinifigures += sets[i].numMinifigs;
		}
		cout << "If you bought one of everything..." << endl;
		cout << "It would cost: $" << totalPrice << endl;
		cout << "You would have " << totalPieces << " pieces in your collection" << endl;
		cout << "You would have an army of " << totalMinifigures << " minifigures!" << endl;
	}

	void handleOptions(int option) {
		string fname;
		if(option == 1) {
			load("lego1.csv");
		}
		else if(option == 2) {
			load("lego2.csv");
		}
		else if(option == 3) {
			load("lego3.csv");
		}
		else if(option == 4) {
			load("lego1.csv");
			load("lego2.csv");
			load("lego3.csv");
		}
	}

	void load(string fname) {
		ifstream infile(fname);

		if (infile.is_open()) {
			int totalSets = 0;

			string tmp;
			getline(infile, tmp);
			while (!infile.eof()) {
				LegoSet s;

				getline(infile, tmp, ',');
				s.setNumber = stoi(tmp);

				getline(infile, tmp, ',');
				s.theme = tmp;

				getline(infile, tmp, ',');
				s.name = tmp;

				getline(infile, tmp, ',');
				s.numMinifigs = stoi(tmp);

				getline(infile, tmp, ',');
				int parts = stoi(tmp);
				s.numParts = parts;

				getline(infile, tmp);
				double price = stod(tmp);
				s.price = price;

				sets.push_back(s);
				totalSets++;
			}
			numSets += totalSets;
		}
		setMaxMinPrice();
	}
};




int main()
{
	cout << std::fixed << setprecision(2);
	cout << "Which file(s) to open?\n";
	cout << "1. lego1.csv" << endl;
	cout << "2. lego2.csv" << endl;
	cout << "3. lego3.csv" << endl;
	cout << "4. All 3 files" << endl;
	int option;
	cin >> option;

   /*======= Load data from file(s) =======*/
	Collection col;

	col.handleOptions(option);

   cout << "1. Most Expensive set" << endl;
	cout << "2. Largest piece count" << endl;
	cout << "3. Search for set name containing..." << endl;
	cout << "4. Search themes..." << endl;
	cout << "5. Part count information" << endl;
	cout << "6. Price information" << endl;
	cout << "7. Minifigure information" << endl;
	cout << "8. If you bought one of everything..." << endl;
	cout << "0. Exit" << endl;
   
	int choice;
	cin >> choice;
   cin.get();  // Clear newline character for any later input
   
   /*======= Print out how many sets were loaded =======*/
   cout << "Total number of sets: " << col.numSets << endl << endl;

   /*======= Based on the choice, execute the appropriate task and show the results =======*/
   if (choice == 1) {
   	col.mostExpensive();
   } else if (choice == 2) {
   	col.mostParts();
   } else if (choice == 3) {
   	col.searchNames();
   } else if (choice == 4) {
   	col.searchThemes();
   } else if (choice == 5) {
   	col.showAveragePartCount();
   } else if (choice == 6) {
   	col.searchPriceInformation();
   } else if (choice == 7) {
   	col.searchMinifigure();
   } else if (choice == 8) {
   	col.ifYouBoughtOneOfEverything();
   }
   
	return 0;
}


