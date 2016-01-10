#pragma once
#include <vector>
#include <algorithm>
#include "Card.h"
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

			// Adds a card from the hand
			void AddCardToHand(string card);

			// Adds a card from the tricks
			void AddCardToTricks(string card);

			// Removes a card from the hand
			void RemoveCardFromHand(string card);

			// Removes a card from the tricks
			void RemoveCardFromTricks(string card);

		public:
			// Defines which suits the player have (based on public statistics)
			map<Suit, bool> hasSuit;

			// Defines the higher trump the player can have (based on public statistics)
			Card* maxTrump;

			// Player constructor
			Player(vector<string> hand);

			// Player destructor
			~Player();

			// Returns the current total score of the player
			float GetScore();

			// Removes a card from the hand
			void PlayCard(string card);

			// Adds cards into the hand
			void ReceiveDog(vector<string> cards);

			// Adds cards into the tricks
			void WinTheRound(vector<string> trick);

			// Takes the cards from the hand and put them into the tricks
			void MakeAside(vector<string> aside);

			// Takes the card `cardFrom` from the player tricks
			// and exchanges it against the card `cardTo` from the other player tricks
			void ExchangeCard(string cardFrom, string cardTo, Player* player);

			// Returns True if the player can have this card in his hand (based on public statistics)
			bool CanHave(Card* card);

			// Returns True if the player can play this card based on the baseCard and highestCard cards
			bool IsPlayableCard(Card* card, Card* baseCard, Card* highestCard);

			// Returns all the playable cards in the hand of the player relative to the baseCard and highestCard cards
			vector<string> GetPlayableCards(Card* baseCard, Card* highestCard);
	};
}

