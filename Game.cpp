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

void Tarot::Game::ReceiveDog(int playerPosition, vector<string> cards)
{
	players[playerPosition].ReceiveDog(cards);
}

void Tarot::Game::WinTheRound(int playerPosition, vector<string> trick)
{
	players[playerPosition].WinTheRound(trick);
}

void Tarot::Game::MakeAside(int playerPosition, vector<string> aside)
{
	players[playerPosition].MakeAside(aside);
}

void Tarot::Game::ExchangeCard(int playerFromPosition, int playerToPosition, string cardFrom, string cardTo)
{
	players[playerFromPosition].ExchangeCard(cardFrom, cardTo, &players[playerToPosition]);
}

float Tarot::Game::GetAttackersScore()
{
	float score = 0;;
	for (unsigned int i = 0; i < attackers.size(); i++) {
		score += players[attackers[i]].GetScore();
	}
	return score;
}

float Tarot::Game::GetDefendersScore()
{
	float score = 0;;
	for (unsigned int i = 0; i < defenders.size(); i++) {
		score += players[defenders[i]].GetScore();
	}
	return score;
}
