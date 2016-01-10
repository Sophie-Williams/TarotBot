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

			// Defines the lenght of each suit of the player (based on private statistics)
			map<Suit, int> suitLength;

			// Defines the trumps of the player sorted from lowest to highest (based on private statistics)
			vector<string> sortedTrumps;

			// Defines which suits the player can have (based on public statistics)
			map<Suit, bool> canHaveSuit;

			// Defines the higher trump the player can have (based on public statistics)
			Card* canHaveMaxTrump;

			// Returns True if the player has this suit in his hand (based on private statistics)
			bool HasSuit(Suit suit);

			// Returns True if the player has a trump higher than this trump in his hand (based on private statistics)
			bool HasHigherTrump(Card* trump);

			// Adds a card from the hand
			void AddCardToHand(string card);

			// Adds a card from the tricks
			void AddCardToTricks(string card);

			// Removes a card from the hand
			void RemoveCardFromHand(string card);

			// Removes a card from the tricks
			void RemoveCardFromTricks(string card);

			// Removes a card from the sorted trumps
			void RemoveCardFromSortedTrumps(string card);

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

			// Returns True if the player can have this suit in his hand (based on public statistics)
			bool CanHaveSuit(Suit suit);

			// Returns True if the player can have a trump higher than this card in his hand (based on public statistics)
			bool CanHaveHigherTrump(Card* trump);

			// Defines the fact that the player has no more card of this suit (based on public statistics)
			void HasNoMoreSuit(Suit suit);

			// Defines the fact that the player has no higher trump than this trump (based on public statistics)
			void HasNoHigherTrump(Card* trump);


			// Returns the play constraints of the player relative to the baseCard and highestCard cards (based on private statistics)
			pair<string, Card*> Player::GetPlayConstraints(Card* baseCard, Card* highestCard);

			// Returns all the playable cards in the hand of the player relative to the baseCard and highestCard cards (based on private statistics)
			vector<string> GetPlayableCards(Card* baseCard, Card* highestCard);
	};
}
