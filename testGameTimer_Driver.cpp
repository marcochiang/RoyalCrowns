/*
 * testGameTimer_Driver.cpp
 *
 *  Created on: Nov 20, 2012
 *      Author: marcochiang
 */

#include <iostream>
#include <stdio.h>
#include "GameTimer.h"

using namespace std;

//Driver to test all of the functions of the GameTimer class
int main(){
	GameTimer test;
	int start = 1;
	while(start){
		cout << "Enter 0 to start timer: " << endl;
		cin >> start;
	}
	test.startTimer();
	int stop = 0;
	while(!stop){
		cout << "Enter 1 to end timer: " << endl;
		cin >> stop;
	}
	test.endTimer();
	cout << "Time Elapsed: " << test.totalTimer << endl;
}
