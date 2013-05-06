#include "HeartsGame.h"
#include "Player.h"
#include "Controller.h"
#include "structs.h"
#include "display.h"
#include "AI.h"
#include "Rules.h"
#include <time.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
//#include <ifstream>


using namespace std;

HeartsGame::HeartsGame()
{
}

HeartsGame::~HeartsGame()
{
    //dtor
}

void HeartsGame::testing(){
	ofstream testfile;

	//Testing Controller::aceNumber function
	testfile.open("output-controller-aceNumber.txt", ios::app);
	for(int i=1; i<14; i++){
		testfile << dealer.aceNumber(i) << endl;
	}
	testfile.close();

	//Testing Controller::advancePassState function
	testfile.open("output-controller-advancePassState.txt", ios::app);
	heartBeat.currentPassState = NOPASS;
	for(int i=0; i<4; i++){
		dealer.advancePassState(heartBeat);
		testfile << heartBeat.currentPassState << endl;
	}
	testfile.close();

	//Testing Controller::initializeDeck function
	testfile.open("output-controller-initializeDeck.txt", ios::app);
	dealer.initializeDeck();
	for(int i=0; i<52; i++){
		testfile << i << " " << dealer.deck[i].cardNumber << " " <<  dealer.deck[i].suit << " " << dealer.deck[i].deckNumber << " " << dealer.deck[i].penaltyValue << " "<< dealer.deck[i].xPosition << " " << dealer.deck[i].yPosition << endl;
	}
	testfile.close();

	//Testing Controller::makeNullCard function
	testfile.open("output-controller-makeNullCard.txt", ios::app);
	for(int i=0; i<52; i++){
		dealer.makeNullCard(dealer.deck[i]);
		testfile << dealer.deck[i].cardNumber << " " <<  dealer.deck[i].suit << " " << dealer.deck[i].deckNumber << " " << dealer.deck[i].penaltyValue << " "<< dealer.deck[i].xPosition << " " << dealer.deck[i].yPosition << endl;
	}
	testfile.close();

}

void HeartsGame::saveFile(){
	ofstream myfile;
	myfile.open ("");
	//myfile << "Writing this to a file.\n";
	myfile.close();
}

bool HeartsGame::fileExists(const char *filename){
  ifstream ifile(filename);
  return ifile;
}

bool HeartsGame::isGameOver(){
	//check if any player's score is greater than or equal to one hundred
	if(heartBeat.gameScoreBoard.p1score >= 100 || heartBeat.gameScoreBoard.p2score >= 100 || heartBeat.gameScoreBoard.p3score >= 100 || heartBeat.gameScoreBoard.p4score >= 100){
		return true;

	}
	return false;
}

int HeartsGame::getNumOfHumans(){
	return 0;		//TODO: fix returns
}

void HeartsGame::setNames(){
}


void HeartsGame::setupGame(){
	p1.setPlayerNumber(1);
	p2.setPlayerNumber(2);
	p3.setPlayerNumber(3);
	p4.setPlayerNumber(4);

	AI2.setPuppet(p2);
	AI3.setPuppet(p3);
	AI4.setPuppet(p4);

	heartBeat.gameScoreBoard.p1score = 0;
	heartBeat.gameScoreBoard.p2score = 0;
	heartBeat.gameScoreBoard.p3score = 0;
	heartBeat.gameScoreBoard.p4score = 0;
	//gameDisplay.bannerBottom("hello!");
//
//	p2.setAIplaceHolder(0);
//	p3.setAIplaceHolder(0);
//	p4.setAIplaceHolder(0);

	dealer.initializeDeck();

	heartBeat.roundNumber=1;

	/*
	switch(getNumOfHumans()){
        case 1:
            //get one name from the user and assign the others
            break;
        case 2:
            //get two names from users and assign the other two
            break;
        case 3:

            break;
        case 4:

            break;
        default:
            break;
        }
        */
}



void HeartsGame::wait(){
int key;
	int counter = 0;
	while(counter <1){
		key = gameDisplay.captureInput();
		if(key != 0 && key == -1){
			counter++;
		}
	}
}

void HeartsGame::determineWinner(){
	int winner = 1;
	int winner2;
	//bool tie = false;
	int lowest = heartBeat.gameScoreBoard.p1score;

	if(heartBeat.gameScoreBoard.p2score <= lowest){
		lowest = heartBeat.gameScoreBoard.p2score;
		winner = 2;
	}
	if(heartBeat.gameScoreBoard.p3score <= lowest) {
		lowest = heartBeat.gameScoreBoard.p3score;
		winner = 3;
	}
	if(heartBeat.gameScoreBoard.p4score <= lowest) {
		lowest = heartBeat.gameScoreBoard.p4score;
		winner = 4;
	}


	if(heartBeat.gameScoreBoard.p1score == lowest){
		lowest = heartBeat.gameScoreBoard.p2score;
		winner2 = 2;
	}
	if(heartBeat.gameScoreBoard.p2score == lowest){
		lowest = heartBeat.gameScoreBoard.p2score;
		winner2 = 2;
	}
	if(heartBeat.gameScoreBoard.p3score == lowest) {
		lowest = heartBeat.gameScoreBoard.p3score;
		winner2 = 3;
	}
	if(heartBeat.gameScoreBoard.p4score == lowest) {
		lowest = heartBeat.gameScoreBoard.p4score;
		winner2 = 4;
	}

	stringstream messageString;

	if(winner!=winner2) {
		messageString.str("");
		messageString << "Player " << winner << " won the game! Click to exit.";
		gameDisplay.bannerTop(messageString.str());
		wait();
		//exit(EXIT_SUCCESS);
	}
	else{
		messageString.str("");
		messageString << "There was a tie! Player " << winner << " and Player " << winner2 << " won the game! Click to exit.";
		gameDisplay.bannerTop(messageString.str());
		wait();
		//exit(EXIT_SUCCESS);
	}


}

void HeartsGame::testGame(){
//define the details of each round/hand
	stringstream messageString;

	//heartBeat.AIplaceHolder = 0;


	messageString.str("");
	//heartBeat.roundNumber++;
	dealer.displayMessageBox(gameDisplay, heartBeat);
	dealer.displayScoreBoard(gameDisplay,heartBeat);
	//dealer.changeTurnState(heartBeat, PASS); doesn't need to be called here because deal takes care of this
	dealer.deal(p1,p2,p3,p4,heartBeat);

	dealer.sortHandBubble(p1);
	dealer.sortHandBubble(p2);
	dealer.sortHandBubble(p3);
	dealer.sortHandBubble(p4);

	dealer.displayHand(gameDisplay,p1);
	gameDisplay.updateScreen();

	mvprintw(12,1,"Player 2");
	mvprintw(12,71,"Player 4");
	mvprintw(6,36,"Player 3");

	messageString.str("");
	messageString << "You are Player 1. Click to continue.";
	gameDisplay.bannerTop(messageString.str());
	wait();

//	messageString.str("");
//	messageString << "Displaying Player1's hand.";
//	gameDisplay.bannerTop(messageString.str());
//	wait();
//
//	dealer.displayHand(gameDisplay,p2);
//	gameDisplay.updateScreen();
//
//	messageString.str("");
//	messageString << "Displaying Player2's hand.";
//	gameDisplay.bannerTop(messageString.str());
//	wait();
//
//	dealer.displayHand(gameDisplay,p3);
//	gameDisplay.updateScreen();
//
//	messageString.str("");
//	messageString << "Displaying Player3's hand.";
//	gameDisplay.bannerTop(messageString.str());
//	wait();
//
//	dealer.displayHand(gameDisplay,p4);
//	gameDisplay.updateScreen();
//
//	messageString.str("");
//	messageString << "Displaying Player4's hand.";
//	gameDisplay.bannerTop(messageString.str());
//	wait();


	messageString.str("");
	messageString << "Starting Round " << heartBeat.roundNumber << ". Click to continue.";
	gameDisplay.bannerTop(messageString.str());
	wait();
	dealer.displayMessageBox(gameDisplay, heartBeat);

//	dealer.displayHand(gameDisplay, p1);
//
//	messageString.str("");
//	messageString << "Click to sort your hand.";
//	gameDisplay.bannerTop(messageString.str());

//	wait();
//	dealer.sortHandBubble(p1);
//	dealer.sortHandBubble(p2);
//	dealer.sortHandBubble(p3);
//	dealer.sortHandBubble(p4);
//
//	dealer.displayHand(gameDisplay, p1);
//	gameDisplay.updateScreen();
	//dealer.userPickPassCards(gameDisplay, p1);

	//dealer.clearTrickCardsDisplay(gameDisplay);
	//dealer.userPlayTrickCard(gameDisplay, p1);
	//dealer.moveAIPassCards(p2,gameDisplay,AI2,rulebook,heartBeat);

//	messageString.str("");
//	messageString << "This is your sorted hand.";
//	gameDisplay.bannerTop(messageString.str());
//	wait();

//	messageString.str("");
//	messageString << "The first card is " << p1.getHand()[0].deckNumber;
//	gameDisplay.bannerTop(messageString.str());
//	wait();
//
//
//	dealer.displayHand(gameDisplay,p2);
//	gameDisplay.updateScreen();
//
//	messageString.str("");
//	messageString << "Displaying Player2's hand.";
//	gameDisplay.bannerTop(messageString.str());
//	wait();
//
//	messageString.str("");
//	messageString << "The first card is " << p2.getHand()[0].deckNumber;
//	gameDisplay.bannerTop(messageString.str());
//	wait();
//
//
//	dealer.displayHand(gameDisplay,p3);
//	gameDisplay.updateScreen();
//
//	messageString.str("");
//	messageString << "Displaying Player3's hand.";
//	gameDisplay.bannerTop(messageString.str());
//	wait();
//
//	messageString.str("");
//	messageString << "The first card is " << p3.getHand()[0].deckNumber;
//	gameDisplay.bannerTop(messageString.str());
//	wait();
//
//
//	dealer.displayHand(gameDisplay,p4);
//	gameDisplay.updateScreen();
//
//	messageString.str("");
//	messageString << "Displaying Player4's hand.";
//	gameDisplay.bannerTop(messageString.str());
//	wait();
//
//	messageString.str("");
//	messageString << "The first card is " << p4.getHand()[0].deckNumber;
//	gameDisplay.bannerTop(messageString.str());
//	wait();


	//dealer.findTwoOfClubs(p1,p2,p3,p4,heartBeat);

//
//	messageString.str("");
//	messageString << "The two of clubs owner is " << heartBeat.twoOfClubsOwner;
//	gameDisplay.bannerTop(messageString.str());
//	wait();
//
//	dealer.displayHand(gameDisplay,p1);
//	gameDisplay.updateScreen();

//	dealer.userPickPassCards(gameDisplay, p1);
//	dealer.moveAIPassCardsDumb(p2, gameDisplay, AI2, rulebook, heartBeat);
//	dealer.moveAIPassCardsDumb(p3, gameDisplay, AI3, rulebook, heartBeat);
//	dealer.moveAIPassCardsDumb(p4, gameDisplay, AI4, rulebook, heartBeat);
//
//	dealer.sortHandBubble(p1);
//	dealer.sortHandBubble(p2);
//	dealer.sortHandBubble(p3);
//	dealer.sortHandBubble(p4);
//
//	dealer.displayHand(gameDisplay,p1);
//	gameDisplay.updateScreen();

//	messageString.str("");
//	messageString << "This is what your hand looks like without your pass cards";
//	gameDisplay.bannerTop(messageString.str());
//	wait();

//	dealer.displayPassCards(gameDisplay,p1);
//	gameDisplay.updateScreen();
//
//	messageString.str("");
//	messageString << "Displaying your pass cards.";
//	gameDisplay.bannerTop(messageString.str());
//	wait();

//	dealer.displayHand(gameDisplay,p2);
//	gameDisplay.updateScreen();
//
//	messageString.str("");
//	messageString << "Displaying Player2's hand.";
//	gameDisplay.bannerTop(messageString.str());
//	wait();
//
//	dealer.displayPassCards(gameDisplay,p2);
//	gameDisplay.updateScreen();
//
//	messageString.str("");
//	messageString << "Displaying Player2's pass cards.";
//	gameDisplay.bannerTop(messageString.str());
//	wait();
//
//	dealer.displayHand(gameDisplay,p3);
//	gameDisplay.updateScreen();
//
//	messageString.str("");
//	messageString << "Displaying Player3's hand.";
//	gameDisplay.bannerTop(messageString.str());
//	wait();
//
//	dealer.displayPassCards(gameDisplay,p3);
//	gameDisplay.updateScreen();
//
//	messageString.str("");
//	messageString << "Displaying Player3's pass cards.";
//	gameDisplay.bannerTop(messageString.str());
//	wait();
//
//	dealer.displayHand(gameDisplay,p4);
//	gameDisplay.updateScreen();
//
//	messageString.str("");
//	messageString << "Displaying Player4's hand.";
//	gameDisplay.bannerTop(messageString.str());
//	wait();
//
//	dealer.displayPassCards(gameDisplay,p4);
//	gameDisplay.updateScreen();
//
//	messageString.str("");
//	messageString << "Displaying Player4's pass cards.";
//	gameDisplay.bannerTop(messageString.str());
//	wait();


//	dealer.pass(gameDisplay, heartBeat, p1, p2, p3, p4);
//
//	dealer.sortHandBubble(p1);
//	dealer.sortHandBubble(p2);
//	dealer.sortHandBubble(p3);
//	dealer.sortHandBubble(p4);
//
//	dealer.displayHand(gameDisplay,p1);
//	gameDisplay.updateScreen();

//	messageString.str("");
//	messageString << "This is what your hand looks like WITH your pass cards";
//	gameDisplay.bannerTop(messageString.str());
//	wait();

//	dealer.displayHand(gameDisplay,p2);
//	gameDisplay.updateScreen();
//
//	messageString.str("");
//	messageString << "Player2's hand after pass";
//	gameDisplay.bannerTop(messageString.str());
//	wait();
//
//	dealer.displayHand(gameDisplay,p3);
//	gameDisplay.updateScreen();
//
//	messageString.str("");
//	messageString << "Player3's hand after pass";
//	gameDisplay.bannerTop(messageString.str());
//	wait();
//
//	dealer.displayHand(gameDisplay,p4);
//	gameDisplay.updateScreen();
//
//	messageString.str("");
//	messageString << "Player4's hand after pass";
//	gameDisplay.bannerTop(messageString.str());
//	wait();
	dealer.displayMessageBox(gameDisplay, heartBeat);
	dealer.initiatePasses(p1,p2,p3,p4,AI2,AI3,AI4,rulebook,gameDisplay,heartBeat);
	dealer.displayMessageBox(gameDisplay, heartBeat);
	dealer.findTwoOfClubs(p1,p2,p3,p4,heartBeat);

//	messageString.str("");
//	messageString << "Now the two of clubs owner is " << heartBeat.twoOfClubsOwner;
//	gameDisplay.bannerTop(messageString.str());
//	wait();

	dealer.changeTurnState(heartBeat, FIRSTHAND);
	dealer.displayMessageBox(gameDisplay, heartBeat);
//	messageString.str("");
//	messageString << "The current turn state is " << heartBeat.currentTurnState;
//	gameDisplay.bannerTop(messageString.str());
//	wait();

//	dealer.userPlayTrickCard(gameDisplay, p1, rulebook, heartBeat);
//	dealer.moveAICardDumb(p2,gameDisplay,AI2,rulebook,heartBeat);
//	dealer.moveAICardDumb(p3,gameDisplay,AI3,rulebook,heartBeat);
//	dealer.moveAICardDumb(p4,gameDisplay,AI4,rulebook,heartBeat);

	heartBeat.currentTrickOwner = heartBeat.twoOfClubsOwner;

//	dealer.displayHand(gameDisplay,p1);
//	gameDisplay.updateScreen();

	dealer.displayHand(gameDisplay, p1);
	dealer.playCardsCWDumb(heartBeat, p1, p2, p3, p4, AI2, AI3, AI4, gameDisplay, rulebook);
	dealer.displayMessageBox(gameDisplay, heartBeat);
	heartBeat.trickWinner = dealer.determineTrickWinner(heartBeat);
	//dealer.playCardsCW(heartBeat, p1, p2, p3, p4, AI2, AI3, AI4, gameDisplay, rulebook);
	messageString.str("");
	messageString << "Player " << heartBeat.trickWinner << " won the trick!";
	gameDisplay.bannerTop(messageString.str());
	wait();

	dealer.clearTrickCardsDisplay(gameDisplay);
	dealer.tallyPoints(heartBeat);
	dealer.displayMessageBox(gameDisplay, heartBeat);
	gameDisplay.updateScreen();
	dealer.putTrickCardsInWinnersPile(heartBeat.trickWinner, p1, p2, p3, p4);
	dealer.clearTrickCardArray();

	int x = heartBeat.currentTrickOwner;
	heartBeat.currentTrickOwner = heartBeat.trickWinner;

	messageString.str("");
	messageString << "The new trick owner is Player " << heartBeat.currentTrickOwner;
	gameDisplay.bannerTop(messageString.str());
	wait();

//	heartBeat.currentTurnState = dealer.detectTurnState(p1,p2,p3,p4);
//
//	messageString.str("");
//	messageString << "The turn state is now " << heartBeat.currentTurnState;
//	gameDisplay.bannerTop(messageString.str());
//	wait();
//
//	dealer.displayHand(gameDisplay,p1);
//	gameDisplay.updateScreen();
//
//	dealer.playCardsCWDumb(heartBeat, p1, p2, p3, p4, AI2, AI3, AI4, gameDisplay, rulebook);
//
//	heartBeat.trickWinner = dealer.determineTrickWinner(heartBeat);
//	//dealer.playCardsCW(heartBeat, p1, p2, p3, p4, AI2, AI3, AI4, gameDisplay, rulebook);
//	messageString.str("");
//	messageString << "Player " << heartBeat.trickWinner << " won the hand!";
//	gameDisplay.bannerTop(messageString.str());
//	wait();
//
//	dealer.clearTrickCardsDisplay(gameDisplay);
//	dealer.tallyPoints(heartBeat);
//	dealer.displayMessageBox(gameDisplay, heartBeat);
//	gameDisplay.updateScreen();
//	dealer.putTrickCardsInWinnersPile(heartBeat.trickWinner, p1, p2, p3, p4);
//
//	x = heartBeat.currentTrickOwner;
//	heartBeat.currentTrickOwner = heartBeat.trickWinner;
//
//	messageString.str("");
//	messageString << "The new trick owner is " << heartBeat.currentTrickOwner << ", used to be " << x;
//	gameDisplay.bannerTop(messageString.str());
//	wait();
//
//	messageString.str("");
//	messageString << "The current turn state is " << heartBeat.currentTurnState;
//	gameDisplay.bannerTop(messageString.str());
//	wait();
	heartBeat.currentTurnState = dealer.detectTurnState(p1,p2,p3,p4,heartBeat);
	dealer.displayMessageBox(gameDisplay, heartBeat);

	while(heartBeat.currentTurnState!=EMPTY){

		dealer.displayHand(gameDisplay,p1);
		gameDisplay.updateScreen();

		dealer.playCardsCWDumb(heartBeat, p1, p2, p3, p4, AI2, AI3, AI4, gameDisplay, rulebook);

		heartBeat.trickWinner = dealer.determineTrickWinner(heartBeat);
		//dealer.playCardsCW(heartBeat, p1, p2, p3, p4, AI2, AI3, AI4, gameDisplay, rulebook);
		messageString.str("");
		messageString << "Player " << heartBeat.trickWinner << " won the trick!";
		gameDisplay.bannerTop(messageString.str());
		wait();

//		dealer.displayTrickCardArray(gameDisplay);
//
//		messageString.str("");
//		messageString << "Displaying contents of Trick Card Array";
//		gameDisplay.bannerTop(messageString.str());
//		wait();


		dealer.clearTrickCardsDisplay(gameDisplay);
		dealer.tallyPoints(heartBeat);
		dealer.displayMessageBox(gameDisplay, heartBeat);
		//gameDisplay.updateScreen();


		dealer.putTrickCardsInWinnersPile(heartBeat.trickWinner, p1, p2, p3, p4);
		dealer.clearTrickCardArray();
		dealer.displayMessageBox(gameDisplay, heartBeat);
//
//		dealer.displayLastFourTrickPileCards(gameDisplay, p1);
//
//		messageString.str("");
//		messageString << "Displaying last 4 cards of P1's trick pile";
//		gameDisplay.bannerTop(messageString.str());
//		wait();
//
//		dealer.displayLastFourTrickPileCards(gameDisplay, p2);
//
//		messageString.str("");
//		messageString << "Displaying last 4 cards of P2's trick pile";
//		gameDisplay.bannerTop(messageString.str());
//		wait();
//
//		dealer.displayLastFourTrickPileCards(gameDisplay, p3);
//
//		messageString.str("");
//		messageString << "Displaying last 4 cards of P3's trick pile";
//		gameDisplay.bannerTop(messageString.str());
//		wait();
//
//		dealer.displayLastFourTrickPileCards(gameDisplay, p4);
//
//		messageString.str("");
//		messageString << "Displaying last 4 cards of P4's trick pile";
//		gameDisplay.bannerTop(messageString.str());
//		wait();
//
//
//		dealer.eraseFirstFourHandCards(gameDisplay);
//		dealer.sortHandBubble(p1);
//		dealer.displayHand(gameDisplay, p1);
//		gameDisplay.updateScreen();


		int x = heartBeat.currentTrickOwner;
		heartBeat.currentTrickOwner = heartBeat.trickWinner;
		dealer.displayMessageBox(gameDisplay, heartBeat);

		messageString.str("");
		messageString << "The new trick owner is Player " << heartBeat.currentTrickOwner;
		gameDisplay.bannerTop(messageString.str());
		wait();

		heartBeat.currentTurnState = dealer.detectTurnState(p1,p2,p3,p4,heartBeat);
		dealer.displayMessageBox(gameDisplay, heartBeat);
//		messageString.str("");
//		messageString << "The turn state is now " << heartBeat.currentTurnState;
//		gameDisplay.bannerTop(messageString.str());
//		wait();
	}
	dealer.shootForTheMoon(heartBeat,gameDisplay);
	dealer.shootForTheSun(p1,p2,p3,p4,heartBeat,gameDisplay);
	dealer.displayScoreBoard(gameDisplay,heartBeat);
	dealer.restartRound(p1,p2,p3,p4,heartBeat);
}

void HeartsGame::runGame(){
		stringstream messageString;

		messageString.str("");
		//heartBeat.roundNumber++;
		dealer.displayMessageBox(gameDisplay, heartBeat);
		dealer.deal(p1,p2,p3,p4,heartBeat);

		messageString.str("");
		messageString << "Starting trick " << heartBeat.roundNumber << ". Click to continue.";
		gameDisplay.bannerTop(messageString.str());
		wait();

		dealer.displayHand(gameDisplay, p1);

		dealer.displayMessageBox(gameDisplay, heartBeat);

		dealer.sortHandBubble(p1);
		dealer.sortHandBubble(p2);
		dealer.sortHandBubble(p3);
		dealer.sortHandBubble(p4);

		dealer.displayHand(gameDisplay, p1);

		dealer.findTwoOfClubs(p1,p2,p3,p4,heartBeat);

		dealer.displayHand(gameDisplay,p1);
		gameDisplay.updateScreen();

		dealer.displayMessageBox(gameDisplay, heartBeat);

		dealer.userPickPassCards(gameDisplay, p1);
		dealer.moveAIPassCardsDumb(p2, gameDisplay, AI2, rulebook, heartBeat);
		dealer.moveAIPassCardsDumb(p3, gameDisplay, AI3, rulebook, heartBeat);
		dealer.moveAIPassCardsDumb(p4, gameDisplay, AI4, rulebook, heartBeat);

		dealer.sortHandBubble(p1);
		dealer.sortHandBubble(p2);
		dealer.sortHandBubble(p3);
		dealer.sortHandBubble(p4);

		dealer.pass(gameDisplay, heartBeat, p1, p2, p3, p4);

		dealer.sortHandBubble(p1);
		dealer.sortHandBubble(p2);
		dealer.sortHandBubble(p3);
		dealer.sortHandBubble(p4);

		dealer.displayHand(gameDisplay,p1);
		gameDisplay.updateScreen();

		dealer.findTwoOfClubs(p1,p2,p3,p4,heartBeat);

		messageString.str("");
		messageString << "The two of clubs owner is " << heartBeat.twoOfClubsOwner;
		gameDisplay.bannerTop(messageString.str());
		wait();

		dealer.changeTurnState(heartBeat, FIRSTHAND);

		heartBeat.currentTrickOwner = heartBeat.twoOfClubsOwner;

		dealer.displayHand(gameDisplay,p1);
		gameDisplay.updateScreen();
//
//		dealer.playCardsCWDumb(heartBeat, p1, p2, p3, p4, AI2, AI3, AI4, gameDisplay, rulebook);
//
//		heartBeat.trickWinner = dealer.determineTrickWinner(heartBeat);
//
//		messageString.str("");
//		messageString << "Player " << heartBeat.trickWinner << " won the hand!";
//		gameDisplay.bannerTop(messageString.str());
//		wait();
//
//		dealer.clearTrickCardsDisplay(gameDisplay);
//		dealer.tallyPoints(heartBeat);
//		dealer.displayMessageBox(gameDisplay, heartBeat);
//		gameDisplay.updateScreen();
//		dealer.putTrickCardsInWinnersPile(heartBeat.trickWinner, p1, p2, p3, p4);
//
//		int x = heartBeat.currentTrickOwner;
//		heartBeat.currentTrickOwner = heartBeat.trickWinner;
//
//		messageString.str("");
//		messageString << "The new trick owner is " << heartBeat.currentTrickOwner << ", used to be " << x;
//		gameDisplay.bannerTop(messageString.str());
//		wait();



















	//define the details of each round/hand
//		stringstream messageString;
//		messageString.str("");
//		//heartBeat.roundNumber++;
//		dealer.displayMessageBox(gameDisplay, heartBeat);
//		dealer.changeTurnState(heartBeat, PASS);
//
//		messageString.str("");
//		messageString << "Starting Round " << heartBeat.roundNumber << ". Click to continue.";
//		gameDisplay.bannerTop(messageString.str());
//		wait();
//
//		dealer.deal(p1,p2,p3,p4, heartBeat);
//		dealer.sortHandBubble(p1);
//		dealer.sortHandBubble(p2);
//		dealer.sortHandBubble(p3);
//		dealer.sortHandBubble(p4);
//		dealer.displayHand(gameDisplay, p1);
//
//		dealer.advancePassState(heartBeat);
//
//		dealer.userPickPassCards(gameDisplay, p1);
//
//		dealer.moveAIPassCardsDumb(p2, gameDisplay, AI2, rulebook, heartBeat);
//		dealer.moveAIPassCardsDumb(p3, gameDisplay, AI3, rulebook, heartBeat);
//		dealer.moveAIPassCardsDumb(p4, gameDisplay, AI4, rulebook, heartBeat);
//
//		dealer.pass(gameDisplay, heartBeat, p1, p2, p3, p4);
//
//		dealer.advancePassState(heartBeat);
//		dealer.changeTurnState(heartBeat, FIRSTHAND);
//
//		dealer.sortHandBubble(p1);
//		dealer.sortHandBubble(p2);
//		dealer.sortHandBubble(p3);
//		dealer.sortHandBubble(p4);
//		gameDisplay.updateScreen();
//
//		dealer.findTwoOfClubs(p1, p2, p3, p4, heartBeat);
//
//		heartBeat.currentTrickOwner = heartBeat.twoOfClubsOwner;
//

		while(heartBeat.currentTurnState!=EMPTY){

			dealer.playCardsCWDumb(heartBeat, p1, p2, p3, p4, AI2, AI3, AI4, gameDisplay, rulebook);
			dealer.displayHand(gameDisplay, p1);
			heartBeat.trickWinner = dealer.determineTrickWinner(heartBeat);
			messageString.str("");
			messageString << "Click to play the next round.";

			wait();

			dealer.clearTrickCardsDisplay(gameDisplay);
			dealer.tallyPoints(heartBeat);
			dealer.displayMessageBox(gameDisplay, heartBeat);
			//gameDisplay.updateScreen();

			dealer.putTrickCardsInWinnersPile(heartBeat.trickWinner, p1, p2, p3, p4);
			dealer.clearTrickCardArray();

			messageString.str("");
			messageString << "Player " << heartBeat.trickWinner << " won the hand! Click to play the next round.";
			gameDisplay.bannerTop(messageString.str());
			wait();

			dealer.resetTrickOwner(heartBeat);
			heartBeat.currentTurnState = dealer.detectTurnState(p1,p2,p3,p4,heartBeat);

		}



}

