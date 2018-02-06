#pragma once

class Tournament{
    public:
        Tournament();
        ~Tournament();
        
        void startTournament();

        void playAgain();


        void endTournament(int hScore, int cScore);

        int Rounds;

        
    

};
