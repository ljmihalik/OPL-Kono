#include <iostream>
#include <string>
#include "boardview.h"
#include "boardview.cpp"
#include "board.h"
#include "board.cpp"
#include "game.h"
#include "game.cpp"

using namespace std;

int main(){
    board table;
    game toss;
    int gridSize=0;

    cout<<"Plese enter grid size 5, 7, 9"<<endl;
    cin>>gridSize;
    cout<<endl;

    table.createBoard();

    int rowPosition=0;
    int columnPosition=0;
    cout<<"Your move! Which piece, give row and column numbers?"<<endl;
    cin>>rowPosition>>columnPosition;

    int newRow=0;
    int newColumn=0;
    cout<<"Where would you like to move "<<rowPosition <<","<<columnPosition<<"?"<<endl;
    cin>>newRow>>newColumn;
    table.movePiece(rowPosition, columnPosition, newRow, newColumn);

}