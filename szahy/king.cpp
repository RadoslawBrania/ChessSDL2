#include "king.h"

King::King(bool isWhite) : RestrictedPiece(isWhite)
{
}

King::~King()
{
}

int King::value() const
{
    return 0;
}

bool King::canMoveTo(Square& location) const
{
    bool validMove = false;
    int translationX = location.getX() - this->location()->getX();
    int translationY = location.getY() - this->location()->getY();
    
    if(abs(translationY) == 1 && translationX == 0)
    {
        validMove = true;
    }
    
    else if(abs(translationX) == 1 && translationY == 0)
    {
        validMove = true;
    }
    
    else if(abs(translationX) == 1 && abs(translationY) == 1)
    {
        validMove = true;
    }

    else if(abs(translationY) == 0 && 
        isInitialPosition() && 
        location.occupied() && 
        location.occupiedBy()->getName()[1] == 'W' &&
        (location.getX() == 0 || location.getX() == 7) && 
        Board::getBoard()->isClearHorizontal(*this->location(), location))
    {
        validMove = true;
    }
    
    return validMove;
}

void King::display() const
{
    cout << _color + "K";
}

string King::getName() const
{
    return _color + "K";
}

bool King::isInitialPosition() const
{
    if (isWhite() && this->location()->getY() == 0 && this->location()->getX() == 4) return true;
    if (!isWhite() && this->location()->getY() == 7 && this->location()->getX() == 4) return true;
    return false;
}
