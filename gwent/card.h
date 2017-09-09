#ifndef CARD_H
#define CARD_H

#include "cardBase.h"

class Card : public CardBase {
private:
	// playing unit's status 
	ID u_id;
	int u_strength;
	//int u_line;		// LINE enum TODO: ������ ���� ������ ������ ���°� ���
	int u_armor;
	//int u_location; // LOCATION enum TODO: ������ ���� ������ ������ ���°� ���

public:
	Card(CardBase* cb, ID _id) :
		CardBase(cb), u_id(_id), u_strength(cb->strength), u_armor(cb->armor) {};

	friend std::ostream& operator<<(std::ostream& os, const Card* m);

	ID getID();
	int getStrength();
	int getArmor();
	void changeStrength(int v);
	void changeArmor(int v);
};

#endif // !CARD_H
