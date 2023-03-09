#ifndef QUEEN_H
#define QUEEN_H

#include <iostream>
#include "square.h"
#include "piece.h"

using namespace std;

class Queen : public Piece
{
 public:
    

    Queen(bool isWhite);

    ~Queen();


    int value() const;


    bool canMoveTo(Square& location) const;

    void display() const;

    string getName() const;

}; 
#endif