#include <string>
#include <vector>

struct Header
{
	char idLength;
	char colorMapType;
	char dataTypeCode;
	short colorMapOrigin;
	short colorMapLength;
	char colorMapDepth;
	short xOrigin;
	short yOrigin;
	short width;
	short height;
	char bitsPerPixel;
	char imageDescriptor;

	void print();
};

struct Pixel {
	unsigned char r;
	unsigned char g;
	unsigned char b;

	Pixel() {}

	Pixel(unsigned char r, unsigned char g, unsigned char b) {
		this->r = r;
		this->g = g;
		this->b = b;
	}

	unsigned char& operator[](int index) {
		if (index == 0)
			return r;
		else if (index == 1)
			return g;
		else
			return b;
	}
};

struct TGA {
	// Image Data
	Header header;
	std::vector<Pixel> pixelData;

	// Read and Write out to/from File
	void read(std::string fname);
	void write(std::string fname);

	// Manipulations
	TGA* multiply(TGA& secondImage);
	TGA* subtract(TGA& secondImage);
	TGA* screen(TGA& secondImage);
	TGA* overlay(TGA& secondImage);
	TGA* addGreen(int val);
	TGA* scaleRed(int scaleFactor);

	static TGA* combine(TGA& imageR, TGA& imageG, TGA& imageB);
	static TGA* rotate(TGA& image);

	// Compare
	bool compare(TGA& secondImage);
};
