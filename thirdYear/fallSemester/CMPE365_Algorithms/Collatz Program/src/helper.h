/*
 * helper.h
 *
 *  Created on: Sep 21, 2018
 *      Author: Poe
 */

#ifndef HELPER_H_
#define HELPER_H_
#define listSize 1000

struct node{
		int number;
		bool visited;
	};

extern node nodeArray[];

bool isEven(int n){
	if(n%2 == 0){
		return 1;
	}
	else{
		return 0;
	}
}

int checkVisitStatus(int i){
	if(i>listSize){					//divide by 5 as node struct has an int and bool - therefore 5 Bytes.
								//if number is greater than the size of array return false. Ex checking up to 1000
								//at 999 we *3+1 this gives number greater than 1000 therefore it isn't in list therefore
								//don't check it
		//replace 1000 with (sizeof(nodeArray)/5)
		return 0;
	}
	else{
		if(nodeArray[i].visited == true){
			return 1;
		}
		else{
			return 0;
		}
	}
}

int collatz(int i, int& recursiveCounter, int& maxValueVisited){
	if(maxValueVisited<i){
		maxValueVisited = i;
	}
	if(checkVisitStatus(i) == true){
		return i;
	}
	else{
		if(i == 1){
			return 1;
		}
		else{
			recursiveCounter++;
			if(isEven(i)){
				i = collatz((i/2), recursiveCounter, maxValueVisited);
			}
			else{
				i = collatz(((i*3)+1), recursiveCounter, maxValueVisited);
			}
		}
	}
}







#endif /* HELPER_H_ */
