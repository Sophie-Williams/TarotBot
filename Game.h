#pragma once
#include <vector>
#include <random>
#include <ctime>
#include <omp.h>
#include "Card.h"
#include "Deck.h"
#include "Player.h"

using namespace std;

namespace Tarot {
	class Game {
		private:
			// The current round
			int currentRound;

			// Total count of round in a game
			int totalRound;

			// The taker position into the current game
			int takerPosition;

			// The current player position into the current game
			int currentPosition;

			// The players into the current game
			vector<Player> players;

			// The attackers into the current game
			vector<int> attackers;

			// The defenders into the current game
			vector<int> defenders;

			// The current trick
			vector<string> currentTrick;

			// Defines the base card of the current trick
			Card* baseCard;

			// Defines the highest card of the current trick
			Card* highestCard;

			// Defines if the current round has the fool
			bool currentTrickHasFool;

			// Defines which player needs to exchange a dumb card against his fool whith which player
			pair<int, int> owesACardTo;

			// Defines the highest card player position in the current round
			int highestCardPlayerPosition;

			// The dog revealed to players
			vector<string> revealedDog;

			// The current played cards
			vector<string> cardsPlayed;

			// The current not played cards
			vector<string> cardsNotPlayed;

		public:
			// Player constructor
			Game(int firstPlayer, vector<string> playerHand1, vector<string> playerHand2, vector<string> playerHand3, vector<string> playerHand4);
			Game(const Game &game);
			Game();

			// Player destructor
			~Game();

			// Defines the taker position into the current game (also defines the attackers and defenders teams)
			void SetTakerPosition(int takerPosition);

			// Makes the player to play a card
			void PlayCard(int playerPosition, string card);

			// Add the cards to the hand of the player
			void ReceiveDog(int playerPosition, vector<string> cards, bool revealed);

			// Takes the cards from the hand of the player and put them into the tricks
			void MakeAside(int playerPosition, vector<string> aside);

			// Add the cards to the tricks of the player
			void WinTheRound(int winnerPosition, vector<string> trick);

			// Resolves the end of the game
			void EndOfTheGame();

			// Randomly plays the current game
			string RandomFlow();

			// Randomly play one move
			void RandomPlay();

			// returns the total current score of the attackers
			float GetAttackersScore();

			// returns the total current score of the defenders
			float GetDefendersScore();
	};
}

