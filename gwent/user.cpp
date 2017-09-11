#include "user.h"
#include "skill.h"

extern SkillMap skillMap;
extern std::vector<CardBase*> cardCollection;
extern ID topOfDeck;

const int PROTECT_SHIELD = 100;

std::ostream& operator<<(std::ostream& os, const User* m)
{
	os << "===THESE ARE MY CARDS===" << std::endl;
	for (auto card : m->cardMap) {
		os << card.second << std::endl;
	}
	os << "========================" << std::endl;
	return os;
}

/* treat card */
void User::drawCard(int count)
{
	int cardNum, cardIndex;
	ID cardID;

	// for the skill of Geels
	if (topOfDeck != ID()) {
		insertInto(LO::HAND, topOfDeck);
		removeFrom(LO::DECK, topOfDeck);
		topOfDeck = ID();
		count--;
	}

	for (int j = 0; j < count; j++) {
		cardNum = deck.size();
		if (cardNum <= 0) return;
		cardIndex = util::getRandNumBetween(0, cardNum - 1);
		cardID = deck[cardIndex];
		insertInto(LO::HAND, cardID);
		removeFrom(LO::DECK, cardID);
	}
}

void User::discardCard(ID cardID)
{
	removeFrom(LO::HAND, cardID);
	insertInto(LO::DECK, cardID);
}

void User::deployCard(LO lo, ID cardID)
{
	Card* card = getCardFromID(cardID);
	// wrong location to deploy card
	if (!(lo == LO::LINE1 || lo == LO::LINE2 || lo == LO::LINE3))
		return;

	// wrong location to deploy card TODO: 그럼 에러 주고 다시 고르게 해야함
	if (card->line != LINE::WEATHER && card->line != LINE::ANY && card->line != LINE::EVENT
		&& (card->line != lo - 2))
		return;

	if (card->line == LINE::WEATHER) {	// deploy weather card on the enemy's filed
		removeFrom(LO::HAND, cardID);
		enemy->insertInto(lo, cardID);
	} else {
		removeFrom(LO::HAND, cardID);
		insertInto(lo, cardID);
	}

	//TODO: targetID랑 location 입력 받아야함. 지금 location은 카드가 놓아진 위치랑 같은곳
	useSkill(SKILLKIND::DEPLOY, cardID, ID(), lo);
}

void User::deployEventCard(ID cardID)
{
}

void User::banishCard(ID cardID) // TODO: lineWeather에 있는 카드는 추방이 안됨
{
	LO lo = findLine(cardID);
	removeFrom(lo, cardID);
}

void User::destroyCard(ID cardID)
{
	LO lo = findLine(cardID);

	// the card is not on field
	if (lo != LO::LINE1 && lo != LO::LINE2 && lo != LO::LINE3)
		return;

	// weather card
	if (getCardFromID(cardID) == nullptr || getCardFromID(cardID)->line == LINE::WEATHER) {
		removeFrom(lo, cardID);
		insertInto(LO::GRAVE_ENEMY, cardID);
		return;
	}

	// if the card is doomed then banish the card
	if (getCardFromID(cardID)->is_doomed) {
		banishCard(cardID);
		return;
	}

	removeFrom(lo, cardID);
	insertInto(LO::GRAVE, cardID);
}

Card* User::spawnCard(int no)
{
	CardBase* cb = nullptr;
	for (auto cardBase : cardCollection) {
		if ((*cardBase).no == no) {
			cb = cardBase;
			break;
		}
	}
	ID newID = util::getID();
	Card* newCard = new Card(cb, newID);
	cardMap[newID] = newCard;

	return newCard;
}

void User::removeAllCardFromLines()
{
	for (int i = 0; i < 3; i++) {
		for (auto cardID : line[i]) {
			insertInto(LO::GRAVE, cardID);
		}
		line[i].clear();
	}
}

bool User::isAt(LO lo, ID cardID)
{
	std::vector<int> v;
	switch (lo) {
	case LO::DECK:
		v = deck; break;
	case LO::HAND:
		v = hand; break;
	case LO::GRAVE:
		v = grave; break;
	case LO::LINE1:
		v = line[0]; break;
	case LO::LINE2:
		v = line[1]; break;
	case LO::LINE3:
		v = line[2]; break;
	case LO::GRAVE_ENEMY:
		v = enemy->grave; break;
	}

	if (std::find(v.begin(), v.end(), cardID) != v.end())
		return true;

	return false;
}

void User::removeFrom(LO lo, ID cardID)
{
	std::vector<int>* v = { 0 };
	switch (lo) {
	case LO::DECK:
		v = &deck; break;
	case LO::HAND:
		v = &hand; break;
	case LO::GRAVE:
		v = &grave; break;
	case LO::LINE1:
		v = &line[0]; break;
	case LO::LINE2:
		v = &line[1]; break;
	case LO::LINE3:
		v = &line[2]; break;
	case LO::GRAVE_ENEMY:
		v = &enemy->grave;
	}

	// not exist
	if (!isAt(lo, cardID)) return;

	// calculate score if the card was on lines
	if (lo == LO::LINE1 || lo == LO::LINE2 || lo == LO::LINE3) {
		if (getCardFromID(cardID) == nullptr) {}	// weather card
		else { changeRoundScoreForLine(lo, -getCardFromID(cardID)->strength); }	// calculate score if the card is going to be deployed
	}

	// remove the element from vector
	(*v).erase(std::remove((*v).begin(), (*v).end(), cardID), (*v).end());
}

void User::insertInto(LO lo, ID cardID)
{
	std::vector<int>* v = { 0 };
	switch (lo) {
	case LO::DECK:
		v = &deck; break;
	case LO::HAND:
		v = &hand; break;
	case LO::GRAVE:
		v = &grave; break;
	case LO::LINE1:
		v = &line[0]; break;
	case LO::LINE2:
		v = &line[1]; break;
	case LO::LINE3:
		v = &line[2]; break;
	case LO::GRAVE_ENEMY:
		v = &enemy->grave;
	}

	// already exist
	if (isAt(lo, cardID)) return;

	if (lo == LO::LINE1 || lo == LO::LINE2 || lo == LO::LINE3) {
		if (getCardFromID(cardID) == nullptr) {}	// weather card
		else { changeRoundScoreForLine(lo, getCardFromID(cardID)->strength); }	// calculate score if the card is going to be deployed
	}

	// insert the element into vector
	(*v).push_back(cardID);
}

LO User::findLine(ID cardID)
{
	LO lo;
	for (int i = LO::LINE1; i <= LO::LINE3; i++) {
		if (isAt(LO(i), cardID)) {
			lo = LO(i);
			return lo;
		}
	}
	return LO();
}

/* treat private variables */
bool User::getIsGiveUp()
{
	return is_giveUp;
}

void User::setIsGiveUp(bool v)
{
	is_giveUp = v;
}

int User::getRoundScore()
{
	return score[round - 1];
}

//void User::changeRoundScore(int v)
//{
//	score[round - 1] += v;
//}

void User::changeRoundScoreForLine(LO lo, int v)
{
	scoreForLine[round - 1][lo - 3] += v; // LINE1 = 3
	score[round - 1] += v;
}

void User::setRound(int r)
{
	round = r;
}

/* others */
void User::myTurn()
{
	// both of users gave up
	if (getIsGiveUp() == true && enemy->getIsGiveUp() == true) {
		//emit signal: 라운드 종료 slot: Game.finishRound
		return;
	}

	if (getIsGiveUp() == true) {
		//emit signal: 턴 넘기기 slot: Game.nextTurn
		return;
	}

	drawCard(1);

	// 날씨 효과
	// timer가 돌아갈 동안 카드를 선택해서 내기 deployCard
	// 만약 시간이 다 됐으면 hand에서 카드 무작위로 한장 버리기
	// 그리고 턴을 넘기기 emit signal: 턴 넘기기 slot: Game.nextTurn
}

void User::useSkill(SKILLKIND kind, ID cardID, ID targetID, LO location)
{
	Card* card = getCardFromID(cardID);
	skill f = nullptr;
	int data = 0;

	if (card == nullptr)
		card = enemy->getCardFromID(cardID);

	switch (kind) {
	case SKILLKIND::NORMAL: {
		f = skillMap.getSkill(SKILL(card->skill)); 
		data = card->skillData;
		break;
	}
	case SKILLKIND::DEPLOY: {
		f = skillMap.getSkill(SKILL(card->deploySkill));
		data = card->deploySkillData;
		break;
	}
	case SKILLKIND::DEATHWISH: {
		f = skillMap.getSkill(SKILL(card->deathWishSkill));
		data = card->deathWishSkillData;
		break;
	}
	}

	if (f == nullptr) return;			//no skill

	if (card == nullptr || card->line == LINE::WEATHER)
		f(this->enemy, cardID, targetID, location, data);
	else
		f(this, cardID, targetID, location, data);

	if (card->line == LINE::EVENT) {	//remove the event card
		removeFrom(findLine(cardID), cardID);
		insertInto(LO::GRAVE, cardID);
	}
}

void User::changeStrength(ID cardID, int v)
{
	Card* card = getCardFromID(cardID);

	if (card == nullptr) return;

	// calculate armor
	int armor = card->getArmor();
	if (armor <= 0) {}
	else if (armor >= v) {
		card->changeArmor(-v);
		v = 0;
	} else if (armor < v) {
		card->changeArmor(-armor);
		v = v - armor;
	} else if (armor == PROTECT_SHIELD) {
		card->changeArmor(-PROTECT_SHIELD);
		v = 0;
	}

	// if the unit is dead
	int prev_str = card->getStrength();
	int is_dead = card->changeStrength(v);

	if (is_dead) {
		changeRoundScoreForLine(findLine(cardID), -prev_str);
		destroyCard(cardID);
		return;
	}

	changeRoundScoreForLine(findLine(cardID), v);
}

ID User::getHighest()
{
	std::vector<ID> highestCardIDs;
	std::vector<ID> _line;
	int max = 0;
	Card* card;

	for (int lo = LO::LINE1; lo < LO::LINE3; lo++) {
		_line = getUnitIDs(LO(lo));
		for (auto id : _line) {
			card = getCardFromID(id);
			//filter weather and event cards
			if (card->getStrength() > max && card->line != LINE::WEATHER && card->line != LINE::EVENT)
				max = card->getStrength();
		}

		_line = enemy->getUnitIDs(LO(lo));
		for (auto id : _line) {
			card = enemy->getCardFromID(id);
			//filter weather and event cards
			if (card->getStrength() > max && card->line != LINE::WEATHER && card->line != LINE::EVENT)
				max = card->getStrength();
		}
	}

	for (int lo = LO::LINE1; lo < LO::LINE3; lo++) {
		_line = getUnitIDs(LO(lo));
		for (auto id : _line) {
			card = getCardFromID(id);
			if (card->getStrength() == max && card->line != LINE::WEATHER && card->line != LINE::EVENT)
				highestCardIDs.push_back(id);
		}

		_line = enemy->getUnitIDs(LO(lo));
		for (auto id : _line) {
			card = enemy->getCardFromID(id);
			if (card->getStrength() == max && card->line != LINE::WEATHER && card->line != LINE::EVENT)
				highestCardIDs.push_back(id);
		}
	}

	// no target card
	if (highestCardIDs.size() <= 0) return ID();

	// select one of highest cards randomly
	int randomIndex = util::getRandNumBetween(0, highestCardIDs.size() - 1);
	return highestCardIDs[randomIndex];
}

ID User::getLowest()
{
	std::vector<ID> lowestCardIDs;
	std::vector<ID> _line;
	int min = 1000;
	Card* card;

	for (int lo = LO::LINE1; lo < LO::LINE3; lo++) {
		_line = getUnitIDs(LO(lo));
		for (auto id : _line) {
			card = getCardFromID(id);
			//filter weather and event cards
			if (card->getStrength() < min && card->line != LINE::WEATHER && card->line != LINE::EVENT)
				min = card->getStrength();
		}

		_line = enemy->getUnitIDs(LO(lo));
		for (auto id : _line) {
			card = enemy->getCardFromID(id);
			//filter weather and event cards
			if (card->getStrength() < min && card->line != LINE::WEATHER && card->line != LINE::EVENT)
				min = card->getStrength();
		}
	}

	for (int lo = LO::LINE1; lo < LO::LINE3; lo++) {
		_line = getUnitIDs(LO(lo));
		for (auto id : _line) {
			card = getCardFromID(id);
			if (card->getStrength() == min && card->line != LINE::WEATHER && card->line != LINE::EVENT)
				lowestCardIDs.push_back(id);
		}

		_line = enemy->getUnitIDs(LO(lo));
		for (auto id : _line) {
			card = enemy->getCardFromID(id);
			if (card->getStrength() == min && card->line != LINE::WEATHER && card->line != LINE::EVENT)
				lowestCardIDs.push_back(id);
		}
	}

	// no target card
	if (lowestCardIDs.size() <= 0) return ID();

	// select one of highest cards randomly
	int randomIndex = util::getRandNumBetween(0, lowestCardIDs.size() - 1);
	return lowestCardIDs[randomIndex];
}

ID User::getHighestFromLine(LO lo)
{
	std::vector<ID> highestCardIDs;
	std::vector<ID> unitIDs = getUnitIDs(lo);
	int max = 0;
	Card* card;

	for (auto id : unitIDs) {
		card = getCardFromID(id);
		//filter weather and event cards
		if (card->getStrength() > max && card->line != LINE::WEATHER && card->line != LINE::EVENT)
			max = card->getStrength();
	}
	for (auto id : unitIDs) {
		card =getCardFromID(id);
		if (card->getStrength() == max && card->line != LINE::WEATHER && card->line != LINE::EVENT)
			highestCardIDs.push_back(id);
	}

	// no unit card in the line
	if (highestCardIDs.size() <= 0) return ID();

	// select one of lowest cards randomly
	int randomIndex = util::getRandNumBetween(0, highestCardIDs.size() - 1);
	return highestCardIDs[randomIndex];
}

ID User::getLowestFromLine(LO lo)
{
	std::vector<ID> lowestCardIDs;
	std::vector<ID> unitIDs = getUnitIDs(lo);
	int min = 1000;
	Card* card;

	for (auto id : unitIDs) {
		card = getCardFromID(id);
		//filter weather and event cards
		if (card->getStrength() < min && card->line != LINE::WEATHER && card->line != LINE::EVENT)
			min = card->getStrength();
	}
	for (auto id : unitIDs) {
		card = getCardFromID(id);
		if (card->getStrength() == min && card->line != LINE::WEATHER && card->line != LINE::EVENT)
			lowestCardIDs.push_back(id);
	}

	// no unit card in the line
	if (lowestCardIDs.size() <= 0) return ID();

	// select one of lowest cards randomly
	int randomIndex = util::getRandNumBetween(0, lowestCardIDs.size() - 1);
	return lowestCardIDs[randomIndex];
}

Card * User::getCardFromID(ID cardID)
{
	return cardMap[cardID];
}

ID User::getWeatherCardIDFromLine(LO lo)
{
	for (auto id : line[lo - 3]) {
		if (getCardFromID(id) == nullptr || getCardFromID(id)->line == LINE::WEATHER) { // 상대방 카드라 내 카드 정보에 없음
			return id;
		}
	}
	return ID();
}

std::vector<ID> User::getUnitIDs(LO lo)
{
	std::vector<ID> unitIDs = std::vector<ID>();

	for (auto id : line[lo - 3]) {
		if (getCardFromID(id) != nullptr && getCardFromID(id)->line != LINE::WEATHER
			&& getCardFromID(id)->line != LINE::EVENT)	//filter weather and event cards
			unitIDs.push_back(id);
	}

	return unitIDs;
}
