#include "Cell.h"

Cell::Cell(unsigned int xx, unsigned int yy) : position({xx,yy}), content(' '), is_bomb(0), is_open(0), visited(0) {};

void Cell::visit() {visited = 1;}

void Cell::reveal() {is_open = 1;}

void Cell::hide() {is_open=0;}

void Cell::setBomb()
{
    is_bomb = 1;
    content = 'B';
}

bool operator==(const Cell& lhs, const Cell& rhs)
{
  return ( (lhs.position.x == rhs.position.x) and (lhs.position.y == rhs.position.y) );
}


