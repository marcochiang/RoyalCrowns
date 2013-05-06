#ifndef HEARTSGAME_H
#define HEARTSGAME_H

#include "display.h"
#include "Controller.h"
#include "Player.h"
#include "AI.h"
#include "Rules.h"

//#pragma once

class HeartsGame
{
    public:
        HeartsGame();
        virtual ~HeartsGame();
        void saveFile();
        bool fileExists(const char *filename);
        void testing();
        void determineWinner();
        void testGame();
        void wait();
        int msleep(unsigned long milisec);
        void delay(int seconds);
        bool isGameOver();  //determines if the game is over
        void runGame();     //function to be called in main to start the game rolling
        void setupGame();   //initialize deck, initialize players(set names), initialize AI
        void setNames();    //retrieves and sets the names of the human/nonhuman players based on the number of human players
        int getNumOfHumans(); //returns the number of humans logged in to play the game
        display gameDisplay;
        Player p1;
        Player p2;
        Player p3;
        Player p4;
        AI AI2;
        AI AI3;
        AI AI4;
        scoreBoard scores;
        theGauvin heartBeat;
        Rules rulebook;
        //AI AI2 = new AI(&p2);

        //p2.playCard(AI2.chooseCard());

        Controller dealer;
        //string messageString;
        //TODO:     
        //create functionality to prevent two players from having the same name
        //setup sockets
        //

    protected:

    private:


};

#endif // HEARTSGAME_H

