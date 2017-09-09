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
	const int BufferLength = 2048; // be careful
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
			figures[4], figures[5], figures[6], figures[7], figures[8], figures[9], figures[10], figures[11]);
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
	user1->drawCard(20);
	user2->drawCard(20);

	for (auto x : user1->hand) {
		cout << "hand: " << x << endl;
	}

	for (auto x : user1->deck) {
		cout <<"deck: "<<  x << endl;
	}

	user1->deployCard(LO::LINE1, 2);
	user1->deployCard(LO::LINE1, 3);
	user1->deployCard(LO::LINE1, 4);
	cout << "score: " << user1->getRoundScore() << endl;

	for (auto x : user1->hand) {
		cout << "hand: " << x << endl;
	}

	for (auto x : user1->deck) {
		cout << "deck: " << x << endl;
	}

	for (auto x : user1->line[0]) {
		cout << "line1: " << x << endl;
	}

	for (auto x : user1->grave) {
		cout << "grave: " << x << endl;
	}

	user2->deployCard(LO::LINE1, 21);
	user1->useSkill(SKILLKIND::NORMAL, 1, 1);

	for (auto x : user2->hand) {
		cout << "2hand: " << x << endl;
	}

	for (auto x : user2->deck) {
		cout << "2deck: " << x << endl;
	}

	for (auto x : user2->grave) {
		cout << "2grave: " << x << endl;
	}

	skill s = skillMap.getSkill(SKILL::SPAWN);
	s(user1, user1->cardMap[1], 1);

	for (auto x : user1->line[0]) {
		cout << "line1: " << x << endl;
	}

	user1->destroyCard(41);

	for (auto x : user1->grave) {
		cout << "grave: " << x << endl;
	}

	for (auto x : user1->line[0]) {
		cout << "line1: " << x << endl;
	}

	system("pause");
	return 0;
}

