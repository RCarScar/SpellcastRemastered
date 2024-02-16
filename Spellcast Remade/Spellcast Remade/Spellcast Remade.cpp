#include "Grid.h"

int main()
{
    Grid grid = Grid();
    grid.InputLetters();
    grid.CreateGrid();

    grid.HashAdjacent();
    grid.Display();

    grid.HashWords();
    
    grid.TraverseGraph();
}
