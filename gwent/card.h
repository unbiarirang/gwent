#ifndef CARD_H
#define CARD_H

#include "cardBase.h"

class Card : public CardBase {
private:
	// playing unit's status 
	ID u_id;
	int u_strength;
	//int u_line;		// LINE enum TODO: 어차피 유저 정보에 잇으니 빼는거 고려
	int u_armor;
	//int u_location; // LOCATION enum TODO: 어차피 유저 정보에 잇으니 빼는거 고려

public:
	Card(CardBase* cb, ID _id) :
		CardBase(cb), u_id(_id), u_strength(cb->strength), u_armor(cb->armor) {};

	friend std::ostream& operator<<(std::ostream& os, const Card* m);

	ID getID();
	int getStrength();
	int getArmor();
	bool changeStrength(int v);	// return is_dead; 쓸 때마다 유닛 죽었는지 확인하고 점수 바꿔줘야함! 
	void changeArmor(int v);
};

#endif // !CARD_H
