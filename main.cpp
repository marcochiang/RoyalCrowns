/* Title: Project 1 ECE373 Driver Class for GoFish
 * Author: Trevor Elkins, Marco Chiang, Liyan Tang, Justin Mills, and John Shields.
 * Description: Runs the GoFish game.
 *
 * NOTES:
 *      * Requires the terminal (Putty) to be set to UTF-8.
 *      * Does not function when running a screen session.
 */
#include "display.h"
#include <signal.h>
#include <ncurses.h>
#include <time.h>
#include <vector>
#include <cstdlib>
#include <sstream>

using namespace std;

/* No Header file for this example driver artifact
 * function declaration here instead.
 */
// Signal Subroutine for Window Resize
static void detectResize (int sig); 
// stub artifact for what the game does when the screen resizes
void stub_PrintResize(void); 

// The gameDisplay object is global, because the static signal handler object
// needs to access the dynamic object.
display gameDisplay;
game currentGame;
// using a stringstream rather than a string to make making the banner easier
stringstream messageString;

/**
* Displays the hand of the player on the screen.
*/
void displayHand(std::vector<card> input)
{
	int displayCoordsX[] = {17,24,31,38,45,52,59,17,24,31,38,45,52};
	int displayCoordsY[] = {13,13,13,13,13,13,13,18,18,18,18,18,18};
	unsigned int x = 0;
	unsigned int y = input.size();
	messageString.str("");
	messageString << "Hand size:" << y ;
	gameDisplay.bannerTop(messageString.str());
	gameDisplay.drawBox(15,13,50,15,A_INVIS);
	for(; x < y; x++)
	{
		gameDisplay.displayCard(displayCoordsX[x],displayCoordsY[x],input.at(x).getSuit(),input.at(x).getFace(), A_NORMAL);
	}
}

/**
* Displays the number of cards left in the deck.
*/
void displayDeck(deck input)
{
	unsigned d = input.getSize();
	messageString.str("");
	messageString << "Deck size: " << d ;
	gameDisplay.bannerTop(messageString.str());
}

/**
* Displays the scores of each player next to them.
*/
void updateScore(int comps)
{
	const char* cstr3;
	const char* cstr2;
	const char* cstr1;
	const char* cstr;
	switch(comps)
	{
	case 3: 
		cstr3 = currentGame.getPlayer(3).getScore().c_str();
		mvprintw(7,5,cstr3); //Falls through to the next player
	case 2: 
		cstr2 = currentGame.getPlayer(2).getScore().c_str();
		mvprintw(7,58,cstr2);
	case 1: 
		cstr1 = currentGame.getPlayer(1).getScore().c_str();
		mvprintw(3,32,cstr1);
	default: 
		cstr = currentGame.getPlayer(0).getScore().c_str();
		mvprintw(12,40,cstr);
	}
}

/**
* Checks the game winning conditions to see if it has been won.
*/
bool isGameOver()
{
	//checks to see if the game is over after each turn if all player hands and deck are empty
	int gameOverCounter=0;
	int totalPlayerCount=currentGame.getPlayerCount();
	for(int i = 0; i < totalPlayerCount; i++)
	{
		if(currentGame.getPlayer(i).getHand().size()==0)
			gameOverCounter++;
	}
	if(gameOverCounter==totalPlayerCount && currentGame.getDeck().isEmpty()==true)
	{
		return true;
	}
	else 
		return false;
}

/*
 * This is the main function that starts the driver artifact.
 * This function demonstrates some of the abilities of the Display class
 */
int main(int argc, char* argv[])
{

	// various variable declarations
	char key;
	int numOfComps = 0;
	int coordX = 0;
	int coordY = 0;
	int gameState = 0;
	int cardSelected = 0;

	// enable a interrupt triggered on a window resize
	signal(SIGWINCH, detectResize); // enable the window resize signal

	/* You can uncomment and change the colors for various cards here*/
	//    init_pair(1, COLOR_CYAN, COLOR_BLACK); // for card outline
	//    init_pair(2, COLOR_BLUE, COLOR_BLACK); // for spades and clubs
	//    init_pair(3, COLOR_RED, COLOR_BLACK);  // for hearts and diamonds
	//    init_pair(4, COLOR_GREEN, COLOR_BLACK); // for turned over card
	//    init_pair(5, COLOR_GREEN, COLOR_BLACK); // for box drawing
	//    init_pair(6, COLOR_GREEN, COLOR_BLACK); // for banner display

	//Display the intro and select the amount of computer players.
	gameDisplay.bannerTop("GoFish!");
	gameDisplay.bannerBottom("Select the number of computer players...");
	gameDisplay.displayCard(10,5,1,1, A_BOLD);
	gameDisplay.displayCard(20,5,1,2, A_BOLD);
	gameDisplay.displayCard(30,5,1,3, A_BOLD);
	for(;;)
	{
		key = gameDisplay.captureInput();
		coordX = gameDisplay.getMouseEventX();
		coordY = gameDisplay.getMouseEventY();
		if(coordX >= 10 && coordX <= 15 && coordY >= 5 && coordY <= 9)
		{
			gameDisplay.bannerBottom("1 Computer selected.");
			numOfComps = 1;
			break;
		}
		else if(coordX >= 20 && coordX <= 25 && coordY >= 5 && coordY <= 9)
		{
			gameDisplay.bannerBottom("2 Computers selected.");
			numOfComps = 2;
			break;
		}
		else if(coordX >= 30 && coordX <= 35 && coordY >= 5 && coordY <= 9)
		{
			gameDisplay.bannerBottom("3 Computers selected.");
			numOfComps = 3;
			break;
		}
	}

	//Creates the computer players on the screen.
	gameDisplay.bannerTop("GoFish");
	gameDisplay.eraseBox(2,2,60,10);
	player player1("Player 1",12,40);
	player player2("Computer 1",35,4,7,5);
	player player3("Computer 2",70,8,7,68);
	player player4("Computer 3",5,8,3,32);
	mvprintw(12,32,"(You)");
	mvprintw(12,40,"Score: 0");
	currentGame.addPlayer(player1);
	if(numOfComps > 2)
	{
		gameDisplay.displayCard(5,8,0,0, COLOR_PAIR(4));
		mvprintw(6,5,"Computer 3");
		mvprintw(7,5,"Score: 0");
		currentGame.addPlayer(player4); //add player to game
	}
	if(numOfComps > 1)
	{
		gameDisplay.displayCard(70,8,0,0, COLOR_PAIR(4));
		mvprintw(6,68,"Computer 2");
		mvprintw(7,68,"Score: 0");
		currentGame.addPlayer(player3); //add player to game
	}
	if(numOfComps > 0)
	{
		gameDisplay.displayCard(35,4,0,0, COLOR_PAIR(4));
		mvprintw(2,32,"Computer 1");
		mvprintw(3,32,"Score: 0");
		currentGame.addPlayer(player2); //add player to game
	}
	currentGame.createGame(); //deal out the cards and perform any other configuration
	displayHand(currentGame.getPlayer(0).getHand()); //display the new hand
	updateScore(numOfComps); //update the score in case any pairs off the bat

	for (;;) 
	{
		bool gameOver = false;
		while(!gameOver)
		{
			key = gameDisplay.captureInput();
			coordX = gameDisplay.getMouseEventX();
			coordY = gameDisplay.getMouseEventY();

			//The Player's turn
			if(gameState == 0) //wait for user input for card selection
			{
				cardSelected = currentGame.getPlayer(0).coordsToCard(coordX,coordY); //see if player clicked on card in hand
				if(currentGame.getPlayer(0).getHand().size() == 0) //Check if hand is empty first
				{
					gameDisplay.bannerBottom("Go Fish!");
					if(currentGame.getDeck().isEmpty() == false)
						currentGame.addCard( currentGame.drawCard(),0 ); //draw a card
					gameState = 2; //Go to computer's turn
					displayHand(currentGame.getPlayer(0).getHand()); //display the new hand
					updateScore(numOfComps); //update the score in case any pairs off the bat
					cardSelected = -1; //invalidate card selection
				}
				else if(cardSelected > -1 && cardSelected < 14) //Card is selected
				{
					char buffer[30];
					sprintf(buffer, "%d selected. Ask a player.", cardSelected);
					gameDisplay.bannerBottom(buffer); //display the card selected
					gameState = 1;
				}
				else
				{
					gameDisplay.bannerBottom("Select a card.");
					cardSelected = -1;
				}
				displayDeck(currentGame.getDeck());
			}
			else if(gameState == 1) //The user must now select a computer to ask
			{


				//Checks if the hand size is empty but the game has not been won yet, can still draw cards
				if(currentGame.getPlayer(0).getHand().size() == 0 && currentGame.getDeck().isEmpty() == false && isGameOver() == false)
				{
					gameDisplay.bannerBottom("Go Fish!");
					if(currentGame.getDeck().isEmpty() == false)
						currentGame.addCard( currentGame.drawCard(),0 );
					displayHand(currentGame.getPlayer(0).getHand()); //display the new hand
					updateScore(numOfComps); //update the score in case any pairs off the bat
					cardSelected = -1;
					gameState = 2;
				}

				//Computer 3's deck selected
				else if(coordX >= 5 && coordX <= 10 && coordY >= 8 && coordY <= 12)
				{
					if(numOfComps == 3) //Check if computer exists
					{
						if(currentGame.getPlayer(3).haveCard(cardSelected) == true) //Check if computer has card
						{
							gameDisplay.bannerBottom("Computer 3");
							card::card c = currentGame.takeCard(cardSelected,3);
							currentGame.addCard( c,0 );
							cardSelected = -1;
							gameState = 2;
							displayHand(currentGame.getPlayer(0).getHand()); //display the new hand
							updateScore(numOfComps); //update the score in case any pairs off the bat
						}
						else //Otherwise draw from deck
						{
							gameDisplay.bannerBottom("Go Fish!");
							if(currentGame.getDeck().isEmpty() == false)
								currentGame.addCard( currentGame.drawCard(),0 );
							displayHand(currentGame.getPlayer(0).getHand()); //display the new hand
							updateScore(numOfComps); //update the score in case any pairs off the bat
							cardSelected = -1;
							gameState = 2;
						}
						gameOver = isGameOver();
						if(gameOver == true)
							break;
					}
					else //Does not exist
					{
						cardSelected = -1;
						gameState = 0;
					}
				}

				//Computer 1's deck selected
				else if(coordX >= 35 && coordX <= 40 && coordY >= 4 && coordY <= 8)
				{
					if(currentGame.getPlayer(1).haveCard(cardSelected) == true) //Check if computer has card
					{
						gameDisplay.bannerBottom("Computer 1");
						card::card c = currentGame.takeCard(cardSelected,1);
						currentGame.addCard( c,0 );
						cardSelected = -1;
						gameState = 2;
						displayHand(currentGame.getPlayer(0).getHand()); //display the new hand
						updateScore(numOfComps); //update the score in case any pairs off the bat
					}
					else //Otherwise draw from deck
					{
						gameDisplay.bannerBottom("Go Fish!");
						if(currentGame.getDeck().isEmpty() == false)
							currentGame.addCard( currentGame.drawCard(),0 );
						displayHand(currentGame.getPlayer(0).getHand()); //display the new hand
						updateScore(numOfComps); //update the score in case any pairs off the bat
						cardSelected = -1;
						gameState = 2;
					}
					gameOver = isGameOver();
					if(gameOver == true)
						break;
				}

				//Computer 2's deck selected
				else if(coordX >= 70 && coordX <= 75 && coordY >= 8 && coordY <= 12) //Computer 2's deck selected
				{
					if(numOfComps > 1) //Check if computer exists
					{
						if(currentGame.getPlayer(2).haveCard(cardSelected) == true) //Check if computer has card
						{
							gameDisplay.bannerBottom("Computer 2");
							card::card c = currentGame.takeCard(cardSelected,2);
							currentGame.addCard( c,0 );
							cardSelected = -1;
							gameState = 2;
							displayHand(currentGame.getPlayer(0).getHand()); //display the new hand
							updateScore(numOfComps); //update the score in case any pairs off the bat
						}
						else //Otherwise draw from deck
						{
							gameDisplay.bannerBottom("Go Fish!");
							if(currentGame.getDeck().isEmpty() == false)
								currentGame.addCard( currentGame.drawCard(),0 );
							displayHand(currentGame.getPlayer(0).getHand()); //display the new hand
							updateScore(numOfComps); //update the score in case any pairs off the bat
							cardSelected = -1;
							gameState = 2;
						}
						gameOver = isGameOver();
						if(gameOver == true)
							break;
					}
					else //Does not exist
					{
						cardSelected = -1;
						gameState = 0;
					}
				}

				else if(coordY < 13) //Coordinates not in playing area, unselect card and start over
				{
					cardSelected = -1;
					gameState = 0;
				}
			}

			//Computer's turn
			else if(gameState == 2)
			{
				/*AI algorithm
				* Iterate through the computer list and randomly select a card from hand and then randomly select a computer to play it on.
				*/
				int i = 1;
				for(; i <= numOfComps; i++) //Loop through computers
				{
					if(currentGame.getPlayer(i).getHand().size() > 0) //Make sure has something in hand
					{
						int computerPlayerFaceVal = currentGame.getPlayer(i).getRandomCard().getFace();//get random card from hand
						srand(time(NULL)); //Seed the random number generator
						int randPlayerNumber = rand()%(numOfComps);
						while(randPlayerNumber == i)
						{
							randPlayerNumber = rand()%(numOfComps); //Make sure computer doesn't ask itself
						}
						if(currentGame.getPlayer(randPlayerNumber).haveCard(computerPlayerFaceVal) == true) //Has card
						{
							currentGame.addCard( currentGame.takeCard(computerPlayerFaceVal,randPlayerNumber),i ); //Take card from player
						}
						else //Otherwise GoFish
						{
							if(currentGame.getDeck().isEmpty() == false)
								currentGame.addCard( currentGame.drawCard(),i );
						}
					}
					else //Otherwise GoFish
					{
						if(currentGame.getDeck().isEmpty() == false)
							currentGame.addCard( currentGame.drawCard(),i );
					}
					gameOver = isGameOver();
					if(gameOver == true)
						break;
				}

				displayHand(currentGame.getPlayer(0).getHand()); //display the new hand
				updateScore(numOfComps); //update the score in case any pairs off the bat
				gameState = 0;
				cardSelected = -1;
			}
		}
		return currentGame.highestScore();
	}
}

/*
 * This is the interrupt service routine called when the resize screen 
 * signal is captured.
 */
void detectResize(int sig) {
	// update the display class information with the new window size
	gameDisplay.handleResize(sig);
	// re-enable the interrupt for a window resize
	signal(SIGWINCH, detectResize);
	/*INSERT YOUR OWN SCREEN UPDATE CODE instead of stub_PrintResize*/
	stub_PrintResize();
}

/*
 * This is a simple stub that should be replaced with what the game does
 * when the screen resizes. 
 */
void stub_PrintResize(void) {
	// gets the new screen size
	int cols = gameDisplay.getCols();
	int lines = gameDisplay.getLines();
	// setups a message stream
	stringstream messageString;
	messageString << "Terminal is " << cols << "x" << lines;
	// prints out the information of the new screen size in a top banner
	gameDisplay.bannerTop(messageString.str());
}

