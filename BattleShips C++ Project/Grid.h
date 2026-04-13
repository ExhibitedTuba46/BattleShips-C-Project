#pragma once
class Grid
{
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

