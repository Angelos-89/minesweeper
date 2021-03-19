#include <random>
#include <ctime>
#include "Grid.h"
using namespace std;

// constructor, note that grid is initialized with a ghost zone
Grid::Grid(unsigned int cols,unsigned int rows,double howDense ) : g_cols(cols), g_rows(rows), density(howDense), g_mat(cols,rows,1) {};

Cell& Grid::operator()(unsigned int i,unsigned int j)
{
    return g_mat(i-1,j-1);
}

void Grid::generateBombs()
{
    Cell cell;
    int grd_size = g_rows*g_cols;
    int total_bombs = grd_size*density;
    srand((unsigned int)time(NULL));
    while (cells_with_bombs.size() < (size_t) total_bombs)
    {
        cell.position.x = rand()%(g_cols) + 1;
        cell.position.y = rand()%(g_rows) + 1;
        cells_with_bombs.insert(cell);
    }
}

std::vector<Cell> Grid::getNeighbors(Cell& center_cell) const
{
    size_t i = center_cell.position.x - 1;
    size_t j = center_cell.position.y - 1;
    std::vector<Cell> block = {};
    block.push_back(g_mat(i+1,j));
    block.push_back(g_mat(i+1,j+1));
    block.push_back(g_mat(i,j+1));
    block.push_back(g_mat(i-1,j+1));
    block.push_back(g_mat(i-1,j));
    block.push_back(g_mat(i-1,j-1));
    block.push_back(g_mat(i,j-1));
    block.push_back(g_mat(i+1,j-1));
    return block;
}

void Grid::init()
{
    // fill the grid with bombs, note that we embed the grid in a bigger frame which contains ghost points
    // the top left cell of the displayed grid has coordinates (1,1)

    int ghost = g_mat.getGhost();
    generateBombs();
    for(int row=-ghost; row<(int)g_rows+ghost; row++)
    {
        for(int col=-ghost; col<(int)g_cols+ghost; col++)
        {
            Cell cell(col+1,row+1);
            if ( cells_with_bombs.find(cell) != cells_with_bombs.end() )
                cell.setBomb();

            g_mat(col,row) = cell;
        }
    }

    // now scan the grid and fill the cells with numbers

    short number;
    std::vector<Cell> neighbors;
    for(unsigned int row=0; row<g_rows; row++)
    {
        for(unsigned int col=0; col<g_cols; col++)
        {
            number = 0;
            if ( !g_mat(col,row).is_bomb )
            {
                neighbors = (*this).getNeighbors(g_mat(col,row));
                for (auto cell_ : neighbors)
                {
                    if (cell_.is_bomb)
                        number++;
                }
                g_mat(col,row).content = number + '0';
            }
        unrevealed_cells.insert(g_mat(col,row));
        }
    }
}

Grid& Grid::reveal_all_zero_cells(unsigned int i, unsigned int j)
{
    (*this)(i,j).reveal();
    (*this)(i,j).visit();
    unrevealed_cells.erase((*this)(i,j));

    std::vector<Cell> neighbors;
    neighbors = getNeighbors((*this)(i,j));

    unsigned int ii,jj;
    for (auto c : neighbors)
    {
        ii = c.position.x;
        jj = c.position.y;
        (*this)(ii,jj).reveal();
        unrevealed_cells.erase((*this)(ii,jj));
    }

    // the chosen point is labeled as C

    /*    NW  N   NE
    //      \ | /
    //    W - C - E
    //      / | \
    //    SW  S   SE
    */

    // move counter-clockwise in the following manner: E -> NE -> N -> NW -> W -> SW -> S -> SE
    // if the move brought you to a cell containing zero and it was not previously visited, call the function again

    if ( (*this)(i+1,j).content   == '0' and !(*this)(i+1,j).visited )
        reveal_all_zero_cells(i+1,j);

    if ( (*this)(i+1,j+1).content == '0' and !(*this)(i+1,j+1).visited )
        reveal_all_zero_cells(i+1,j+1);

    if ( (*this)(i,j+1).content   == '0' and !(*this)(i,j+1).visited )
        reveal_all_zero_cells(i,j+1);

    if ( (*this)(i-1,j+1).content == '0' and !(*this)(i-1,j+1).visited )
        reveal_all_zero_cells(i-1,j+1);

    if ( (*this)(i-1,j).content   == '0' and !(*this)(i-1,j).visited )
        reveal_all_zero_cells(i-1,j);

    if ( (*this)(i-1,j-1).content == '0' and !(*this)(i-1,j-1).visited )
        reveal_all_zero_cells(i-1,j-1);

    if ( (*this)(i,j-1).content   == '0' and !(*this)(i,j-1).visited )
        reveal_all_zero_cells(i,j-1);

    if ( (*this)(i+1,j-1).content == '0' and !(*this)(i+1,j-1).visited )
        reveal_all_zero_cells(i+1,j-1);

    return *this;
}

void Grid::draw() const
{
    Cell cell;
    for(unsigned int row=0; row<g_rows; row++)
    {
        for(unsigned int col=0; col<g_cols; col++)
        {
            cell = g_mat(col,row);
            if ( !cell.is_open )
                cout << '+' << "  ";
            else
                cout << cell.content << "  ";
        }
        cout << endl;
    }
}

void Grid::reveal_all()
{
    for(unsigned int row=0; row<g_rows; row++)
    {
        for(unsigned int col=0; col<g_cols; col++)
            g_mat(col,row).reveal();
    }
}

