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

	skillMap.setSkill(SKILL::DAGON, dagon);
	skillMap.setSkill(SKILL::FOGLET, foglet);
	skillMap.setSkill(SKILL::GEELS, geels);
	skillMap.setSkill(SKILL::CELAENOHARPY, celaenoHarpy);
	skillMap.setSkill(SKILL::WOODLANDSPIRIT, woodlandSpirit);
	skillMap.setSkill(SKILL::EARTHELEMENTAL, earthElemental);
	skillMap.setSkill(SKILL::CRONEWEAVESS, croneWeavess);
	skillMap.setSkill(SKILL::CRONEWHISPESS, croneWhispess);
	skillMap.setSkill(SKILL::CRONEBREWESS, croneBrewess);
	skillMap.setSkill(SKILL::ARCHGRIFFIN, archgriffin);
	skillMap.setSkill(SKILL::CARANTHIR, caranthir);
	skillMap.setSkill(SKILL::FRIGHTENER, frightener);
	skillMap.setSkill(SKILL::UNSEENELDER, unseenElder);
	skillMap.setSkill(SKILL::ARACHAS, arachas);
	skillMap.setSkill(SKILL::VRANWARRIOR, vranWarrior);
	skillMap.setSkill(SKILL::ARACHASBEHEMOTH, arachasBehemoth);
	skillMap.setSkill(SKILL::WILDHUNTRIDER, wildHuntRider);
	skillMap.setSkill(SKILL::HARPYEGG, harpyEgg);
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

/*
@ user
@ targetID
@ data
*/
void getArmor(User* user, ID cardID, ID targetID = 0, LO location = LO(), int data = 0)
{
	Card* card = user->getCardFromID(targetID);
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

// data: damage count
void attack(User* user, ID cardID, ID targetID = 0, LO location = LO(), int data = 0)
{
	if (user->enemy->getCardFromID(targetID)->line != LINE::WEATHER)
		user->enemy->changeStrength(targetID, -data);
}

void boostPower(User* user, ID cardID, ID targetID = 0, LO location = LO(), int data = 0)
{

}

/*
@ user
@ targetID
*/
void boost(User* user, ID cardID, ID targetID = 0, LO location = LO(), int data = 0)
{
	user->changeStrength(targetID, data);
}

// data: LO enum (LO::LINE1, LO::LINE2, LO::LINE3)
void removeWeather(User* user, ID cardID, ID targetID = 0, LO location = LO(), int data = 0)
{
	LO line = location;
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

/*
destroy the user's unit
@ user
@ targetID
*/
void destroy(User* user, ID cardID, ID targetID = 0, LO location = LO(), int data = 0) {
	user->destroyCard(targetID);
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

// data: attack power
void bitingFrost(User * user, ID cardID, ID targetID, LO location = LO(), int data = 0)
{
	ID lowestID = user->enemy->getLowestFromLine(location);

	attack(user, cardID, lowestID, location, data);
}

// data: attack power
void impenetrableFog(User * user, ID cardID, ID targetID, LO location = LO(), int data = 0)
{
	ID highestID = user->enemy->getHighestFromLine(location);

	attack(user, cardID, highestID, location, data);
}

// data: attack power
void torrentialRain(User * user, ID cardID, ID targetID, LO location = LO(), int data = 0)
{
	User* enemy = user->enemy;
	std::vector<ID> unitIDs = enemy->getUnitIDs(location);

	for (auto id : enemy->line[location - 3]) {
		if (enemy->getCardFromID(id)->line != LINE::WEATHER)	//filter weather cards
			unitIDs.push_back(id);
	}

	if (unitIDs.size() <= 0) return; //first attack

	// select one of unit cards randomly
	int randomIndex = util::getRandNumBetween(0, unitIDs.size() - 1);
	ID id = enemy->line[location - 3][randomIndex];
	attack(user, cardID, id, location, data);

	unitIDs.erase(std::remove(unitIDs.begin(), unitIDs.end(), id), unitIDs.end());

	if (unitIDs.size() <= 0) return; // second attack

	randomIndex = util::getRandNumBetween(0, unitIDs.size() - 1);
	id = enemy->line[location - 3][randomIndex];
	attack(user, cardID, id, location, data);
}

// data: attack power
void lacerate(User * user, ID cardID, ID targetID, LO location = LO(), int data = 0)
{
	std::vector<ID> unitIDs = user->enemy->getUnitIDs(location);

	for (auto id : unitIDs) {
			attack(user, cardID, id, location, data);
	}
}

/*
미안하지만 가운데 기준으로 5명
@ user
@ targetID
@ location
@ data
*/
void commandersHorn(User * user, ID cardID, ID targetID, LO location = LO(), int data = 0)
{
	std::vector<ID> unitIDs = user->getUnitIDs(location);
	auto pos = std::distance(unitIDs.begin(), find(unitIDs.begin(), unitIDs.end(), targetID));

	if (pos >= unitIDs.size()) //target card not found
		return;

	boost(user, cardID, unitIDs[pos], location, data);

	for (auto p = pos + 1; p <= pos + 2; p++) {
		if (p >= unitIDs.size()) //no card one the right side of the target card
			break;

		boost(user, cardID, unitIDs[p], location, data);
	}

	for (auto p = pos - 1; p >= pos - 2; p--) {
		if (p < 0) //no card one the left side of the target card
			return;

		boost(user, cardID, unitIDs[p], location, data);
	}
}

void bekkersTwistedMirror(User * user, ID cardID, ID targetID, LO location = LO(), int data = 0)
{
	ID highestID = user->getHighest();
	ID lowestID = user->getLowest();

	int changeValue = 0;

	// the higest unit is the user's
	if (user->getCardFromID(highestID) != nullptr) {
		changeValue = user->getCardFromID(highestID)->getStrength();
		if (changeValue > 10) changeValue = 10;
		damage(user, highestID, targetID, location, changeValue);
	} else {
		changeValue = user->enemy->getCardFromID(highestID)->getStrength();
		if (changeValue > 10) changeValue = 10;
		attack(user, cardID, highestID, location, changeValue);
	}

	// the lowest unit is the user's
	if (user->getCardFromID(lowestID) != nullptr)
		boost(user, cardID, lowestID, location, changeValue);
	else
		boost(user->enemy, cardID, lowestID, location, changeValue);
}

void geraltIgni(User * user, ID cardID, ID targetID, LO location = LO(), int data = 0)
{
	LO lo = user->findLine(cardID);
	int totalStr = 0;

	for (auto id : user->enemy->line[lo - 3]) {
		totalStr += user->enemy->getCardFromID(id)->getStrength();
	}

	if (totalStr < 25) return;

	// select all highest cards from enemy's line
	std::vector<ID> highestCardIDs;
	int max = 0;
	Card* card;
	std::vector<ID> line = user->enemy->line[lo - 3];

	for (auto id : line) {
		card = user->enemy->getCardFromID(id);
		//filter weather and event cards
		if (card->getStrength() > max && card->line != LINE::WEATHER && card->line != LINE::EVENT)
			max = card->getStrength();
	}
	for (auto id : line) {
		card = user->enemy->getCardFromID(id);
		if (card->getStrength() == max && card->line != LINE::WEATHER && card->line != LINE::EVENT)
			highestCardIDs.push_back(id);
	}

	// no unit card in the line
	if (highestCardIDs.size() <= 0) return;

	for (auto id : highestCardIDs)
		destroy(user->enemy, cardID, id, location, 0);
}

/*
TODO: 얘는 deploy skill도 아니고 그냥 skill도 아니고 특별 처리가 필요함 ㅡㅡ
@ user
@ cardID
*/
void roach(User * user, ID cardID, ID targetID, LO location = LO(), int data = 0)
{
	int randLineNum = util::getRandNumBetween(LO::LINE1, LO::LINE3);
	user->deployCard(LO(randLineNum), cardID);
}

/*
미안하지만 가운데 기준으로 3명
@ user
@ targetID
@ location
@ data
*/
void thunderboltPosition(User * user, ID cardID, ID targetID, LO location = LO(), int data = 0)
{
	std::vector<ID> unitIDs = user->getUnitIDs(location);
	auto pos = std::distance(unitIDs.begin(), find(unitIDs.begin(), unitIDs.end(), targetID));

	if (pos >= unitIDs.size()) //target card not found
		return;

	getArmor(user, cardID, unitIDs[pos], location, user->getCardFromID(cardID)->skillData);
	boost(user, cardID, unitIDs[pos], location, data);

	auto p = pos + 1;
	if (p < unitIDs.size()) { //there is a card one the right side of the target card
		getArmor(user, cardID, unitIDs[p], location, user->getCardFromID(cardID)->skillData);
		boost(user, cardID, unitIDs[p], location, data);
	}

	p = pos - 1;
	if (p < 0) //no card one the left side of the target card
		return;

	getArmor(user, cardID, unitIDs[p], location, user->getCardFromID(cardID)->skillData);
	boost(user, cardID, unitIDs[p], location, data);
}

void dagon(User * user, ID cardID, ID targetID, LO location, int data)
{
}

void foglet(User * user, ID cardID, ID targetID, LO location, int data)
{
}

void geels(User * user, ID cardID, ID targetID, LO location, int data)
{
}

void celaenoHarpy(User * user, ID cardID, ID targetID, LO location, int data)
{
}

void woodlandSpirit(User * user, ID cardID, ID targetID, LO location, int data)
{
}

void earthElemental(User * user, ID cardID, ID targetID, LO location, int data)
{
}

void croneWeavess(User * user, ID cardID, ID targetID, LO location, int data)
{
}

void croneWhispess(User * user, ID cardID, ID targetID, LO location, int data)
{
}

void croneBrewess(User * user, ID cardID, ID targetID, LO location, int data)
{
}

void archgriffin(User * user, ID cardID, ID targetID, LO location, int data)
{
}

void caranthir(User * user, ID cardID, ID targetID, LO location, int data)
{
}

void frightener(User * user, ID cardID, ID targetID, LO location, int data)
{
}

void unseenElder(User * user, ID cardID, ID targetID, LO location, int data)
{
}

void arachas(User * user, ID cardID, ID targetID, LO location, int data)
{
}

void vranWarrior(User * user, ID cardID, ID targetID, LO location, int data)
{
}

void arachasBehemoth(User * user, ID cardID, ID targetID, LO location, int data)
{
}

void wildHuntRider(User * user, ID cardID, ID targetID, LO location, int data)
{
}

void harpyEgg(User * user, ID cardID, ID targetID, LO location, int data)
{
}
