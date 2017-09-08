#ifndef ENUM_H
#define ENUM_H

enum LO { // location of a card
	DECK, HAND, GRAVE, LINE1, LINE2, LINE3, GRAVE_ENEMY
};

// type 1: 브론즈 2: 실버 3: 골드
enum TYPE { // card type (tear)
	BRONZE = 1, SILVER, GOLD
};

// camp 1: 중립 2: 몬스터
enum CAMP {
	NEUTRAL = 1, MONSTER = 2
};

// line 1: 근접 2: 원거리 3: 공성 4: 아무곳 5: 이벤트카드
enum LINE {
	MELEE = 1, RANGED, SIEGE, ANY, EVENT
};

enum RESULT {
	USER0WIN = 1, USER1WIN, DRAW
};

//figures 순서
//"armor": 0,
//"camp": 2,
//"is_doomed": 1,
//"is_leader": 1,
//"is_stubborn": 1,
//"line": 4,
//"no": 1,
//"power": 0,
//"strength": 6,
//"type": 3
#endif