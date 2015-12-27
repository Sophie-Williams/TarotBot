#pragma once
#include <vector>
#include <algorithm>
#include "Deck.h"

namespace Tarot {
	class Player
	{
		private:
			// The hand of the player into the current game
			vector<string> hand;

			// The tricks of the player into the current game
			vector<string> tricks;

			// Adds a card from the hand
			void AddCardToHand(string card);

			// Adds a card from the tricks
			void AddCardToTricks(string card);

			// Removes a card from the hand
			void RemoveCardFromHand(string card);

			// Removes a card from the tricks
			void RemoveCardFromTricks(string card);

		public:
			// Player constructor
			Player(vector<string> hand);

			// Player destructor
			~Player();

			// Returns the current total score of the player
			float GetScore();

			// Removes a card from the hand
			void PlayCard(string card);

			// Adds cards into the hand
			void AddCards(vector<string> cards);

			// Adds cards into the tricks
			void AddTrick(vector<string> trick);

			// Takes the cards from the hand and put them into the tricks
			void MakeAside(vector<string> aside);

			// Takes the card `cardFrom` from the player tricks
			// and exchanges it against the card `cardTo` from the other player tricks
			void ExchangeCard(string cardFrom, string cardTo, Player* player);
	};
}

