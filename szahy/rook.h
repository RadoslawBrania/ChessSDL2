#ifndef ROOK_H
#define ROOK_H

#include <iostream>
#include "restrictedPiece.h"
#include "square.h"

using namespace std;

class Rook : public RestrictedPiece
{
 public:
    
 
    Rook(bool isWhite);
 
    ~Rook();

 
    int value() const;

    bool canMoveTo(Square& location) const;
    
 
    void display() const;

    string getName() const;

}; 

#endif
