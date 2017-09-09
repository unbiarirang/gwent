#include "user.h"
#include "skill.h"

extern SkillMap skillMap;

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

void User::banishCard(ID cardID) // TODO: lineWeather에 있는 카드는 추방이 안됨
{
	for (int i = LO::DECK; i < LO::LINE3; i++) {
		if (isAt(LO(i), cardID)) {
			removeFrom(LO(i), cardID);
			break;
		}
	}
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
		addRoundScore(-cardMap[cardID]->strength);
		addRoundScoreForLine(lo, -cardMap[cardID]->strength);
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
		addRoundScore(cardMap[cardID]->strength);
		addRoundScoreForLine(lo, cardMap[cardID]->strength);
	}

	// insert the element into vector
	if (!isAt(lo, cardID))
		(*v).push_back(cardID);
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

void User::addRoundScore(int v)
{
	score[round - 1] = score[round - 1] + v;
}

void User::addRoundScoreForLine(LO lo, int v)
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
		//emit signal: 라운드 종료 slot: Game.finishRound
		return;
	}

	if (getIsGiveUp() == true) {
		//emit signal: 턴 넘기기 slot: Game.nextTurn
		return;
	}

	drawCard(1);

	// timer가 돌아갈 동안 카드를 선택해서 내기 deployCard
	// 만약 시간이 다 됐으면 hand에서 카드 무작위로 한장 버리기
	// 그리고 턴을 넘기기 emit signal: 턴 넘기기 slot: Game.nextTurn
}

void User::useSkill(ID cardID, int value)
{
	Card* card = cardMap[cardID];
	skill f = skillMap.getSkill(SKILL(card->skill));
	f(card, value);
}
