#include "json/json.h"

#include "user.h"
#include "game.h"
#include "skill.h"

#include <iostream>
#include <fstream>

#pragma comment(lib, "json/json_vc71_libmtd")
using namespace std;

vector<CardBase*> cardCollection;
extern SkillMap skillMap;

bool ReadFromFile(const char* filename, char* buffer, int len) {
	FILE* fp = nullptr;
	fopen_s(&fp, filename, "rb");

	if (fp == nullptr) return false;

	size_t fileSize = fread(buffer, 1, len, fp);

	fclose(fp);

	return true;
}

int ReadFromJson() {
	const int BufferLength = 10000; // be careful
	char readBuffer[BufferLength] = { 0, };

	if (ReadFromFile("card.json", readBuffer, BufferLength) == false) {
		system("pause");
		return 0;
	}

	string config_doc = readBuffer;
	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(config_doc, root);

	if (parsingSuccessful == false) {
		cout << "failed to parse" << reader.getFormatedErrorMessages();
		system("pause");
		return 0;
	}

	string name;
	vector<int> figures;
	Json::Value fg;
	for (int i = 0; i < root.size(); i++) {
		string index = to_string(i + 1);
		name = root[index]["name"].asString();
		fg = root[index]["figures"];
		figures.clear();
		for (int j = 0; j < fg.size(); j++) {
			figures.push_back(fg[j].asInt());
		}
		CardBase* card = new CardBase(name, figures[0], figures[1], figures[2],figures[3], 
			figures[4], figures[5], figures[6], figures[7], figures[8], figures[9], figures[10], figures[11],
			figures[12], figures[13], figures[14], figures[15]);
		cardCollection.push_back(card);

		cout << card->name << endl;
	}

	return 1;
}

int main() {
	if (ReadFromJson() == 0) return -1;

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

