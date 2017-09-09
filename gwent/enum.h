#ifndef ENUM_H
#define ENUM_H

enum LO { // location of a card. 실제 카드 위치. TODO: lineWeather은 없음
	DECK, HAND, GRAVE, LINE1, LINE2, LINE3, GRAVE_ENEMY
};

enum TYPE { // card type (tear)
	BRONZE = 1, SILVER, GOLD
};

enum CAMP {
	NEUTRAL = 1, MONSTER = 2
};

// line 속성. 1:근접 2:원거리 3:공성 4:아무곳 5:이벤트카드 6:날씨
enum LINE {
	MELEE = 1, RANGED, SIEGE, ANY, EVENT, WEATHER
};

enum RESULT {
	USER0WIN = 1, USER1WIN, DRAW
};

enum SKILLKIND { NORMAL, DEPLOY, DEATHWISH };

/* figures 순서 */
//"armor": 0,
//"camp": 2,			1:중립, 2:몬스터
//"is_doomed": 1,
//"is_leader": 1,
//"is_stubborn": 1,
//"line": 4,			1:근접 2:원거리 3:공성 4:아무곳이나 5:이벤트카드

//"no": 1,				카드 넘버
//"power": 0,
//"strength": 6,
//"type": 3,			1:브론즈 2:실버 3:골드
//"skill": ?,
//"deploySkill": ?
#endif