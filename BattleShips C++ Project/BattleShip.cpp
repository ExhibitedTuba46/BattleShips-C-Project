#include "BattleShip.h"
#include <iostream>
using namespace std;

int BattleShip::GetSizeInCells() { return sizeInCells; }

int BattleShip::GetXConstraints(int index) { return xConstraints[index]; }

int BattleShip::GetYConstraints(int index) { return yConstraints[index]; }

int BattleShip::GetShipIdentifier() { return shipIdentifier; }

void BattleShip::DamageShip() {
	if (timesHit < (sizeInCells - 1))
	{
		timesHit++;
	}
	else
	{
		cout << "You Sunk Me" << endl;
	}
}

int BattleShip::ShipSize(int x, int cellNumber)
{
	switch (cellNumber)
	{
	case 4:
		return x - 2;
	case 3:
		return x + 2;
		break;
	case 2:
		return x - 1;
		break;
	case 1:
		return x + 1;
		break;
	case 0:
		return x;
		break;
	default:
		break;
	}
}

BattleShip::BattleShip(int sizeOfShip, int xConstraint1, int xConstraint2, int yConstraint1, int yConstraint2, int identifier)
{
	sizeInCells = sizeOfShip;
	shipIdentifier = identifier;

	xConstraints[0] = xConstraint1;
	xConstraints[1] = xConstraint2;

	yConstraints[0] = yConstraint1;
	yConstraints[1] = yConstraint2;
}