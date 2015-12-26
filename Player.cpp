#include "Player.h"

Tarot::Player::Player(vector<string> hand) {
	this->hand = hand;
}

Tarot::Player::~Player() {
}

float Tarot::Player::GetScore() {
	float score = 0;
	for (unsigned int i = 0; i < tricks.size(); i++) {
		score += Deck[tricks[i]].GetScore();
	}
	return score;
}

void Tarot::Player::RemoveCard(string card) {
	// See "Erase-remove idiom" : http://stackoverflow.com/questions/3385229/c-erase-vector-element-by-value-rather-than-by-position
	hand.erase(remove(hand.begin(), hand.end(), card), hand.end());
}

void Tarot::Player::PlayCard(string card) {
	RemoveCard(card);
}

void Tarot::Player::AddCards(vector<string> cards) {
	for (unsigned int i = 0; i < cards.size(); i++) {
		hand.push_back(cards[i]);
	}
}

void Tarot::Player::AddTrick(vector<string> trick) {
	for (unsigned int i = 0; i < trick.size(); i++) {
		tricks.push_back(trick[i]);
	}
}

void Tarot::Player::MakeAside(vector<string> aside) {
	for (unsigned int i = 0; i < aside.size(); i++) {
		RemoveCard(aside[i]);
		tricks.push_back(aside[i]);
	}
}
