#include "skill.h"
#include "enum.h"

SkillMap skillMap;	// for common use to every source file

void consume(User* user, Card* card, int value = 0) {
	std::cout << "SKILL::CONSUME 발동카드: " << card << std::endl;

	User* enemy = user->enemy;
	// TODO: 클릭으로 타겟 카드 아이디 입력 받음
	ID targetID = 21; // FIXME: 임시 숫자
	Card* targetCard = enemy->cardMap[targetID];

	card->changeStrength(targetCard->strength);	// boost the card
	enemy->destroyCard(targetID);				// destroy the target card
}

void spawn(User* user, Card* card, int value = 0) {
	std::cout << "SKILL::SPAWN 발동카드: " << card << std::endl;

	// TODO: skill인지 deploySkill인지 deadWishSkill 인지 인자로 받아야 함
	// user->spawnCard(card->skillData)
	Card* newCard = user->spawnCard(1); // FIXME: 임시 숫자

	// 클릭으로 라인을 정하던지 자동으로 배치 되던지
	LO lo = LO::LINE1; // FIXME: 임시 숫자
	user->insertInto(lo, newCard->getID());
}

void damage(User * user, Card * card, int value)
{
	card->changeStrength(-value);

	if (card->getStrength() <= 0)
		user->destroyCard(card->getID());
}

void getArmor(User * user, Card * card, int value)
{
	card->changeArmor(value);
}

void summon(User * user, Card * card, int value)
{
	//ID targetID = 
}

void attack(User * user, Card * card, int value)
{
}

void boostPower(User * user, Card * card, int value)
{
}

void boost(User * user, Card * card, int value)
{
}

void removeWeather(User * user, Card * card, int value)
{
}

void moveToEnemyGrave(User * user, Card * card, int value)
{
}

void drawCard(User * user, Card * card, int value)
{
}

void strengthen(User * user, Card * card, int value)
{
}

void resurrect(User * user, Card * card, int value)
{
}

void destoryHighest(User * user, Card * card, int value) // 걍 구체적인걸로 만들자 어차피 아그니밖에 안쓰는듯
{
	//ID highest = user->getHighest();
	//ID highest2 = user->enemy->getHighest();

	//int str = user->getCardFromID(highest)->getStrength();
	//int str2 = user->getCardFromID(highest2)->getStrength();

	//if (str < str2) {
	//	highest = highest2;
	//	str = str2;
	//}
	//else if (str == str2) {

	//}
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
