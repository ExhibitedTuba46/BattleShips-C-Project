#include "Grid.h"
#include <iostream>
using namespace std;

int Grid::GetCell(int x, int y)
{
	return grid[x][y];
}

void Grid::SetCell(int x, int y, int value)
{
	grid[x][y] = value;
}

/*
Example layout of how this could look 

*Strking Grid
  0 1 2 3 4 5 6 7 8 9
A ~ X ~ ~ ~ ~ ~ ~ ~ ~
B ~ X ~ ~ ~ ~ ~ ~ ~ ~ 
C ~ ~ ~ ~ ~ ~ ~ ~ O ~
E ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
D ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
F ~ ~ ~ ~ ~ ~ ~ X ~ ~
G ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
H ~ ~ O ~ ~ ~ ~ ~ ~ ~
I ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
J ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

*Placement Grid
  0 1 2 3 4 5 6 7 8 9
A ~ # ~ ~ ~ ~ ~ ~ ~ ~
B ~ # ~ ~ ~ ~ ~ ~ ~ ~
C ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
E ~ ~ ~ # # # ~ ~ ~ ~
D ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
F # ~ ~ ~ ~ ~ # # # #
G # ~ ~ ~ ~ ~ ~ ~ ~ ~
H # ~ ~ ~ # ~ ~ ~ ~ ~
I # ~ ~ ~ # ~ ~ ~ ~ ~
J # ~ ~ ~ # ~ ~ ~ ~ ~
*/

