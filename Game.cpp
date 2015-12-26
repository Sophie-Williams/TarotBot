#include "Game.h"

Tarot::Game::Game(vector<string> playerHand1, vector<string> playerHand2, vector<string> playerHand3, vector<string> playerHand4)
{
	takerPosition = -1;
	players = {
		Player(playerHand1),
		Player(playerHand2),
		Player(playerHand3),
		Player(playerHand4)
	};
}

Tarot::Game::Game()
{
}

Tarot::Game::~Game()
{
}

void Tarot::Game::SetTakerPosition(int takerPosition)
{
	this->takerPosition = takerPosition;
	attackers = { takerPosition };
	defenders = {};
	for (unsigned int i = 0; i < 4; i++) {
		if (i != takerPosition) {
			defenders.push_back(i);
		}
	}
}

void Tarot::Game::PlayCard(int playerPosition, string card)
{
	players[playerPosition].PlayCard(card);
}

void Tarot::Game::AddCards(int playerPosition, vector<string> cards)
{
	players[playerPosition].AddCards(cards);
}

void Tarot::Game::AddTrick(int playerPosition, vector<string> trick)
{
	players[playerPosition].AddTrick(trick);
}

void Tarot::Game::MakeAside(int playerPosition, vector<string> aside)
{
	players[playerPosition].MakeAside(aside);
}
