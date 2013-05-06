/*
 * CardCounter.h
 *
 *  Created on: Nov 21, 2012
 *      Author: marcochiang
 */

#ifndef CARDCOUNTER_H_
#define CARDCOUNTER_H_

class CardCounter{

public:
	CardCounter();
	int totalCardCount;
	int goFishCardCount;
	int heartsCardCount;
	int blackJackCardCount;
	void incrCardCount();
};


#endif /* CARDCOUNTER_H_ */
