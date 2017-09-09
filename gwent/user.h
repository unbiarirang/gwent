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

	// (�߹���Ѱ� �ƴϸ�) ī�尡 ���� �ټ� ������ �ѱ������� ������ ����
	std::vector<ID> deck;
	std::vector<ID> hand;
	std::vector<ID> grave;
	std::vector<ID> line[3];
	ID lineWeather[3];			// lineWeather[line]

private:
	int score[3];				// score[round] �ýð��� ���ϴ� ����
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
	void removeAllCardFromLines();		// remove all cards from all lines;

	bool isAt(LO lo, ID cardID);
	void removeFrom(LO lo, ID cardID);	// ���� ��� �ڵ����� ����
	void insertInto(LO lo, ID cardID);	// ���� ��� �ڵ����� ����

	/* treat private variables */
	bool getIsGiveUp();
	void setIsGiveUp(bool v);
	void setRound(int r);
	int getRoundScore();				// get playing round score
	void addRoundScore(int v);			// add or sub playing round score
	void addRoundScoreForLine(LO lo, int v);	// add or sub playing round score for a line

	/* others */
	void myTurn();						// play game in my turn (draw and deploy)
	void useSkill(ID cardID, int value);
};

#endif