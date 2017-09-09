#ifndef SKILL_H
#define SKILL_H

#include "user.h"

#include <vector>
#include <map>
#include <iostream>

typedef void (*skill)(User*, Card*, int);

// ��ų�� ������ -1�� ǥ��
enum SKILL {	
	CONSUME,			// ���
	SPAWN,				// ����
	DAMAGE,				// �ڽ��� �Դ� ����
	GETARMOR,			// ���� ȹ��
	SUMMON,				// ��ȯ
	ATTACK,				// ����, ��뿡�� ���ظ� ����
	BOOSTPOWER,			// ���ݷ� ����
	BOOST,				// ����
	REMOVEWEATHER,		// ���� ����
	MOVETOENEMYGRAVE,	// ���� �������� �̵�
	DRAWCARD,			// ī�� �̱�
	STRENGTHEN,			// ��ȭ
	RESURRECT,			// ��Ȱ
	DESTROY				// �ı�
};

void consume(User* user,Card* card, int value);
void spawn(User* user, Card* card, int value);
void damage(User* user, Card* card, int value);
void getArmor(User* user, Card* card, int value);
void summon(User* user, Card* card, int value);
void attack(User* user, Card* card, int value);
void boostPower(User* user, Card* card, int value);
void boost(User* user, Card* card, int value);
void removeWeather(User* user, Card* card, int value);
void moveToEnemyGrave(User* user, Card* card, int value);
void drawCard(User* user, Card* card, int value);
void strengthen(User* user, Card* card, int value);
void resurrect(User* user, Card* card, int value);
void destoryHighest(User* user, Card* card, int value);

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