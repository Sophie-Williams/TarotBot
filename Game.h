#pragma once
#include <vector>
#include "Card.h"
#include "Deck.h"
#include "Player.h"

using namespace std;

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

			// Defines the base card of the current round
			Card* baseCard;

			// Defines the highest card of the current round
			Card* highestCard;

			// The dog revealed to players
			vector<string> revealedDog;

			// The current played cards
			vector<string> cardsPlayed;

			// The current not played cards
			vector<string> cardsNotPlayed;

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
			void ReceiveDog(int playerPosition, vector<string> cards, bool revealed);

			// Add the cards to the tricks of the player
			void WinTheRound(int playerPosition, vector<string> trick);

			// Takes the cards from the hand of the player and put them into the tricks
			void MakeAside(int playerPosition, vector<string> aside);

			// Takes the card `cardFrom` from the player `playerFromPosition` tricks
			// and exchanges it against the card `cardTo` from the player `playerToPosition` tricks
			void ExchangeCard(int playerFromPosition, int playerToPosition, string cardFrom, string cardTo);

			// returns the total current score of the attackers
			float GetAttackersScore();

			// returns the total current score of the defenders
			float GetDefendersScore();
	};
}

