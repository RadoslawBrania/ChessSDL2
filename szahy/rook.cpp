#include "rook.h"

Rook::Rook(bool isWhite) : RestrictedPiece(isWhite)
{
}

Rook::~Rook()
{
}

int Rook::value() const
{
    return 5;
}

bool Rook::canMoveTo(Square& location) const
{
    bool validMove = false;
    
    if(Board::getBoard()->isClearVertical(*(this->location()), location))
    {
        validMove = true;
    }
    
    else if(Board::getBoard()->isClearHorizontal(*(this->location()), location))
    {
        validMove = true;
    }
    
    return validMove;
}

void Rook::display() const
{
    cout << _color + "W";
}

string Rook::getName() const
{
    return _color + "W";
}
