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
	void init();		// skillMap ����ϱ� ���� �ѹ��� �� �������

	skill getSkill(SKILL skillName);
	void setSkill(SKILL skillName, skill f);
};

#endif