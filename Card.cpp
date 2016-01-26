#include "Card.h"
#include <vector>

using namespace std;

Tarot::Card::Card(Suit suit, Rank rank) {
	this->suit = suit;
	this->rank = rank;
	if (suit == Trump) {
		if (rank == One || rank == TwentyOne || rank == Fool) {
			this->score = 4.5;
		}
		else {
			this->score = 0.5;
		}
	}
	else {
		if (rank == King) {
			this->score = 4.5;
		}
		else if (rank == Queen) {
			this->score = 3.5;
		}
		else if (rank == Knight) {
			this->score = 2.5;
		}
		else if (rank == Jack) {
			this->score = 1.5;
		}
		else {
			this->score = 0.5;
		}
	}
}

Tarot::Suit Tarot::Card::GetSuit() {
	return suit;
}

Tarot::Rank Tarot::Card::GetRank() {
	return rank;
}

float Tarot::Card::GetScore() {
	return score;
}

bool Tarot::Card::IsOudler() {
	return (suit == Trump) && (rank == One || rank == TwentyOne || rank == Fool);
}

bool Tarot::Card::IsFool() {
	return suit == Trump && rank == Fool;
}

bool Tarot::Card::IsPetit() {
	return suit == Trump && rank == One;
}

bool Tarot::Card::IsWorld() {
	return suit == Trump && rank == TwentyOne;
}

bool Tarot::Card::Equals(Card* card) {
	return this->suit == card->suit && this->rank == card->rank;
}

bool Tarot::Card::IsHigher(Card* card) {
	return
		(this->suit == card->suit && this->rank > card->rank)
		||
		(!this->IsFool() && this->suit == Trump && card->suit != Trump);
}
