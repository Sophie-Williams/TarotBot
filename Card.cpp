#include "Card.h"

Tarot::Card::Card(Suit suit, Rank rank)
{
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

Tarot::Card::Card()
{
}

Tarot::Card::~Card()
{
}

Tarot::Suit Tarot::Card::GetSuit()
{
	return suit;
}

Tarot::Rank Tarot::Card::GetRank()
{
	return rank;
}

float Tarot::Card::GetScore()
{
	return score;
}
