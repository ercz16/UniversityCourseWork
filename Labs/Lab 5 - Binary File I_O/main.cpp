#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>

using namespace std;

struct Weapon {
	string name_;
	int powerRating_;
	float powerConsumption_;
};

struct Ship {
	string name_;
	string class_;
	short length;
	int shieldCapacity;
	float maxWarpSpeed;

	vector<Weapon> inventory;

	void print() {
		cout << "Name: " << name_ << endl;
		cout << "Class: " << class_ << endl;
		cout << "Length: " << length << endl;
		cout << "Shield capacity: " << shieldCapacity << endl;
		cout << "Maximum Warp: " << maxWarpSpeed << endl;
		cout << "Armaments:" << endl;
		if (inventory.size() == 0)
			cout << "Unarmed" << endl;
		else {
			int totalPower = 0;
			for (int k = 0; (long unsigned int)k < inventory.size(); ++k) {
				totalPower += inventory[k].powerRating_;
				cout << inventory[k].name_ << ", "
				     << inventory[k].powerRating_ << ", " 
				     << inventory[k].powerConsumption_
				     << endl;
			}
			cout << "Total firepower: " << totalPower << endl;
		}

		cout << endl;
	}
};

struct Collection {
	vector<Ship> garage;

	void read(string fname) {
		ifstream inFile(fname, ios_base::binary);

		int shipCount;

		int nameLength;
		int classLength;

		int weaponCount;

		inFile.read((char*)&shipCount, 4);

		for(int i = 0; i < shipCount; ++i) {
			Ship newShip;

			// Read in name
			inFile.read((char*)&nameLength, 4);
			char* buffer = new char[nameLength];
			inFile.read(buffer, nameLength);
			newShip.name_ = buffer;
			delete [] buffer;

			// Read in class
			inFile.read((char*)&classLength, 4);
			buffer = new char[classLength];
			inFile.read(buffer, classLength);
			newShip.class_ = buffer;
			delete [] buffer;

			// Read in length 
			inFile.read((char*)&newShip.length, 2);

			// Read in shield capacity
			inFile.read((char*)&newShip.shieldCapacity, 4);

			// Read in maximum warp speed
			inFile.read((char*)&newShip.maxWarpSpeed, 4);

			// Read in weapons and push back into inventory
			inFile.read((char*)&weaponCount, 4);
			for(int j = 0; j < weaponCount; ++j) {
				Weapon w;
				int weaponNameLength;

				inFile.read((char*)&weaponNameLength, 4);
				buffer = new char[weaponNameLength];
				inFile.read(buffer, weaponNameLength);
				w.name_ = buffer;
				delete [] buffer;

				inFile.read((char*)&w.powerRating_, 4);
				inFile.read((char*)&w.powerConsumption_, 4);

				newShip.inventory.push_back(w);
			}

			// Append to garage
			garage.push_back(newShip);
		}
	}

	void print() {
		for(int i = 0; (long unsigned int)i < garage.size(); ++i) {
			garage[i].print();
		}
	}

	void strongest() {
		int highestPower = INT_MIN;
		int ind = -1;
		for(int i = 0; (long unsigned int)i < garage.size(); ++i) {
			for(int j = 0; (long unsigned int)j < garage[i].inventory.size(); ++j) {
				if(garage[i].inventory[j].powerRating_ > highestPower) {
					highestPower = garage[i].inventory[j].powerRating_;
					ind = i;
				}
			}
		}
		if(ind != -1)
			garage[ind].print();
	}

	void strongestOverall() {
		int highestPower = INT_MIN;
		int ind = -1;
		for(int i = 0; (long unsigned int)i < garage.size(); ++i) {
			int powerSum = 0;
			for(int j = 0; (long unsigned int)j < garage[i].inventory.size(); ++j) {
				powerSum += garage[i].inventory[j].powerRating_;
			}
			if(powerSum > highestPower) {
				highestPower = powerSum;
				ind = i;
			}
		}
		if(ind != -1)
			garage[ind].print();
	}

	void weakest() {
		int lowestPower = INT_MAX;
		int ind = -1;
		for(int i = 0; (long unsigned int)i < garage.size(); ++i) {

			if(garage[i].inventory.size() == 0) 
				continue;
			int powerSum = 0;
			for(int j = 0; (long unsigned int)j < garage[i].inventory.size(); ++j) {
				powerSum += garage[i].inventory[j].powerRating_;
			}
			if(powerSum < lowestPower) {
				lowestPower = powerSum;
				ind = i;
			}
		}
		if(ind != -1)
			garage[ind].print();
	}

	void unarmed() {
		for(int i = 0; (long unsigned int)i < garage.size(); ++i) {
			if(garage[i].inventory.size() == 0)
				garage[i].print();
		}
	}
};

int main()
{
	cout << "Which file(s) to open?\n";
	cout << "1. friendlyships.shp" << endl;
	cout << "2. enemyships.shp" << endl;
	cout << "3. Both files" << endl;
	int option;
	cin >> option;

   /* Load files here */
	Collection c;
	if (option == 1)
		c.read("friendlyships.shp");
	else if (option == 2)
		c.read("enemyships.shp");
	else if (option == 3) {
		c.read("friendlyships.shp");
		c.read("enemyships.shp");
	}

	c.print();

	cout << "1. Print all ships" << endl;
	cout << "2. Starship with the strongest weapon" << endl;
	cout << "3. Strongest starship overall" << endl;
	cout << "4. Weakest ship (ignoring unarmed)" << endl;
	cout << "5. Unarmed ships" << endl;
	
	cin >> option;
	
	/* Work your magic here */
	switch (option) {
		case 1: c.print(); break;

		case 2: c.strongest(); break;

		case 3: c.strongestOverall(); break;

		case 4: c.weakest(); break;

		case 5: c.unarmed(); break;

		default: break;
	}
	
   return 0;
}