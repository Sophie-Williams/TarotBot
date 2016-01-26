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

	// Defines all the card suits into the Tarot game
	const enum Bid { Pass, Take, Guard, GuardWithout, GuardAgainst };

	class Game {
		private:
			// A structure that defines the MinMax Algorithm Tree
			class Node {
				private:
					// Currente state of the Node (defines the root of the current tree)
					Game* state;

					// Defines the child nodes (by card's key)
					vector<string> children;

					// Defines the current max score
					float maxScore;

					// Defines the child with the current max score
					string maxChild;

				public:
					// Node constructor
					Node(Game* state);

					// Returns the child with the max score
					string GetMax();
			};

			// Number of player
			const int playersCount = 4;

			// The current round
			int currentRound;

			// Total count of round in a game
			int totalRound;

			// The taker position into the current game
			int takerPosition;

			// The current player position into the current game
			int currentPosition;

			// Defines the take level
			Bid takeLevel;

			// The players into the current game
			vector<Player*> players;

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

			// Defines if the taker already played
			bool takerHasPlayed;

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

			// The current played colors
			map<Suit, bool> colorsPlayed;

		public:
			// Game constructor
			Game(int firstPlayer, vector<string> playerHand1, vector<string> playerHand2, vector<string> playerHand3, vector<string> playerHand4);

			// Game cloning constructor
			Game(const Game &game);

			// Game destructor
			~Game();

			// Defines the taker position into the current game (also defines the attackers and defenders teams)
			void SetTakerPosition(int takerPosition);

			// Makes the player to play a card
			void PlayCard(int playerPosition, string card);

			// Add the cards to the hand of the player
			void ReceiveDog(int playerPosition, vector<string> cards, Bid takeLevel);

			// Takes the cards from the hand of the player and put them into the tricks
			void MakeAside(int playerPosition, vector<string> aside);

			// Add the cards to the tricks of the player
			void WinTheRound(int winnerPosition, vector<string> trick);

			// Resolves the end of the game
			void EndOfTheGame();

			// returns the total current score of the attackers
			float GetAttackersScore();

			// returns the total current score of the defenders
			float GetDefendersScore();



			// Returns the best next card to play (using min-max algorithm)
			string GetNextMinMaxCard();

			// Returns the best next card to play (using a meta-heuristic for the fool)
			string GetNextFoolHeuristicCard();

			// Returns the best next card to play (using a meta-heuristic for trumps)
			string GetNextTrumpHeuristicCard();

			// Returns the best next card to play (using a meta-heuristic to find taker cuts)
			string GetNextCutHeuristicCard();

			// Returns the best next card to play (using a meta-heuristic to find taker singletons)
			string GetNextSingletonHeuristicCard();
	};
}

