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
	Card* card = cardMap[cardID];
	// wrong location to deploy card
	if (!(lo == LO::LINE1 || lo == LO::LINE2 || lo == LO::LINE3))
		return;

	// wrong location to deploy card
	if ((card->line != LINE::ANY) && (card->line != lo - 2))
		return;

	removeFrom(LO::HAND, cardID);
	insertInto(lo, cardID);
}

void User::deployEventCard(ID cardID)
{
}

void User::banishCard(ID cardID) // TODO: lineWeather�� �ִ� ī��� �߹��� �ȵ�
{
	LO lo = findLine(cardID);
	removeFrom(lo, cardID);
}

void User::destroyCard(ID cardID)
{
	LO lo = findLine(cardID);

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
	if (lo == LO::LINE1 || lo == LO::LINE2 || lo == LO::LINE3) {
		changeRoundScore(-cardMap[cardID]->strength);
		changeRoundScoreForLine(lo, -cardMap[cardID]->strength);
	}

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
	if (lo == LO::LINE1 || lo == LO::LINE2 || lo == LO::LINE3) {
		changeRoundScore(cardMap[cardID]->strength);
		changeRoundScoreForLine(lo, cardMap[cardID]->strength);
	}

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

void User::changeRoundScore(int v)
{
	score[round - 1] = score[round - 1] + v;
}

void User::changeRoundScoreForLine(LO lo, int v)
{
	scoreForLine[round - 1][lo - 3] = v; // LINE1 = 3
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
		//emit signal: ���� ���� slot: Game.finishRound
		return;
	}

	if (getIsGiveUp() == true) {
		//emit signal: �� �ѱ�� slot: Game.nextTurn
		return;
	}

	drawCard(1);

	// timer�� ���ư� ���� ī�带 �����ؼ� ���� deployCard
	// ���� �ð��� �� ������ hand���� ī�� �������� ���� ������
	// �׸��� ���� �ѱ�� emit signal: �� �ѱ�� slot: Game.nextTurn
}

void User::useSkill(SKILLKIND kind, ID cardID, int value)
{
	Card* card = getCardFromID(cardID);
	skill f = nullptr;

	switch (kind) {
	case SKILLKIND::NORMAL:
		f = skillMap.getSkill(SKILL(card->skill)); break;
	case SKILLKIND::DEPLOY:
		f = skillMap.getSkill(SKILL(card->deploySkill)); break;
	case SKILLKIND::DEATHWISH:
		f = skillMap.getSkill(SKILL(card->deathWishSkill)); break;
	}

	f(this, card, value);
}

ID User::getHighest()
{
	ID highestCardID;
	int max = 0;
	for (int i = 0; i <= 3; i++) {
		for (auto id : line[i]) {
			if (cardMap[id]->getStrength() > max) {
				max = cardMap[id]->getStrength();
				highestCardID = id;
			} else if (cardMap[id]->getStrength() < max) {}
			else {
				if (util::getRandNumBetween(0, 1)) {	// randomly select one
					max = cardMap[id]->getStrength();
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
			if (cardMap[id]->getStrength() < min) {
				min = cardMap[id]->getStrength();
				lowestCardID = id;
			}
			else if (cardMap[id]->getStrength() > min) {}
			else {
				if (util::getRandNumBetween(0, 1)) {	// randomly select one
					min = cardMap[id]->getStrength();
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
