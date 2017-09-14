#ifndef GAME_H
#define GAME_H

#include "user.h"
#include <QWidget>
#include <QObject>

class Game : public QObject {
    Q_OBJECT
private:
	User* user[2];

public:
	int round;				// round 1,2,3
	int turn;				// 0 for user0 and 1 for user1
	int result[3];			// enum RESULT
    int winner;
	struct {				// rounds score
		int user0Score;
		int user1Score;
	} score[3];

	// FIXME: QTimer timer Ãß°¡

public:
	Game(User* _user0, User* _user1) {
		round = 1;
        turn = 0;
		*result = { 0 };
		user[0] = _user0;
		user[1] = _user1;
		user[0]->enemy = _user1;
		user[1]->enemy = _user0;
	}

signals:
    void turnChangedSignal();
    void finishGameSignal();

public slots:
	void decideOrder();
	void setCardsToDeck();
    void startGame(QWidget* page);
	void finishRound();
	void finishGame();
	void removeLineWeather(User* u, int i);
    void turnChange();

	User* getUser(int i);
};
#endif // !GAME_H
