#include <iostream>
#include <fstream>
#include <string>

#include "tga.h"

using namespace std;

void Header::print() {
	cout << "idLength: " << (int)idLength << endl;
	cout << "colorMapType: " << (int)colorMapType << endl;
	cout << "dataTypeCode: " << (int)dataTypeCode << endl;
	cout << "colorMapOrigin: " << colorMapOrigin << endl;
	cout << "colorMapLength: " << colorMapLength << endl;
	cout << "colorMapDepth: " << (int)colorMapDepth << endl;
	cout << "xOrigin: " << xOrigin << endl;
	cout << "yOrigin: " << yOrigin << endl;
	cout << "width: " << width << endl;
	cout << "height: " << height << endl;
	cout << "bitsPerPixel: " << (int)bitsPerPixel << endl;
	cout << "imageDescriptor: " << (int)imageDescriptor << endl;
}

void TGA::read(string fname) {

	ifstream file(fname, ios_base::binary);

	// Read Header
	file.read(&header.idLength, 1);
	file.read(&header.colorMapType, 1);
	file.read(&header.dataTypeCode, 1);
	file.read((char*)&header.colorMapOrigin, 2);
	file.read((char*)&header.colorMapLength, 2);
	file.read(&header.colorMapDepth, 1);
	file.read((char*)&header.xOrigin, 2);
	file.read((char*)&header.yOrigin, 2);
	file.read((char*)&header.width, 2);
	file.read((char*)&header.height, 2);
	file.read(&header.bitsPerPixel, 1);
	file.read(&header.imageDescriptor, 1);

	// Read Pixel Data
	for (int i = 0; i < (int)header.width * (int)header.height; ++i) {
		Pixel newPixel;

		file.read((char*)&newPixel.b, 1);
		file.read((char*)&newPixel.g, 1);
		file.read((char*)&newPixel.r, 1);

		pixelData.push_back(newPixel);
	}

	// Close File
	file.close();
}

void TGA::write(string fname) {

	ofstream file(fname, ios_base::binary);

	// Write Header
	file.write(&header.idLength, 1);
	file.write(&header.colorMapType, 1);
	file.write(&header.dataTypeCode, 1);
	file.write((char*)&header.colorMapOrigin, 2);
	file.write((char*)&header.colorMapLength, 2);
	file.write(&header.colorMapDepth, 1);
	file.write((char*)&header.xOrigin, 2);
	file.write((char*)&header.yOrigin, 2);
	file.write((char*)&header.width, 2);
	file.write((char*)&header.height, 2);
	file.write(&header.bitsPerPixel, 1);
	file.write(&header.imageDescriptor, 1);

	// Write Pixel Data
	for (unsigned int i = 0; i < pixelData.size(); ++i) {
		file.write((char*)&pixelData[i].b, 1);
		file.write((char*)&pixelData[i].g, 1);
		file.write((char*)&pixelData[i].r, 1);
	}

	// Close File
	file.close();
}

TGA* TGA::multiply(TGA& secondImage) {
	TGA* resultImage = new TGA();

	resultImage->header = header;

	for (unsigned int i = 0; i < pixelData.size(); ++i) {
		Pixel newPixel;
		int a = (int)pixelData[i].r;
		int b = (int)secondImage.pixelData[i].r;
		unsigned char c = (unsigned char)((a * b / 255.0) + 0.5f);
		newPixel.r = c;

		a = (int)pixelData[i].g;
		b = (int)secondImage.pixelData[i].g;
		c = (unsigned char)((a * b / 255.0) + 0.5f);
		newPixel.g = c;

		a = (int)pixelData[i].b;
		b = (int)secondImage.pixelData[i].b;
		c = (unsigned char)((a * b / 255.0) + 0.5f);
		newPixel.b = c;

		resultImage->pixelData.push_back(newPixel);
	}

	return resultImage;
}

TGA* TGA::subtract(TGA& secondImage) {
	TGA* resultImage = new TGA();

	resultImage->header = header;

	for (unsigned int i = 0; i < pixelData.size(); ++i) {
		Pixel newPixel;
		int a = (int)pixelData[i].r;
		int b = (int)secondImage.pixelData[i].r;
		unsigned char c;
		if (a > b) c = 0;
		else c = (unsigned char)(b - a);
		newPixel.r = c;

		a = (int)pixelData[i].g;
		b = (int)secondImage.pixelData[i].g;
		if (a > b) c = 0;
		else c = (unsigned char)(b - a);
		newPixel.g = c;

		a = (int)pixelData[i].b;
		b = (int)secondImage.pixelData[i].b;
		if (a > b) c = 0;
		else c = (unsigned char)(b - a);
		newPixel.b = c;

		resultImage->pixelData.push_back(newPixel);
	}

	return resultImage;
}

TGA* TGA::screen(TGA& secondImage) {
	TGA* resultImage = new TGA();

	resultImage->header = header;

	for (unsigned int i = 0; i < pixelData.size(); ++i) {
		Pixel newPixel;
		for (int j = 0; j < 3; ++j) {
			int a = (int)pixelData[i][j];
			int b = (int)secondImage.pixelData[i][j];
			int c = 255 - ((255 - a) * (255 - b) / 255.0f) + 0.5f;

			newPixel[j] = (unsigned char)c;
		}	
		resultImage->pixelData.push_back(newPixel);
	}
	return resultImage;
}

TGA* TGA::overlay(TGA& secondImage) {
	TGA* resultImage = new TGA();

	resultImage->header = header;

	for (unsigned int i = 0; i < pixelData.size(); ++i) {
		Pixel newPixel;
		for (int j = 0; j < 3; ++j) {
			int a = (int)pixelData[i][j];
			int b = (int)secondImage.pixelData[i][j];
			int c;

			if (b <= 127) c = 2 * (a * b / 255.0f) + 0.5f;
			else c = 255 - 2 * ((255 - a) * (255 - b) / 255.0f) + 0.5f;

			newPixel[j] = (unsigned char)c;
		}
		resultImage->pixelData.push_back(newPixel);
	}
	return resultImage;
}

TGA* TGA::addGreen(int val) {
	TGA* resultImage = new TGA();

	resultImage->header = header;

	for (unsigned int i = 0; i < pixelData.size(); ++i) {
		Pixel newPixel;
		for (int j = 0; j < 3; ++j) {
			int a = (int)pixelData[i][j];

			if (j == 1) {
				a += val;
				if (a > 255) a = 255;
			}

			newPixel[j] = (unsigned char)a;
		}	
		resultImage->pixelData.push_back(newPixel);
	}
	return resultImage;
}

TGA* TGA::scaleRed(int scaleFactor) {
	TGA* resultImage = new TGA();

	resultImage->header = header;

	for (unsigned int i = 0; i < pixelData.size(); ++i) {
		Pixel newPixel;
		for (int j = 0; j < 3; ++j) {
			int a = (int)pixelData[i][j];

			if (j == 0) {
				a *= scaleFactor;
				if (a > 255) a = 255;
			} else if (j == 2) {
				a = 0;
			}

			newPixel[j] = (unsigned char)a;
		}	
		resultImage->pixelData.push_back(newPixel);
	}
	return resultImage;
}

TGA* TGA::combine(TGA& imageR, TGA& imageG, TGA& imageB) {
	TGA* resultImage = new TGA();

	resultImage->header = imageR.header;

	for(unsigned int i = 0; i < imageR.pixelData.size(); ++i) {
		resultImage->pixelData.push_back(
			Pixel(imageR.pixelData[i][0], 
				  imageG.pixelData[i][1], 
				  imageB.pixelData[i][2]
				  )
			);
	}

	return resultImage;
}

TGA* TGA::rotate(TGA& image) {
	TGA* resultImage = new TGA();

	resultImage->header = image.header;

	for(unsigned int i = 0; i < image.pixelData.size(); ++i) {
		resultImage->pixelData.push_back(
			Pixel(image.pixelData[image.pixelData.size()-1-i][0], 
				  image.pixelData[image.pixelData.size()-1-i][1], 
				  image.pixelData[image.pixelData.size()-1-i][2]
				  )
			);
	}

	return resultImage;
}

bool TGA::compare(TGA& secondImage) {
	for (unsigned int i = 0; i < pixelData.size(); ++i) {
		if (pixelData[i].r != secondImage.pixelData[i].r ||
			pixelData[i].g != secondImage.pixelData[i].g ||
			pixelData[i].b != secondImage.pixelData[i].b
			) 
			{return false;}
	}
	return true;
}
