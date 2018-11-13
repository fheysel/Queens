//============================================================================
// Name        : fortyThievesAttempt1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include "fortyThievesAttempt1.h"

#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>
#include <stack>


using namespace std;

//Global Variables

//Each array specifies the next cards we can play in each suit pile
int clubNext[2];
int diamondNext[2];
int heartNext[2];
int spadeNext[2];

//The algorithm runs until at least 15 cards have been moved in the autostart function.
int moveCount;

void setUpSeed(){
	srand(time(0));
}

vector<card> createDeck(){
	vector<card> deck;
	int suitIndicator = 0;//loops through the 4 suits
	int cardValue = 1;//the value the card will become
	string requiredSuit;//the suit that the card will become

	for(int i=0; i<104; i++){//104 as forty thieves plays with two full decks

		switch(suitIndicator){//choose suit
			case 0 :
				requiredSuit = "club";
				break;
			case 1 :
				requiredSuit = "diamond";
				break;
			case 2 :
				requiredSuit = "heart";
				break;
			case 3 :
				requiredSuit = "spade";
				break;
		}
		suitIndicator = (suitIndicator+1)%4; //update counter so next suit is assigned properly

		if((i%4) == 0 && i != 0){//ensure that each suit gets a value
			cardValue++;
			if(cardValue == 14)
				cardValue = 1;
			}

		card theCard;
		theCard.suit = requiredSuit;
		theCard.value = cardValue;
		deck.push_back(theCard);
	}
	return deck;
}


void shuffle(vector<card> &deck){
	random_shuffle(deck.begin(), deck.end());//shuffle the deck
}

void dealCards(vector<card> &deck, table &table){
	 for(int i = 0; i<4; i++){
		 for(int j = 0; j<10; j++){
			 table.unsortedPiles[j].push(deck.at(i+j));
		 }
	 }
}

int checkCard(table &table, int pileNum){
	string cardSuit = table.unsortedPiles[pileNum].top().suit;//determine the suit of the card in question.
	int cardValue = table.unsortedPiles[pileNum].top().value;//determine the suit of the card in question.

	//cout<<"Checking the "<< table.unsortedPiles[pileNum].top().value <<" of "<<table.unsortedPiles[pileNum].top().suit<<endl;

	if(cardSuit == "club"){
		if(cardValue == clubNext[0]){
			clubNext[0] += 1;
			return 1;//the first club pile
		}
		if(cardValue == clubNext[1]){
			clubNext[1] += 1;
			return 5;//second club pile
		}
	}else if(cardSuit == "diamond"){
		if (cardValue == diamondNext[0]){
			diamondNext[0] += 1;
			return 0; //the first diamond pile
		}
		if (cardValue == diamondNext[1]){
			diamondNext[1] += 1;
			return 4; //second diamond pile
		}
	}else if(cardSuit == "heart"){
		if (cardValue == heartNext[0]){
			heartNext[0] += 1;
			return 2; //the first heart pile
		}
		if (cardValue == heartNext[1]){
			heartNext[1] += 1;
			return 6; //second heart pile
		}
	}else if(cardSuit == "spade"){
		if (cardValue == spadeNext[0]){
			spadeNext[0] += 1;
			return 3; //the first spade pile
		}
		if (cardValue == clubNext[1]){
			spadeNext[0] += 1;
			return 7; //second spade pile
		}
	}

	return -1;//no match indicator
}

void moveCard(table &table, int sendingPile, int recievingPile){
	card tempCard = table.unsortedPiles[sendingPile].top();
	table.unsortedPiles[sendingPile].pop();
	table.sortedPiles[recievingPile].push(tempCard);
	return;
}

void autoStart(table &table){//uses greedy algorithm to lay out the cards. If a card can be played then it is.
	for(int i = 0; i<2; i++){//initialize ace as the next card that can be played on the sorted piles
		clubNext[i] = 1;
		diamondNext[i] = 1;
		heartNext[i] = 1;
		spadeNext[i] = 1;
	}

	bool noAction;//boolean to indicate that no cards were laid in a pass of all 10 piles. If noAction is true the loop will end
	int recievingPile;//the indicator of which pile to move a card to. If no action should be completed it is set to -1.

	do{
		noAction = true;
		for(int pileInQuestion=0; pileInQuestion<10; pileInQuestion++){//check all 10 unsorted piles to see if a move can be made
			recievingPile = checkCard(table, pileInQuestion);
			if (recievingPile != -1) {
				//cout << table.unsortedPiles[pileInQuestion].top().value << " of "<< table.unsortedPiles[pileInQuestion].top().suit << " moved to "<<recievingPile<<endl;
				moveCard(table, pileInQuestion, recievingPile);
				noAction = false;//a card was moved therefore we must loop again.
				moveCount++;
			}
		}

	}while(!noAction);
}

table::table(){}//empty constructor

void table::reset(){//clears all table stacks so that the game can reset
	for(int i=0; i<10;i++){//clean up all the unsorted piles
		while(!this->unsortedPiles[i].empty()){
				this->unsortedPiles[i].pop();
			}
	}
	for(int i=0; i<8; i++){ //clean up all the sorted piles
		while(!this->sortedPiles[i].empty()){
			this->sortedPiles[i].pop();
		}
	}
}

int main() {
	setUpSeed();//set up random seed

	cout << "Welcome to the game"<<endl<<endl<<endl;

	vector<card> deck;//the vector that will hold the cards
	deck = createDeck();//populate the deck with cards
	table table; //create table class

	do{
		moveCount = 0;//reset the count of how many cards were moved in the autostart function.
		shuffle(deck);//shuffle the cards
		table.reset();//clear the table
		dealCards(deck, table);//deal the cards
		autoStart(table);//run the greedy algorithm

		if (moveCount >= 5) {
			for (int i = 0; i < 8; i++) { //clean up all the sorted piles
				while (!table.sortedPiles[i].empty()) {
					cout << "Pile " << i << " "
							<< table.sortedPiles[i].top().value << " of "
							<< table.sortedPiles[i].top().suit << "s" << endl;
					table.sortedPiles[i].pop();
				}
			}
		}
	}while(moveCount<5);//repeat until 15 cards have successfully been moved
	return 0;
}
