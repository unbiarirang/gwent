#ifndef SKILL_H
#define SKILL_H

#include "user.h"

#include <vector>
#include <map>
#include <iostream>

typedef void (*skill)(User*, ID, ID, LO, int);

// ��ų�� ������ -1�� ǥ��
enum SKILL {	
	CONSUME = 1,		// ���
	SPAWN,				// ����
	DAMAGE,				// �ڽ��� �Դ� ����
	GETARMOR,			// ���� ȹ��
	SUMMON,				// ��ȯ
	ATTACK,				// ����, ��뿡�� ���ظ� ����
	BOOST,				// ����
	REMOVEWEATHER,		// ���� ����
	MOVETOENEMYGRAVE,	// ���� �������� �̵�
	DRAWCARD,			// ī�� �̱�
	STRENGTHEN,			// ��ȭ
	RESURRECT,			// ��Ȱ <- �ʿ� ����?
	DESTROY,			// �ı�
	DESTROYHIGHEST,		// ���� ���� ���� �ı�
	SPAWNWEATHER,		// ���� ����

	FIRSTLIGHT = 21,
	BITINGFROST,
	IMPENETRABLEFOG,
	TORRENTIALRAIN,
	LACERATE,
	COMMANDERSHORN,
	BEKKERSTWISTEDMIRROR,
	GERALTIGNI,
	ROACH,
	THUNDERBOLTPOTION,

	DAGON = 41,
	FOGLET,
	GEELS,
	CELAENOHARPY,
	WOODLANDSPIRIT,
	EARTHELEMENTAL,
	CRONE,
	ARCHGRIFFIN = 50,
	CARANTHIR,
	FRIGHTENER,
	UNSEENELDER,
	ARACHAS,
	VRANWARRIOR,
	ARACHASBEHEMOTH,
	WILDHUNTRIDER,
	HARPYEGG
};

/* BASIC */
void consume(User* user, ID cardID, ID targetID, LO location, int data);
void spawn(User* user, ID cardID, ID targetID, LO location, int data);
void damage(User* user, ID cardID, ID targetID, LO location, int data);
void getArmor(User* user, ID cardID, ID targetID, LO location, int data);
void summon(User* user, ID cardID, ID targetID, LO location, int data);
void attack(User* user, ID cardID, ID targetID, LO location, int data); // ���� ī��� �������� �ʵ��� ����
void boost(User* user, ID cardID, ID targetID, LO location, int data);
void removeWeather(User* user, ID cardID, ID targetID, LO location, int data);
void moveToEnemyGrave(User* user, ID cardID, ID targetID, LO location, int data);
void drawCard(User* user, ID cardID, ID targetID, LO location, int data);
void strengthen(User* user, ID cardID, ID targetID, LO location, int data);
void resurrect(User* user, ID cardID, ID targetID, LO location, int data);
void destroy(User* user, ID cardID, ID targetID, LO location, int data);
void destroyHighest(User* user, ID cardID, ID targetID, LO location, int data);
void rally(User* user, ID cardID, ID targetID, LO location, int data);

/* SPECIFIC event card */
void firstLight(User* user, ID cardID, ID targetID, LO location, int data);
void bitingFrost(User* user, ID cardID, ID targetID, LO location, int data);
void impenetrableFog(User* user, ID cardID, ID targetID, LO location, int data);
void torrentialRain(User* user, ID cardID, ID targetID, LO location, int data);
void lacerate(User* user, ID cardID, ID targetID, LO location, int data);
void commandersHorn(User* user, ID cardID, ID targetID, LO location, int data);
void bekkersTwistedMirror(User* user, ID cardID, ID targetID, LO location, int data);
void geraltIgni(User* user, ID cardID, ID targetID, LO location, int data);
void roach(User* user, ID cardID, ID targetID, LO location, int data);
void thunderboltPotion(User* user, ID cardID, ID targetID, LO location, int data);

/* SPECIFIC unit card */
void dagon(User* user, ID cardID, ID targetID, LO location, int data);
void foglet(User* user, ID cardID, ID targetID, LO location, int data);
void geels(User* user, ID cardID, ID targetID, LO location, int data);
void celaenoHarpy(User* user, ID cardID, ID targetID, LO location, int data);
void woodlandSpirit(User* user, ID cardID, ID targetID, LO location, int data);
void earthElemental(User* user, ID cardID, ID targetID, LO location, int data);
void crone(User* user, ID cardID, ID targetID, LO location, int data);
void archgriffin(User* user, ID cardID, ID targetID, LO location, int data);
void caranthir(User* user, ID cardID, ID targetID, LO location, int data);
void frightener(User* user, ID cardID, ID targetID, LO location, int data);
void unseenElder(User* user, ID cardID, ID targetID, LO location, int data);
void arachas(User* user, ID cardID, ID targetID, LO location, int data);
void vranWarrior(User* user, ID cardID, ID targetID, LO location, int data);
void arachasBehemoth(User* user, ID cardID, ID targetID, LO location, int data);
void wildHuntRider(User* user, ID cardID, ID targetID, LO location, int data);
void harpyEgg(User* user, ID cardID, ID targetID, LO location, int data);

class SkillMap {
private:
	std::map<SKILL, skill> map;
public:
	SkillMap() {
		init();
	}

	void init();		// skillMap ����ϱ� ���� �ѹ��� �� �������

	skill getSkill(SKILL skillName);
	void setSkill(SKILL skillName, skill f);
};

#endif