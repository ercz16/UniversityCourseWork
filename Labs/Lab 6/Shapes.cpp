#include <iostream>
#include <math.h>

#include "Shapes.h"

using namespace std;

const float PI = 3.14159f;

// Shape 2D
void Shape2D::ShowArea() const {
	cout << "The area of the " << GetName2D() << " is : " << Area() << endl;
}

bool Shape2D::operator>(const Shape2D &rhs) const {
	if (this->Area() > rhs.Area())
		return true;
	else
		return false;
}

bool Shape2D::operator<(const Shape2D &rhs) const {
	if (this->Area() < rhs.Area())
		return true;
	else
		return false;
}
bool Shape2D::operator==(const Shape2D &rhs) const {
	if (this->Area() == rhs.Area())
		return true;
	else
		return false;
}

// Shape 3D
void Shape3D::ShowVolume() const {
	cout << "The volume of the " << GetName3D() << " is : " << Volume() << endl;
}

bool Shape3D::operator>(const Shape3D &rhs) const {
	if (this->Volume() > rhs.Volume())
		return true;
	else
		return false;
}

bool Shape3D::operator<(const Shape3D &rhs) const {
	if (this->Volume() < rhs.Volume())
		return true;
	else
		return false;
}

bool Shape3D::operator==(const Shape3D &rhs) const {
	if (this->Volume() == rhs.Volume())
		return true;
	else
		return false;
}

// Square Class Definitions
Square::Square() {
	side = 0;
	area = 0;
}

Square::Square(float sideLength) {
	this->side = sideLength;
	this->area = pow(sideLength, 2);
}

void Square::Scale(float scaleFactor) {
	side *= scaleFactor;
	area *= pow(scaleFactor, 2);
}

void Square::Display() const {
	cout << "The area of the Square is : " << Area() << endl;
	cout << "Length of a side: " << side << endl;
}

float Square::Area() const {
	return area;
}

string Square::GetName2D() const {
	return name2D;
}

// Triangle Class Definitions
Triangle::Triangle() {
	base = 0;
	height = 0;
	area = 0;
}

Triangle::Triangle(float base, float height) {
	this->base = base;
	this->height = height;
	this->area = base * height * 0.5;
}

void Triangle::Scale(float scaleFactor) {
	base *= scaleFactor;
	height *= scaleFactor;
	area *= pow(scaleFactor, 2);
}

void Triangle::Display() const {
	cout << "The area of the Triangle is : " << Area() << endl;
	cout << "Base: " << base << endl;
	cout << "Height: " << height << endl;
}

float Triangle::Area() const {
	return area;
}

string Triangle::GetName2D() const {
	return name2D;
}

// Circle Class Definitions
Circle::Circle() {
	radius = 0;
	area = 0;
}

Circle::Circle(float radius) {
	this->radius = radius;
	this->area = PI * pow(radius, 2);
}

void Circle::Scale(float scaleFactor) {
	radius *= scaleFactor;
	area *= pow(scaleFactor, 2);
}

void Circle::Display() const {
	cout << "The area of the Circle is : " << Area() << endl;
	cout << "Radius: " << radius << endl;
}

float Circle::Area() const {
	return area;
}

string Circle::GetName2D() const {
	return name2D;
}

// Triangular Pyramid Definitions
TriangularPyramid::TriangularPyramid() {
	height = 0;
	triangle = Triangle(0, 0);
}

TriangularPyramid::TriangularPyramid(float height, float baseLength, float baseHeight) {
	this->height = height;
	this->triangle = Triangle(baseLength, baseHeight);
}

void TriangularPyramid::Scale(float scaleFactor) {
	height *= scaleFactor;
	triangle.Scale(scaleFactor);
}

void TriangularPyramid::Display() const {
	cout << "The volume of the TriangularPyramid is : " << Volume() << endl;
	cout << "The height is: " << height << endl;
	triangle.Display();
}

float TriangularPyramid::Volume() const {
	return triangle.Area() * height / 3.0f;
}

string TriangularPyramid::GetName3D() const {
	return name3D;
}

// Cylinder Definitions
Cylinder::Cylinder() {
	height = 0;
	circle = Circle(0);
}

Cylinder::Cylinder(float height, float circleRadius) {
	this->height = height;
	this->circle = Circle(circleRadius);
}

void Cylinder::Scale(float scaleFactor) {
	height *= scaleFactor;
	circle.Scale(scaleFactor);
}

void Cylinder::Display() const {
	cout << "The volume of the Cylinder is : " << Volume() << endl;
	cout << "The height is: " << height << endl;
	circle.Display();
}

float Cylinder::Volume() const {
	return circle.Area() * height;
}

string Cylinder::GetName3D() const {
	return name3D;
}

// Sphere Definitions
Sphere::Sphere() {
	radius = 0;
	circle = Circle(0);
}

Sphere::Sphere(float radius) {
	this->radius = radius;
	this->circle = Circle(radius);
}

void Sphere::Scale(float scaleFactor) {
	radius *= scaleFactor;
	circle.Scale(scaleFactor);
}

void Sphere::Display() const {
	cout << "The volume of the Sphere is : " << Volume() << endl;
	circle.Display();
}

float Sphere::Volume() const {
	return 4 * PI * pow(radius, 3) / 3.0f;
}

string Sphere::GetName3D() const {
	return name3D;
}
