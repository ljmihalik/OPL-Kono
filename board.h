using namespace std;

class board{
    public:
        void createBoard();
        
        //take in value moving and where to validate if piece made it to other side
        void movePiece(int row, int column, int newRow, int newCol);

        void viewBoard(); //print board
};