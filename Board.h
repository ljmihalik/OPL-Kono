#pragma once
#include <vector>
#include <string>
using namespace std;
class Board{
    public:
        Board();
        ~Board();

        void createBoard(int gridSize);

        //take in value moving and where to validate if piece made it to other side
        void movePiece(int row, int column, string coordinate);

        int score();

        void viewBoard(); //print board

        bool validateMove(int row, int column, string coordinate, string color);

        void devOption(int gridSize);

        bool checkWinner();
        
        int mGridsize;
    
    private:
        //can use resize for row/col
        vector<vector<string> > mBoard;
};