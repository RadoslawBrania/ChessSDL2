#ifndef KING_H
#define KING_H

#include <iostream>
#include "restrictedPiece.h"

using namespace std;

class King : public RestrictedPiece
{
 public:

    King(bool isWhite);
    
    ~King();

    int value() const;

    bool canMoveTo(Square& location) const;
    
    void display() const;

    bool isInitialPosition() const;


    string getName() const;

}; 

#endif
