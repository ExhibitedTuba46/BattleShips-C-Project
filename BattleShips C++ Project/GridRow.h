#pragma once
class GridRow
{
	char rowID;
	int row[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

public: int GetCell(int cell);
};

