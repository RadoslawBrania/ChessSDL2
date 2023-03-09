#ifndef RESTRICTED_H
#define RESTRICTED_H

#include "piece.h"

class Player;

using namespace std;

class RestrictedPiece : public Piece
{
 public:
    

    RestrictedPiece(bool isWhite);
    
   
    virtual ~RestrictedPiece();

 
    virtual bool moveTo(Player& byPlayer, Square& to);

 
    bool hasMoved() const;

 private:
   

    bool _moved;

};  

#endif