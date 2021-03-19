#ifndef GRID_H
#define GRID_H

#include <unordered_set>
#include "Mat2D.h"
#include "Cell.h"

// hash function for class Cell
namespace std
{
  template <>
  struct hash<Cell>
  {
    size_t operator()( const Cell& cell ) const
    {
      return((53 + std::hash<int>()(cell.position.x))*53
	         + std::hash<int>()(cell.position.y));
    }
  };
}

class Grid
{
    private:

        unsigned int g_cols;
        unsigned int g_rows;
        double density;
        Mat2D<Cell> g_mat;

    public:

        Grid(unsigned int cols,unsigned int rows,double howDense);
        Cell& operator()(unsigned int i,unsigned int j);
        std::unordered_set<Cell> cells_with_bombs;
        std::unordered_set<Cell> unrevealed_cells;
        std::vector<Cell> getNeighbors(Cell& center_cell) const;
        Grid& reveal_all_zero_cells(unsigned int i, unsigned int j);
        void reveal_all();
        void generateBombs();
        void init();
        void draw() const;

};

#endif // GRID_H
