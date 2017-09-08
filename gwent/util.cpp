#include "util.h"
#include <random>

static int id = 0;

std::random_device rd;
std::mt19937_64 rng(rd());

int getID()
{
	id++;
	return id;
}

int getRandNumBetween(int x, int y)
{
	std::uniform_int_distribution<__int64> result(x, y);
	return result(rng);
}
