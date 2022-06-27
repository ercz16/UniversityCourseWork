#include <string>

using std::string;

class Color
{
private:
	string name;
	string hexValue;
	unsigned char R;
	unsigned char G;
	unsigned char B;
public:
	void SetValue(int value);
	void SetName(const char *name);

	// Accessors
	unsigned char GetR() const;
	unsigned char GetG() const;
	unsigned char GetB() const;
	string GetHexValue() const;
	string GetName() const;

	// Functions
	void Print() const;
};