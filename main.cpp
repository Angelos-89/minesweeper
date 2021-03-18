#include <windows.h>
#include <stdio.h>
#include "Cell.h"
#include "Grid.h"
using namespace std;

struct difficulty
{
    unsigned int cols;
    unsigned int rows;
    double density;
}DIFFICULTY;

char play_again='1';
char dif;
bool game_over = 0;
bool win = 0;

void clear_screen(char fill = ' ') {
    COORD tl = {0,0};
    CONSOLE_SCREEN_BUFFER_INFO s;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(console, &s);
    DWORD written, cells = s.dwSize.X * s.dwSize.Y;
    FillConsoleOutputCharacter(console, fill, cells, tl, &written);
    FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
    SetConsoleCursorPosition(console, tl);
}

struct difficulty& setDifficulty()
{
    cout << "Set Difficulty level:\n\nPress 1 for 9x9   grid \nPress 2 for 16x16 grid \nPress 3 for 16x30 grid" << endl;
    do{
        scanf(" %c",&dif);
    }while(dif!='1' && dif!='2' && dif!='3');
    cout << endl;

    switch(dif)
    {
        case '1':
            DIFFICULTY.rows = 9;
            DIFFICULTY.cols = 9;
            DIFFICULTY.density = 0.12346;
            break;

        case '2':
            DIFFICULTY.rows = 16;
            DIFFICULTY.cols = 16;
            DIFFICULTY.density = 0.15625;
            break;

        case '3':
            DIFFICULTY.rows = 16;
            DIFFICULTY.cols = 30;
            DIFFICULTY.density = 0.20625;
            break;

        default:
            DIFFICULTY.rows = 9;
            DIFFICULTY.cols = 9;
            DIFFICULTY.density = 12.346;
    }
    return DIFFICULTY;
}

void logic(Grid& grid)
{
    // choose a cell

    unsigned int x;
    unsigned int y;
    scanf(" %d",&x);
    scanf(" %d",&y);

    // if you moved and it is a bomb, you lost

    if (grid(x,y).is_bomb)
    {
        game_over = 1;
        return;
    }

    // if you moved and it is a non zero number, reveal it, and erase that cell from the set containing the unrevealed cells

    if (grid(x,y).content != '0' && !grid(x,y).is_bomb)
     {
         grid(x,y).reveal();
         grid.unrevealed_cells.erase(grid(x,y));
     }

    // if you moved and it has zero bombs around it, open all neighboring cells that also have zero bombs around them

    if (grid(x,y).content == '0')
        grid.reveal_all_zero_cells(x,y);

    // if the remaining unrevealed cells are the ones containing bombs, you won

    if (grid.cells_with_bombs == grid.unrevealed_cells)
    {
        game_over = 1;
        win = 1;
    }

}

void exit()
{
    if(win)
        cout << "Seems like you are good!" << endl;
    else
        cout << "Seems like you suck!" << endl;
}

void printStats()
{
    if (dif == '1')
        cout << "Difficulty: Easy" << endl;
    if(dif == '2')
        cout << "Difficulty: Moderate" << endl;
    if(dif == '3')
        cout << "Difficulty: Hard" << endl;
    cout << "Let's see what you got!\n" << endl;
}

int main()
{
    cout << "Welcome to the command line minesweeper my friend!\n" << endl;
    while (play_again == '1')
    {
        setDifficulty();
        clear_screen();
        Grid grid(DIFFICULTY.cols,DIFFICULTY.rows,DIFFICULTY.density);
        grid.init();
        while(!game_over)
        {
            printStats();
            grid.draw();
            logic(grid);
            clear_screen();
        }
        exit();
        cout << "Play again? Press 1, otherwise exit with 0" << endl;
        do{
        scanf(" %c",&play_again);
        }while(play_again != '1' && play_again != '0' );
        clear_screen();
        if (play_again == '1')
            game_over = 0;
        else if (play_again == '0')
            return 0;
    }
}
