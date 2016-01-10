#include "Game.h"

Tarot::Game::Game(vector<string> playerHand1, vector<string> playerHand2, vector<string> playerHand3, vector<string> playerHand4)
{
	baseCard = nullptr;
	highestCard = nullptr;
	takerPosition = -1;
	players = {
		Player(playerHand1),
		Player(playerHand2),
		Player(playerHand3),
		Player(playerHand4)
	};
	Deck::Foreach([this](string key, Card value) {
		cardsNotPlayed.push_back(key);
	});
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
	// Adds the card to the played cards
	cardsPlayed.push_back(card);

	// Removes the card from the not played cards
	cardsNotPlayed.erase(remove(cardsNotPlayed.begin(), cardsNotPlayed.end(), card), cardsNotPlayed.end());

	// Defines the base card of the round
	Card* playedCard = Deck::Get(card);
	if (baseCard == nullptr && !playedCard->IsFool()) {
		baseCard = playedCard;
	}

	// Defines the higher card of the round
	if (highestCard == nullptr || playedCard->IsHigher(highestCard)) {
		highestCard = playedCard;
	}

	// Adds usefull data about the player
	if (!playedCard->IsFool()) {
		if (baseCard->GetSuit() == Suit::Trump) {
			// The player has no more trump
			if (playedCard->GetSuit() != Suit::Trump) {
				players[playerPosition].hasSuit[Suit::Trump] = false;
			}
			// The player has no more trump higher than the baseCard
			else if (!playedCard->IsHigher(baseCard)) {
				players[playerPosition].maxTrump = baseCard;
			}
		}
		else {
			// The player has no more card of the baseCard's suit
			if (playedCard->GetSuit() == Suit::Trump) {
				players[playerPosition].hasSuit[baseCard->GetSuit()] = false;
			}
			// The player has no more trump nor more card of the baseCard's suit
			else if (playedCard->GetSuit() != baseCard->GetSuit()) {
				players[playerPosition].hasSuit[Suit::Trump] = false;
				players[playerPosition].hasSuit[baseCard->GetSuit()] = false;
			}
		}

	}

	players[playerPosition].PlayCard(card);
}

void Tarot::Game::ReceiveDog(int playerPosition, vector<string> cards)
{
	players[playerPosition].ReceiveDog(cards);
}

void Tarot::Game::WinTheRound(int playerPosition, vector<string> trick)
{
	players[playerPosition].WinTheRound(trick);

	baseCard = nullptr;
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
