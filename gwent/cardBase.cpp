#include "cardBase.h"

std::vector<CardBase*> cardCollection;

bool ReadFromFile(const char* filename, char* buffer, int len) {
	FILE* fp = nullptr;
	fopen_s(&fp, filename, "rb");

	if (fp == nullptr) return false;

	size_t fileSize = fread(buffer, 1, len, fp);

	fclose(fp);

	return true;
}

void ReadFromJson() {
	const int BufferLength = 10000; // be careful
	char readBuffer[BufferLength] = { 0, };

	if (ReadFromFile("card.json", readBuffer, BufferLength) == false) {
		system("pause");
		return;
	}

	std::string config_doc = readBuffer;
	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(config_doc, root);

	if (parsingSuccessful == false) {
		std::cout << "failed to parse" << reader.getFormatedErrorMessages();
		system("pause");
		return;
	}

	std::string name;
	std::vector<int> figures;
	Json::Value fg;
	for (int i = 0; i < root.size(); i++) {
		std::string index = std::to_string(i + 1);
		name = root[index]["name"].asString();
		fg = root[index]["figures"];
		figures.clear();
		for (int j = 0; j < fg.size(); j++) {
			figures.push_back(fg[j].asInt());
		}
		CardBase* card = new CardBase(name, figures[0], figures[1], figures[2], figures[3],
			figures[4], figures[5], figures[6], figures[7], figures[8], figures[9], figures[10], figures[11],
			figures[12], figures[13], figures[14], figures[15]);
		cardCollection.push_back(card);
	}

	return;
}

void initCardCollection()
{
	ReadFromJson();
}
