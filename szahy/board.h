#ifndef BOARD_H
#define BOARD_H

#include <ostream>
#include "square.h"

using namespace std;

class Board 
{
 public:

    ~Board();

    static Board* getBoard();

    Square* squareAt(int x, int y) const;

    bool isClearVertical(Square& from, Square& to) const;

    bool isClearHorizontal(Square& from, Square& to) const;

    bool isClearDiagonal(Square& from, Square& to) const;
    
    bool isEndRow(Square& location) const;

    void display(ostream& outStream) const;


 private:
    

    Board();


    static Board* _theBoard;
    static const int _DIMENSION = 8;
    Square* _squares[_DIMENSION][_DIMENSION];

};

#endif
