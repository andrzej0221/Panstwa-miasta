#include "stdafx.h"
#include "Game.h"
#include <iostream>

Game::Game()
{
}

Game::Game(const int & numberOfRounds, const int & numberOfPlayers) : _numberOfRounds(numberOfRounds), _numberOfPlayers(numberOfPlayers)
{
}


void Game::createPlayers(const int & numberOfPlayers)
{
	_numberOfPlayers = numberOfPlayers;
	_players = new Player[_numberOfPlayers];
	_words = new string*[_numberOfPlayers];
	_result = new int[_numberOfPlayers];
}


void Game::setPlayersNames()
{
	for (int i = 0; i < _numberOfPlayers; i++)
	{
		cout << "Podaj imie " << i + 1 << ". gracza" << endl;
		string name;
		cin >> name;
		_players[i].setPlayerName(name);
		_players[i].setPlayerNumber(i + 1);
	}
}

void Game::setPlayersNames(vector<string> players)
{
	_numberOfPlayers = players.size();
	createPlayers(_numberOfPlayers);
	for (int i = 0; i < _numberOfPlayers; i++)
	{
		_players[i].setPlayerName(players[i]);
		_players[i].setPlayerNumber(i + 1);

		cout << "Players " << i << " " << _players[i].getPlayerName()  << endl;
	}
}

void Game::getPlayersNames() const
{
	for (int i = 0; i < _numberOfPlayers; i++)
	{
		string name = _players[i].getPlayerName();
	}
}

const vector<Player> Game::getPlayers()
{
	vector<Player> allPlayers;
	
	for (int i = 0; i < _numberOfPlayers; i++)
	{
		allPlayers.push_back(_players[i]);
	}

	return allPlayers;
}


void Game::play()
{
	cout << "Nowa runda" << endl;
	bool continueGame = true;
	_character = _round.selectTheRandomLetter();
	cout << _character << endl;
}

void Game::playGame()
{
	cout << "Nowa runda" << endl;
	bool continueGame = true;

	do
	{
		_character = _round.selectTheRandomLetter();
		for (int i = 0; i < _numberOfPlayers; i++)
		{
			cout << "i= " << i << endl;
			_round.waitingForPlayer(i, _players[i].getPlayerName());
			_players[i].playRound(_character);
		}

		for (int i = 0; i < _numberOfPlayers; i++)
		{
			_words[i] = _players[i].getWords();
		}

		_result = _round.calculatePoints(_words, _numberOfPlayers);

		for (int i = 0; i < _numberOfPlayers; i++)
		{
			addPoints(i, _result[i]);
		}

		system("cls");
		cout << "\tPanstwo\t|\tMiasto\t|\tRzecz\t|\tRoslina" << endl;
		
		for (int j = 0; j < _numberOfPlayers; j++)
		{
			cout << "GRACZ " << j + 1 << ": ";
			for (int i = 0; i < 4; i++)
			{
				cout << _words[j][i] << "   |   ";
			}
			cout << endl;
		}
		
		for (int i = 0; i < _numberOfPlayers; i++)
		{
			cout << "Gracz nr " << i + 1 << " posiada " << _players[i].getPoints() << " punktow" << endl;
		}
		
		
		cout << "Kontynuowac gre? <y/n>" << endl;
		char choose;
		do
		{
			choose = _getch();
		} 
		while ((choose != 'y') && (choose != 'n'));

		if (choose == 'y')
		{
			continueGame = true;
		}
		else
		{
			continueGame = false;
		}
	} while (continueGame);


	system("cls");
	Player * temporaryPlayers = new Player[_numberOfPlayers];


	for (int i = 0; i < _numberOfPlayers; i++)
	{
		temporaryPlayers[i] = _players[i];
	}

	bool continueLoop = true;
	do
	{
		continueLoop = false;
		for (int i = 1; i < _numberOfPlayers; i++)
		{
			if (temporaryPlayers[i - 1].getPoints() < temporaryPlayers[i].getPoints())
			{
				swap(temporaryPlayers[i - 1], temporaryPlayers[i]);
				continueLoop = true;
			}
		}
	} while (continueLoop);





	int place = 0;

	if (temporaryPlayers[0].getPoints() != temporaryPlayers[1].getPoints())
	{
		place++;
		cout << "Wygaral gracz nr " << temporaryPlayers[0].getPlayerNumber() << ". (" << temporaryPlayers[0].getPlayerName() << "). Ilosc punktow " << temporaryPlayers[0].getPoints() << ". Gratulacje :)" << endl;
	}
	else
	{
		cout << "Mamy remis!" << endl;
		cout << "Wygarali:" << endl;
		cout << "gracz nr " << temporaryPlayers[0].getPlayerNumber() << ". (" << temporaryPlayers[0].getPlayerName() << "). Ilosc punktow " << temporaryPlayers[0].getPoints() << endl;
		
		bool inLoop = true;
		int i = 1;
		do 
		{
			place++;
			inLoop = false;
			if (temporaryPlayers[i].getPoints() == temporaryPlayers[i - 1].getPoints())
			{
				cout << "gracz nr " << temporaryPlayers[i].getPlayerNumber() << ". (" << temporaryPlayers[i].getPlayerName() << "). Ilosc punktow " << temporaryPlayers[i].getPoints() << endl;
				inLoop = true;
			}
			i++;
		} while (inLoop);
		cout << "Gratulacje :)" << endl;
	}

	for (int i = place; i < _numberOfPlayers - 1; i++)
	{
		if (temporaryPlayers[i].getPoints() == temporaryPlayers[i + 1].getPoints() || temporaryPlayers[i].getPoints() == temporaryPlayers[i - 1].getPoints())
		{
			cout << place + 1 << ". miejsce zajal ex aequo gracz nr " << temporaryPlayers[i].getPlayerNumber() << ". (" << temporaryPlayers[i].getPlayerName() << "). Ilosc punktow " << temporaryPlayers[i].getPoints() << endl;
		}
		else
		{
			cout << i + 1 << ". miejsce zajal gracz nr " << temporaryPlayers[i].getPlayerNumber() << ". (" << temporaryPlayers[i].getPlayerName() << "). Ilosc punktow " << temporaryPlayers[i].getPoints() << endl;
			place = i + 1;
		}
	}	

	if (temporaryPlayers[_numberOfPlayers - 1].getPoints() != temporaryPlayers[0].getPoints())
	{
		if (temporaryPlayers[_numberOfPlayers - 1].getPoints() == temporaryPlayers[_numberOfPlayers - 2].getPoints())
		{
			cout << place + 1 << ". miejsce zajal ex aequo gracz nr " << temporaryPlayers[_numberOfPlayers - 1].getPlayerNumber() << ". (" << temporaryPlayers[_numberOfPlayers - 1].getPlayerName() << "). Ilosc punktow " << temporaryPlayers[_numberOfPlayers - 1].getPoints() << endl;
		}
		else
		{
			cout << _numberOfPlayers << ". miejsce zajal gracz nr " << temporaryPlayers[_numberOfPlayers - 1].getPlayerNumber() << ". (" << temporaryPlayers[_numberOfPlayers - 1].getPlayerName() << "). Ilosc punktow " << temporaryPlayers[_numberOfPlayers - 1].getPoints() << endl;
		}
	}

	_getch();

}

void Game::addPoints(const int & numberOfPlayer, const int & amountOfPoints)
{
	_players[numberOfPlayer].addPoints(amountOfPoints);
}

vector<int> Game::getPointsOfAllPlayers()
{
	vector<int> score;

	_words = new string*[_numberOfPlayers];
	_result = new int[_numberOfPlayers];

	for (int i = 0; i < _numberOfPlayers; i++)
	{
		_words[i] = _players[i].getWords();
	}

	for (int i = 0; i < _numberOfPlayers; i++)
	{
		cout << "_words[" << i << "]" << _words[i][0] << endl;
	}

	_result = _round.calculatePoints(_words, _numberOfPlayers);

	for (int i = 0; i < _numberOfPlayers; i++)
	{
		addPoints(i, _result[i]);
	}

	for (int i = 0; i < _numberOfPlayers; i++)
	{
		score.push_back(_result[i]);
	}

	for (int i = 0; i < _numberOfPlayers; i++)
	{
		cout << "_result[" << i << "]" << _result[i] << endl;
	}
	

	return score;
}

void Game::setAnswers(int numberOfPlayer, std::string country, std::string city, std::string thing, std::string plant)
{
	_players[numberOfPlayer].setAnswers(country, city, thing, plant);
}


void Game::endGame()
{
}

void Game::setNumberOfRounds(const int & number)
{
	_numberOfRounds = number;
}

int Game::getNumberOfRounds() const
{
	return _numberOfRounds;
}

const char Game::getCharacter()
{
	return _character;
}

const int Game::getPlayersCount()
{
	return _numberOfPlayers;
}



Game::~Game()
{
	delete[] _players;
	delete _result;
	delete _words;
}
