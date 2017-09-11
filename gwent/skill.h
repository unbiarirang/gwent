#ifndef SKILL_H
#define SKILL_H

#include "user.h"

#include <vector>
#include <map>
#include <iostream>

typedef void (*skill)(User*, ID, ID, LO, int);

// 스킬이 없으면 -1로 표기
enum SKILL {	
	CONSUME = 1,		// 흡수
	SPAWN,				// 생성
	DAMAGE,				// 자신이 입는 피해
	GETARMOR,			// 방어력 획득
	SUMMON,				// 소환
	ATTACK,				// 공격, 상대에게 피해를 입힘
	BOOST,				// 증폭
	REMOVEWEATHER,		// 날씨 제거
	MOVETOENEMYGRAVE,	// 상대방 무덤으로 이동
	DRAWCARD,			// 카드 뽑기
	STRENGTHEN,			// 강화
	RESURRECT,			// 부활 <- 필요 없네?
	DESTROY,			// 파괴
	DESTROYHIGHEST,		// 가장 강한 유닛 파괴
	SPAWNWEATHER,		// 날씨 생성

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
void attack(User* user, ID cardID, ID targetID, LO location, int data); // 날씨 카드는 공격하지 않도록 주의
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

	void init();		// skillMap 사용하기 전에 한번은 꼭 해줘야함

	skill getSkill(SKILL skillName);
	void setSkill(SKILL skillName, skill f);
};

#endif