#ifndef SKILL_H
#define SKILL_H

#include "user.h"

#include <vector>
#include <map>
#include <iostream>

typedef void (*skill)(User*, Card*, int);

// 스킬이 없으면 -1로 표기
enum SKILL {	
	CONSUME,			// 흡수
	SPAWN,				// 생성
	DAMAGE,				// 자신이 입는 피해
	GETARMOR,			// 방어력 획득
	SUMMON,				// 소환
	ATTACK,				// 공격, 상대에게 피해를 입힘
	BOOSTPOWER,			// 공격력 증폭
	BOOST,				// 증폭
	REMOVEWEATHER,		// 날씨 제거
	MOVETOENEMYGRAVE,	// 상대방 무덤으로 이동
	DRAWCARD,			// 카드 뽑기
	STRENGTHEN,			// 강화
	RESURRECT,			// 부활
	DESTROY				// 파괴
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

	void init();		// skillMap 사용하기 전에 한번은 꼭 해줘야함

	skill getSkill(SKILL skillName);
	void setSkill(SKILL skillName, skill f);
};

#endif