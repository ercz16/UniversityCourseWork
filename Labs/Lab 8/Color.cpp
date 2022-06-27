#include <iostream>
#include <string>
#include "Color.h"

using namespace std;

string convertToHex(int hex) {
	if (hex == 10) {
		return "A";
	} else if (hex == 11) {
		return "B";
	} else if (hex == 12) {
		return "C";
	} else if (hex == 13) {
		return "D";
	} else if (hex == 14) {
		return "E";
	} else if (hex == 15) {
		return "F";
	} else {
		return to_string(hex);
	}
}

string getHex(int value) {
	string hexValue = "";
	hexValue += convertToHex(value / 16);
	hexValue += convertToHex(value % 16);
	return hexValue;
}

void Color::SetValue(int value) {
	B = value & 255;
	value >>= 8;
	G = value & 255;
	value >>= 8;
	R = value & 255;

	hexValue += getHex((int)R);
	hexValue += getHex((int)G);
	hexValue += getHex((int)B);
}

void Color::SetName(const char *name) {
	this->name = name;
}

unsigned char Color::GetR() const {
	return R;
}

unsigned char Color::GetG() const {
	return G;
}

unsigned char Color::GetB() const {
	return B;
}

string Color::GetHexValue() const {
	return hexValue;	
}

string Color::GetName() const {
	return name;
}

void Color::Print() const {
   	cout << GetName() << "\t0x" << GetHexValue() 
   	<< "\t" << (int)GetR() << "," << (int)GetG() << "," 
   	<< (int)GetB() << endl;
}