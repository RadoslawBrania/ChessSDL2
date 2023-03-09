#ifndef PAWN_H
#define PAWN_H

#include <iostream>
#include "square.h"
#include "restrictedPiece.h"

using namespace std;

class Pawn : public RestrictedPiece
{
 public:

    Pawn(bool isWhite);
    

    ~Pawn();


    void setLocation(Square* location);


    int value() const;
 
    bool moveTo(Player& byPlayer, Square& to);

  
    bool canMoveTo(Square& location) const;


    void display() const;

    string getName() const;
   
   
 private:


    Piece* _delegate;

};

#endif
