#pragma once
#include "Grid.h"
#include "PlacementGrid.h"
class PlacementGrid : public Grid
{
public: void DisplayGrid() override;

private: int DisplayCellPlacement(int x, int y);

private: void DisplayPotentialBattleShip(int x, int y, bool isVertical);

public: void QueryBattleShipInput();

private: void ClearPotentialBattleShips();
};
