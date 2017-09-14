#include "game.h"

User* Game::getUser(int i)
{
	if (i != 0 && i != 1)
		return nullptr;
	return user[i];
}

void Game::decideOrder()
{
	turn = util::getRandNumBetween(0, 1);
}

void Game::setCardsToDeck()
{
	for (int i = 0; i < 2; i++) {
        for (auto card : user[i]->cardMap)
			user[i]->deck.push_back(card.first);
	}
}

void Game::turnChange()
{
    if (turn == 0) turn = 1;
    else turn = 0;

    if (user[0]->getIsGiveUp() == true && user[1]->getIsGiveUp() == true) {
        finishGame();
        return;
    }

    User* userNow = getUser(turn);
    if (userNow == user[0]) {
        userNow->myTurn();
    }
    else {
        userNow->myTurnAI();
        emit turnChangedSignal();
    }
}

void Game::finishRound()
{
	int user0Score = user[0]->getRoundScore();
	int user1Score = user[1]->getRoundScore();

	// save result
	if (user0Score > user1Score)
		result[round - 1] = RESULT::USER0WIN;
	else if (user0Score == user1Score)
		result[round - 1] = RESULT::DRAW;
	else
		result[round - 1] = RESULT::USER1WIN;

	// save score
	score[round - 1] = { user0Score, user1Score };

	// finish game
	if (result[0] == RESULT::USER0WIN && result[1] == RESULT::USER0WIN
		|| result[0] == RESULT::USER1WIN && result[1] == RESULT::USER1WIN
		|| round == 3) {
		// emit ���� ���� �� signal
		finishGame();
		return;
	}

	round++;
	// initialize game to play next round
	for (int i = 0; i < 2; i++) {
		user[i]->removeAllCardFromLines();
		user[i]->setIsGiveUp(false);
		user[i]->setRound(round);
		for (int j = 0; j < 3; j++)
			removeLineWeather(user[i], j);
	}
}

void Game::finishGame()
{
    if (user[0]->getRoundScore() > user[1]->getRoundScore())
        winner = 0;
    else if (user[0]->getRoundScore() < user[1]->getRoundScore())
        winner = 1;
    else
        winner = 2;

    emit finishGameSignal();
}

void Game::removeLineWeather(User* u, int i)
{
	u->lineWeather[i] = 0;
}
