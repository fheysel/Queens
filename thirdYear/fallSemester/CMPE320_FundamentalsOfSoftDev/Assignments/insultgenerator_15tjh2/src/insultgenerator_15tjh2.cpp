/*
 * insultgenerator_15tjh2.cpp
 *
 *  Created on: Sep 26, 2018
 *      Author: Tom Heysel
 *      NetID: 15tjh2
 *
 */

#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>
#include "insultgenerator_15tjh2.h"

using namespace std;

//Exception Constructors
FileException::FileException(){
	message = "Error with file";
}

FileException::FileException(string statement){
	message = statement;
}

NumInsultsOutOfBounds::NumInsultsOutOfBounds(){
	message = "Error! Number of insults you are attempting to create is invalid";
}

NumInsultsOutOfBounds::NumInsultsOutOfBounds(string statement){
	message = statement;
}

string FileException::what(){
	return message;
}

string NumInsultsOutOfBounds::what(){
	return message;
}


	// The initialize() method should load all the source phrases from the InsultsSource.txt file into the attributes.
	// If the file cannot be read, the method should throw an exception.
void InsultGenerator::initialize(){
	srand(time(0));//set up random seed

	string InsultsSource = "InsultsSource.txt";
	string line;
	ifstream fileIn;

	fileIn.open(InsultsSource.c_str());//open file
	if (fileIn.fail()) {//If file open fails, throw exception
		throw FileException("Error could not open file");
	}

	for(int i=0; i<50; i++){//for each line of text file enter the correct vector
		getline(fileIn, line, '\t');
		adjective.push_back(line);

		getline(fileIn, line, '\t');
		hyphenAdj.push_back(line);

		getline(fileIn, line, '\n');
		noun.push_back(line);
	}

	fileIn.close();//close file

	for(int i=0; i<50; i++){//initialize array to track if an insult has already been used
		for(int j=0; j<50; j++){
			for(int k=0; k<50; k++){
				insultTracker[i][j][k] = false;
			}
		}
	}
}

string InsultGenerator::talkToMe(){//returns a single insult
	int adjElement = rand()%50;//gets random insult
	int hyphenAdjElement = rand()%50;
	int nounElement = rand()%50;

	return ("Thou "+adjective.at(adjElement) +" "+ hyphenAdj.at(hyphenAdjElement) +" "+ noun.at(nounElement)+ "!\n");//returns it
}


vector<string> InsultGenerator::generate(const int &numInsults){//geerates a specified number of insults
	if(numInsults>10000){//throw exception
		throw NumInsultsOutOfBounds("Number of requested insults too large!");
	}
	else if(numInsults<1){//throw exception
		throw NumInsultsOutOfBounds("Cannot have a negative number of insults");
	}
	else{//the required number of insults is in valid range
		vector<string> insults;//create vector to store strings

		int adjElement;
		int hyphenAdjElement;
		int nounElement;
		string singleInsult;

		for(int i=0; i<numInsults; i++){
			do{//while the insult generated hasn't already been used
				adjElement = rand()%50;//generate random insult indices
				hyphenAdjElement = rand()%50;
				nounElement = rand()%50;
			}while(insultTracker[adjElement][hyphenAdjElement][nounElement]);

			//create an insult
			singleInsult = ("Thou "+adjective.at(adjElement) +" "+ hyphenAdj.at(hyphenAdjElement) +" "+ noun.at(nounElement)+ "!\n");
			insults.push_back(singleInsult);//add it to the vector
		}

		sort(insults.begin(), insults.end());//sort the insults alphabetically

		return insults;
	}
}


void InsultGenerator::generateAndSave(const string &fileName, const int &numInsults){// calls generate function and saves the insults into specified file
	if(numInsults>10000){//throw exception
		throw NumInsultsOutOfBounds("Number of requested insults too large!");
	}
	else if(numInsults<1){
		throw NumInsultsOutOfBounds("Cannot have a negative number of insults!");
	}
	else{//number is in valid range
		vector<string> insults = generate(numInsults);
		//Storing file
		ofstream fileOut;
		fileOut.open(fileName.c_str());//open file for output
		for(string x : insults){
			fileOut << x << "\n";
		}
		fileOut.close();

		if(!fileOut){
			throw FileException("Error could not write to file!");
		}
		else{
			cout << "Writing to " + fileName + " successful!";
		}
	}
}
