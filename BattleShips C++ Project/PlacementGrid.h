#pragma once
#include "Grid.h"
#include "PlacementGrid.h"
class PlacementGrid : public Grid
{
public: void DisplayGrid() override;

private: int DisplayCellPlacement(int x, int y);

public: void PlaceBattleShip(int x, int y);
};
