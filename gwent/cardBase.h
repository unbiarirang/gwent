#ifndef CARDBASE_H
#define CARDBASE_H

#include <string>
#include <vector>

typedef int ID;

// for parsing json
//void initCardCollection();

class CardBase {
public:
	int no;
	int type;
	std::string name;
	int camp;
	int line;
	int strength;
	int armor;
	int power;	// 공격력 (일단 frost를 생각하고 만듬)
	int is_doomed;
	int is_stubborn;
	int is_leader;
	int skill;
	int deploySkill;
	int deathWishSkill; 
	int skillData;
	int deploySkillData;
    int needTarget;

	CardBase(std::string _name = "", int _armor = 0, int _camp = 0, int _is_doomed = 0, int _is_leader = 0, int _is_stubborn = 0,
		int _line = 0, int _no = 0, int _power = 0, int _strength = 0, int _type = 0, int _skill = 0, int _deploySkill = 0,
        int _deathWishSkill = 0, int _skillData = 0, int _deploySkillData = 0, int _needTarget = 0) :
			no(_no), type(_type), name(_name), camp(_camp), line(_line), strength(_strength), armor(_armor), power(_power),
			is_doomed(_is_doomed), is_stubborn(_is_stubborn), is_leader(_is_leader), skill(_skill), deploySkill(_deploySkill),
            deathWishSkill(_deathWishSkill), skillData(_skillData), deploySkillData(_deploySkillData), needTarget(_needTarget){};
	CardBase(CardBase* cb, ID _id = 0) :
		no(cb->no), type(cb->type), name(cb->name), camp(cb->camp), line(cb->line), strength(cb->strength), armor(cb->armor), power(cb->power),
		is_doomed(cb->is_doomed), is_stubborn(cb->is_stubborn), is_leader(cb->is_leader), skill(cb->skill), deploySkill(cb->deploySkill),
        deathWishSkill(cb->deathWishSkill), skillData(cb->skillData), deploySkillData(cb->deploySkillData), needTarget(cb->needTarget){};
};

std::vector<CardBase*> setDeck();

#endif
