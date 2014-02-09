#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define UNIVERSE_ROWS 25
#define UNIVERSE_COLS 25
typedef int Universe[UNIVERSE_ROWS][UNIVERSE_COLS];

int numNeighbours(Universe universe, int row, int col)
{
    int numNeighbours = 0;
    for (int rowAux = row-1; rowAux <= row+1; rowAux++) {
        for (int colAux = col-1; colAux <= col+1; colAux++)
            if (!(row == rowAux && col == colAux)
                    && universe[(rowAux+UNIVERSE_ROWS) % UNIVERSE_ROWS][(colAux+UNIVERSE_COLS) % UNIVERSE_COLS])
                numNeighbours++;
    }
    return numNeighbours;
}

void evolve(Universe universe)
{
    Universe newUniverse;

    for (int row = 0; row < UNIVERSE_ROWS; row++) {
        for (int col = 0; col < UNIVERSE_COLS; col++) {
            int neighbours = numNeighbours(universe, row, col);
            newUniverse[row][col] = (neighbours == 3 || (universe[row][col] && neighbours == 2));
        }
    }

    for (int row = 0; row < UNIVERSE_ROWS; row++) {
        for (int col = 0; col < UNIVERSE_COLS; col++)
            universe[row][col] = newUniverse[row][col];
    }
}

void show(Universe universe)
{
    printf("\033[H");
    printf("\033[2J");
    for (int row = 0; row < UNIVERSE_ROWS; row++) {
        for (int col = 0; col < UNIVERSE_COLS; col++)
            printf(universe[row][col] ? "\033[07m  \033[m" : "  ");
        printf("\n");
    }
    fflush(stdout);
}

int main()
{
    Universe universe;

    srand(time(NULL));
    for (int row = 0; row < UNIVERSE_ROWS; row++) {
        for (int col = 0; col < UNIVERSE_COLS; col++)
            universe[row][col] = rand() % 2;
    }

    for (;;) {
        show(universe);
        evolve(universe);
        usleep(100000);
    }

    return 0;
}
