#include "Player.h"

Tarot::Player::Player(vector<string> hand) {
	this->hand = hand;
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

void Tarot::Player::AddCards(vector<string> cards) {
	for (unsigned int i = 0; i < cards.size(); i++) {
		AddCardToHand(cards[i]);
	}
}

void Tarot::Player::AddTrick(vector<string> trick) {
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
