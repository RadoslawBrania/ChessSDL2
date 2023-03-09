#include "pawn.h"
#include "queen.h"
#include "board.h"

Pawn::Pawn(bool isWhite) : RestrictedPiece(isWhite), _delegate(NULL)
{
}

Pawn::~Pawn()
{
    if(_delegate)
        delete _delegate;
}

void Pawn::setLocation(Square* location)
{
    Piece::setLocation(location);
}

int Pawn::value() const
{
    return 1;
}

bool Pawn::moveTo(Player& byPlayer, Square& to)
{
    bool valid = false;
    

    if(_delegate)
    {
        valid = _delegate->moveTo(byPlayer, to);
        
        if(valid)
        {
            location()->setOccupier(NULL);
            
            setLocation(&to);
            
            location()->setOccupier(this);
        }
    }
    else 
    {
        valid = RestrictedPiece::moveTo(byPlayer, to);
        
 
       
    }
    
    return valid;
}

bool Pawn::canMoveTo(Square& location) const
{
    bool validMove = false;
    int translationX = location.getX() - this->location()->getX();
    int translationY = location.getY() - this->location()->getY();
    
    if(_delegate)
    {
        validMove = _delegate->canMoveTo(location);
    }
    else 
    {
        if(!isWhite())
        {
            translationX *= -1;
            translationY *= -1;
        }
        
        if(!location.occupied() && translationY == 1 && translationX == 0)
        {
            validMove = true;
        }
        

        else if(!hasMoved() && translationY == 2 && translationX == 0 &&
                Board::getBoard()->isClearVertical(*(this->location()), location))
        {
            validMove = true;
        }
        
        else if(location.occupied() && translationY == 1 && 
                (translationX == 1 || translationX == -1))
        {
            validMove = true;
        }        
    }

    return validMove;
}

void Pawn::display() const
{
    if(_delegate)
    {
        _delegate->display();
    }
    else
    {
        cout << _color + "P";
    }
}

string Pawn::getName() const
{
    return _color + "P";
}
