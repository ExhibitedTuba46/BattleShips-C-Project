#include "BattleShip.h"
#include <iostream>
#include <string>
using namespace std;

/// <summary>
/// Returns the number of cells this ship occupies
/// </summary>
/// <returns></returns>
int BattleShip::GetSizeInCells() { return sizeInCells; }

/// <summary>
/// Returns the X constraints of this ship on the grid
/// </summary>
/// <param name="index">Whether the higher or lower bounds are needed</param>
/// <returns></returns>
int BattleShip::GetXConstraints(int index) { return xConstraints[index]; }

/// <summary>
/// Returns the Y constraints of this ship on the grid
/// </summary>
/// <param name="index">Whether the higher or lower bounds are needed</param>
/// <returns></returns>
int BattleShip::GetYConstraints(int index) { return yConstraints[index]; }

/// <summary>
/// Return this ships identifier on the placement grid
/// </summary>
/// <returns></returns>
int BattleShip::GetShipIdentifier() { return shipIdentifier; }

/// <summary>
/// Return the name of this ship to be displayed
/// </summary>
/// <returns></returns>
string BattleShip::GetShipName() { return shipName; }

/// <summary>
/// Return whether this ship has sunk
/// </summary>
/// <returns></returns>
bool BattleShip::GetShipStatus() { return hasSunk; }

/// <summary>
/// Register damage on this ship
/// </summary>
void BattleShip::DamageShip() {
	//If this ship has been hit less times than the number of cells it occupies
	//Otherwise this ship must have been sunk
	if (timesHit < (sizeInCells - 1))
	{
		//Increase the number of times this ship has been hit
		timesHit++;
		system("cls");

		//If this ship was placed by an AI display a message informing the player that they have hit an enemy ship 
		if (isAI == true)
		{
			cout << "You hit an enemy ship!" << endl;
		}
		//If this ship was not placed by an AI then warn the player that one of their ships has been hit
		else
		{
			cout << "The AI has hit one of your ships!" << endl;
		}
		cout << endl;
	}
	//If this hip has been sunk
	else
	{
		system("cls");
		//If this ship was placed by an AI display a message informing the player that they have sunk an enemy ship
		if (isAI == true)
		{
			cout << "You sunk the AI's " << shipName << "!" << endl;
		}
		//If this ship was not placed by an AI then warn the player that one of their ships has been sunk
		else
		{
			cout << "The AI has sunk your " << shipName << "!" << endl;
		}

		//Mark this ship as sunk
		hasSunk = true;

		cout << endl;
	}
}

/// <summary>
/// Return the location of requested cell this ship contains based on the given location
/// </summary>
/// <param name="x">The coordinate the main cell is located (can be either X or Y)</param>
/// <param name="cellNumber">The number of the cell needed</param>
/// <returns></returns>
int BattleShip::ShipSize(int x, int cellNumber)
{
	//As the biggest a ship can be is 5 cells this function does not go higher 
	//A larger ship would have multiple cells triggered by this function, alternating from right to left:
	//Destroyer 0 1
	//Submarine/Cruiser 2 0 1
	//Battleship 2 0 1 3
	//Carrier 4 2 0 1 3
	switch (cellNumber)
	{
		//If the cell number given is 4, then return the cell two cells to the left of the main cell (Carrier)
	case 4:
		return x - 2;
		//If the cell number given is 3, then return the cell two eells to the right of the main cell (Battleship)
	case 3:
		return x + 2;
		break;
		//If the cell number given is 2, then return the cell to the left of the main cell (Submarine or Cruiser)
	case 2:
		return x - 1;
		break;
		//If the cell number given is 1, then return the cell to the right of the main cell (Destroyer)
	case 1:
		return x + 1;
		break;
		//If the cell number given is 0, then this is the main ship cell and therefore it's location remains unchanged
	case 0:
		return x;
		break;
	default:
		break;
	}
}

/// <summary>
/// The constructor for a new battleship
/// </summary>
/// <param name="sizeOfShip">The size of the ship in cells</param>
/// <param name="xConstraint1">The lower X constraint on the grid</param>
/// <param name="xConstraint2">The higher X constraint on the grid</param>
/// <param name="yConstraint1">The lower Y constraint on the grid</param>
/// <param name="yConstraint2">The higher Y constraint on the grid</param>
/// <param name="identifier">This ship's identifier on a placement grid</param>
/// <param name="name">This ship's name</param>
/// <param name="_isAI">Whether this ship was placed by AI</param>
BattleShip::BattleShip(int sizeOfShip, int xConstraint1, int xConstraint2, int yConstraint1, int yConstraint2, int identifier, string name, bool _isAI)
{
	isAI = _isAI;

	sizeInCells = sizeOfShip;
	shipIdentifier = identifier;

	xConstraints[0] = xConstraint1;
	xConstraints[1] = xConstraint2;

	yConstraints[0] = yConstraint1;
	yConstraints[1] = yConstraint2;

	shipName = name;
}