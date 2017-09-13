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
	skillMap.setSkill(SKILL::THUNDERBOLTPOTION, thunderboltPotion);

	skillMap.setSkill(SKILL::DAGON, dagon);
	skillMap.setSkill(SKILL::FOGLET, foglet);
	skillMap.setSkill(SKILL::GEELS, geels);
	skillMap.setSkill(SKILL::CELAENOHARPY, celaenoHarpy);
	skillMap.setSkill(SKILL::WOODLANDSPIRIT, woodlandSpirit);
	skillMap.setSkill(SKILL::EARTHELEMENTAL, earthElemental);
	skillMap.setSkill(SKILL::CRONE, crone);
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

/*
@ user
@ targetID
*/
void consume(User* user, ID cardID, ID targetID = 0, LO location = LO(), int data = 0) {
	Card* targetCard = user->getCardFromID(targetID);

	user->changeStrength(cardID, targetCard->getStrength());	// boost the card
	user->destroyCard(targetID);				// destroy the target card
}

/*
@ user
@ location
@ data : target card no
*/
void spawn(User* user, ID cardID, ID targetID = 0, LO location = LO(), int data = 0) {
    if (location == LO()) return;

	Card* newCard = user->spawnCard(data);

	if (newCard->line == LINE::WEATHER)
		user->enemy->insertInto(location, newCard->getID());
	else
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
@ cardID
@ data
*/
void getArmor(User* user, ID cardID, ID targetID = 0, LO location = LO(), int data = 0)
{
	Card* card = user->getCardFromID(cardID);
	card->changeArmor(data);
}

/*
손에있는거 우선으로 손이나 덱에 있는 카드 한장 소환 (발동카드 옆에)
@ user
@ location : 소환이 라인을 고를 수 있는 거라면 필요함
@ data
*/
void summon(User* user, ID cardID, ID targetID = 0, LO location = LO(), int data = 0)
{
    if (location == LO()) return;

	int summonCardNo = data;
	ID summonID = ID();
	LO lo;

	for (auto id : user->deck) {
		if (user->getCardFromID(id)->no == data) {
			summonID = id;
			lo = LO::DECK;
			break;
		}
	}

	for (auto id : user->hand) {
		if (user->getCardFromID(id)->no == data) {
			summonID = id;
			lo = LO::HAND;
			break;
		}
	}

	if (summonID == ID()) return;

	user->removeFrom(lo, summonID);
	user->insertInto(location, summonID);

	// targetID와 location 입력 필요 (필요하다면)
	user->useSkill(SKILLKIND::DEPLOY, summonID, targetID, location);
}

// data: damage count
void attack(User* user, ID cardID, ID targetID = 0, LO location = LO(), int data = 0)
{
	if (user->enemy->getCardFromID(targetID) != nullptr) // not weather card
		user->enemy->changeStrength(targetID, -data);
}

/*
@ user
@ targetID
*/
void boost(User* user, ID cardID, ID targetID = 0, LO location = LO(), int data = 0)
{
	user->changeStrength(targetID, data);
}

/*
@ user
@ location
*/
void removeWeather(User* user, ID cardID, ID targetID = 0, LO location = LO(), int data = 0)
{
	ID weatherCardID = user->getWeatherCardIDFromLine(location);
	user->destroyCard(weatherCardID);
}

/*
from my grave to enemy's grave
@ user
@ targetID
*/
void moveToEnemyGrave(User* user, ID cardID, ID targetID = 0, LO location = LO(), int data = 0)
{
	user->removeFrom(LO::GRAVE, targetID);
	user->insertInto(LO::GRAVE_ENEMY, targetID);
}

/*
@ user
@ data
*/
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
    ID lowestID = user->enemy->getLowestFromLine(location);
    if (lowestID == ID()) return;

    attack(user, cardID, lowestID, location, data);
}

// data: attack power
void impenetrableFog(User * user, ID cardID, ID targetID, LO location = LO(), int data = 0)
{
	ID highestID = user->enemy->getHighestFromLine(location);
    if (highestID == ID()) return;
	attack(user, cardID, highestID, location, data);
}

// data: attack power
void torrentialRain(User * user, ID cardID, ID targetID, LO location = LO(), int data = 0)
{
	User* enemy = user->enemy;
	std::vector<ID> unitIDs = enemy->getUnitIDs(location);

//	for (auto id : unitIDs) {
//		if (enemy->getCardFromID(id)->line != LINE::WEATHER)	//filter weather cards
//			unitIDs.push_back(id);
//	}

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

    for (auto id : unitIDs)
        attack(user, cardID, id, location, data);
}

/*
어차피 최대 다섯명임
@ user
@ targetID
@ location
@ data
*/
void commandersHorn(User * user, ID cardID, ID targetID, LO location = LO(), int data = 0)
{
    std::vector<ID> unitIDs = user->getUnitIDs(location);

    for (auto id : unitIDs)
        boost(user, cardID, id, location, data);
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
    if (!user->isAt(LO::DECK, cardID)) return;

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
void thunderboltPotion(User * user, ID cardID, ID targetID, LO location = LO(), int data = 0)
{
	std::vector<ID> unitIDs = user->getUnitIDs(location);
	auto pos = std::distance(unitIDs.begin(), find(unitIDs.begin(), unitIDs.end(), targetID));

	if (pos >= unitIDs.size()) //target card not found
		return;

	getArmor(user, unitIDs[pos], targetID, location, user->getCardFromID(cardID)->skillData);
	boost(user, cardID, unitIDs[pos], location, data);

	auto p = pos + 1;
	if (p < unitIDs.size()) { //there is a card one the right side of the target card
		getArmor(user, unitIDs[p], targetID, location, user->getCardFromID(cardID)->skillData);
		boost(user, cardID, unitIDs[p], location, data);
	}

	p = pos - 1;
	if (p < 0) //no card one the left side of the target card
		return;

	getArmor(user, unitIDs[p], targetID, location, user->getCardFromID(cardID)->skillData);
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
	LO lo = LO::LINE1;
	spawn(user, cardID, targetID, lo, data);
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
    spawn(user, cardID, targetID, LO::LINE1, data);
    spawn(user, cardID, targetID, LO::LINE1, data);
    spawn(user, cardID, targetID, LO::LINE1, data);
    spawn(user, cardID, targetID, location, user->getCardFromID(cardID)->skillData); // spawn fog
}

void earthElemental(User * user, ID cardID, ID targetID, LO location, int data)
{
	spawn(user, cardID, targetID, user->findLine(cardID), data);
	spawn(user, cardID, targetID, user->findLine(cardID), data);
	getArmor(user, cardID, targetID, location, 100); // protect shield
}

void crone(User * user, ID cardID, ID targetID, LO location, int data)
{
	summon(user, cardID, targetID, user->findLine(cardID), data);
	summon(user, cardID, targetID, user->findLine(cardID), user->getCardFromID(cardID)->skillData);
}

void archgriffin(User * user, ID cardID, ID targetID, LO location, int data)
{
	LO lo = LO::LINE1; // FIXME: 라인 입력 받아야 함
	removeWeather(user, cardID, targetID, lo, data);

	std::vector<ID> bronzeIDs = std::vector<ID>();
	std::vector<ID> unitIDs = user->enemy->getUnitIDs(LO::GRAVE);
	for (auto id : unitIDs) {
		if (user->enemy->getCardFromID(id)->type == TYPE::BRONZE)
			bronzeIDs.push_back(id);
	}

	if (bronzeIDs.size() <= 0) return;

	int randIndex = util::getRandNumBetween(0, bronzeIDs.size() - 1);
	targetID = bronzeIDs[randIndex];
	moveToEnemyGrave(user->enemy, cardID, targetID, location, data);
}

/*
@ user
@ targetID
@ location
@ data
*/
void caranthir(User * user, ID cardID, ID targetID, LO location, int data)
{
	// FIXME: targetID, location 받아야함
	targetID = 1;
	user->enemy->removeFrom(user->enemy->findLine(targetID), targetID);
	user->enemy->insertInto(location, targetID);
	spawn(user, cardID, targetID, location, data);
}

/*
@ user
@ targetID
*/
void frightener(User * user, ID cardID, ID targetID, LO location, int data)
{
	// FIXME: targetID 받아야함
	targetID = 1;
	user->removeFrom(user->findLine(targetID), targetID);
	user->insertInto(location, targetID);
	drawCard(user, cardID, targetID, location, data);
}

/*
FIXME: 증폭으로 했지 강화로 안했음. 강화 뭔지 모르겠음
@ user
@ cardID
@ targetID
*/
void unseenElder(User * user, ID cardID, ID targetID, LO location, int data)
{
	if (user->getCardFromID(cardID)->skillData <= 0) return;

	for (int i = 0; i < 3; i++) {
		int unitCount = 0;
		for (int j = 0; j < 3; j++)
			unitCount += user->line[j].size();
		if (unitCount <= 1) return;	// no unit except the unseenElder

		// FIXME: targetID 받아야함
		targetID = i + 1;
		consume(user, cardID, targetID, location, data);
	}
	user->getCardFromID(cardID)->skillData -= 1;
}

/*
@ user
@ data : summon target unit no
*/
void arachas(User * user, ID cardID, ID targetID, LO location, int data)
{
	for (auto id : user->deck) {
		if (user->getCardFromID(id)->no == data) {
			user->removeFrom(LO::DECK, id);
			user->insertInto(location, id);
		}
	}
}

void vranWarrior(User * user, ID cardID, ID targetID, LO location, int data)
{
	if (data != 0) {
		user->getCardFromID(cardID)->skillData -= 1;
		return; // repeat per two turns
	}

	std::vector<ID> unitIDs = user->getUnitIDs(location);
	auto pos = std::distance(unitIDs.begin(), find(unitIDs.begin(), unitIDs.end(), cardID));

	if (pos + 1 <= unitIDs.size()) // vranWarrior is at the end of the line (right side)
		return;

	targetID = unitIDs[pos + 1];
	consume(user, cardID, targetID, location, data);

	user->getCardFromID(cardID)->skillData = 1;
}

/*
normal skill
@ user
@ data : damage
*/
void arachasBehemoth(User * user, ID cardID, ID targetID, LO location, int data)
{
	// TODO: arachas hatchling 아직 json에 추가 안함
	spawn(user, cardID, targetID, LO(util::getRandNumBetween(LO::LINE1, LO::LINE3)), 2);
	
	// receive damage but ignore armor
	Card* card = user->getCardFromID(cardID);

	if (card == nullptr) return;

	// if the unit is dead
	int prev_str = card->getStrength();
	int is_dead = card->changeStrength(-data);

	if (is_dead) {
        //user->changeRoundScoreForLine(location, -prev_str);
        card->setStrength(prev_str);
		user->destroyCard(cardID);
		return;
	}

	user->changeRoundScoreForLine(location, -data);
}

/*
@ user
@ location
@ data : boost power target id
*/
void wildHuntRider(User * user, ID cardID, ID targetID, LO location, int data)
{
	// TODO: location 받아야함
	ID weatherID = user->enemy->getWeatherCardIDFromLine(location);

	if (weatherID == ID() || weatherID != data) return;

	user->getCardFromID(weatherID)->skillData += 1;
}

void harpyEgg(User * user, ID cardID, ID targetID, LO location, int data)
{
	// TODO: 하피 해츨링 아직 json에 추가 안함
	spawn(user, cardID, targetID, location, 31);
}
