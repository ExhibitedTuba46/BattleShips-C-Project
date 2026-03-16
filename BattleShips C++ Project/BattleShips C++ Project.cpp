#include <iostream>
#include "Grid.h"
#include "BattleShip.h"
#include "StrikingGrid.h"
#include "PlacementGrid.h"
#include "AIOpponent.h"
using namespace std;

StrikingGrid playerStrikingGrid;
PlacementGrid playerPlacementGrid;
StrikingGrid aitrikingGrid;
PlacementGrid aiPlacementGrid;
AIOpponent opponent;
BattleShip playerDestroyer(2, 0, 9, 0, 8, 4, "Destroyer");
BattleShip playerSubmarine(3, 0, 9, 1, 8, 5, "Submarine");
BattleShip playerCruiser(3, 0, 9, 1, 8, 6 , "Cruiser");
BattleShip playerBattleShip(4, 0, 9, 1, 7, 7, "BattleShip");
BattleShip playerCarrier(5, 0, 9, 2, 7, 8, "Aircraft Carrier");

BattleShip opponentDestroyer(2, 0, 9, 0, 8, 4, "Destroyer");
BattleShip opponentSubmarine(3, 0, 9, 1, 8, 5, "Submarine");
BattleShip opponentCruiser(3, 0, 9, 1, 8, 6, "Cruiser");
BattleShip opponentBattleShip(4, 0, 9, 1, 7, 7, "BattleShip");
BattleShip opponentCarrier(5, 0, 9, 2, 7, 8, "Aircraft Carrier");

int main()
{
	bool rotation = opponent.GetRandomRotation();
	playerPlacementGrid.PlaceAIShip(&opponentDestroyer, 
		opponent.ChooseRandomStartingCellX(aiPlacementGrid, opponentDestroyer, rotation),
		opponent.ChooseRandomStartingCellY(aiPlacementGrid, opponentDestroyer, rotation), 
		rotation);

	/*
	playerPlacementGrid.QueryBattleShipInput(&playerDestroyer);
	playerPlacementGrid.QueryBattleShipInput(&playerSubmarine);
	playerPlacementGrid.QueryBattleShipInput(&playerCruiser);
	playerPlacementGrid.QueryBattleShipInput(&playerBattleShip);
	playerPlacementGrid.QueryBattleShipInput(&playerCarrier);
	*/

	playerStrikingGrid.QuerySrikeInput(playerPlacementGrid);
	playerStrikingGrid.DisplayGrid();
	playerPlacementGrid.DisplayGrid();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
