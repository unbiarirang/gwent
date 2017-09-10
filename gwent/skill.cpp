#include "skill.h"
#include "enum.h"

SkillMap skillMap;	// for common use to every source file
ID topOfDeck = ID(); // for the skill of Geels

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

/*
@ user
@ location
@ data : target card no
*/
void spawn(User* user, ID cardID, ID targetID = 0, LO location = LO(), int data = 0) {
	Card* newCard = user->spawnCard(data);
	user->insertInto(location, newCard->getID());

	//TODO: targetID랑 location 입력 받아야함
	user->useSkill(SKILLKIND::DEPLOY, newCard->getID(), targetID, location);
}

/*
@ user
@ targetID
@ data
*/
void damage(User* user, ID cardID, ID targetID = 0, LO location = LO(), int data = 0)
{
	user->changeStrength(targetID, -data);
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
	if (user->enemy->getCardFromID(targetID) != nullptr) // not weather card
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

/*
@ user
@ location
*/
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
				user->deployCard(location, id);
				return;
			}
		}
	}
}

/*
@ user
@ location
@ data : target card no
*/
void spawnWeather(User * user, ID cardID, ID targetID, LO location, int data)
{
	Card* newCard = user->enemy->spawnCard(data);
	user->enemy->insertInto(location, newCard->getID());
}

/*
@ user
@ location
@ data: 0 or 1 (clear skies or rally)
*/
void firstLight(User * user, ID cardID, ID targetID, LO location = LO(), int data = 0)
{
	// clear skies
	if (data == 0) {
		for (int i = LO::LINE1; i <= LO::LINE3; i++) {
			removeWeather(user, cardID, targetID, location, i);
		}
		return;
	}

	location = LO::LINE1; // FIXME: 입력 받아야함
	// rally
	rally(user, cardID, targetID, location, data);
}

/*
@ user
@ location
@ data : attack power
*/
void bitingFrost(User * user, ID cardID, ID targetID, LO location = LO(), int data = 0)
{
	ID lowestID = user->getLowestFromLine(location);

	damage(user, cardID, lowestID, location, data);
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

/*
@ user
*/
void bekkersTwistedMirror(User * user, ID cardID, ID targetID, LO location = LO(), int data = 0)
{
	ID highestID = user->getHighest();
	ID lowestID = user->getLowest();

	int changeValue = 0;

	// the higest unit is the user's
	if (user->getCardFromID(highestID) != nullptr) {
		changeValue = user->getCardFromID(highestID)->getStrength();
		if (changeValue > 10) changeValue = 10;
		damage(user, cardID, highestID, location, changeValue);
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

/*
@ user
@ cardID
*/
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

/*
@ user
@ location
@ data : 22:bitingFrost, 23:impenetrableFog, 24:torrentialRain
*/
void dagon(User * user, ID cardID, ID targetID, LO location, int data)
{
	data = 22; // FIXME: 날씨 배치할 location이랑 data 받아야하는데 어떻게 받을지 고민
	spawn(user->enemy, cardID, targetID, location, data);
}

/*
@ user
@ cardID
*/
void foglet(User * user, ID cardID, ID targetID, LO location, int data)
{
	User* enemy = user->enemy;
	bool is_fog = false;

	//whether there is fog on the enemy's line
	for (int i = LO::LINE1; i <= LO::LINE3; i++) {
		Card* card = enemy->getCardFromID(enemy->getWeatherCardIDFromLine(LO(i)));
		if (card != nullptr) {
			if (card->no == 23) {  //impenetrableFog
				is_fog = true;
				break;
			}
		}
	}

	if (!is_fog) return;

	//look up the deck first
	for (auto id : user->deck) {
		if (user->getCardFromID(id)->no == 23) {
			user->deployCard(user->findLine(cardID), id);
			return;
		}
	}

	//then look up the grave
	for (auto id : user->grave) {
		if (user->getCardFromID(id)->no == 23) {
			user->deployCard(user->findLine(cardID), id);
			return;
		}
	}
}

void geels(User * user, ID cardID, ID targetID, LO location, int data)
{
	std::vector<ID> silverIDs = std::vector<ID>();
	for (auto id : user->deck) {
		if (user->getCardFromID(id)->type == TYPE::SILVER) {
			silverIDs.push_back(id);
		}
	}

	std::vector<ID> goldIDs = std::vector<ID>();
	for (auto id : user->deck) {
		if (user->getCardFromID(id)->type == TYPE::GOLD) {
			goldIDs.push_back(id);
		}
	}

	int cardNum, cardIndex;
	ID silverCardID = ID();

	if (silverIDs.size() != 0) {
		cardNum = silverIDs.size();
		cardIndex = util::getRandNumBetween(0, cardNum - 1);
		silverCardID = silverIDs[cardIndex];

		user->insertInto(LO::HAND, silverCardID);
		user->removeFrom(LO::DECK, silverCardID);
	}

	ID goldCardID = ID();
	if (goldIDs.size() != 0) {
		cardNum = goldIDs.size();
		cardIndex = util::getRandNumBetween(0, cardNum - 1);
		goldCardID = goldIDs[cardIndex];

		user->insertInto(LO::HAND, goldCardID);
		user->removeFrom(LO::DECK, goldCardID);
	}

	// TODO:여기서 데이터를 입력받아야함. 실버카드를 고를지 골드카드를 고를지
	// TODO: 어디다가 둘지도 받아야함 location
	data = TYPE::SILVER;
	LO lo = LO::LINE1;

	if (data == TYPE::SILVER && silverCardID != ID()) {
		user->deployCard(lo, silverCardID);
		user->discardCard(goldCardID);
		topOfDeck = goldCardID;
	} else if (data == TYPE::GOLD && goldCardID != ID()) {
		user->deployCard(lo, goldCardID);
		user->discardCard(silverCardID);
		topOfDeck = silverCardID;
	}
}

/*
@ user
@ data: spawn card no (Harpy Egg ID)
*/
void celaenoHarpy(User * user, ID cardID, ID targetID, LO location, int data)
{
	spawn(user, cardID, targetID, user->findLine(cardID), data);
	spawn(user, cardID, targetID, user->findLine(cardID), data);
}

/*
@ user
@ cardID
@ data : target card no
*/
void woodlandSpirit(User * user, ID cardID, ID targetID, LO location, int data)
{
	spawn(user, cardID, targetID, user->findLine(cardID), data);
	spawn(user, cardID, targetID, user->findLine(cardID), data);
	spawn(user, cardID, targetID, user->findLine(cardID), data);
	spawn(user->enemy, cardID, targetID, user->findLine(cardID), 23); // spawn fog
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
	// TODO: 하피 해츨링 아직 json에 추가 안함
	spawn(user, cardID, targetID, user->findLine(cardID), 31);
}
