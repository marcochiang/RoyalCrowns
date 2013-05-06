/*
 * CardCounter.cpp
 *
 *  Created on: Nov 21, 2012
 *      Author: marcochiang
 */
#include "CardCounter.h"

CardCounter::CardCounter(){
	CardCounter::totalCardCount = 0;
	CardCounter::goFishCardCount = 0;
	CardCounter::heartsCardCount = 0;
	CardCounter::blackJackCardCount = 0;
}

void CardCounter::incrCardCount(){
	totalCardCount++;
}
