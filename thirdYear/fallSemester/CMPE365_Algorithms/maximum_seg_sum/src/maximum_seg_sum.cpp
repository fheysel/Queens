//============================================================================
// Name        : maximum_seg_sum.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

//returns the max of two integers
int max(int a, int b){
	return ((a > b) ? a:b);
}

//overloaded max function to take 3 integers, returns largest
int max(int a, int b, int c){
	return max(max(a,b),c);
}

int findMaxCrossSum(int array[], int startIndex, int midpoint, int endIndex, int& mostLeftIndex, int& mostRightIndex){

	int sum = 0;
	int leftSum = -20000; // very low number
	for(int i = midpoint; i >= startIndex; i--){//starting at midpoint moving towards start, find largest sum
		sum += array[i];
		if(sum>leftSum){ //if array[i] increases the left sum, add its value to leftSum
			leftSum = sum;
			mostLeftIndex = i; //max left index visited
		}
	}

	sum = 0;
	int rightSum = -20000;//very low number
	for(int i = midpoint+1; i <= endIndex; i++){ //starting 1 index past midpoint moving towards end, find largest sum
		sum += array[i];//accumulate sum

		if(sum>rightSum){ //if array[i] increase the right sum, add its value to rightSum
			rightSum = sum;
			mostRightIndex = i;
		}
	}

	return leftSum + rightSum;//returns sum of elements left and right of the midpoint
}

int findMaxSum(int array[], int startIndex, int endIndex, int &mostLeftIndex, int &mostRightIndex){
	int maxLeft;
	int maxRight;
	int maxCross;
	int maxTotal;

	int trackerArrayLeft[2];
	int trackerArrayRight[2];
	int trackerArrayCross[2];

	//Base case one element
	if(startIndex == endIndex){
		mostLeftIndex = startIndex;//start and end of max subarray is startIndex
		mostRightIndex = startIndex;
		return array[startIndex];
	}

	//find middle of segment
	int midpoint((startIndex + endIndex)/2);

	//Checking left side
	maxLeft = findMaxSum(array, startIndex, midpoint, mostLeftIndex, mostRightIndex); //storing the max value found in left side
	trackerArrayLeft[0] = mostLeftIndex; //storing max left and right index visited temporarily so tracker
	trackerArrayLeft[1] = mostRightIndex;

	//Checking Right Side
	maxRight = findMaxSum(array, midpoint+1, endIndex, mostLeftIndex, mostRightIndex);
	trackerArrayRight[0] = mostLeftIndex;
	trackerArrayRight[1] = mostRightIndex;

	//Checking full sub array
	maxCross = findMaxCrossSum(array, startIndex, midpoint, endIndex, mostLeftIndex, mostRightIndex);
	trackerArrayCross[0] = mostLeftIndex;
	trackerArrayCross[1] = mostRightIndex;

	maxTotal = max(maxLeft, maxRight, maxCross); //calculate total max sub array

	if(maxTotal == maxLeft){
		mostLeftIndex = trackerArrayLeft[0]; //restoring max left and right index visited to be returned by reference
		mostRightIndex = trackerArrayLeft[1];
		return maxLeft;
	}
	else if(maxTotal == maxRight){
		mostLeftIndex = trackerArrayRight[0];
		mostRightIndex = trackerArrayRight[1];
		return maxRight;
	}
	else if(maxTotal == maxCross){
		mostLeftIndex = trackerArrayCross[0];
		mostRightIndex = trackerArrayCross[1];
		return maxCross;
	}
}

int main() {
	int array[10] = {1, 2, -3, 7, 4, 0, 5, 1, -1, 9};
	int array1[10] = {-10, -1, -4, -2, -2,-6, -1, -12, -1, -3};
	int array2[10] = {1, 6, 88, 12, 4, -6, 2, 3, -2, 52};
	int maxSum(0);

	int mostLeftIndex;//farthest left index in max subarray
	int mostRightIndex; //farthest right index in max subarray

	//First Array
	int startIndex = 2;
	int endIndex = 8;

	maxSum = findMaxSum(array, startIndex, endIndex, mostLeftIndex, mostRightIndex);

	cout << "The max segment sum of the array {";
	for(int i = 0; i<9; i++){
		cout << array[i] <<", ";
	}
	cout << array[9] << "} bounded at the given positions " << startIndex << " and " << endIndex << " is: " <<maxSum << ". \n";
	cout << "The sub array is that produces this result is {";
	for(int i = mostLeftIndex; i<mostRightIndex; i++){
		cout << array[i] <<", ";
	}
	cout << array[mostRightIndex] << "}. \n"<< endl;

	//First Array changing bounds
	startIndex = 7;
	endIndex = 7;
	maxSum = findMaxSum(array, startIndex, endIndex, mostLeftIndex, mostRightIndex);

	cout << "The max segment sum of the array {";
	for(int i = 0; i<9; i++){
		cout << array[i] <<", ";
	}
	cout << array[9] << "} bounded at the given positions " << startIndex << " and " << endIndex << " is: " <<maxSum << ". \n";
	cout << "The sub array is that produces this result is {";
	for(int i = mostLeftIndex; i<mostRightIndex; i++){
		cout << array[i] <<", ";
	}
	cout << array[mostRightIndex] << "}. \n"<< endl;

	//Second Array
	startIndex = 3;
	endIndex = 6;
	maxSum = findMaxSum(array1, startIndex, endIndex, mostLeftIndex, mostRightIndex);

	cout << "The max segment sum of the array {";
	for(int i = 0; i<9; i++){
		cout << array1[i] <<", ";
	}
	cout << array1[9] << "} bounded at the given positions " << startIndex << " and " << endIndex << " is: " <<maxSum << ". \n";
	cout << "The sub array is that produces this result is {";
	for(int i = mostLeftIndex; i<mostRightIndex; i++){
		cout << array1[i] <<", ";
	}
	cout << array1[mostRightIndex] << "}. \n"<< endl;

	//Third Array
	startIndex = 0;
	endIndex = 8;
	maxSum = findMaxSum(array2, startIndex, endIndex, mostLeftIndex, mostRightIndex);

	cout << "The max segment sum of the array {";
	for(int i = 0; i<9; i++){
		cout << array2[i] <<", ";
	}
	cout << array2[9] << "} bounded at the given positions " << startIndex << " and " << endIndex << " is: " <<maxSum << ". \n";
	cout << "The sub array is that produces this result is {";
	for(int i = mostLeftIndex; i<mostRightIndex; i++){
		cout << array2[i] <<", ";
	}
	cout << array2[mostRightIndex] << "}. \n"<< endl;

	//Third Array Changing Bounds
	startIndex = 0;
	endIndex = 9;
	maxSum = findMaxSum(array2, startIndex, endIndex, mostLeftIndex, mostRightIndex);

	cout << "The max segment sum of the array {";
	for(int i = 0; i<9; i++){
		cout << array2[i] <<", ";
	}
	cout << array2[9] << "} bounded at the given positions " << startIndex << " and " << endIndex << " is: " <<maxSum << ". \n";
	cout << "The sub array is that produces this result is {";
	for(int i = mostLeftIndex; i<mostRightIndex; i++){
		cout << array2[i] <<", ";
	}
	cout << array2[mostRightIndex] << "}. \n"<< endl;


	/////////////////////////////////////////////////////////
	//PART 2
	////////////////////////////////////////////////////////

	//First Array
	startIndex = 0;
	endIndex = 9;

	maxSum = findMaxSum(array, startIndex, endIndex, mostLeftIndex, mostRightIndex);

	//print results
	cout << "The max segment sum of the array {";
	for(int i = 0; i<9; i++){
		cout << array[i] <<", ";
	}
	cout << array[9] << "} bounded at the given positions " << startIndex << " and " << endIndex << " is: " <<maxSum << ". \n";
	cout << "The sub array is that produces this result is {";
	for(int i = mostLeftIndex; i<mostRightIndex; i++){
		cout << array[i] <<", ";
	}
	cout << array[mostRightIndex] << "}. Replace these elements with -20 000 and run the program again to find 2nd largest non-overlapping subarray."<< endl;

	//replace values
	for(int i = mostLeftIndex; i<=mostRightIndex; i++){
		array[i] = -20000;
	}

	//find second largest non-overlapping subarray.
	maxSum = findMaxSum(array, startIndex, endIndex, mostLeftIndex, mostRightIndex);
	if(maxSum == -20000){
		cout << "Sorry a 2nd largest non-overlapping subarray does not exist in the given bounds.";
	}
	else{
		//print results
		cout << "The max segment sum of the array {";
		for(int i = 0; i<9; i++){
			cout << array[i] <<", ";
		}
		cout << array[9] << "} bounded at the given positions " << startIndex << " and " << endIndex << " is: " <<maxSum << ". \n";
		cout << "The sub array is that produces this result is {";
		for(int i = mostLeftIndex; i<mostRightIndex; i++){
			cout << array[i] <<", ";
		}
		cout << array[mostRightIndex] << "}.\n" << endl;
	}


	/////////////////////////////////////////TEST 2nd array///////////////////////////////////////////////////////////////////////////////////////////
	startIndex = 3;
	endIndex = 7;

	maxSum = findMaxSum(array1, startIndex, endIndex, mostLeftIndex, mostRightIndex);

	//print results
	cout << "The max segment sum of the array {";
	for(int i = 0; i<9; i++){
		cout << array1[i] <<", ";
	}
	cout << array1[9] << "} bounded at the given positions " << startIndex << " and " << endIndex << " is: " <<maxSum << ". \n";
	cout << "The sub array is that produces this result is {";
	for(int i = mostLeftIndex; i<mostRightIndex; i++){
		cout << array1[i] <<", ";
	}
	cout << array1[mostRightIndex] << "}. Replace these elements wiht -20 000 and run the program again to find 2nd largest non-overlapping subarray."<< endl;

	//replace values
	for(int i = mostLeftIndex; i<=mostRightIndex; i++){
		array1[i] = -20000;
	}

	//find second largest non-overlapping subarray.
	maxSum = findMaxSum(array1, startIndex, endIndex, mostLeftIndex, mostRightIndex);
	if(maxSum == -20000){
		cout << "Sorry a 2nd largest non-overlapping subarray does not exist in the given bounds.";
	}
	else{
		//print results
		cout << "The max segment sum of the array {";
		for(int i = 0; i<9; i++){
			cout << array1[i] <<", ";
		}
		cout << array1[9] << "} bounded at the given positions " << startIndex << " and " << endIndex << " is: " <<maxSum << ". \n";
		cout << "The sub array is that produces this result is {";
		for(int i = mostLeftIndex; i<mostRightIndex; i++){
			cout << array1[i] <<", ";
		}
		cout << array1[mostRightIndex] << "}.\n" << endl;
	}

	////////////////////////////////////////////TEST 3rd Array//////////////////////////////////////////////////////////////////////////////////
	startIndex = 0;
	endIndex = 9;

	maxSum = findMaxSum(array2, startIndex, endIndex, mostLeftIndex, mostRightIndex);

	//print results
	cout << "The max segment sum of the array {";
	for(int i = 0; i<9; i++){
		cout << array2[i] <<", ";
	}
	cout << array2[9] << "} bounded at the given positions " << startIndex << " and " << endIndex << " is: " <<maxSum << ". \n";
	cout << "The sub array is that produces this result is {";
	for(int i = mostLeftIndex; i<mostRightIndex; i++){
		cout << array2[i] <<", ";
	}
	cout << array2[mostRightIndex] << "}. Replace these elements with -20 000 and run the program again to find 2nd largest non-overlapping subarray."<< endl;

	//replace values
	for(int i = mostLeftIndex; i<=mostRightIndex; i++){
		array2[i] = -20000;
	}

	//find second largest non-overlapping subarray.
	maxSum = findMaxSum(array2, startIndex, endIndex, mostLeftIndex, mostRightIndex);
	if(maxSum == -20000){
		cout << "Sorry a 2nd largest non-overlapping subarray does not exist in the given bounds.";
	}
	else{
		//print results
		cout << "The max segment sum of the array {";
		for(int i = 0; i<9; i++){
			cout << array2[i] <<", ";
		}
		cout << array2[9] << "} bounded at the given positions " << startIndex << " and " << endIndex << " is: " <<maxSum << ". \n";
		cout << "The sub array is that produces this result is {";
		for(int i = mostLeftIndex; i<mostRightIndex; i++){
			cout << array2[i] <<", ";
		}
		cout << array2[mostRightIndex] << "}.\n" << endl;
	}

	return 0;
}

