#ifndef SKILL_H
#define SKILL_H

#include "card.h"

#include <vector>
#include <map>
#include <iostream>

typedef void (*skill)(Card*, int);

enum SKILL {
	CONSUME, SPAWN
};

void consume(int x, int y);
void spawn(int x, int y);

class SkillMap {
private:
	std::map<SKILL, skill> map;
public:
	void init();		// skillMap 사용하기 전에 한번은 꼭 해줘야함

	skill getSkill(SKILL skillName);
	void setSkill(SKILL skillName, skill f);
};

#endif