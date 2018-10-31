//============================================================================
// Name        : CMPE365_Lab3_15tjh2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <math.h>
using namespace std;

struct point{
	int x;
	int y;
};

void generatePoints(const int &numberOfPoints, point coordinates[], const int &range){
	int doubleRange = range*2;
	for(int i=0; i<numberOfPoints; i++){//randomly generate the number of points specified in the range given. Return array by reference
		coordinates[i].x = (rand()%doubleRange)-range;//calculates an x-coordinate between -range and range
		coordinates[i].y = (rand()%doubleRange)-range;//calculates an y-coordinate between -range and range
	}
}


int orientation(point p1, point p2, point p3){
	int value = (p2.y - p1.y) * (p3.x - p2.x) - (p2.x - p1.x) * (p3.y - p2.y);

	if(value == 0 ){//if co-linear
		return 0;//indication of colinear
	}
	else if(value > 0){//if clockwise
		return 1;//indicate clockwise
	}
	else{
		return 2;//indicate counter clockwise
	}
}


vector<point> calculateConvexHull(point coordinates[], const int &numberOfPoints){//Calculating the convex hull of a given array of points using Jarvis' March Algorithm
	if(numberOfPoints<3){
		cerr<<"There must be at least 3 points to find the convex hull!"<<endl;
		vector<point> nullVector;//must be at least 3 points
		return nullVector;
	}

	vector<point> convexHull;//create vector of points

	int leftMost = 0;
	for(int i=0; i<numberOfPoints; i++){//finds the leftmost element
		if(coordinates[i].x < coordinates[leftMost].x)
			leftMost = i;
	}

	int current = leftMost;
	int traverser;
	do{//while you haven't got back to the start
		convexHull.push_back(coordinates[current]); //Add the current point to the convex hull

		traverser = (current+1)%numberOfPoints;//go to next element in array
		for(int i=0; i<numberOfPoints; i++){// find the point that is the last visited and counter clockwise  orientation
			if(orientation(coordinates[current], coordinates[i], coordinates[traverser]) == 2){
				traverser = i;
			}
		}

		//Now move to the next element in the convex hull
		current = traverser;

	}while(current != leftMost);

	cout<<"The convex hull contains the following points:"<<endl;
	for(unsigned int i=0; i<convexHull.size(); i++){
		cout<<convexHull.at(i).x << " "<< convexHull.at(i).y<<endl;
	}

	return convexHull;
//	return (float)convexHull.size()/(float)numberOfPoints;

}


//Same function as above but returns float ratio.USed for questions 1 and 2
float calculateConvexHull2(point coordinates[], const int &numberOfPoints){//Calculating the convex hull of a given array of points using Jarvis' March Algorithm
	if(numberOfPoints<3){
		cerr<<"There must be at least 3 points to find the convex hull!"<<endl;
		return 0;
	}

	vector<point> convexHull;//create vector of points

	int leftMost = 0;
	for(int i=0; i<numberOfPoints; i++){//finds the leftmost element
		if(coordinates[i].x < coordinates[leftMost].x)
			leftMost = i;
	}

	int current = leftMost;
	int traverser;
	do{//while you haven't got back to the start
		convexHull.push_back(coordinates[current]); //Add the current point to the convex hull

		traverser = (current+1)%numberOfPoints;//go to next element in array
		for(int i=0; i<numberOfPoints; i++){// find the point that is the last visited and counter clockwise  orientation
			if(orientation(coordinates[current], coordinates[i], coordinates[traverser]) == 2){
				traverser = i;
			}
		}

		//Now move to the next element in the convex hull
		current = traverser;

	}while(current != leftMost);

	cout<<"The convex hull contains the following points:"<<endl;
	for(unsigned int i=0; i<convexHull.size(); i++){
		cout<<convexHull.at(i).x << " "<< convexHull.at(i).y<<endl;
	}

	return (float)convexHull.size()/(float)numberOfPoints;

}





point getAverage(vector<point> convexHull){
	point averageP;
	float avgX = 0;
	float avgY = 0;
	for(point p : convexHull){
		avgX += p.x;
		avgY += p.y;
	}

	avgX = avgX/convexHull.size();
	avgY = avgY/convexHull.size();

	averageP.x = avgX;
	averageP.y = avgY;

	return averageP;

}

float findRadius(point center, vector<point> convexHull){
	point farthest = center;
	float distance;
	float currentRadius = 0;
	for(point p : convexHull){
		distance = sqrt(pow((p.x - center.x),2) + pow((p.y - center.y), 2)); // calculate distance from every point on convexHull to center

		if(distance > currentRadius){
			currentRadius = distance; //update the radius
			farthest = p;
		}
	}
	cout<<"Radius of bounding circle: " << currentRadius<<endl;
	return currentRadius;
}

int checkIntersection(float radius1, float radius2, point average1, point average2){
	float distance = sqrt(pow((average1.x - average2.x),2) + pow((average1.y - average2.y), 2));
	if(distance>=(radius1+radius2)){//if the circles will not intersect. Here I define touching to not be intersecting
		return 0;
	}
	else
		return 1;
}


int main() {
//	srand(time(0));//setting seed to current time

	int numberOfPoints = 20;//number of points to generate
	int range = 50;//how far away from origin points are allowed to be
	point coordinates[numberOfPoints];//array to hold points

//	generatePoints(numberOfPoints, coordinates, range);//generate the random points
//
//	cout<<"The randomly generated points are:"<<endl;
//	for(point p : coordinates)
//		cout<<p.x << " "<< p.y<<endl;
//
//	// changed calculateConvexHull() such that it returns a vector<points> of the convex hull, not a float of the ratio
//	float ratio = calculateConvexHull(coordinates, numberOfPoints);//calculate the convex of the points given
//
//	cout<<"With "<< numberOfPoints << " randomly generated points and a range of "<< range<<" the ratio of points in convex hull to total number of points is: " << ratio <<endl;
//
//
//	for(int i = 30; i<100; i+=10){
//		numberOfPoints = i;
//		point coordinates1[numberOfPoints];
//		generatePoints(numberOfPoints, coordinates1, range);
//
//		ratio = calculateConvexHull(coordinates1, numberOfPoints);
//		cout<<"With "<< numberOfPoints << " randomly generated points and a range of "<< range<<" the ratio of points in convex hull to total number of points is: " << ratio <<endl;
//	}
//
//	range = 500;
//	numberOfPoints = 100;
//	float ratioCounter = 0;
//	for(int i =0; i<1000; i++){
//		point coordinates1[numberOfPoints];
//		generatePoints(numberOfPoints, coordinates1, range);
//
//		ratio = calculateConvexHull(coordinates1, numberOfPoints);
//		ratioCounter += ratio;
//	}
//
//	cout << "The average ratio is: "<<ratioCounter/1000<<endl;

//////////////////////////////////////Question 2////////////////////////////////////////////////////////////////////////////

numberOfPoints = 50;


random_device randDevice;
mt19937 generator(randDevice());

normal_distribution<> dist(0, 68);

point set[numberOfPoints];

for(point p : set){
	p.x = round(dist(generator));
	p.y = round(dist(generator));

	cout << "Randomly generated point is: "<<p.x<<" "<<p.y<<endl;
}

float ratio = calculateConvexHull2(set, numberOfPoints);

cout<<"The ratio of points in convex hull to total number of points is "<< ratio<<endl;




//////////////////////////////////////Question 3////////////////////////////////////////////////////////////////////////////
//	numberOfPoints = 10;
//	range = 100;
//
//	point coord1[numberOfPoints];
//	point coord2[numberOfPoints];
//
//	generatePoints(numberOfPoints, coord1, range); //generate random set, print results, find convex hull
//	cout<<"The randomly generated points are:"<<endl;
//	for(point p : coord1)
//		cout<<p.x << " "<< p.y<<endl;
//	vector<point> convexHull1 = calculateConvexHull(coord1, numberOfPoints);
//
//	generatePoints(numberOfPoints, coord2, range);//generate second set of random points, print results, find convex hull
//
//	//shifting coord2 points so to make non-intersection a viable option
//	for(point& p : coord2){
//		p.x = p.x + range*1.5;
//		p.y = p.y + range*1.5;
//	}
//
//	cout<<"The randomly generated points are:"<<endl;
//	for(point p : coord2)
//		cout<<p.x << " "<< p.y<<endl;
//	vector<point> convexHull2 = calculateConvexHull(coord2, numberOfPoints);
//
//	point average1 = getAverage(convexHull1);
//	float radius1 = findRadius(average1, convexHull1);
//	point average2 = getAverage(convexHull2);
//	float radius2 = findRadius(average2, convexHull2);
//
//	int intersectionIndicator = checkIntersection(radius1, radius2, average1, average2); //returns 0 if no intersection 1 if intersection
//	if(intersectionIndicator == 1){
//		cout<<"The two bounding circles intersect therefore the convex hulls may also intersect."<<endl;
//	}
//	else
//		cout<<"The two bounding circles do not intersect therefore the convex hulls will not intersect."<<endl;
//	return 0;
}
