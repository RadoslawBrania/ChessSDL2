#ifndef PIECE_H
#define PIECE_H

#include <ostream>
#include "square.h"
#include "board.h"
class Player;

using namespace std;

class Piece 
{
 public:
   

    Piece(bool isWhite);
    
  
    virtual ~Piece();


    virtual bool moveTo(Player& byPlayer, Square& toSquare);


    virtual void setLocation(Square* location);

    virtual int value() const = 0;


    bool isWhite() const;


    string color() const;    
    
    bool tryCheck(Player& byPlayer, Square& toSquare);

    virtual void display() const = 0;

    virtual string getName() const = 0;

    virtual bool canMoveTo(Square& location) const = 0;

    bool isOnSquare() const;

    Square* location() const;

 protected:
    bool _isWhite;
    string _color;
    
 private:


    Square* _square;

};

#endif
