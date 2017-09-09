//#include "class.h"
//#include <algorithm>
//
///* =============class Card============= */
//std::ostream & operator<<(std::ostream & os, const Card * m)
//{
//	os << "the card's id is: " << m->u_id << " name is: " << m->name;
//	return os;
//}
//
///* =============class Game============= */
//int Game::getHighest()
//{
//	return 0;
//}
//
//int Game::getLowest()
//{
//	return 0;
//}
//
//User* Game::getUser(int i)
//{
//	if (i != 0 && i != 1)
//		return nullptr;
//	return user[i];
//}
//
//void Game::decideOrder()
//{
//	turn = util::getRandNumBetween(0, 1);
//}
//
//void Game::setCardsToDeck()
//{
//	for (int i = 0; i < 2; i++) {
//		for (auto card : user[i]->cardMap) {
//			user[i]->deck.push_back(card.first);
//		}
//	}
//}
//
//void Game::finishRound()
//{
//	int user0Score = user[0]->getRoundScore();
//	int user1Score = user[1]->getRoundScore();
//
//	// save result
//	if (user0Score > user1Score)
//		result[round - 1] = RESULT::USER0WIN;
//	else if (user0Score == user1Score)
//		result[round - 1] = RESULT::DRAW;
//	else
//		result[round - 1] = RESULT::USER1WIN;
//
//	// save score
//	score[round - 1] = { user0Score, user1Score };
//
//	// finish game
//	if (result[0] == RESULT::USER0WIN && result[1] == RESULT::USER0WIN
//		|| result[0] == RESULT::USER1WIN && result[1] == RESULT::USER1WIN
//		|| round == 3) {
//		// emit 완전 게임 끝 signal
//		finishGame();
//		return;
//	}
//
//	round++;
//	// initialize game to play next round
//	for (int i = 0; i < 2; i++) {
//		user[i]->removeAllFromLines();
//		user[i]->setIsGiveUp(false);
//		user[i]->setRound(round);
//		for (int j = 0; j < 3; j++)
//			removeLineWeather(user[i], j);
//	}
//}
//
//void Game::finishGame()
//{
//	// TODO: 여러가지 ui 동작
//}
//
//void Game::removeLineWeather(User* u, int i)
//{
//	u->lineWeather[i] = 0;
//}
//
///* =============class User============= */
//std::ostream& operator<<(std::ostream& os, const User* m)
//{
//	os << "===THESE ARE MY CARDS===" << std::endl;
//	for (auto card : m->cardMap) {
//		os << card.second << std::endl;
//	}
//	os << "========================" << std::endl;
//	return os;
//}
//
//void User::drawCard(int count)
//{
//	int cardNum, cardIndex;
//	ID cardID;
//	for (int j = 0; j < count; j++) {
//		cardNum = deck.size();
//		cardIndex = util::getRandNumBetween(0, cardNum - 1);
//		cardID = deck[cardIndex];
//		insertInto(LO::HAND, cardID);
//		removeFrom(LO::DECK, cardID);
//	}
//}
//
//void User::discardCard(ID cardID)
//{
//	removeFrom(LO::HAND, cardID);
//	insertInto(LO::DECK, cardID);
//}
//
//void User::deployCard(LO lo, ID cardID)
//{
//	Card* card = cardMap[cardID];
//	// wrong location to deploy card
//	if (!(lo == LO::LINE1 || lo == LO::LINE2 || lo == LO::LINE3))
//		return;
//
//	// wrong location to deploy card
//	if ((card->line != LINE::ANY) && (card->line != lo - 2))
//		return;
//
//	removeFrom(LO::HAND, cardID);
//	insertInto(lo, cardID);
//}
//
//void User::deployEventCard(ID cardID)
//{
//}
//
//void User::banishCard(ID cardID) // 주의: lineWeather에 있는 카드는 추방이 안됨
//{
//	for (int i = LO::DECK; i < LO::LINE3; i++) {
//		if (isAt(LO(i), cardID)) {
//			removeFrom(LO(i), cardID);
//			break;
//		}
//	}
//}
//
//void User::removeAllFromLines()
//{
//	LO loArr[3] = { LO::LINE1, LO::LINE2, LO::LINE3 };
//	for (int i = 0; i < 3; i++) {
//		for (auto cardID : line[i]) {
//			removeFrom(loArr[i], cardID);
//			insertInto(LO::GRAVE, cardID);
//		}
//	}
//}
//
//bool User::isAt(LO lo, ID cardID)
//{
//	std::vector<int> v;
//	switch (lo) {
//	case LO::DECK:
//		v = deck; break;
//	case LO::HAND:
//		v = hand; break;
//	case LO::GRAVE:
//		v = grave; break;
//	case LO::LINE1:
//		v = line[0]; break;
//	case LO::LINE2:
//		v = line[1]; break;
//	case LO::LINE3:
//		v = line[2]; break;
//	case LO::GRAVE_ENEMY:
//		v = enemy->grave; break;
//	}
//
//	if (std::find(v.begin(), v.end(), cardID) != v.end())
//		return true;
//
//	return false;
//}
//
//void User::removeFrom(LO lo, ID cardID)
//{
//	std::vector<int>* v = { 0 };
//	switch (lo) {
//	case LO::DECK:
//		v = &deck; break;
//	case LO::HAND:
//		v = &hand; break;
//	case LO::GRAVE:
//		v = &grave; break;
//	case LO::LINE1:
//		v = &line[0]; break;
//	case LO::LINE2:
//		v = &line[1]; break;
//	case LO::LINE3:
//		v = &line[2]; break;
//	case LO::GRAVE_ENEMY:
//		v = &enemy->grave;
//	}
//
//	// calculate score if the card was on lines
//	if (lo == LO::LINE1 || lo == LO::LINE2 || lo == LO::LINE3) {
//		addRoundScore(-cardMap[cardID]->strength);
//		addRoundScoreForLine(lo, -cardMap[cardID]->strength);
//	}
//
//	// remove the element from vector
//	if (isAt(lo, cardID))
//		(*v).erase(std::remove((*v).begin(), (*v).end(), cardID), (*v).end());
//}
//
//void User::insertInto(LO lo, ID cardID)
//{
//	std::vector<int>* v = { 0 };
//	switch (lo) {
//	case LO::DECK:
//		v = &deck; break;
//	case LO::HAND:
//		v = &hand; break;
//	case LO::GRAVE:
//		v = &grave; break;
//	case LO::LINE1:
//		v = &line[0]; break;
//	case LO::LINE2:
//		v = &line[1]; break;
//	case LO::LINE3:
//		v = &line[2]; break;
//	case LO::GRAVE_ENEMY:
//		v = &enemy->grave;
//	}
//
//	// calculate score if the card is going to be deployed
//	if (lo == LO::LINE1 || lo == LO::LINE2 || lo == LO::LINE3) {
//		addRoundScore(cardMap[cardID]->strength);
//		addRoundScoreForLine(lo, cardMap[cardID]->strength);
//	}
//
//	// insert the element into vector
//	if(!isAt(lo, cardID))
//		(*v).push_back(cardID);
//}
//
//void User::myTurn()
//{
//	// both of users gave up
//	if (getIsGiveUp() == true && enemy->getIsGiveUp() == true) {
//		//emit signal: 라운드 종료 slot: Game.finishRound
//		return;
//	}
//
//	if (getIsGiveUp() == true) {
//		//emit signal: 턴 넘기기 slot: Game.nextTurn
//		return;
//	}
//
//	drawCard(1);
//
//	// timer가 돌아갈 동안 카드를 선택해서 내기 deployCard
//	// 만약 시간이 다 됐으면 hand에서 카드 무작위로 한장 버리기
//	// 그리고 턴을 넘기기 emit signal: 턴 넘기기 slot: Game.nextTurn
//}
//
//bool User::getIsGiveUp()
//{
//	return is_giveUp;
//}
//
//void User::setIsGiveUp(bool v)
//{
//	is_giveUp = v;
//}
//
//int User::getRoundScore()
//{
//	return score[round - 1];
//}
//
//void User::addRoundScore(int v)
//{
//	score[round - 1] = score[round - 1] + v;
//}
//
//void User::addRoundScoreForLine(LO lo, int v)
//{
//	scoreForLine[round - 1][lo - 3] = v; // LINE1 = 3
//}
//
//void User::setRound(int r)
//{
//	round = r;
//}
