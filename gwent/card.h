#ifndef CARD_H
#define CARD_H

#include "cardBase.h"

class Card : public CardBase {
private:
	// playing unit's status 
	ID u_id;
	int u_strength;
	int u_armor;

public:
    Card(CardBase* cb, ID _id = 0) : CardBase(cb) {
        if (cb != nullptr) {
            u_id = _id;
            u_strength = 0;
            u_armor = 0;
        }
    };

    //friend std::ostream& operator<<(std::ostream& os, const Card* m);

	ID getID();
	int getStrength();
	int getArmor();
    bool changeStrength(int v);	// return is_dead
	void changeArmor(int v);
    void setStrength(int v);
};

#endif // !CARD_H
