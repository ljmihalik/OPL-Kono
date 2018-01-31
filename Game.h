#include <string>
#pragma once
using namespace std;
class Game{
    public:
        Game();
        ~Game();
        //if winner is brought in then dont need to throw dice
        void startGame(string winner); 

        void saveGame(int roundNum, Board& table, Human& person, Computer& AI);

        void loadGame(Board& table);
        
        bool humanTurn;
    
    private:
    /*
        int round;
        int Cscore;
        int Ccolor;
        int Hscore;
        int Hcolor;
        string nextplayer;
        */
       
    

};
