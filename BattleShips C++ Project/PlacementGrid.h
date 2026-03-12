#pragma once
#include "Grid.h"
#include "BattleShip.h"
#include "PlacementGrid.h"
#include <vector>
using namespace std;

class PlacementGrid : public Grid
{
private: int previousGridValue = 0;

private: vector<BattleShip*> placedShips;

public: void DisplayGrid() override;

private: int DisplayCellPlacement(int x, int y);

private: void DisplayPotentialBattleShip(int x, int y, bool isVertical, BattleShip* shipToDisplay);

public: void QueryBattleShipInput(BattleShip* shipToQuery);

public: void PlaceAIShip(BattleShip* shipToPlace, int x, int y);

public: int QueryHitInput(int x, int y);

private: void ClearPotentialBattleShips();
};
