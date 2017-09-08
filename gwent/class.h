#ifndef CLASS_H
#define CLASS_H

#include <string>
#include <vector>
#include <map>
#include "util.h"
#include "enum.h"

typedef int ID;

// TODO: CardBase랑 Card 계승으로 만들기
struct CardBase {
	int no;
	int type;
	std::string name;
	int camp;
	int line;
	int strength;
	int armor;
	int power;	// 공격력 (일단 frost를 생각하고 만듬)
	int is_doomed;
	int is_stubborn;
	int is_leader;

	CardBase(std::string _name="", int _armor=0, int _camp=0, int _is_doomed=0, int _is_leader = 0,
		   int _is_stubborn = 0, int _line = 0, int _no = 0, int _power = 0, int _strength = 0, int _type = 0) :
		no(_no), type(_type), name(_name), camp(_camp), line(_line), strength(_strength),
		armor(_armor), power(_power), is_doomed(_is_doomed), is_stubborn(_is_stubborn), is_leader(_is_leader) {};
};

class Card {
private:
	// unit's basic information
	CardBase* base;

	// playing unit's status 
	int u_id;
	int u_strength;
	int u_line;		// LINE enum TODO: 어차피 유저 정보에 잇으니 빼는거 고려
	int u_armor;
	int u_location; // LOCATION enum TODO: 어차피 유저 정보에 잇으니 빼는거 고려

public:
	Card(CardBase* _base = new CardBase(), int _id = 0) : 
		base(_base), u_id(_id), u_strength(0),
		u_line(0), u_armor(0), u_location(LO::DECK) {}

	friend std::ostream& operator<<(std::ostream& os, const Card* m);
};

class User {
public:
	std::map<int, Card*> cardMap;
	User* enemy;

	std::vector<int> deck;
	std::vector<int> hand;
	std::vector<int> grave;
	std::vector<int> line[3];

private:
	int lineWeather[3];
	int score[3];
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
			int newID = getID();
			Card *card = new Card(cardBase, newID);
			cardMap[newID] = card;
		}
	};

public:
	friend std::ostream& operator<<(std::ostream& os, const User* m);

	void drawCard(int count);
	void discardCard(int cardID);		// move a card from hand to deck
	void deployCard(LO lo, int cardID); // deploy a card to line 1 or 2 or 3
	void removeAllFromLines();			// remove all cards from all lines;

	bool isAt(LO lo, int cardID);
	void removeFrom(LO lo, int cardID);
	void insertInto(LO lo, int cardID);

	void myTurn();						// play game in my turn (draw and deploy)

	bool getIsGiveUp();
	void setIsGiveUp(bool v);
	void setRound(int r);
	int getRoundScore();				// get playing round score
	void addRoundScore(int v);			// add or sub playing round score
};

class Game {
private:
	User* user[2];

	int round;				// round 1,2,3
	int turn;				// 0 for user0 and 1 for user1
	int result[3];			// enum RESULT
	struct {				// rounds score
		int user0Score;
		int user1Score;
	} score[3];
	
	// FIXME: QTimer timer 추가

public:
	Game(User* _user0, User* _user1) {
		round = 1;
		*result = { 0 };
		user[0] = _user0;
		user[1] = _user1;
		user[0]->enemy = _user1;
		user[1]->enemy = _user0;
	}

public:
	void decideOrder();
	void setCardsToDeck();
	void finishRound();
	void finishGame();

	User* getUser(int i);
	int getHighest();
	int getLowest();
};
#endif // !CLASS_H