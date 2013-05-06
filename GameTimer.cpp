/*
 * GameTimer.cpp
 *
 *  Created on: Nov 20, 2012
 *      Author: Marco Chiang
 *
 *      This class uses the included library "time" to
 *      start and end a timer and store the difference in
 *      each game timer.
 */

#include <time.h>
#include "GameTimer.h"
//constructor
GameTimer::GameTimer(){
	GameTimer::goFishTimer = 0.0;
	GameTimer::heartsTimer = 0.0;
	GameTimer::blackJackTimer = 0.0;
	GameTimer::totalTimer = 0.0;
}

//starts the game timer
void GameTimer::startTimer() {
	time(&start);
}

//ends the game timer and calculates the difference
void GameTimer::endTimer() {
		time(&end);
		//goFishTimer += difftime(end, start);
		totalTimer += difftime(end,start);
}
