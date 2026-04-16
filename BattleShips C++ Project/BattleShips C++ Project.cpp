#include <iostream>
#include <Windows.h>
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
BattleShip playerDestroyer(2, 0, 9, 0, 8, 4, "Destroyer", false);
BattleShip playerSubmarine(3, 0, 9, 1, 8, 5, "Submarine", false);
BattleShip playerCruiser(3, 0, 9, 1, 8, 6 , "Cruiser", false);
BattleShip playerBattleShip(4, 0, 9, 1, 7, 7, "BattleShip", false);
BattleShip playerCarrier(5, 0, 9, 2, 7, 8, "Aircraft Carrier", false);

BattleShip opponentDestroyer(2, 0, 9, 0, 8, 4, "Destroyer", true);
BattleShip opponentSubmarine(3, 0, 9, 1, 8, 5, "Submarine", true);
BattleShip opponentCruiser(3, 0, 9, 1, 8, 6, "Cruiser", true);
BattleShip opponentBattleShip(4, 0, 9, 1, 7, 7, "BattleShip", true);
BattleShip opponentCarrier(5, 0, 9, 2, 7, 8, "Aircraft Carrier", true);

int main()
{
	bool hasGameFinished = false;

	bool rotation = opponent.GetRandomRotation();
	pair<int, int> shipPlacement = opponent.ChooseRandomCell(aiPlacementGrid, opponentDestroyer, rotation);
	aiPlacementGrid.PlaceAIShip(&opponentDestroyer, shipPlacement.first, shipPlacement.second, rotation);

	rotation = opponent.GetRandomRotation();
	shipPlacement = opponent.ChooseRandomCell(aiPlacementGrid, opponentCruiser, rotation);
	aiPlacementGrid.PlaceAIShip(&opponentCruiser, shipPlacement.first, shipPlacement.second, rotation);

	rotation = opponent.GetRandomRotation();
	shipPlacement = opponent.ChooseRandomCell(aiPlacementGrid, opponentSubmarine, rotation);
	aiPlacementGrid.PlaceAIShip(&opponentSubmarine, shipPlacement.first, shipPlacement.second, rotation);

	rotation = opponent.GetRandomRotation();
	shipPlacement = opponent.ChooseRandomCell(aiPlacementGrid, opponentBattleShip, rotation);
	aiPlacementGrid.PlaceAIShip(&opponentBattleShip, shipPlacement.first, shipPlacement.second, rotation);

	rotation = opponent.GetRandomRotation();
	shipPlacement = opponent.ChooseRandomCell(aiPlacementGrid, opponentCarrier, rotation);
	aiPlacementGrid.PlaceAIShip(&opponentCarrier, shipPlacement.first, shipPlacement.second, rotation);
	
	
	playerPlacementGrid.QueryBattleShipInput(&playerDestroyer);
	playerPlacementGrid.QueryBattleShipInput(&playerSubmarine);
	playerPlacementGrid.QueryBattleShipInput(&playerCruiser);
	playerPlacementGrid.QueryBattleShipInput(&playerBattleShip);
	playerPlacementGrid.QueryBattleShipInput(&playerCarrier);
	

	while (hasGameFinished == false)
	{
		playerStrikingGrid.QuerySrikeInput(&aiPlacementGrid, playerPlacementGrid);
		if (aiPlacementGrid.GetShipsRemaining() == 0)
		{
			hasGameFinished = true;
			system("cls");
			cout << "You win!";
			break;
		}
		
		Sleep(1000);

		cout << "AI's turn:" << endl;

		Sleep(1000);

		cout << "AI is thinking..." << endl;

		Sleep(1000);

		opponent.UpdateHeatMap(aitrikingGrid);
		pair<int, int> chosenCell = opponent.GetBestCell();
		aitrikingGrid.AIStrike(&playerPlacementGrid, chosenCell);

		if (playerPlacementGrid.GetShipsRemaining() == 0)
		{
			hasGameFinished = true;
			system("cls");
			cout << "The Ai wins!";
			break;
		}
	}
	Sleep(100000);
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
