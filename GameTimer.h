/*
 * GameTimer.h
 *
 *  Created on: Nov 20, 2012
 *      Author: Marco Chiang
 */

#ifndef GAMETIMER_H_
#define GAMETIMER_H_

class GameTimer{
public:
	GameTimer();
	time_t start;
	time_t end;
	double goFishTimer;
	double heartsTimer;
	double blackJackTimer;
	double totalTimer;
	void startTimer();
	void endTimer();
};


#endif /* GAMETIMER_H_ */
