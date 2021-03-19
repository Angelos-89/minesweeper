#ifndef CELL_H
#define CELL_H

#include <iostream>

struct point
{
    unsigned int x;
    unsigned int y;
};

typedef struct point POINT_;

class Cell
{
    public:
        POINT_ position;
        char content;
        bool is_bomb;
        bool is_open;
        bool visited;
        void visit();
        void reveal();
        void hide();
        void setBomb();
        Cell(unsigned int xx=0, unsigned int yy=0);
        friend bool operator==(const Cell& lhs, const Cell& rhs);
};

#endif // CELL_H
