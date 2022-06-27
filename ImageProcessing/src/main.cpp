#include <iostream>
#include <fstream>

#include "tga.h"

using namespace std;

int testsPassed = 0;

void test1();
void test2();
void test3();
void test4();
void test5();
void test6();
void test7();
void test8();
void test9();
void test10();

void displayResult(int testNumber, TGA& a, TGA& b);

int main()
{
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test7();
	test8();
	test9();
	test10();

	cout << "Test results: " << testsPassed << " / 10" << endl;

	return 0;
}

void test1() {
	TGA imageA;
	TGA imageB;
	TGA* imageC;

	// Read in images
	imageA.read("input/layer1.tga");
	imageB.read("input/pattern1.tga");

	// Multiply imageA and imageB and set to imageC
	imageC = imageA.multiply(imageB);
	imageC->write("output/part1.tga");
	delete imageC;

	// Compare output image with examples
	TGA resultImage;
	TGA exampleImage;
	resultImage.read("output/part1.tga");
	exampleImage.read("examples/EXAMPLE_part1.tga");
	displayResult(1, resultImage, exampleImage);
}

void test2() {
	TGA imageA; // Top layer
	TGA imageB; // Bottom layer
	TGA* imageC; // Resulting image

	// Read in images
	imageA.read("input/layer2.tga");
	imageB.read("input/car.tga");

	// Substract imageA from imageB
	imageC = imageA.subtract(imageB);
	imageC->write("output/part2.tga");
	delete imageC;

	// Compare output image with exampmles
	TGA resultImage;
	TGA exampleImage;
	resultImage.read("output/part2.tga");
	exampleImage.read("examples/EXAMPLE_part2.tga");
	displayResult(2, resultImage, exampleImage);
}

void test3() {
	TGA imageA; // Top layer
	TGA imageB; // Bottom layer
	TGA imageC; // Third layer
	TGA* resultImage; // Resulting image

	// Read in images
	imageA.read("input/layer1.tga");
	imageB.read("input/pattern2.tga");
	imageC.read("input/text.tga");

	// Multiply and Screen
	TGA* tmpImage = imageA.multiply(imageB);
	resultImage = imageC.screen(*tmpImage);
	resultImage->write("output/part3.tga");
	delete tmpImage;
	delete resultImage;

	// Compare output image with example
	TGA output;
	TGA exampleImage;
	output.read("output/part3.tga");
	exampleImage.read("examples/EXAMPLE_part3.tga");
	displayResult(3, output, exampleImage);
}

void test4() {
	TGA imageA;
	TGA imageB;
	TGA imageC;
	TGA* resultImage;

	// Read in images
	imageA.read("input/layer2.tga");
	imageB.read("input/circles.tga");
	imageC.read("input/pattern2.tga");

	// Multiply and Subtract
	TGA* tmpImage = imageA.multiply(imageB);
	resultImage = imageC.subtract(*tmpImage);
	resultImage->write("output/part4.tga");
	delete tmpImage;
	delete resultImage;

	// Compare output image with example
	TGA output;
	TGA exampleImage;
	output.read("output/part4.tga");
	exampleImage.read("examples/EXAMPLE_part4.tga");
	displayResult(4, output, exampleImage);
}

void test5() {
	TGA imageA;
	TGA imageB;
	TGA* resultImage;

	// Read in images
	imageA.read("input/layer1.tga");
	imageB.read("input/pattern1.tga");

	// Multiply and Subtract
	resultImage = imageA.overlay(imageB);
	resultImage->write("output/part5.tga");
	delete resultImage;

	// Compare output image with example
	TGA output;
	TGA exampleImage;
	output.read("output/part5.tga");
	exampleImage.read("examples/EXAMPLE_part5.tga");
	displayResult(5, output, exampleImage);
}

void test6() {
	TGA imageA;
	TGA* resultImage;

	// Read in images
	imageA.read("input/car.tga");

	// Add 200 to the green channel
	resultImage = imageA.addGreen(200);
	resultImage->write("output/part6.tga");
	delete resultImage;

	// Compare output image with example
	TGA output;
	TGA exampleImage;
	output.read("output/part6.tga");
	exampleImage.read("examples/EXAMPLE_part6.tga");
	displayResult(6, output, exampleImage);
}

void test7() {
	TGA imageA;
	TGA* resultImage;

	// Read in images
	imageA.read("input/car.tga");

	// Scale red channel by 4
	resultImage = imageA.scaleRed(4);
	resultImage->write("output/part7.tga");
	delete resultImage;

	// Compare output image with example
	TGA output;
	TGA exampleImage;
	output.read("output/part7.tga");
	exampleImage.read("examples/EXAMPLE_part7.tga");
	displayResult(7, output, exampleImage);
}

void test8() {
	TGA imageA;
	TGA imageR;
	TGA imageG;
	TGA imageB;

	// Read in image and set headers
	imageA.read("input/car.tga");
	imageR.header = imageA.header;
	imageG.header = imageA.header;
	imageB.header = imageA.header;

	// Split channels
	for (unsigned int i = 0; i < imageA.pixelData.size(); ++i) {
		unsigned char r = imageA.pixelData[i][0];
		unsigned char g = imageA.pixelData[i][1];
		unsigned char b = imageA.pixelData[i][2];

		imageR.pixelData.push_back(Pixel(r, r, r));
		imageG.pixelData.push_back(Pixel(g, g, g));
		imageB.pixelData.push_back(Pixel(b, b, b));
	}

	// Write out
	imageR.write("output/part8_r.tga");
	imageG.write("output/part8_g.tga");
	imageB.write("output/part8_b.tga");

	// Compare output image with example
	TGA outputR, outputG, outputB;
	TGA exampleR, exampleG, exampleB;
	outputR.read("output/part8_r.tga");
	outputG.read("output/part8_g.tga");
	outputB.read("output/part8_b.tga");
	exampleR.read("examples/EXAMPLE_part8_r.tga");
	exampleG.read("examples/EXAMPLE_part8_g.tga");
	exampleB.read("examples/EXAMPLE_part8_b.tga");

	if (outputR.compare(exampleR) &&
		outputG.compare(exampleG)) {
		displayResult(8, outputB, exampleB);
	} else {
		cout << "Test #8...... Failed!" << endl;
	}
}

void test9() {
	TGA imageR, imageG, imageB;
	TGA* resultImage;

	// Read in images
	imageR.read("input/layer_red.tga");
	imageG.read("input/layer_green.tga");
	imageB.read("input/layer_blue.tga");

	// Combine
	resultImage = TGA::combine(imageR, imageG, imageB);
	resultImage->write("output/part9.tga");
	delete resultImage;

	// Compare output
	TGA output, example;
	output.read("output/part9.tga");
	example.read("examples/EXAMPLE_part9.tga");

	displayResult(9, output, example);
}

void test10() {
	TGA imageA;
	TGA* resultImage;

	// Read in
	imageA.read("input/text2.tga");

	// Rotate
	resultImage = TGA::rotate(imageA);
	resultImage->write("output/part10.tga");
	delete resultImage;

	// Compare
	TGA output, example;
	output.read("output/part10.tga");
	example.read("examples/EXAMPLE_part10.tga");
	displayResult(10, output, example);
}

void displayResult(int testNumber, TGA& a, TGA& b) {
	cout << "Test #" << testNumber << "...... ";
	if (a.compare(b)) {
		testsPassed++;
		cout << "Passed!" << endl;
	} else {
		cout << "Failed!" << endl;
	}
}
