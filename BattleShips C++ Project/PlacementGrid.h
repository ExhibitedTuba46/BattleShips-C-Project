#pragma once
#include "Grid.h"
#include "BattleShip.h"
#include "PlacementGrid.h"
class PlacementGrid : public Grid
{
public: void DisplayGrid() override;

private: int DisplayCellPlacement(int x, int y);

private: void DisplayPotentialBattleShip(int x, int y, bool isVertical, BattleShip shipToDisplay);

public: void QueryBattleShipInput(BattleShip shipToQuery);

private: void ClearPotentialBattleShips();
};
