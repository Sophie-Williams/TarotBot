#include "Player.h"

Tarot::Player::Player(vector<string> hand) {
	this->hand = hand;

	// Private statistics
	suitLength[Club] = 0;
	suitLength[Diamond] = 0;
	suitLength[Heart] = 0;
	suitLength[Spade] = 0;
	suitLength[Trump] = 0; // Excluding the fool
	for (string cardKey : hand) {
		Card* card = Deck::Get(cardKey);
		if (!card->IsFool()) {
			suitLength[card->GetSuit()]++;
			if (card->GetSuit() == Suit::Trump) {
				sortedTrumps.push_back(cardKey);
			}
		}
	}
	sort(sortedTrumps.begin(), sortedTrumps.end(), [](string trumpKey1, string trumpKey2) {
		return Deck::Get(trumpKey1)->GetRank() < Deck::Get(trumpKey2)->GetRank();
	});

	// Public statistics
	canHaveSuit[Club] = true;
	canHaveSuit[Diamond] = true;
	canHaveSuit[Heart] = true;
	canHaveSuit[Spade] = true;
	canHaveSuit[Trump] = true; // Excluding the fool
	canHaveMaxTrump = Deck::Get("trump-21");
}

Tarot::Player::~Player() {
}

bool Tarot::Player::HasSuit(Suit suit) {
	return suitLength[suit] > 0;
}

bool Tarot::Player::HasHigherTrump(Card* trump) {
	return Deck::Get(sortedTrumps.back())->GetRank() > trump->GetRank();
}

void Tarot::Player::AddCardToHand(string card) {
	hand.push_back(card);
}

void Tarot::Player::AddCardToTricks(string card) {
	tricks.push_back(card);
}

void Tarot::Player::RemoveCardFromHand(string card) {
	// See "Erase-remove idiom" : http://stackoverflow.com/questions/3385229/c-erase-vector-element-by-value-rather-than-by-position
	hand.erase(remove(hand.begin(), hand.end(), card), hand.end());
}

void Tarot::Player::RemoveCardFromTricks(string card) {
	// See "Erase-remove idiom" : http://stackoverflow.com/questions/3385229/c-erase-vector-element-by-value-rather-than-by-position
	tricks.erase(remove(tricks.begin(), tricks.end(), card), tricks.end());
}

void Tarot::Player::RemoveCardFromSortedTrumps(string card) {
	// See "Erase-remove idiom" : http://stackoverflow.com/questions/3385229/c-erase-vector-element-by-value-rather-than-by-position
	sortedTrumps.erase(remove(sortedTrumps.begin(), sortedTrumps.end(), card), sortedTrumps.end());
}

float Tarot::Player::GetScore() {
	float score = 0;
	for (unsigned int i = 0; i < tricks.size(); i++) {
		score += Deck::Get(tricks[i])->GetScore();
	}
	return score;
}

void Tarot::Player::PlayCard(string card) {
	RemoveCardFromHand(card);

	// Updates private player statistics
	Card* cardPlayed = Deck::Get(card);
	if (!cardPlayed->IsFool()) {
		// Reduces suit length
		suitLength[cardPlayed->GetSuit()]--;
		if (cardPlayed->GetSuit() == Suit::Trump) {
			// Removes from sortedTrumps
			RemoveCardFromSortedTrumps(card);
		}
	}
}

void Tarot::Player::ReceiveDog(vector<string> cards) {
	for (unsigned int i = 0; i < cards.size(); i++) {
		AddCardToHand(cards[i]);
	}
}

void Tarot::Player::WinTheRound(vector<string> trick) {
	for (unsigned int i = 0; i < trick.size(); i++) {
		AddCardToTricks(trick[i]);
	}
}

void Tarot::Player::MakeAside(vector<string> aside) {
	for (unsigned int i = 0; i < aside.size(); i++) {
		RemoveCardFromHand(aside[i]);
		AddCardToTricks(aside[i]);
	}
}

void Tarot::Player::ExchangeCard(string cardFrom, string cardTo, Player* player) {
	this->RemoveCardFromTricks(cardFrom);
	player->RemoveCardFromTricks(cardTo);
	this->AddCardToTricks(cardTo);
	player->AddCardToTricks(cardFrom);
}

bool Tarot::Player::CanHave(Card* card) {
	bool canHaveThisSuit = CanHaveSuit(card->GetSuit());

	if (card->GetSuit() == Suit::Trump) {
		return card->IsFool() || (canHaveThisSuit && CanHaveHigherTrump(card));
	}

	return canHaveThisSuit;
}

bool Tarot::Player::CanHaveSuit(Suit suit) {
	return canHaveSuit[suit];
}

bool Tarot::Player::CanHaveHigherTrump(Card * trump) {
	return trump->GetRank() < canHaveMaxTrump->GetRank();
}

void Tarot::Player::HasNoMoreSuit(Suit suit) {
	canHaveSuit[suit] = false;
}

void Tarot::Player::HasNoHigherTrump(Card* trump) {
	canHaveMaxTrump = trump;
}

pair<string, Tarot::Card*> Tarot::Player::GetPlayConstraints(Card* baseCard, Card* highestCard) {
	// If no base card, the player can play whatever he wants
	if (baseCard == nullptr) {
		return pair<string, Card*>("anyCards", nullptr);
	}

	// If the player has no card of the required suit
	if (!HasSuit(baseCard->GetSuit())) {
		// If the player pisses, he can play whatever he wants
		if (!HasSuit(Suit::Trump)) {
			return pair<string, Card*>("anyCards", nullptr);
		}
		// Else the player must play a trump (or the fool)
		else {
			// A trump higher than highestCard
			if (highestCard->GetSuit() == Suit::Trump && HasHigherTrump(highestCard)) {
				return pair<string, Card*>("trumpsHigherThan", highestCard);
			}
			// Any trump
			else {
				return pair<string, Card*>("anyCardsInSameSuit", highestCard);
			}
		}
	}
	// Else, the player must play in this suit (or the fool)
	else {
		// A trump higher than highestCard
		if (baseCard->GetSuit() == Suit::Trump && HasHigherTrump(highestCard)) {
			return pair<string, Card*>("trumpsHigherThan", highestCard);
		}
		// Any card of this suit
		else {
			return pair<string, Card*>("anyCardsInSameSuit", baseCard);
		}
	}
}

vector<string> Tarot::Player::GetPlayableCards(Card* baseCard, Card* highestCard) {
	pair<string, Card*> playConstraints = GetPlayConstraints(baseCard, highestCard);
	vector<string> playableCards;
	for (string cardKey : hand) {
		Card* card = Deck::Get(cardKey);
		if (
			(playConstraints.first == "anyCards")
			||
			(card->IsFool())
			||
			(playConstraints.first == "trumpsHigherThan" && card->GetSuit() == Suit::Trump && card->IsHigher(playConstraints.second))
			||
			(playConstraints.first == "anyCardsInSameSuit" && card->GetSuit() == playConstraints.second->GetSuit())
		) {
			playableCards.push_back(cardKey);
		}
	}
	return playableCards;
}
