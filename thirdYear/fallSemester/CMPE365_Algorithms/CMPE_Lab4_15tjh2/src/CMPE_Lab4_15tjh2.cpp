//============================================================================
// Name        : CMPE_Lab4_15tjh2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct gate{
	double arrivalTime;
	double departureTime;
};

void readFromFile(const string& fileName, vector<double> &list){
	string line;
	double time;

	//open file
	ifstream fileIn;
	fileIn.open(fileName);
	if (fileIn.fail()) {//If file open fails, tell user
			cerr << "Error could not open file";
		}

	//read in entries
	while(!fileIn.eof()){
		getline(fileIn, line, '\n');//get number as string
		time = atof(line.c_str());//convert to double
		list.push_back(time);//enter into list
	}
	fileIn.close();//close file
	list.pop_back();//remove the added zero from vector;
	return;
}

int findMinNumOfGates(const vector<double>& arrivals, const vector<double>& departures){
	vector<gate> gates(0);
	gate tempGate;
	unsigned int n = 0;
	bool resolved = false;

	for(unsigned int i = 0; i<arrivals.size(); i++){//Greedy algorithm to find minimum number of required gates
		if(gates.size() == 0){//create first gate
			tempGate.arrivalTime = arrivals.at(i);
			tempGate.departureTime = departures.at(i);

			gates.push_back(tempGate);
			//cout<<"Flight "<<i<<" Arrives at "<<arrivals.at(i)<<" Departs at "<< departures.at(i)<<". It will use Gate "<<n<<endl;
			//cout<<i<<"\t"<<arrivals.at(i)<<"\t"<< departures.at(i)<<"\t"<<n<<endl;//excel testing
		}
		else{
			n = 0;
			resolved = false;
			while(n < gates.size() && resolved != true){//while we haven't found a gate that the flight will fit into
				if(arrivals.at(i) >= gates.at(n).departureTime){//if flight fits with gate update the gate's info and mark resolved as true
					gates.at(n).arrivalTime = arrivals.at(i);
					gates.at(n).departureTime = departures.at(i);
					resolved = true;
					//cout<<"Flight "<<i<<" Arrives at "<<arrivals.at(i)<<" Departs at "<< departures.at(i)<<". It will use Gate "<<n<<endl;
					//cout<<i<<"\t"<<arrivals.at(i)<<"\t"<< departures.at(i)<<"\t"<<n<<endl;//excel testing
				}
				n++;// increase gate counter
			}
			if(resolved == false){//flight requires another gate to fit in
				tempGate.arrivalTime = arrivals.at(i);
				tempGate.departureTime = departures.at(i);
				gates.push_back(tempGate);//add new gate to the vector of gates
				//cout<<"Flight "<<i<<" Arrives at "<<arrivals.at(i)<<" Departs at "<< departures.at(i)<<". It will use Gate "<<n<<endl;
				//cout<<i<<"\t"<<arrivals.at(i)<<"\t"<< departures.at(i)<<"\t"<<n<<endl;//excel testing
			}
		}
	}

	return (int)gates.size();
}

void delayFlights(vector<double> &arrivals, vector<double> &departures, const double& maxDelayTime, int& numLateFlights){
	//the chance of an arrival or departure becomes delayed is 5%. This percentage was chosen arbitrarily.
	int arrivalDelay;//each arrival will have a 1 in 20 chance of being delayed
	int departureDelay;//each departure will have a 1 in 20 chance of being delayed
	double tempDelay;
	int isLate = 0;//0 for not late 1 or 2 for late
	numLateFlights = 0;

	for(unsigned int i = 0; i < arrivals.size(); i++){
		isLate = 0;//each flight starts out as not late
		departureDelay = rand()%20;//1 in 20 chance
		if(departureDelay == 0){//if the random number generated was a zero, give the departure time a delay
			tempDelay = ((double)rand()/maxDelayTime)+1;
			departures.at(i) += (tempDelay/60);
			isLate++;//marked as late
		}
		arrivalDelay = rand()%20;

		//if random num generated is zero AND arrival time delay still allows for 10 minutes in between landing and take off then apply the delay
		if(arrivalDelay == 0 && (departures.at(i) - (arrivals.at(i) + maxDelayTime) > 0.1666)){//0.1666 is decimal for 10 minutes9
			tempDelay = ((double)rand()/maxDelayTime)+1;
			arrivals.at(i) += (tempDelay/60);
			isLate++;//marked as late
		}
		if(isLate != 0)//if it was marked as late ie isLate == 1 or ==2
			numLateFlights++;//add it to the number of late flights
	}
}

int findGatesWithDelay(vector<double> &arrivals, vector<double> &departures, const double& maxDelayTime, int& numLateFlights){
	delayFlights(arrivals, departures, maxDelayTime, numLateFlights);
	cout<<numLateFlights << "\t";//excel analysis
	return findMinNumOfGates(arrivals, departures);//return the average number of gates needed
}

int main() {
	srand(time(0));//set up random seed

	//set strings to file names
	string arrivalsFile1 = "start1.csv";
	string departuresFile1 = "finish1.csv";
	string arrivalsFile2 = "start2.csv";
	string departuresFile2 = "finish2.csv";
	int gates = 0;

	//PART 1
	//make vectors to hold arrival and departure times
	vector<double> arrivals1;
	vector<double> departures1;
	vector<double> arrivals2;
	vector<double> departures2;

	//fill vectors
	readFromFile(arrivalsFile1, arrivals1);
	readFromFile(departuresFile1, departures1);
	readFromFile(arrivalsFile2, arrivals2);
	readFromFile(departuresFile2, departures2);

	//implement greedy algorithm. This function will print the minimum required number of gates.
	gates = findMinNumOfGates(arrivals1, departures1);
	//print total number of gates needed
	cout<<"The total number of gates required for this schedule is "<<gates<<endl;

	gates = findMinNumOfGates(arrivals2, departures2);
	//print total number of gates needed
	cout<<"The total number of gates required for this schedule is "<<gates<<endl;

	cout<<endl<<endl;

	////////////////////////////////////////PART 2//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int numLateFlights = 0;

	for(int i=1;i<=180;i++){
		//cout<< "Schedule 1 requires "<<findGatesWithDelay(arrivals1, departures1, i)<< " gates if each flight has 5% chance of being delayed "<<i<<" minutes." << endl;
		cout<<findGatesWithDelay(arrivals1, departures1, i, numLateFlights)<<"\t"<<i << endl;//excel analysis
	}

	cout<<endl<<endl;

	for(int i=1;i<=180;i++){
		//cout<< "Schedule 2 requires "<<findGatesWithDelay(arrivals2, departures2, i)<< " gates if each flight has 5% chance of being delayed "<<i<<" minutes." << endl;
		cout<<findGatesWithDelay(arrivals2, departures2, i, numLateFlights)<<"\t"<<i << endl;//excel analysis
	}

	return 0;
}
