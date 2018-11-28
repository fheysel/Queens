/*
 * Good Shapes
 * Written by Tom Heysel, 200000838, 15tjh2
 * For CISC/CMPE 320, Assignment 5
 */
#pragma once

#include <string>
using namespace std;

class Fillable{//Parent of any class that has a fill colour
public:
	Fillable(const string& fillCol);
	virtual ~Fillable();
	virtual void draw();

private:
	string fillColour;
};

class Textable{//Parent of any class that can have text written inside their  shape
public:
	Textable(const string& text);
	virtual ~Textable();
	virtual void draw();
private:
	string text;
};

class Shape {//base class of all shapes
public:
	Shape(const int& len, const int& wid, const string& borderCol);
	virtual ~Shape();
	virtual void draw();

private:
	int length, width;
	string borderColour;
};

class Square : public Shape {//parent of fillable square
public:
	Square(const int& len, const int& wid, const string& borderCol);
	virtual ~Square();
	virtual void draw();
};

class FilledSquare : public Square, public Fillable {
public:
	FilledSquare(const int& len, const int& wid, const string& borderCol, const string& fillCol);
	virtual ~FilledSquare();
	virtual void draw();
};

class FilledTextSquare : public FilledSquare, public Textable {
public:
	FilledTextSquare(const int& len, const int& wid, const string& borderCol, const string& fillCol, const string& text);
	virtual ~FilledTextSquare();
	virtual void draw();
};

class Circle : public Shape {
public:
	Circle(const int&, const int&, const string&);
	virtual ~Circle();
	virtual void draw();
};

class FilledCircle : public Circle, public Fillable {
public:
	FilledCircle(const int&, const int&, const string&, const string&);
	virtual ~FilledCircle();
	virtual void draw();
};

class Arc : public Shape {
public:
	Arc(const int&, const int&, const string&);
	virtual ~Arc();
	virtual void draw();
};
