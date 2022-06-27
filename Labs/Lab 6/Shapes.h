#pragma once

#include <string>

using namespace std;

class Shape {
public:
	virtual void Scale(float scaleFactor) = 0;
	virtual void Display() const = 0;

	virtual ~Shape() {}
};

class Shape2D : virtual public Shape {
public:
	virtual float Area() const = 0;
	void ShowArea() const;
	virtual string GetName2D() const = 0;
	bool operator>(const Shape2D &rhs) const;
	bool operator<(const Shape2D &rhs) const;
	bool operator==(const Shape2D &rhs) const;
};	

class Shape3D : virtual public Shape {
public:
	virtual float Volume() const = 0;
	void ShowVolume() const;
	virtual string GetName3D() const = 0;
	bool operator>(const Shape3D &rhs) const;
	bool operator<(const Shape3D &rhs) const;
	bool operator==(const Shape3D &rhs) const;
};

class Square : public Shape2D {
private:
	float side;
	float area;
	string name2D = "Square";
public:
	// Constructor
	Square();
	Square(float sideLength);

	// Scale and Display
	void Scale(float scaleFactor);
	void Display() const;

	// Accessors
	float Area() const;
	string GetName2D() const;
};

class Triangle : public Shape2D {
private:
	float base;
	float height;
	float area;
	string name2D = "Triangle";
public:
	// Constructors
	Triangle();
	Triangle(float base, float height);

	// Scale and Display
	void Scale(float scaleFactor);
	void Display() const;

	// Accessors
	float Area() const;
	string GetName2D() const;
};

class Circle : public Shape2D {
private:
	float radius;
	float area;
	string name2D = "Circle";
public:
	// Constructors
	Circle();
	Circle(float radius);

	// Scale and Display
	void Scale(float scaleFactor);
	void Display() const;

	// Accessors
	float Area() const;
	string GetName2D() const;
};

// 3D Shapes
class TriangularPyramid : public Shape3D, private Triangle {
private:
	float height;
	Triangle triangle;
	string name3D = "TriangularPyramid";
public:
	// Constructors
	TriangularPyramid();
	TriangularPyramid(float height, float baseLength, float baseHeight);

	// Scale and Display
	void Scale(float scaleFactor);
	void Display() const;

	// Accessors
	float Volume() const;
	string GetName3D() const;
};

class Cylinder : public Shape3D, private Circle {
private:
	float height;
	Circle circle;
	string name3D = "Cylinder";
public:
	// Constructors
	Cylinder();
	Cylinder(float height, float circleRadius);

	// Scale and Display 
	void Scale(float scaleFactor);
	void Display() const;

	// Accessors
	float Volume() const;
	string GetName3D() const;
};

class Sphere : public Shape3D, private Circle {
private:
	float radius;
	Circle circle;
	string name3D = "Sphere";
public:
	// Accessors
	Sphere();
	Sphere(float radius);

	// Scale and Display
	void Scale(float scaleFactor);
	void Display() const;

	// Accessors
	float Volume() const;
	string GetName3D() const ;
};
