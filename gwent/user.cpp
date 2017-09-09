#include "user.h"
#include "skill.h"

extern SkillMap skillMap;
extern std::vector<CardBase*> cardCollection;

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
	for (int j = 0; j < count; j++) {
		cardNum = deck.size();
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

	// wrong location to deploy card
	if (card->line != LINE::ANY && card->line != LINE::WEATHER && card->line != LINE::EVENT
		&& (card->line != lo - 2))
		return;

	removeFrom(LO::HAND, cardID);
	insertInto(lo, cardID);

	//targetID 입력 받아야함
	useSkill(SKILLKIND::DEPLOY, cardID, 0, lo);
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

	if (lo != LO::LINE1 && lo != LO::LINE2 && lo != LO::LINE3) // the card is not on field
		return;

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

	// calculate score if the card was on lines
	if (lo == LO::LINE1 || lo == LO::LINE2 || lo == LO::LINE3)
		changeRoundScoreForLine(lo, -getCardFromID(cardID)->getStrength());

	// remove the element from vector
	if (isAt(lo, cardID))
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

	// calculate score if the card is going to be deployed
	if (lo == LO::LINE1 || lo == LO::LINE2 || lo == LO::LINE3)
		changeRoundScoreForLine(lo, getCardFromID(cardID)->strength);

	// insert the element into vector
	if (!isAt(lo, cardID))
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

	f(this, cardID, targetID, location, data);

	if (card->line == LINE::EVENT) {	//remove the event card
		removeFrom(findLine(cardID), cardID);
		insertInto(LO::GRAVE, cardID);
	}
}

void User::changeStrength(ID cardID, int v)
{
	Card* card = getCardFromID(cardID);

	int prev_str = card->getStrength();
	int is_dead = card->changeStrength(v);

	if (is_dead) {
		destroyCard(cardID);
		changeRoundScoreForLine(findLine(cardID), -prev_str);
		return;
	}

	changeRoundScoreForLine(findLine(cardID), v);
}

ID User::getHighest()
{
	ID highestCardID;
	int max = 0;
	for (int i = 0; i <= 3; i++) {
		for (auto id : line[i]) {
			Card* card = getCardFromID(id);
			if (card->getStrength() > max) {
				max = card->getStrength();
				highestCardID = id;
			} else if (card->getStrength() < max) {}
			else {
				if (util::getRandNumBetween(0, 1)) {	// randomly select one
					max = card->getStrength();
					highestCardID = id;
				}
			}
		}
	}
	return highestCardID;
}

ID User::getLowest()
{
	ID lowestCardID;
	int min = 1000;
	for (int i = 0; i <= 3; i++) {
		for (auto id : line[i]) {
			Card* card = getCardFromID(id);
			if (card->getStrength() < min) {
				min = card->getStrength();
				lowestCardID = id;
			}
			else if (card->getStrength() > min) {}
			else {
				if (util::getRandNumBetween(0, 1)) {	// randomly select one
					min = card->getStrength();
					lowestCardID = id;
				}
			}
		}
	}
	return lowestCardID;
}

Card * User::getCardFromID(ID cardID)
{
	return cardMap[cardID];
}

ID User::getWeatherCardIDFromLine(LO lo)
{
	for (auto id : line[lo - 3]) {
		if (getCardFromID(id)->line == LINE::WEATHER) {
			return id;
		}
	}
	return 0;
}
