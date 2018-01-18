#include "boardview.h"
#include <iomanip>
using namespace std;

void board::createBoard(){
    string board[5][5]={ {"W - W - W - W - W" "\n"
                         "| - | - | - | - |" "\n"},
                      {"W - + - + - + - W" "\n"
                        "| - | - | - | - |" "\n"},
                      {"+ - + - + - + - +" "\n"
                      "| - | - | - | - |" "\n"},
                      {"B - + - + - + - B" "\n"
                      "| - | - | - | - |" "\n"},
                        {"B - B - B - B - B" "\n"},
                                                    };

    for(int row=0; row<5; row++){
        for(int col=0; col<5; col++){
            cout<<board[row][col];
        }
    }
}

void board::movePiece(int row, int column, int newRow, int newCol){
    string board[5][5]={ {"W - W - W - W - W" "\n"
                         "| - | - | - | - |" "\n"},
                      {"W - + - + - + - W" "\n"
                        "| - | - | - | - |" "\n"},
                      {"+ - + - + - + - +" "\n"
                      "| - | - | - | - |" "\n"},
                      {"B - + - + - + - B" "\n"
                      "| - | - | - | - |" "\n"},
                        {"B - B - B - B - B" "\n"},
                                                  };
   
    //piece being moved is now open
    board[row][column]="+";

    //loop to the new position, when there clear the letter or + and add the new WB
    for (int i=0; i<=5; i++){
        for(int x=0; x<5; x++){
            board[newRow][newCol]=" ";
            board[newRow][newCol]="W";
            cout<<board[i][x];
        }
    }
}

/*
void board::viewBoard(){
    
    for(int row=0; row<5; row++){
        for(int col=0; col<5; col++){
            cout<<board[row][col];
        }
    }
}
*/