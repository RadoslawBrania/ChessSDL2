#ifndef SQUARE_H
#define SQUARE_H

class Piece;

using namespace std;

class Square 
{
 public:
   
  
    Square(int x, int y);
    Square();


    ~Square();
    
    
    void setOccupier(Piece* piece);

    int getX() const;

    int getY() const;

 
    bool occupied() const;   

 
    Piece* occupiedBy() const;


 private:


    int _x;
    int _y;
    Piece* _piece;

}; 

#endif
