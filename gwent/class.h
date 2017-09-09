//#ifndef CLASS_H
//#define CLASS_H
//
//#include <string>
//#include <vector>
//#include <iostream>
//#include <map>
//#include "util.h"
//#include "enum.h"
//
//typedef int ID;
//
//// TODO: CardBase랑 Card 계승으로 만들기
//class CardBase {
//public:
//	int no;
//	int type;
//	std::string name;
//	int camp;
//	int line;
//	int strength;
//	int armor;
//	int power;	// 공격력 (일단 frost를 생각하고 만듬)
//	int is_doomed;
//	int is_stubborn;
//	int is_leader;
//
//	CardBase(std::string _name="", int _armor=0, int _camp=0, int _is_doomed=0, int _is_leader = 0,
//			int _is_stubborn = 0, int _line = 0, int _no = 0, int _power = 0, int _strength = 0, int _type = 0) :
//		no(_no), type(_type), name(_name), camp(_camp), line(_line), strength(_strength),
//		armor(_armor), power(_power), is_doomed(_is_doomed), is_stubborn(_is_stubborn), is_leader(_is_leader) {};
//	CardBase(CardBase* cb, ID _id = 0) :
//		no(cb->no), type(cb->type), name(cb->name), camp(cb->camp), line(cb->line), strength(cb->strength),
//		armor(cb->armor), power(cb->power), is_doomed(cb->is_doomed), is_stubborn(cb->is_stubborn), is_leader(cb->is_leader) {};
//};
//
//class Card : public CardBase {
//private:
//	// playing unit's status 
//	ID u_id;
//	int u_strength;
//	//int u_line;		// LINE enum TODO: 어차피 유저 정보에 잇으니 빼는거 고려
//	int u_armor;
//	//int u_location; // LOCATION enum TODO: 어차피 유저 정보에 잇으니 빼는거 고려
//
//public:
//	Card(CardBase* cb, ID _id = 0) :
//		CardBase(cb), u_id(_id), u_strength(0),u_armor(0) {};
//
//	friend std::ostream& operator<<(std::ostream& os, const Card* m);
//};
//
//class User {
//public:
//	std::map<ID, Card*> cardMap;
//	User* enemy;
//
//	// (추방당한거 아니면) 카드가 여기 다섯 군데중 한군데에는 무조건 있음
//	std::vector<ID> deck;
//	std::vector<ID> hand;
//	std::vector<ID> grave;
//	std::vector<ID> line[3];
//	ID lineWeather[3];			// lineWeather[line]
//
//private:
//	int score[3];				// score[round] 시시각각 변하는 점수
//	int scoreForLine[3][3];		// scoreForLine[round][line]
//	int round;
//
//	bool is_giveUp;
//
//public:
//	User(std::vector<CardBase*> *cardBaseCollection = new std::vector<CardBase*>) :
//		is_giveUp(0)
//	{
//		*lineWeather = { 0 };
//		*score = { 0 };
//		round = 1;
//
//		for (auto cardBase : *cardBaseCollection) {
//			ID newID = util::getID();
//			Card *card = new Card(cardBase, newID);
//			cardMap[newID] = card;
//		}
//	};
//
//public:
//	friend std::ostream& operator<<(std::ostream& os, const User* m);
//
//	void drawCard(int count);
//	void discardCard(ID cardID);		// trash the card from hand to deck at the beginning
//	void deployCard(LO lo, ID cardID);	// deploy the card to line 1 or 2 or 3
//	void deployEventCard(ID cardID);	// deploy the event card
//	void banishCard(ID cardID);			// remove the card from the game
//	void removeAllFromLines();			// remove all cards from all lines;
//
//	bool isAt(LO lo, ID cardID);
//	void removeFrom(LO lo, ID cardID);	// 점수 계산 자동으로 해중
//	void insertInto(LO lo, ID cardID);	// 점수 계산 자동으로 해줌
//
//	void myTurn();						// play game in my turn (draw and deploy)
//
//	bool getIsGiveUp();
//	void setIsGiveUp(bool v);
//	void setRound(int r);
//	int getRoundScore();				// get playing round score
//	void addRoundScore(int v);			// add or sub playing round score
//	void addRoundScoreForLine(LO lo, int v);	// add or sub playing round score for a line
//};
//
//class Game {
//private:
//	User* user[2];
//
//	int round;				// round 1,2,3
//	int turn;				// 0 for user0 and 1 for user1
//	int result[3];			// enum RESULT
//	struct {				// rounds score
//		int user0Score;
//		int user1Score;
//	} score[3];
//	
//	// FIXME: QTimer timer 추가
//
//public:
//	Game(User* _user0, User* _user1) {
//		round = 1;
//		*result = { 0 };
//		user[0] = _user0;
//		user[1] = _user1;
//		user[0]->enemy = _user1;
//		user[1]->enemy = _user0;
//	}
//
//public:
//	void decideOrder();
//	void setCardsToDeck();
//	void finishRound();
//	void finishGame();
//	void removeLineWeather(User* u, int i);
//
//	User* getUser(int i);
//	int getHighest();
//	int getLowest();
//};
//#endif // !CLASS_H