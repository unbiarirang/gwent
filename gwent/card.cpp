#include "card.h"
#include <QDebug>

ID Card::getID()
{
	return u_id;
}

int Card::getStrength()
{
	return u_strength;
}

int Card::getArmor()
{
	return u_armor;
}

// return is_dead
bool Card::changeStrength(int v)
{
	u_strength += v;

	if (u_strength <= 0) {	//the unit is destroyed
		u_strength = 0;
		return true;
	}

	return false;
}

void Card::setStrength(int v)
{
    u_strength = v;
}

void Card::changeArmor(int v)
{
	u_armor = u_armor + v;
}
