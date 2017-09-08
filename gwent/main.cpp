#include <iostream>
#include <vector>
#include <fstream>
#include "json/json.h"
#include "class.h"
#pragma comment(lib, "json/json_vc71_libmtd")
using namespace std;

vector<CardBase*> cardCollection;

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
		for (int j = 0; j < fg.size(); j++) {
			figures.push_back(fg[j].asInt());
		}
		CardBase* card = new CardBase(name, figures[0], figures[1], figures[2],figures[3], 
			figures[4], figures[5], figures[6], figures[7], figures[8], figures[9]);
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
	user1->drawCard(10);

	for (auto x : user1->hand) {
		cout << "hand: " << x << endl;
	}

	for (auto x : user1->deck) {
		cout <<"deck: "<<  x << endl;
	}

	int x = user1->deck[0];
	user1->removeFrom(LO::DECK, x);
	int y = user1->deck[0];
	user1->removeFrom(LO::DECK, y);
	user1->insertInto(LO::LINE1, x);
	user1->insertInto(LO::LINE1, y);
	for (auto x : user1->line[0]) {
		cout << "line1: " << x << endl;
	}

	for (auto x : user1->deck) {
		cout << "deck: " << x << endl;
	}

	user1->removeAllFromLines();
	for (auto x : user1->line[0]) {
		cout << "line1: " << x << endl;
	}

	system("pause");
	return 0;
}

