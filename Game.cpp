#include "Game.h"

Tarot::Game::Game(int firstPlayer, vector<string> playerHand1, vector<string> playerHand2, vector<string> playerHand3, vector<string> playerHand4) {
	currentRound = 0;
	totalRound = 18;
	baseCard = nullptr;
	highestCard = nullptr;
	takerPosition = -1;
	currentPosition = firstPlayer;
	currentTrickHasFool = false;
	owesACardTo = { -1, -1 };
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

Tarot::Game::Game(const Game &game) {
	this->currentRound = game.currentRound;
	this->totalRound = game.totalRound;
	this->takerPosition = game.takerPosition;
	this->currentPosition = game.currentPosition;
	this->players = game.players;
	this->attackers = game.attackers;
	this->defenders = game.defenders;
	this->currentTrick = game.currentTrick;
	this->baseCard = game.baseCard;
	this->highestCard = game.highestCard;
	this->currentTrickHasFool = game.currentTrickHasFool;
	this->owesACardTo = game.owesACardTo;
	this->highestCardPlayerPosition = game.highestCardPlayerPosition;
	this->revealedDog = game.revealedDog;
	this->cardsPlayed = game.cardsPlayed;
	this->cardsNotPlayed = game.cardsNotPlayed;
}

Tarot::Game::Game() {
}

Tarot::Game::~Game() {
}

void Tarot::Game::SetTakerPosition(int takerPosition) {
	this->takerPosition = takerPosition;
	attackers = { takerPosition };
	defenders = {};
	for (unsigned int i = 0; i < 4; i++) {
		if (i != takerPosition) {
			defenders.push_back(i);
		}
	}
}

void Tarot::Game::PlayCard(int playerPosition, string card) {
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
		highestCardPlayerPosition = playerPosition;
	}

	// The card does not go to the trick
	if (playedCard->IsFool()) {
		// Render to Caesar the things that are Caesar's (give back his fool)
		players[playerPosition].WinCards({ card });
		currentTrickHasFool = true;
		owesACardTo.first = playerPosition;
	}
	// The card goes to the trick
	else {
		currentTrick.push_back(card);

		// Adds usefull data about the player
		if (baseCard->GetSuit() == Suit::Trump) {
			// The player has no more trump
			if (playedCard->GetSuit() != Suit::Trump) {
				players[playerPosition].HasNoMoreSuit(Suit::Trump);
			}
			// The player has no more trump higher than the baseCard
			else if (!playedCard->IsHigher(baseCard)) {
				players[playerPosition].HasNoHigherTrump(baseCard);
			}
		}
		else {
			// The player has no more card of the baseCard's suit
			if (playedCard->GetSuit() == Suit::Trump) {
				players[playerPosition].HasNoMoreSuit(baseCard->GetSuit());
			}
			// The player has no more trump nor more card of the baseCard's suit
			else if (playedCard->GetSuit() != baseCard->GetSuit()) {
				players[playerPosition].HasNoMoreSuit(Suit::Trump);
				players[playerPosition].HasNoMoreSuit(baseCard->GetSuit());
			}
		}
	}

	// Makes the player to play his card
	players[playerPosition].PlayCard(card);
	currentPosition = (currentPosition + 1) % players.size();

	// End of the round
	if (currentTrick.size() == 4 || (currentTrick.size() == 3 && currentTrickHasFool)) {
		WinTheRound(highestCardPlayerPosition, currentTrick);

		// Defines which players have to exchange a card (fool card against dumb card)
		if (currentTrickHasFool) {
			owesACardTo.second = highestCardPlayerPosition;
			currentTrickHasFool = false;
		}
	}
}

void Tarot::Game::ReceiveDog(int playerPosition, vector<string> cards, bool revealed) {
	players[playerPosition].ReceiveDog(cards);

	if (revealed) {
		revealedDog = cards;
	}
}

void Tarot::Game::MakeAside(int playerPosition, vector<string> aside) {
	players[playerPosition].MakeAside(aside);
}

void Tarot::Game::WinTheRound(int winnerPosition, vector<string> trick) {
	players[winnerPosition].WinCards(trick);

	currentPosition = winnerPosition;
	currentRound++;
	currentTrick = {};
	baseCard = nullptr;
	highestCard = nullptr;

	if (currentRound == totalRound) {
		EndOfTheGame();
	}
}

void Tarot::Game::EndOfTheGame() {
	// Exchanges a card (dumb) from the player fromPlayerPosition with a card (fool) of the player toPlayerPosition
	string dumbCard = "";
	int playerFromPosition;
	int playerToPosition = owesACardTo.second;

	vector<int> fromTeam = (owesACardTo.first == takerPosition) ? attackers : defenders;
	for (int playerPosition : fromTeam) {
		string card = players[playerPosition].GetDumbCard();
		if (dumbCard == "" || (card != "" && Deck::Get(card)->GetScore() < Deck::Get(dumbCard)->GetScore())) {
			dumbCard = card;
			playerFromPosition = playerPosition;
		}
	}

	if (dumbCard != "") {
		players[playerFromPosition].GiveDumbCardTo(dumbCard, &players[playerToPosition]);
	}
}

string Tarot::Game::RandomFlow() {
	map<string, float> scores;
	vector<string> playableCards = players[currentPosition].GetPlayableCards(baseCard, highestCard);
	if (playableCards.size() == 1) {
		return playableCards[0];
	}
	for (int i = 0; i < playableCards.size(); i++) {
		scores[playableCards[i]] = 0;
	}

	int maxTimeInSec = 1;
	clock_t begin = clock();
	do {
		int i;
		#pragma omp parallel for
		for (i = 0; i < playableCards.size(); i++) {
			Game clone = *(this);
			clone.PlayCard(clone.currentPosition, playableCards[i]);
			while (clone.currentRound < clone.totalRound) {
				clone.RandomPlay();
			}
			scores[playableCards[i]] += currentPosition == takerPosition ? clone.GetAttackersScore() : clone.GetDefendersScore();
		}
	} while ((double(clock() - begin) / CLOCKS_PER_SEC) < maxTimeInSec);

	string bestCard = playableCards[0];
	for (int i = 1; i < playableCards.size(); i++) {
		if (scores[playableCards[i]] > scores[bestCard]) {
			bestCard = playableCards[i];
		}
	}

	return bestCard;
}

void Tarot::Game::RandomPlay() {
	vector<string> playableCards = players[currentPosition].GetPlayableCards(baseCard, highestCard);
	int randomCard = rand() % playableCards.size();
	PlayCard(currentPosition, playableCards[randomCard]);
}

float Tarot::Game::GetAttackersScore() {
	float score = 0;
	for (unsigned int i = 0; i < attackers.size(); i++) {
		score += players[attackers[i]].GetScore();
	}
	return score;
}

float Tarot::Game::GetDefendersScore() {
	float score = 0;;
	for (unsigned int i = 0; i < defenders.size(); i++) {
		score += players[defenders[i]].GetScore();
	}
	return score;
}
