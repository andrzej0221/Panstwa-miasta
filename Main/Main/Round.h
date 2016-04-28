#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
class Round
{
private:
	char _character;
	int _duration;
	int *_points;
	int _whichPlayer;

public:
	Round();
	char selectTheRandomLetter();
	void endTheRound();
	void checkWords();
	void calculateAPoints();
	void addPoints();
	~Round();
};

