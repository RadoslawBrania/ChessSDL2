#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "player.h"
#include "board.h"
#include "game.h"
#include <string>
#include <chrono>
#include <ctime>

#include "bishop.h"
#include "knight.h"
#include "queen.h"
#include "rook.h"
#define X_MIN 'a'
#define X_MAX 'h'
#define Y_MIN '1'
#define Y_MAX '8'

Player::Player(string name, bool isWhite, King& myKing, set<Piece*>& myPieces) :
_name(name), _isWhite(isWhite), _myPieces(myPieces), _myKing(myKing)
{
}

Player::~Player()
{
}

bool Player::makeMove(int fSquare, int tSquare)
{
    string fromSquare = "";
    string toSquare = "";
  
    char c = char(8 - (fSquare / 8) + 48);
    char f = char(fSquare % 8 + 97);

    


    string badInput; 
  
    fromSquare += f;
    fromSquare += c;
    f = char(tSquare % 8 +97);
    c = char(8 - tSquare / 8 +48);
  
   
    toSquare += f;
    toSquare += c;
    std::cout << toSquare;
    std::cout << fromSquare;
    int fromX=0;
    int fromY=0;
    int toX=0;
    int toY=0;
    

    if(inCheck())
    {
        cout << _name << " jest w szachu!" << endl;
    }
    

    while (fromSquare.length() != 2 ||
          toSquare.length() != 2 ||
          tolower(fromSquare.at(0)) < X_MIN ||
          tolower(fromSquare.at(0)) > X_MAX ||
          tolower(toSquare.at(0)) < X_MIN ||
          tolower(toSquare.at(0)) > X_MAX ||
          tolower(fromSquare.at(1)) < Y_MIN ||
          tolower(fromSquare.at(1)) > Y_MAX ||
          tolower(toSquare.at(1)) < Y_MIN ||
          tolower(toSquare.at(1)) > Y_MAX ||
          !(Board::getBoard()->squareAt(tolower(fromSquare.at(0)) - X_MIN, 
                                      tolower(fromSquare.at(1)) - Y_MIN)->occupied())
          )
    {
        return 0;
        toSquare = "";
        fromSquare = "";
    }
    
    fromX = tolower(fromSquare.at(0)) - X_MIN;
    fromY = tolower(fromSquare.at(1)) - Y_MIN;
    toX = tolower(toSquare.at(0)) - X_MIN;
    toY = tolower(toSquare.at(1)) - Y_MIN;
    // stworzenie pliku z ostatnim ruchem do save'a i en passant
    ofstream MyFile("Last move.txt");
    MyFile << fromSquare << " ruch na " << toSquare << endl;
    MyFile.close();
    ofstream MyFile_octal("Last_move_octal.txt");

    if (Board::getBoard()->squareAt(fromX, fromY)->occupiedBy());
    {

        MyFile_octal <</* Board::getBoard()->squareAt(fromX, fromY)->occupiedBy()->getName() <<*/ fromX << fromY << toX << toY << endl; ;
    }
    MyFile_octal.close();
    return Board::getBoard()->squareAt(fromX, fromY)->occupiedBy()->moveTo(*this, 
                                                                  *(Board::getBoard()->squareAt(toX, toY)));
}

bool Player::inCheck()
{
    bool check = false;
    

    for (set<Piece*>::iterator itr = Game::opponentOf(*this)->myPieces()->begin(); 
         itr != Game::opponentOf(*this)->myPieces()->end(); ++itr)
    {

        if (((Piece*)*itr)->location() && 
            ((Piece*)*itr)->canMoveTo(*(myKing()->location())))
        {
            check = true;
        }
    }
    
    return check;
}

bool Player::inCheckMate()
{
    bool checkMate = true;



    for (set<Piece*>::iterator itr = myPieces()->begin();
        itr != myPieces()->end(); ++itr)
    {
        for(int i = 0; i < 8; i++)
        {
	        for(int j = 0; j < 8; j++)
	        {
                Square& toSquare = *Board::getBoard()->squareAt(i, j);
                if ((*itr)->location() &&
                    (*itr)->canMoveTo(toSquare) && !(*itr)->tryCheck(*this, toSquare))
                {
                    if(toSquare.occupied())
                    {
                        if (toSquare.occupiedBy()->isWhite() == this->isWhite()) continue;
                    }
                    return false;
                }
	        }
        }
    }

    return checkMate;
}

bool Player::availablePromotion() const
{
    int y;
    if (isWhite()) y = 7;
    else y = 0;
    for (set<Piece*>::iterator itr = myPieces()->begin();
        itr != myPieces()->end(); ++itr)
    {
        if ((*itr)->getName()[1] == 'P' && (*itr)->location() && (*itr)->location()->getY() == y) return true;
    }

    return false;
}

void Player::promotePawn(char piece)
{
    int y;
    if (isWhite()) y = 7;
    else y = 0;
    for (set<Piece*>::iterator itr = myPieces()->begin();
        itr != myPieces()->end(); ++itr)
    {
            if ((*itr)->getName()[1] == 'P' && (*itr)->location() && (*itr)->location()->getY() == y)
            {

                Square* square = (*itr)->location();
                Piece* piecePtr;
	            (*itr)->setLocation(NULL);
                switch (piece)
                {
                case 'Q':
                    piecePtr = new Queen(isWhite());
                    square->setOccupier(piecePtr);
                    piecePtr->setLocation(square);
                    break;
                case 'W':
                    piecePtr = new Rook(isWhite());
                    square->setOccupier(piecePtr);
                    piecePtr->setLocation(square);
                    break;
                case 'G':
                    piecePtr = new Bishop(isWhite());
                    square->setOccupier(piecePtr);
                    piecePtr->setLocation(square);
                    break;
                case 'S':
                    piecePtr = new Knight(isWhite());
                    square->setOccupier(piecePtr);
                    piecePtr->setLocation(square);
                    break;
                }



            }
    }

}



void Player::capture(Piece* aPiece)
{
    aPiece->setLocation(NULL);
    
    _capturedPieces.insert(aPiece);
}

string Player::getName() const
{
    return _name;
}

bool Player::isWhite() const
{
   
    return _isWhite;
}

int Player::score() const
{
    int score = 0;
    
    for (set<Piece*>::iterator itr = _capturedPieces.begin(); itr != _capturedPieces.end(); ++itr)
    {
        score += ((Piece*)*itr)->value();
    }
    
    return score;
}

set<Piece*>* Player::myPieces() const
{
    return &_myPieces;
}

King* Player::myKing() const
{
    return &_myKing;
}