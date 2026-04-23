#pragma once
class Grid
{
	//The grid that all children of this class will use
protected: int grid[10][10] = { 
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0}, 
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0}, 
	{0,0,0,0,0,0,0,0,0,0}, 
	{0,0,0,0,0,0,0,0,0,0}, 
	{0,0,0,0,0,0,0,0,0,0}, 
	{0,0,0,0,0,0,0,0,0,0} };

public: int GetCell(int x, int y);

public: void SetCell(int x, int y, int value);

public: virtual void DisplayGrid();

public: virtual void DisplayGridRaw();
};

