#ifndef KNIGHT_H
#define KNIGHT_H

#include <iostream>
#include "square.h"
#include "piece.h"

using namespace std;

class Knight : public Piece
{
 public:
    

    Knight(bool isWhite);
    

    ~Knight();

    int value() const;

    bool canMoveTo(Square& location) const;

    void display() const;

    string getName() const;

};

#endif
