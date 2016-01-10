#include "Player.h"

Tarot::Player::Player(vector<string> hand) {
	this->hand = hand;
	hasSuit[Club] = true;
	hasSuit[Diamond] = true;
	hasSuit[Heart] = true;
	hasSuit[Spade] = true;
	hasSuit[Trump] = true;
	maxTrump = Deck::Get("trump-21");
}

Tarot::Player::~Player() {
}

float Tarot::Player::GetScore() {
	float score = 0;
	for (unsigned int i = 0; i < tricks.size(); i++) {
		score += Deck::Get(tricks[i])->GetScore();
	}
	return score;
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

void Tarot::Player::PlayCard(string card) {
	RemoveCardFromHand(card);
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
	bool hasThisSuit = hasSuit[card->GetSuit()];

	if (card->GetSuit() == Suit::Trump) {
		return card->IsFool() || (hasThisSuit && card->GetRank() < maxTrump->GetRank());
	}

	return hasThisSuit;
}

bool Tarot::Player::IsPlayableCard(Card* card, Card* baseCard, Card* highestCard) {
	/*if (card->GetSuit() == baseCard->GetSuit()) {
		if (baseCard->GetSuit() == Suit::Trump && maxTrump) {
			return card->GetRank() > highestCard->GetRank();
		}
		return true;
	}*/
}

vector<string> Tarot::Player::GetPlayableCards(Card* baseCard, Card* highestCard) {
	// If no base card, the player can play whatever he wants
	if (baseCard == nullptr) {
		return hand;
	}

	// If the player has no card of the required suit
	if (!hasSuit[baseCard->GetSuit()]) {
		// If the player pisses, he can play whatever he wants
		if (!hasSuit[Suit::Trump]) {
			return hand;
		}
		// Else the player must play a trump (or the fool)
		else {
			// A trump higher than highestCard
			if (/* if player has trump > highestCard */) {

			}
			// Any trump
			else {

			}
		}
	}
	// Else, the player must play in this suit (or the fool)
	else {
		if (baseCard->GetSuit() == Suit::Trump) {
			// A trump higher than highestCard
			if (/* if player has trump > highestCard */) {

			}
			// Any trump
			else {

			}
		}
		else {

		}
	}

	// Else, we must loop through his hand to loop for any playable card
	/*vector<string> playableCards;
	for (int i = 0; i < hand.size(); i++) {
		if (IsPlayableCard(Deck::Get(hand[i]), baseCard, highestCard)) {
			playableCards.push_back(hand[i]);
		}
	}
	return playableCards;*/
}
