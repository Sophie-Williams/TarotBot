#pragma once
#include <vector>
#include "Player.h"
#include "Card.h"

namespace Tarot {
	class Game
	{
		private:
			// The taker position into the current game
			int takerPosition;

			// The players into the current game
			vector<Player> players;

			// The attackers into the current game
			vector<int> attackers;

			// The defenders into the current game
			vector<int> defenders;

		public:
			// Player constructor
			Game(vector<string> playerHand1, vector<string> playerHand2, vector<string> playerHand3, vector<string> playerHand4);
			Game();

			// Player destructor
			~Game();

			// Defines the taker position into the current game (also defines the attackers and defenders teams)
			void SetTakerPosition(int takerPosition);

			// Makes the player to play a card
			void PlayCard(int playerPosition, string card);

			// Add the cards to the hand of the player
			void AddCards(int playerPosition, vector<string> cards);

			// Add the cards to the tricks of the player
			void AddTrick(int playerPosition, vector<string> trick);

			// Takes the cards from the hand of the player and put them into the tricks
			void MakeAside(int playerPosition, vector<string> aside);

			// returns the total current score of the attackers
			float GetAttackersScore();

			// returns the total current score of the defenders
			float GetDefendersScore();
	};
}

