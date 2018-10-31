//============================================================================
// Name        : Collatz.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include  "helper.h"
using namespace std;


node nodeArray[listSize];


int main() {

	for(int i = 1; i <= listSize;  i++){//create array of nodes numbered from 1-1000. All initialized as not visited.
		nodeArray[i] = {i, false};
	}

	cout << "Let's run the optimized Collatz problem for all numbers up to 1000" << endl << endl;

	int terminationPoint = 1;
	int recursiveCounter;
	int maxValueVisited;

	for(int i=1; i<=listSize; i++){ //test each node from 1-1000 if it returns 1 mark visited as true
		recursiveCounter = 0;
		maxValueVisited= i;
		terminationPoint = collatz(i, recursiveCounter, maxValueVisited);
		if(terminationPoint != 0){
			cout << "Collatz problem works for integer n = "<< nodeArray[i].number << ". It terminates once it reaches "<< terminationPoint << ". This takes "<< recursiveCounter<< " recursive calls. The max value visited = " << maxValueVisited << endl; // proper output
			//output of x,y co-ordinates to plot in excel cout << nodeArray[i].number << "\t" << recursiveCounter << endl;
			//cout << nodeArray[i].number << "\t" << maxValueVisited << endl;//more excel outputs
			nodeArray[i].visited = true;
		}
		else{
			cout << "The Collatz program fails with integer n = "<< nodeArray[i].number << endl;
		}
	}
	return 0;
}


