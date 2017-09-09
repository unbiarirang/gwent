#include "skill.h"
#include "enum.h"

SkillMap skillMap;	// for common use to every source file

void consume(User* user, Card* card, int value = 0) {
	std::cout << "SKILL::CONSUME �ߵ�ī��: " << card << std::endl;

	User* enemy = user->enemy;
	// TODO: Ŭ������ Ÿ�� ī�� ���̵� �Է� ����
	ID targetID = 21; // FIXME: �ӽ� ����
	Card* targetCard = enemy->cardMap[targetID];

	card->changeStrength(targetCard->strength);	// boost the card
	enemy->destroyCard(targetID);				// destroy the target card
}

void spawn(User* user, Card* card, int value = 0) {
	std::cout << "SKILL::SPAWN �ߵ�ī��: " << card << std::endl;

	// TODO: skill���� deploySkill���� deadWishSkill ���� ���ڷ� �޾ƾ� ��
	// user->spawnCard(card->skillData)
	Card* newCard = user->spawnCard(1); // FIXME: �ӽ� ����

	// Ŭ������ ������ ���ϴ��� �ڵ����� ��ġ �Ǵ���
	LO lo = LO::LINE1; // FIXME: �ӽ� ����
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

void destoryHighest(User * user, Card * card, int value) // �� ��ü���ΰɷ� ������ ������ �Ʊ״Ϲۿ� �Ⱦ��µ�
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
