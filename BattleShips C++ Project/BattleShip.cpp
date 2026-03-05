#include "BattleShip.h"

int BattleShip::GetSizeInCells() { return sizeInCells; }

int BattleShip::GetXConstraints(int index) { return xConstraints[index]; }

int BattleShip::GetYConstraints(int index) { return yConstraints[index]; }

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

BattleShip::BattleShip(int sizeOfShip, int xConstraint1, int xConstraint2, int YConstraint1, int YConstraint2)
{
	sizeInCells = sizeOfShip;

	xConstraints[0] = xConstraint1;
	xConstraints[1] = xConstraint2;

	yConstraints[0] = YConstraint1;
	yConstraints[1] = YConstraint2;
}