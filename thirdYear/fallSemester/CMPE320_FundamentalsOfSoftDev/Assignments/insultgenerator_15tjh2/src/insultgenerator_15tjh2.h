/*
 * insultgenerator_15tjh2.h
 *
 *  Created on: Sep 26, 2018
 *      Author: Tom Heysel
 *      NetID: 15tjh2
 */
#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class InsultGenerator{//insult generator class
public:
	void initialize();//loads all the insults from Insults.txt file into attributes adjective, hyphenAdj and noun. If this is not possible, throw FileException
	string talkToMe();//returns a single insult
	vector<string> generate(const int &numInsults);//creates the number of insults stated in numInsults and returns them in a vector of strings
	void generateAndSave(const string &fileName, const int &numInsults);//creates the number of insults stated in numInsults and stores it in the file fileName

private:
	vector<string> adjective;//stores the first column of words in Insults.txt
	vector<string> hyphenAdj;//stores the second column of words in Insults.txt
	vector<string> noun;//stores the third column of words in INsults.txt
	bool insultTracker[50][50][50];//Array to check if an insult has been used already - prevents duplicates. It is initialized all to false in
								   //initialize(). Since the testing file generates nowhere near 125 000 insults it is safe to only initialize it once.
								   //If this was being implemented in a larger program, this structure would have to change.
};

class FileException: public exception{//Exception class for errors in reading/writing to files
public:
	FileException();//generic constructor with prewritten statement being assigned to attribute message
	FileException(string statement);//constructor with programmer-dictated statement being assigned to message
	string what();//getter of the attribute message
private:
	string message;//message that explains exception
};

class NumInsultsOutOfBounds : public exception{//Exception class for requesting an invalid number of insults ie too many or a negative amount
public:
	NumInsultsOutOfBounds();//generic constructor with prewritten statement being assigned to attribute message
	NumInsultsOutOfBounds(string statement);//constructor with programmer-dictated statement being assigned to message
	string what();//getter of the attribute message
private:
	string message;//message that explains exception
};




