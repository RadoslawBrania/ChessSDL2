

#ifndef BISHOP_H
#define BISHOP_H

#include <iostream>
#include "piece.h"
#include "square.h"

using namespace std;

class Bishop : public Piece
{
 public:
    
 
    Bishop(bool isWhite);
    
 
    ~Bishop();


    int value() const;


    bool canMoveTo(Square& location) const;

    void display() const;

    string getName() const;

};

#endif
