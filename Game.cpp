#include "Game.h"

Tarot::Game::Game(int firstPlayer, vector<string> playerHand1, vector<string> playerHand2, vector<string> playerHand3, vector<string> playerHand4) {
	currentRound = 0;
	totalRound = 18;
	takerPosition = -1;
	currentPosition = firstPlayer;
	players = {
		new Player(playerHand1),
		new Player(playerHand2),
		new Player(playerHand3),
		new Player(playerHand4)
	};
	baseCard = nullptr;
	highestCard = nullptr;
	currentTrickHasFool = false;
	owesACardTo = { -1, -1 };
	highestCardPlayerPosition = -1;
	Deck::Foreach([this](string key, Card* value) {
		cardsNotPlayed.push_back(key);
	});
	colorsPlayed = {
		{ Club, false },
		{ Diamond, false },
		{ Heart, false },
		{ Spade, false }
	};
}

Tarot::Game::Game(const Game &game) {
	this->currentRound = game.currentRound;
	this->totalRound = game.totalRound;
	this->takerPosition = game.takerPosition;
	this->currentPosition = game.currentPosition;
	this->players = {
		new Player(*game.players[0]),
		new Player(*game.players[1]),
		new Player(*game.players[2]),
		new Player(*game.players[3])
	};
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

Tarot::Game::~Game() {
	for (int i = 0; i < playersCount; i++) {
		delete players[i];
	}
}

void Tarot::Game::SetTakerPosition(int takerPosition) {
	this->takerPosition = takerPosition;
	attackers = { takerPosition };
	defenders = {};
	for (int i = 0; i < playersCount; i++) {
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

	// Add usefull data about the game
	if (playedCard->GetSuit() != Trump) {
		colorsPlayed[playedCard->GetSuit()] = true;
	}
	if (currentPosition == takerPosition) {
		takerHasPlayed = true;
	}

	// The card does not go to the trick
	if (playedCard->IsFool()) {
		// Renders to Caesar the things that are Caesar's (gives back his fool)
		players[playerPosition]->WinCards({ card });
		currentTrickHasFool = true;
		owesACardTo.first = playerPosition;
	}
	// The card goes to the trick
	else {
		currentTrick.push_back(card);

		// Adds usefull data about the player
		if (baseCard->GetSuit() == Trump) {
			// The player has no more trump
			if (playedCard->GetSuit() != Trump) {
				players[playerPosition]->HasNoMoreSuit(Trump);
			}
			// The player has no more trump higher than the baseCard
			else if (!playedCard->IsHigher(baseCard)) {
				players[playerPosition]->HasNoHigherTrump(baseCard);
			}
		}
		else {
			// The player has no more card of the baseCard's suit
			if (playedCard->GetSuit() == Trump) {
				players[playerPosition]->HasNoMoreSuit(baseCard->GetSuit());
			}
			// The player has no more trump nor more card of the baseCard's suit
			else if (playedCard->GetSuit() != baseCard->GetSuit()) {
				players[playerPosition]->HasNoMoreSuit(Trump);
				players[playerPosition]->HasNoMoreSuit(baseCard->GetSuit());
			}
		}
	}

	// Makes the player to play his card
	players[playerPosition]->PlayCard(card);
	currentPosition = (currentPosition + 1) % players.size();

	// Ends the round
	if (currentTrick.size() == playersCount || (currentTrick.size() == (playersCount - 1) && currentTrickHasFool)) {
		WinTheRound(highestCardPlayerPosition, currentTrick);
	}
}

void Tarot::Game::ReceiveDog(int playerPosition, vector<string> cards, Bid takeLevel) {
	players[playerPosition]->ReceiveDog(cards);
	this->takeLevel = takeLevel;

	if (takeLevel > Pass && takeLevel < GuardWithout) {
		revealedDog = cards;
	}
}

void Tarot::Game::MakeAside(int playerPosition, vector<string> aside) {
	players[playerPosition]->MakeAside(aside);
}

void Tarot::Game::WinTheRound(int winnerPosition, vector<string> trick) {
	// Defines which players have to exchange a card (fool card against dumb card)
	if (currentTrickHasFool) {
		owesACardTo.second = highestCardPlayerPosition;
	}

	// Gives the trick to the winner
	players[winnerPosition]->WinCards(trick);

	// Resets trick/round data
	currentPosition = winnerPosition;
	currentRound++;
	currentTrick = {};
	baseCard = nullptr;
	highestCard = nullptr;
	highestCardPlayerPosition = -1;
	takerHasPlayed = false;
	currentTrickHasFool = false;

	// Ends the game
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
		string card = players[playerPosition]->GetDumbCard();
		if (dumbCard == "" || (card != "" && Deck::Get(card)->GetScore() < Deck::Get(dumbCard)->GetScore())) {
			dumbCard = card;
			playerFromPosition = playerPosition;
		}
	}

	if (dumbCard != "") {
		players[playerFromPosition]->GiveDumbCardTo(dumbCard, players[playerToPosition]);
	}
}

float Tarot::Game::GetAttackersScore() {
	float score = 0;
	for (int i = 0; i < attackers.size(); i++) {
		score += players[attackers[i]]->GetScore();
	}
	return score;
}

float Tarot::Game::GetDefendersScore() {
	float score = 0;;
	for (int i = 0; i < defenders.size(); i++) {
		score += players[defenders[i]]->GetScore();
	}
	return score;
}




Tarot::Game::Node::Node(Game* state) {
	this->state = state;
	children = state->players[state->currentPosition]->GetPlayableCards(state->baseCard, state->highestCard);
	maxChild = "";
	maxScore = -10000;

	if (children.size() == 1) {
		maxChild = children[0];
		return;
	}

	// Simulates a round
	for (int i = 0; i < children.size(); i++) {
		string currentChild = children[i];

		// Simulates a child move
		Game* clone = new Game(*state);
		clone->PlayCard(clone->currentPosition, currentChild);

		// Continues until the end of the turn
		if (clone->currentTrick.size() > 0) {
			Node n = Node(clone);
		}

		// Get child score
		float currentScore;
		if (state->currentPosition == state->takerPosition) {
			currentScore = clone->GetAttackersScore() - clone->GetDefendersScore();
		}
		else {
			currentScore = clone->GetDefendersScore() - clone->GetAttackersScore();
		}

		// Updates if better
		if (maxScore < currentScore) {
			maxScore = currentScore;
			maxChild = currentChild;
		}
		delete clone;
	}
}

string Tarot::Game::Node::GetMax() {
	return maxChild;
}




string Tarot::Game::GetNextMinMaxCard() {
	Game* clone = new Game(*this);
	Node root = Node(clone);
	return root.GetMax();
	return "";
}

string Tarot::Game::GetNextFoolHeuristicCard() {
	vector<string> cards = players[currentPosition]->GetPlayableCards(baseCard, highestCard);
	if (cards.size() == 1) {
		return cards[0];
	}
	bool playerHasFool = false;
	bool playerHasPetit = false;
	for (int i = 0; i < cards.size(); i++) {
		Card* potentialCard = Deck::Get(cards[i]);
		if (potentialCard->IsFool()) {
			playerHasFool = true;
		}
		else if (potentialCard->IsPetit()) {
			playerHasPetit = true;
		}
	}

	// If the player has the fool but not the petit
	if (playerHasFool && !playerHasPetit) {
		bool isTaker = currentPosition == takerPosition;
		bool lastPlayer = currentTrick.size() == (playersCount - 1) || (currentTrick.size() == (playersCount - 2) && currentTrickHasFool);
		bool takerIsMaster = highestCardPlayerPosition == takerPosition;
		bool canOvertrump = Deck::Get(cards[0])->IsHigher(highestCard) || Deck::Get(cards[1])->IsHigher(highestCard);
		float trickScore = 0;
		for (int i = 0; i < currentTrick.size(); i++) {
			trickScore += Deck::Get(currentTrick[i])->GetScore();
		}

		// If defender
			// If the taker has played && he is not master of the trick
			// or
			// If last player && the taker is master && trick score < 2
			// or
			// If must pissed
		if (!isTaker) {
			if ((takerHasPlayed && !takerIsMaster) || (lastPlayer && takerIsMaster && trickScore < 2) || (!canOvertrump)) {
				return "trump-fool";
			}
		}

		// If taker
			// If last player && trick score < 2
			// or
			// If must pissed
		else {
			if ((lastPlayer && trickScore < 2) || (!canOvertrump)) {
				return "trump-fool";
			}
		}
	}

	// Can return nothing
	return "";
}

string Tarot::Game::GetNextTrumpHeuristicCard() {
	vector<string> cards = players[currentPosition]->GetPlayableCards(baseCard, highestCard);
	if (cards.size() == 1) {
		return cards[0];
	}

	bool isTaker = currentPosition == takerPosition;
	bool lastPlayer = currentTrick.size() == (playersCount - 1) || (currentTrick.size() == (playersCount - 2) && currentTrickHasFool);
	bool takerIsMaster = highestCardPlayerPosition == takerPosition;
	bool canOvertrump = Deck::Get(cards[0])->IsHigher(highestCard) || Deck::Get(cards[1])->IsHigher(highestCard);
	float trickScore = 0;
	for (int i = 0; i < currentTrick.size(); i++) {
		trickScore += Deck::Get(currentTrick[i])->GetScore();
	}

	// Si défenseur
		// Si doit pisser
			// Si preneur après ou preneur maitre
				// => Mettre le plus petit atout (saut petit)
			// Sinon
				// Mettre le plus petit atout (petit compris)
		// Sinon (si maitre)
			// Si preneur après
				// Si point > 3 && certain d'assur le pli
					// => Asurer le pli (avec le plus petit atout nécessaire sauf petit ni excuse)
				// Sinon
					// => Mettre le plus petit atout (sauf petit)
			// Sinon
				// Mettre le plus petit atout (petit compris)
	if (!isTaker) {
		if (!canOvertrump) {
			if (!takerHasPlayed || takerIsMaster) {
				string minCard = "";
				for (int i = 0; i < cards.size(); i++) {
					Card* potentialCard = Deck::Get(cards[i]);
					if (minCard == "" || Deck::Get(minCard)->IsHigher(potentialCard)) {
						if (potentialCard->GetRank() != One && !players[takerPosition]->CanHaveHigherTrump(potentialCard)) {
							minCard = cards[i];
						}
					}
				}
				return minCard;
			}
			else {
				string minCard = "";
				for (int i = 0; i < cards.size(); i++) {
					Card* potentialCard = Deck::Get(cards[i]);
					if (minCard == "" || Deck::Get(minCard)->IsHigher(potentialCard)) {
						if (potentialCard->GetRank() != Fool && potentialCard->GetRank() != One && !players[takerPosition]->CanHaveHigherTrump(potentialCard)) {
							minCard = cards[i];
						}
					}
				}
				return minCard;
			}
		}
		else {
			if (!takerHasPlayed) {
				string minCardExceptPetit = "";
				string minCardToBeMaster = "";
				for (int i = 0; i < cards.size(); i++) {
					Card* potentialCard = Deck::Get(cards[i]);
					if (minCardExceptPetit == "" || Deck::Get(minCardExceptPetit)->IsHigher(potentialCard)) {
						if (potentialCard->GetRank() != One) {
							minCardExceptPetit = cards[i];
						}
					}
					if (minCardToBeMaster == "" || Deck::Get(minCardToBeMaster)->IsHigher(potentialCard)) {
						if (potentialCard->GetRank() != Fool && !players[takerPosition]->CanHaveHigherTrump(potentialCard)) {
							minCardToBeMaster = cards[i];
						}
					}
				}
				if (trickScore > 3 && minCardToBeMaster != "") {
					return minCardToBeMaster;
				}
				return minCardExceptPetit;
			}
			else {
				string minCard = "";
				for (int i = 0; i < cards.size(); i++) {
					Card* potentialCard = Deck::Get(cards[i]);
					if (minCard == "" || Deck::Get(minCard)->IsHigher(potentialCard)) {
						if (potentialCard->GetRank() != Fool) {
							minCard = cards[i];
						}
					}
				}
				return minCard;
			}
		}
	}

	// Si attaquant
		// Si doit pisser
			// => Mettre le plus petit atout nécessaire (sauf petit)
		// Sinon
			// Si c'est une de ses coupes (et première fois qu'il coupe)
				// Mettre le plus petit atout (petit compris)
			// Si adversaire après
				// Si point > 3 && certain d'assur le pli
					// => Asurer le pli (avec le plus petit atout nécessaire sauf petit ni excuse)
				// Sinon
					// => Mettre le plus petit atout (sauf petit)
			// Sinon
				// Mettre le plus petit atout (petit compris)
	else {
		if (!canOvertrump) {
			string minCard = "";
			for (int i = 0; i < cards.size(); i++) {
				Card* potentialCard = Deck::Get(cards[i]);
				if (minCard == "" || Deck::Get(minCard)->IsHigher(potentialCard)) {
					if (potentialCard->GetRank() != One && !players[takerPosition]->CanHaveHigherTrump(potentialCard)) {
						minCard = cards[i];
					}
				}
			}
			return minCard;
		}
		else {
			if (baseCard->GetSuit() != Trump && players[currentPosition]->CanHaveSuit(baseCard->GetSuit()) && !players[currentPosition]->HasPlayedSuit(baseCard->GetSuit()) && (Deck::Get(cards[0])->GetSuit() == Trump || Deck::Get(cards[1])->GetSuit() == Trump)) {
				string minCard = "";
				for (int i = 0; i < cards.size(); i++) {
					Card* potentialCard = Deck::Get(cards[i]);
					if (minCard == "" || Deck::Get(minCard)->IsHigher(potentialCard)) {
						if (!players[takerPosition]->CanHaveHigherTrump(potentialCard)) {
							minCard = cards[i];
						}
					}
				}
				return minCard;
			}
			else if (!lastPlayer) {
				string minCardExceptPetit = "";
				string minCardToBeMaster = "";
				for (int i = 0; i < cards.size(); i++) {
					Card* potentialCard = Deck::Get(cards[i]);
					if (minCardExceptPetit == "" || Deck::Get(minCardExceptPetit)->IsHigher(potentialCard)) {
						if (potentialCard->GetRank() != One) {
							minCardExceptPetit = cards[i];
						}
					}
					if (minCardToBeMaster == "" || Deck::Get(minCardToBeMaster)->IsHigher(potentialCard)) {
						if (potentialCard->GetRank() != Fool && potentialCard->GetRank() != One && !players[takerPosition]->CanHaveHigherTrump(potentialCard)) {
							minCardToBeMaster = cards[i];
						}
					}
				}
				if (trickScore > 3 && minCardToBeMaster != "") {
					return minCardToBeMaster;
				}
				return minCardExceptPetit;
			}
			else {
				string minCard = "";
				for (int i = 0; i < cards.size(); i++) {
					Card* potentialCard = Deck::Get(cards[i]);
					if (minCard == "" || Deck::Get(minCard)->IsHigher(potentialCard)) {
						if (!players[takerPosition]->CanHaveHigherTrump(potentialCard)) {
							minCard = cards[i];
						}
					}
				}
				return minCard;
			}
		}
	}
}

string Tarot::Game::GetNextCutHeuristicCard() {
	vector<string> cards = players[currentPosition]->GetPlayableCards(baseCard, highestCard);
	if (cards.size() == 1) {
		return cards[0];
	}

	// Retrieves not played colors where the current player has a dumb card or a king
	map<Suit, string> colorsWithDumb;
	map<Suit, string> colorsWithKing;
	for (int i = 0; i < cards.size(); i++) {
		Card* card = Deck::Get(cards[i]);
		Suit cardSuit = card->GetSuit();
		if (cardSuit != Trump && !colorsPlayed[cardSuit]) {
			if (card->GetRank() == King) {
				colorsWithKing[cardSuit] = cards[i];
			}
			else if(card->GetScore() == 0.5 && (colorsWithDumb.count(cardSuit) == 0 || Deck::Get(colorsWithDumb[cardSuit])->IsHigher(card))) {
				colorsWithDumb[cardSuit] = cards[i];
			}
		}
	}
	int takerCutsCount = players[takerPosition]->GetCutsCount();
	int takerSingletonsCount = players[takerPosition]->GetSingletonsCount();

	// Foreach colors
		// If the player as a dumb card BUT no king (priority to save other player king)
			// => Play the dumb card
	for (Suit color : Colors) {
		if (colorsWithDumb.count(color) == 1 && colorsWithKing.count(color) == 0) {
			return colorsWithDumb[color];
		}
	}

	// Foreach colors
		// If the player as a king and taker already cut in 2+ other colors, or cut in 1+ other color + singleton in 1+ other color, or taker just do a "take" and cut in 1+ other color
			// => Play the king
	for (Suit color : Colors) {
		if (colorsWithKing.count(color) == 1 && (takerCutsCount >= 2 || (takerCutsCount >= 1 && (takerSingletonsCount >= 1 || takeLevel == Take)))) {
			return colorsWithKing[color];
		}
	}

	// Foreach colors
		// If the player as a dumb
			// => Play the dumb card
	for (Suit color : Colors) {
		if (colorsWithDumb.count(color)) {
			return colorsWithDumb[color];
		}
	}

	// Can return nothing
	return "";
}

string Tarot::Game::GetNextSingletonHeuristicCard() {
	vector<string> cards = players[currentPosition]->GetPlayableCards(baseCard, highestCard);
	if (cards.size() == 1) {
		return cards[0];
	}

	// Retrieves colors only played once where the taker does not cut and the current player has a dumb card or a king or a queen
	map<Suit, string> colorsWithDumb;
	map<Suit, string> colorsWithQueen;
	map<Suit, string> colorsWithKing;
	map<Suit, bool> colorsWithKingPlayed = { { Club, false }, { Diamond, false }, { Heart, false }, { Spade, false } };
	map<Suit, bool> colorsWithQueenPlayed = { { Club, false },{ Diamond, false },{ Heart, false },{ Spade, false } };
	for (int i = 0; i < cards.size(); i++) {
		Card* card = Deck::Get(cards[i]);
		Suit cardSuit = card->GetSuit();
		if (cardSuit != Trump && players[takerPosition]->CanHaveSuit(cardSuit) && players[takerPosition]->HasPlayedSuitOnce(cardSuit)) {
			if (card->GetRank() == King) {
				colorsWithKing[cardSuit] = cards[i];
			}
			else if (card->GetRank() == Queen) {
				colorsWithQueen[cardSuit] = cards[i];
			}
			else if (card->GetScore() == 0.5 && (colorsWithDumb.count(cardSuit) == 0 || Deck::Get(colorsWithDumb[cardSuit])->IsHigher(card))) {
				colorsWithDumb[cardSuit] = cards[i];
			}
		}
	}
	for (int i = 0; i < cardsPlayed.size(); i++) {
		Card* card = Deck::Get(cardsPlayed[i]);
		Suit cardSuit = card->GetSuit();
		if (cardSuit != Trump) {
			if (card->GetRank() == King) {
				colorsWithKingPlayed[cardSuit] = true;
			}
			else if (card->GetRank() == Queen) {
				colorsWithQueenPlayed[cardSuit] = true;
			}
		}
	}
	int takerCutsCount = players[takerPosition]->GetCutsCount();
	int takerSingletonsCount = players[takerPosition]->GetSingletonsCount();

	// Foreach colors
		// If the player as a dumb card BUT no king nor queen (priority to save other player king or queen (if not already played))
			// => Play the dumb card
	for (Suit color : Colors) {
		if (colorsWithDumb.count(color) == 1 && colorsWithKing.count(color) == 0 && colorsWithQueen.count(color) == 0 && (!colorsWithQueenPlayed[color] || !colorsWithKingPlayed[color])) {
			return colorsWithDumb[color];
		}
	}

	// Foreach colors
		// If the player as a king and taker already cut in 1+ other colors, or singleton in 1+ other color, or taker just do a "take" and cut in 1+ other color
			// => Play the king
		// Else if the player as the queen and the king has already been played
			// => Play the queen
	for (Suit color : Colors) {
		if (colorsWithKing.count(color) == 1 && (takerCutsCount >= 1 || takerSingletonsCount >= 1 || takeLevel == Take)) {
			return colorsWithKing[color];
		}
		else if (colorsWithQueen.count(color) == 1 && colorsWithKingPlayed[color]) {
			return colorsWithQueen[color];
		}
	}

	// Foreach colors
		// If the player as a dumb
			// => Play the dumb card
	for (Suit color : Colors) {
		if (colorsWithDumb.count(color)) {
			return colorsWithDumb[color];
		}
	}

	// Can return nothing
	return "";
}
