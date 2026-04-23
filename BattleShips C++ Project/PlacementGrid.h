#pragma once
#include "Grid.h"
#include "BattleShip.h"
#include "PlacementGrid.h"
#include <vector>
using namespace std;

class PlacementGrid : public Grid
{
	//This grid is used to temporarily store the locations of ships on the grid separately from the main grid
	//This is used to reset the grid after it has been changed to display where potential ships could be placed
private: int realGridValues[10][10];

	   //The ships that have already been placed on the grid
private: vector<BattleShip*> placedShips;

public: int GetShipsRemaining();

public: void DisplayGrid() override;

private: int DisplayCellPlacement(int x, int y);

private: void DisplayPotentialBattleShip(int x, int y, bool isVertical, BattleShip* shipToDisplay);

public: void QueryBattleShipInput(BattleShip* shipToQuery);

public: void PlaceAIShip(BattleShip* shipToPlace, int x, int y, bool isVertical);

public: int QueryHitInput(int x, int y);

private: void ClearPotentialBattleShips();

private: bool PlaceBattleShip(bool isVertical, BattleShip* shipBeingPlaced, int x, int y, bool isPlayer);
};
