#pragma once
#include <vector>
#include <algorithm>
#include "Deck.h"

using namespace std;

namespace Tarot {
	class Player
	{
		private:
			// The hand of the player into the current game
			vector<string> hand;

			// The tricks of the player into the current game
			vector<string> tricks;

			// Removes a card from the hand
			void RemoveCard(string card);

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
	};
}

