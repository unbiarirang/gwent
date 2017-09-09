#include "skill.h"

SkillMap skillMap;	// for common use to every source file

void consume(Card* x, int y = 0) {
	std::cout << "consume " << x << " " << y << std::endl;
}

void spawn(Card* x, int y) {
	std::cout << "spawn " << x << " " << y << std::endl;
}

void SkillMap::init()
{
	skillMap.setSkill(SKILL::CONSUME, consume);
	skillMap.setSkill(SKILL::SPAWN, spawn);
}

skill SkillMap::getSkill(SKILL skillName)
{
	return map[skillName];
}

void SkillMap::setSkill(SKILL skillName, skill f)
{
	map[skillName] = f;
}
