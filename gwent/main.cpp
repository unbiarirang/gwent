#include "json/json.h"

#include "user.h"
#include "game.h"
#include "skill.h"

#include <iostream>
#include <fstream>

#pragma comment(lib, "json/json_vc71_libmtd")
using namespace std;

extern SkillMap skillMap;
extern vector<CardBase*> cardCollection;

int main() {
	initCardCollection();

	User* user1 = new User(&cardCollection);
	User* user2 = new User(&cardCollection);

	Game* game = new Game(user1, user2);

	cout << game->getUser(0) << game->getUser(1) << endl;

	game->setCardsToDeck();
	user1->drawCard(30);
	user2->drawCard(30);

	user1->deployCard(LO::LINE3, 16);
	skillMap.getSkill(SKILL::ARACHASBEHEMOTH)(user1, 16, 0, LO::LINE3, 1);
	cout << "user1 score: " << user1->getRoundScore() << endl;
	cout << "user2 score: " << user2->getRoundScore() << endl;

	for (auto x : user1->line[0]) {
		cout << "user1 line1: " << x << endl;
	}
	for (auto x : user2->line[0]) {
		cout << "user2 line1: " << x << endl;
	}
	for (auto x : user1->grave) {
		cout << "user1 grave: " << x << endl;
	}
	for (auto x : user2->grave) {
		cout << "user2 grave: " << x << endl;
	}
	cout << "=====================" << endl;

	cout << "user1 score: " << user1->getRoundScore() << endl;
	cout << "user2 score: " << user2->getRoundScore() << endl;

	for (auto x : user1->line[0]) {
		cout << "user1 line1: " << x << endl;
	}
	for (auto x : user2->line[0]) {
		cout << "user2 line1: " << x << endl;
	}
	for (auto x : user1->grave) {
		cout << "user1 grave: " << x << endl;
	}
	for (auto x : user2->grave) {
		cout << "user2 grave: " << x << endl;
	}

	system("pause");
	return 0;
}

