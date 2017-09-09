#include "skill.h"
#include "enum.h"

SkillMap skillMap;	// for common use to every source file

void SkillMap::init()
{
	skillMap.setSkill(SKILL::CONSUME, consume);
	skillMap.setSkill(SKILL::SPAWN, spawn);
	skillMap.setSkill(SKILL::DAMAGE, damage);
	skillMap.setSkill(SKILL::GETARMOR, getArmor);
	skillMap.setSkill(SKILL::SUMMON, summon);
	skillMap.setSkill(SKILL::ATTACK, attack);
	skillMap.setSkill(SKILL::BOOSTPOWER, boostPower);
	skillMap.setSkill(SKILL::BOOST, boost);
	skillMap.setSkill(SKILL::REMOVEWEATHER, removeWeather);
	skillMap.setSkill(SKILL::MOVETOENEMYGRAVE, moveToEnemyGrave);
	skillMap.setSkill(SKILL::DRAWCARD, drawCard);
	skillMap.setSkill(SKILL::STRENGTHEN, strengthen);
	skillMap.setSkill(SKILL::RESURRECT, resurrect);
	skillMap.setSkill(SKILL::DESTROY, destroy);
	skillMap.setSkill(SKILL::DESTROYHIGHEST, destroyHighest);

	skillMap.setSkill(SKILL::FIRSTLIGHT, firstLight);
	skillMap.setSkill(SKILL::BITINGFROST, bitingFrost);
	skillMap.setSkill(SKILL::IMPENETRABLEFOG, impenetrableFog);
	skillMap.setSkill(SKILL::TORRENTIALRAIN, torrentialRain);
	skillMap.setSkill(SKILL::LACERATE, lacerate);
	skillMap.setSkill(SKILL::COMMANDERSHORN, commandersHorn);
	skillMap.setSkill(SKILL::BEKKERSTWISTEDMIRROR, bekkersTwistedMirror);
	skillMap.setSkill(SKILL::GERALTIGNI, geraltIgni);
	skillMap.setSkill(SKILL::ROACH, roach);
	skillMap.setSkill(SKILL::THUNDERBOLTPOSITION, thunderboltPosition);
}

skill SkillMap::getSkill(SKILL skillName)
{
	return map[skillName];
}

void SkillMap::setSkill(SKILL skillName, skill f)
{
	map[skillName] = f;
}


void consume(User* user, ID cardID, ID targetID = 0, LO location = LO(), int data = 0) {
	Card* card = user->getCardFromID(cardID);
	Card* targetCard = user->getCardFromID(targetID);

	std::cout << "SKILL::CONSUME 발동카드: " << card << std::endl;

	user->changeStrength(cardID, targetCard->getStrength());	// boost the card
	user->destroyCard(targetID);				// destroy the target card
}

// data: target card no
void spawn(User* user, ID cardID, ID targetID = 0, LO location = LO(), int data = 0) {
	int targetCardNo = data;
	Card* card = user->getCardFromID(cardID);

	std::cout << "SKILL::SPAWN 발동카드: " << card << std::endl;

	targetCardNo = 1; // FIXME: 임시 숫자
	Card* newCard = user->spawnCard(targetCardNo);

	// 클릭으로 라인을 정하던지 자동으로 배치 되던지
	LO lo = LO::LINE1; // FIXME: 임시 숫자
	user->insertInto(lo, newCard->getID());
}

// data: damage count
void damage(User* user, ID cardID, ID targetID = 0, LO location = LO(), int data = 0)
{
	user->changeStrength(cardID, -data);
}

void getArmor(User* user, ID cardID, ID targetID = 0, LO location = LO(), int data = 0)
{
	Card* card = user->getCardFromID(cardID);

	card->changeArmor(data);
}

// 이거 지금 손에있는거 우선으로 손이나 덱에 있는 카드 한장 소환하는거. 구체적 필요
void summon(User* user, ID cardID, ID targetID = 0, LO location = LO(), int data = 0)
{
	int summonCardNo = data;
	ID summonID;
	LO lo;

	for (auto id : user->deck) {
		if (user->getCardFromID(id)->no == data) {
			summonID = user->getCardFromID(id)->getID();
			lo = LO::DECK;
			break;
		}
	}

	for (auto id : user->hand) {
		if (user->getCardFromID(id)->no == data) {
			summonID = user->getCardFromID(id)->getID();
			lo = LO::HAND;
			break;
		}
	}

	LO line;
	line = user->findLine(cardID);
	user->removeFrom(lo, summonID);
	user->insertInto(line, summonID);
}

void attack(User* user, ID cardID, ID targetID = 0, LO location = LO(), int data = 0)
{
	user->enemy->changeStrength(targetID, -data);
}

void boostPower(User* user, ID cardID, ID targetID = 0, LO location = LO(), int data = 0)
{

}

void boost(User* user, ID cardID, ID targetID = 0, LO location = LO(), int data = 0)
{
	user->changeStrength(targetID, data);
}

// data: LO enum (LO::LINE1, LO::LINE2, LO::LINE3)
void removeWeather(User* user, ID cardID, ID targetID = 0, LO location = LO(), int data = 0)
{
	LO line = LO(data);
	ID weatherCardID = user->getWeatherCardIDFromLine(line);

	user->destroyCard(weatherCardID);
}

// from my grave to enemy's grave
void moveToEnemyGrave(User* user, ID cardID, ID targetID = 0, LO location = LO(), int data = 0)
{
	user->removeFrom(LO::GRAVE, cardID);
	user->insertInto(LO::GRAVE_ENEMY, cardID);
}

void drawCard(User* user, ID cardID, ID targetID = 0, LO location = LO(), int data = 0)
{
	int drawCount = data;
	user->drawCard(drawCount);
}

void strengthen(User* user, ID cardID, ID targetID = 0, LO location = LO(), int data = 0)
{
	user->changeStrength(cardID, data);
}

// 실행 카드와 같은 라인에 부활
void resurrect(User* user, ID cardID, ID targetID = 0, LO location = LO(), int data = 0)
{
	user->removeFrom(LO::GRAVE, targetID);
	user->insertInto(user->findLine(cardID), targetID);
}

// destroy the enemy's unit
void destroy(User* user, ID cardID, ID targetID = 0, LO location = LO(), int data = 0) {
	user->enemy->destroyCard(targetID);
}

void destroyHighest(User* user, ID cardID, ID targetID = 0, LO location = LO(), int data = 0) // 걍 구체적인걸로 만들자 어차피 아그니밖에 안쓰는듯
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

// data: no use
void rally(User * user, ID cardID, ID targetID, LO location = LO(), int data = 0)
{
	bool is_exist = false;
	for (auto x : user->deck) {
		if (user->getCardFromID(x)->type == TYPE::BRONZE) {
			is_exist = true;
			break;
		}
	}
	
	int cardNum = user->deck.size();
	int cardIndex;
	ID id;

	if (is_exist) {
		while (true) {
			cardIndex = util::getRandNumBetween(0, cardNum - 1);
			id = user->deck[cardIndex];

			if (user->getCardFromID(id)->type == TYPE::BRONZE) {
				user->insertInto(LO::HAND, id);
				user->removeFrom(LO::DECK, id);
				return;
			}
		}
	}
}

// data: 0 or 1 (clear skies or rally)
void firstLight(User * user, ID cardID, ID targetID, LO location = LO(), int data = 0)
{
	// clear skies
	if (data == 0) {
		for (int i = LO::LINE1; i <= LO::LINE3; i++) {
			removeWeather(user, cardID, targetID, location, i);
		}
		return;
	}

	// rally
	rally(user, cardID, targetID, location, 0);
}

// data: LO enum (LO::LINE1, LO::LINE2, LO::LINE3)
void bitingFrost(User * user, ID cardID, ID targetID, LO location = LO(), int data = 0)
{
	LO lo = location;

	std::vector<ID> lowestCardIDs;
	int min = 1000;
	Card* card;

	for (auto id : user->enemy->line[lo - 3]) {
		card = user->enemy->getCardFromID(id);
		if (card->getStrength() < min && card->line != LINE::WEATHER)
			min = card->getStrength();
	}
	for (auto id : user->enemy->line[lo - 3]) {
		card = user->enemy->getCardFromID(id);
		if (card->getStrength() == min)
			lowestCardIDs.push_back(id);
	}

	// no unit card in the line
	if (lowestCardIDs.size() == 0) return;

	int randomIndex = util::getRandNumBetween(0, lowestCardIDs.size() - 1);
	ID lowestID = lowestCardIDs[randomIndex];

	attack(user, cardID, lowestID, location, user->getCardFromID(cardID)->power);
}

void impenetrableFog(User * user, ID cardID, ID targetID, LO location = LO(), int data = 0)
{
}

void torrentialRain(User * user, ID cardID, ID targetID, LO location = LO(), int data = 0)
{
}

void lacerate(User * user, ID cardID, ID targetID, LO location = LO(), int data = 0)
{
}

void commandersHorn(User * user, ID cardID, ID targetID, LO location = LO(), int data = 0)
{
}

void bekkersTwistedMirror(User * user, ID cardID, ID targetID, LO location = LO(), int data = 0)
{
}

void geraltIgni(User * user, ID cardID, ID targetID, LO location = LO(), int data = 0)
{
}

void roach(User * user, ID cardID, ID targetID, LO location = LO(), int data = 0)
{
}

void thunderboltPosition(User * user, ID cardID, ID targetID, LO location = LO(), int data = 0)
{
}
