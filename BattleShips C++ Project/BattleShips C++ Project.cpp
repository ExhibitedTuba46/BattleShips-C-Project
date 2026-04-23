#include <iostream>
#include <Windows.h>
#include "Grid.h"
#include "BattleShip.h"
#include "StrikingGrid.h"
#include "PlacementGrid.h"
#include "AIOpponent.h"
using namespace std;

//Initialise the player and AI's striking grid and placement grid
StrikingGrid playerStrikingGrid;
PlacementGrid playerPlacementGrid;
StrikingGrid aitrikingGrid;
PlacementGrid aiPlacementGrid;
//Initialise the AI
AIOpponent opponent;

//Initialise the player's ships
BattleShip playerDestroyer(2, 0, 9, 0, 8, 4, "Destroyer", false);
BattleShip playerSubmarine(3, 0, 9, 1, 8, 5, "Submarine", false);
BattleShip playerCruiser(3, 0, 9, 1, 8, 6, "Cruiser", false);
BattleShip playerBattleShip(4, 0, 9, 1, 7, 7, "BattleShip", false);
BattleShip playerCarrier(5, 0, 9, 2, 7, 8, "Aircraft Carrier", false);

//Initialise the AI's ships
BattleShip opponentDestroyer(2, 0, 9, 0, 8, 4, "Destroyer", true);
BattleShip opponentSubmarine(3, 0, 9, 1, 8, 5, "Submarine", true);
BattleShip opponentCruiser(3, 0, 9, 1, 8, 6, "Cruiser", true);
BattleShip opponentBattleShip(4, 0, 9, 1, 7, 7, "BattleShip", true);
BattleShip opponentCarrier(5, 0, 9, 2, 7, 8, "Aircraft Carrier", true);

int main()
{
	bool canStart = false;
	//Welcome the user to the program and ask them whether they already know how to play battleship
	cout << "Welcome user!" << endl;
	cout << "Do you already know how to play Battleship?" << endl;
	cout << "'\033[33mY\033[0m' I'm all set!" << endl;
	cout << "'\033[33mN\033[0m' I would like a refresher." << endl;
	//While the player has still not given an answer
	while (canStart == false)
	{
		//If the player presses Y for yes
		if (GetKeyState('Y') & 0x8000)
		{
			//Begin the game
			system("cls");
			canStart = true;
		}
		//If the player presses N for no
		else if (GetKeyState('N') & 0x8000)
		{
			system("cls");
			//If the player has not stated they wish to exit
			bool isDoneReading = false;
			//Display a brief overview of battleship's rules so the player can understand how to play
			cout << "BATTLESHIP RULES:" << endl;
			cout << endl;

			cout << "You and an opponent each have a game board that represents an ocean, and on this board you may place your ships however you please." << endl;
			cout << "There are five ships that you may place on your board: " << endl;
			cout << " *Destroyer - 2 cells" << endl;
			cout << " *Submarine - 3 cells" << endl;
			cout << " *Cruiser - 3 cells" << endl;
			cout << " *Battleship - 4 cells" << endl;
			cout << " *Aircraft Carrier - 5 cells" << endl;
			cout << endl;

			cout << "The goal of the game is to sink each of your opponents ships before they can sink yours." << endl;
			cout << "You may only strike one cell of the opponents board at a time, but you cannot see where their ships are placed, only the result of the strike." << endl;
			cout << "In this program you will be playing against an AI agent." << endl;
			cout << endl;

			cout << "Press '\033[33mEscape\033[0m' to continue." << endl;
			
			//While the player has not stated they wish to stop reading
			while (isDoneReading == false)
			{
				//If escape is pressed
				if (GetKeyState(VK_ESCAPE) & 0x8000)
				{
					system("cls");
					//Display the welcome message again and prompt the user with the same question
					cout << "Welcome user!" << endl;
					cout << "Do you already know how to play Battleship?" << endl;
					cout << "'\033[33mY\033[0m' I'm all set!" << endl;
					cout << "'\033[33mN\033[0m' I would like a refresher." << endl;
					isDoneReading = true;
				}
			}
		}
	}


	bool hasGameFinished = false;

	//Place each of the AI's ships
	//Each ship is given a random rotation and location
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

	//Query the player to place each of their ships
	playerPlacementGrid.QueryBattleShipInput(&playerDestroyer);
	playerPlacementGrid.QueryBattleShipInput(&playerSubmarine);
	playerPlacementGrid.QueryBattleShipInput(&playerCruiser);
	playerPlacementGrid.QueryBattleShipInput(&playerBattleShip);
	playerPlacementGrid.QueryBattleShipInput(&playerCarrier);

	//A brief buffer to tell the player that the AI has placed their ships
	system("cls");
	cout << "AI placement phase:" << endl;
	Sleep(1000);
	cout << "AI is placing ships..." << endl;
	Sleep(1000);
	system("cls");

	while (hasGameFinished == false)
	{
		//Query a strike from the player
		playerStrikingGrid.QuerySrikeInput(&aiPlacementGrid, playerPlacementGrid);
		//Check the AI's placement grid, if there are no ships remaining the player has won
		if (aiPlacementGrid.GetShipsRemaining() == 0)
		{
			hasGameFinished = true;
			system("cls");
			//Congratulate the player on winning
			cout << "You win!" << endl;

			//Display both the AI and player's placement boards to show where each placed their ships
			cout << "Final boards:" << endl;
			cout << endl;
			cout << "AI's board:" << endl;
			aiPlacementGrid.DisplayGrid();

			cout << "Your board:" << endl;
			playerPlacementGrid.DisplayGrid();
			break;
		}

		//A buffer to show the player the AI is taking it's turn
		//If no buffer was here then the game would just skip straight to the AI's result without any in-between, which would make it hard for the player to follow
		Sleep(1000);

		cout << "AI's turn:" << endl;

		Sleep(1000);

		cout << "AI is thinking..." << endl;

		Sleep(1000);

		//Query a strike from the AI
		//Update it's heatmap
		opponent.UpdateHeatMap(aitrikingGrid);
		pair<int, int> chosenCell = opponent.TargetHeatmapCell();
		aitrikingGrid.AIStrike(&playerPlacementGrid, chosenCell);
		//If there are no ships left on the player's placement grid then the AI has won
		if (playerPlacementGrid.GetShipsRemaining() == 0)
		{
			hasGameFinished = true;
			system("cls");
			//Inform the player the AI has won
			cout << "The Ai wins!" << endl;

			//Display both the AI and player's placement boards to show where each placed their ships
			cout << "Final boards:" << endl;
			cout << endl;
			cout << "Your board:" << endl;
			playerPlacementGrid.DisplayGrid();

			cout << "AI's board:" << endl;
			aiPlacementGrid.DisplayGrid();
			break;
		}
	}
	cout << endl;
	//Prompt the player to press escape when they wish to leave 
	cout << "Press '\033[33mEscape\033[0m' to exit the program." << endl;
	//Wait for the player to signal that they wish to exit the program
	bool isExitKeyPressed = false;
	while (isExitKeyPressed == false)
	{
		//When the player presses escape
		if (GetKeyState(VK_ESCAPE) & 0x8000)
		{
			//Exit the program
			isExitKeyPressed = true;
			exit(0);
			return 0;
		}
	}
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
