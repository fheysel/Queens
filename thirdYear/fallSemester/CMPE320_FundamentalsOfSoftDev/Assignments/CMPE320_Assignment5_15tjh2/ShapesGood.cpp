/*
 * This is the implementation of the bad structure built in the header file.  Instead of
 * drawing anything, you can see that the various drawing functions just display some text
 * to the console to indicate what the function would be doing.
 *
 * For CISC/CMPE 320, Assignment 5
 */
#include <iostream>
#include <string>
#include "ShapesGood.h"

using namespace std;

//////////////////////////FILLABLE/////////////////////////////////////////////
Fillable::Fillable(const string& fillCol) : fillColour(fillCol){}
Fillable::~Fillable(){}
void Fillable::draw(){
	cout<< " With "<<fillColour<<" fill.";
}

//////////////////////////TEXTABLE/////////////////////////////////////////////
Textable::Textable(const string& tex) : text(tex){}
Textable::~Textable(){}
void Textable::draw(){
	cout<<" Containing the text \""<<text<<"\".";
}

//////////////////////////SHAPE////////////////////////////////////////////////
Shape::Shape(const int& len, const int& wid, const string& borderCol) : length(len), width(wid), borderColour(borderCol) {}
Shape::~Shape() {}
void Shape::draw(){
	cout<<"\nDrawing a(n) "<<borderColour;
}

///////////////////////////SQUARE//////////////////////////////////////////
Square::Square(const int& len, const int& wid, const string& borderCol) : Shape(len, wid ,borderCol){}
Square::~Square(){};
void Square::draw(){
	Shape::draw();
	cout<<" square.";
}

//////////////////////////FILLED SQUARE/////////////////////////////////////
FilledSquare::FilledSquare(const int& len, const int& wid, const string& borderCol, const string& fillCol) : Square(len, wid, borderCol), Fillable(fillCol){}
FilledSquare::~FilledSquare(){};
void FilledSquare::draw(){
	Square::draw();
	Fillable::draw();
}

/////////////////////////FILLED TEXT SQUARE//////////////////////////////////
FilledTextSquare::FilledTextSquare(const int& len, const int& wid, const string& borderCol, const string& fillCol, const string& text) : FilledSquare(len, wid, borderCol, fillCol), Textable(text){}
FilledTextSquare::~FilledTextSquare(){};
void FilledTextSquare::draw(){
	FilledSquare::draw();
	Textable::draw();
}

/////////////////////////CIRCLE////////////////////////////////////////////
Circle::Circle(const int& len, const int& wid, const string& borderCol) : Shape(len, wid, borderCol){}
Circle::~Circle(){};
void Circle::draw(){
	Shape::draw();
	cout<<" circle.";
}


//////////////////////FILLED CIRCLE////////////////////////////////////////
FilledCircle::FilledCircle(const int& len, const int& wid, const string& borderCol, const string& fillCol) : Circle(len, wid, borderCol), Fillable(fillCol){}
FilledCircle::~FilledCircle(){};
void FilledCircle::draw(){
	Circle::draw();
	Fillable::draw();
}

//////////////////////ARC/////////////////////////////////////////////////
Arc::Arc(const int& len, const int& wid, const string& borderCol) : Shape(len, wid, borderCol){}
Arc::~Arc(){};
void Arc::draw() {
	Shape::draw();
	cout<<" arc.";
}
