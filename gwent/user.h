#ifndef USER_H
#define USER_H

#include "card.h"
#include "util.h"
#include "enum.h"

#include <map>
#include <vector>
#include <algorithm>

class User {
public:
	std::map<ID, Card*> cardMap;
	User* enemy;

	// (추방당한거 아니면) 카드가 여기 다섯 군데중 한군데에는 무조건 있음
	std::vector<ID> deck;
	std::vector<ID> hand;
	std::vector<ID> grave;
	std::vector<ID> line[3];
	ID lineWeather[3];			// lineWeather[line] TODO: 없에자. 그냥 날씨도 다 라인에 넣자

private:
	int score[3];				// score[round] 시시각각 변하는 점수
	int scoreForLine[3][3];		// scoreForLine[round][line]
	int round;

	bool is_giveUp;

public:
	User(std::vector<CardBase*> *cardBaseCollection = new std::vector<CardBase*>) :
		is_giveUp(0)
	{
		*lineWeather = { 0 };
		*score = { 0 };
		round = 1;

		for (auto cardBase : *cardBaseCollection) {
			ID newID = util::getID();
			Card *card = new Card(cardBase, newID);
			cardMap[newID] = card;
		}
	};

public:
	friend std::ostream& operator<<(std::ostream& os, const User* m);

	/* treat card */
	void drawCard(int count);
	void discardCard(ID cardID);		// trash the card from hand to deck at the beginning
	void deployCard(LO lo, ID cardID);	// deploy the card to line 1 or 2 or 3
	void deployEventCard(ID cardID);	// deploy the event card
	void banishCard(ID cardID);			// remove the card from the game
	void destroyCard(ID cardID);		// move the card from field to grave
	Card* spawnCard(int no);			// spawn card
	void removeAllCardFromLines();		// remove all cards from all lines

	bool isAt(LO lo, ID cardID);
	void removeFrom(LO lo, ID cardID);	// 점수 계산 자동으로 해중
	void insertInto(LO lo, ID cardID);	// 점수 계산 자동으로 해줌
	LO findLine(ID cardID);

	/* treat private variables */
	bool getIsGiveUp();
	void setIsGiveUp(bool v);
	void setRound(int r);
	int getRoundScore();						// get playing round score
	//void changeRoundScore(int v);				// add or sub playing round score
	void changeRoundScoreForLine(LO lo, int v);	// add or sub playing round score for a line

	/* others */
	void myTurn();						// play game in my turn (draw and deploy)
	void useSkill(SKILLKIND kind, ID cardID, ID targetID, LO location);
	void changeStrength(ID cardID, int v);

	ID getHighest();					// among all units in the field
	ID getLowest();						// among all units in the field
	ID getHighestFromLine(LO lo);		// select the highest randomly if there are more than one higest
	ID getLowestFromLine(LO lo);		// select the lowest randomly if there are more than one lowest

	Card* getCardFromID(ID cardID);
	ID getWeatherCardIDFromLine(LO lo);
	std::vector<ID> getUnitIDs(LO lo);
};

#endif