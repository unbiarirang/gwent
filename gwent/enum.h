#ifndef ENUM_H
#define ENUM_H

enum LO { // location of a card. ���� ī�� ��ġ. TODO: lineWeather�� ����
	DECK, HAND, GRAVE, LINE1, LINE2, LINE3, GRAVE_ENEMY
};

enum TYPE { // card type (tear)
	BRONZE = 1, SILVER, GOLD
};

enum CAMP {
	NEUTRAL = 1, MONSTER = 2
};

// line �Ӽ�. 1:���� 2:���Ÿ� 3:���� 4:�ƹ��� 5:�̺�Ʈī�� 6:����
enum LINE {
	MELEE = 1, RANGED, SIEGE, ANY, EVENT, WEATHER
};

enum RESULT {
	USER0WIN = 1, USER1WIN, DRAW
};

enum SKILLKIND { NORMAL, DEPLOY, DEATHWISH };

/* figures ���� */
//"armor": 0,
//"camp": 2,			1:�߸�, 2:����
//"is_doomed": 1,
//"is_leader": 1,
//"is_stubborn": 1,
//"line": 4,			1:���� 2:���Ÿ� 3:���� 4:�ƹ����̳� 5:�̺�Ʈī��

//"no": 1,				ī�� �ѹ�
//"power": 0,
//"strength": 6,
//"type": 3,			1:����� 2:�ǹ� 3:���
//"skill": ?,
//"deploySkill": ?
#endif