#pragma once
#include <vector>
#include <algorithm>
#include "Card.h"
#include "Deck.h"

using namespace std;

namespace Tarot {
	class Player {
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

			// Defines the lenght of each suit of the player (based on public statistics)
			map<Suit, int> suitPlayedLength;

			// Defines the higher trump the player can have (based on public statistics)
			Card* canHaveMaxTrump;

			// Returns True if the player has this suit in his hand (based on private statistics)
			bool HasSuit(Suit suit);

			// Returns True if the player has a trump higher than this trump in his hand (based on private statistics)
			bool HasHigherTrump(Card* trump);

			// Adds a card to the hand
			void AddCardToHand(string card);

			// Adds a card to the tricks
			void AddCardToTricks(string card);

			// Adds a card to the sorted trumps
			void AddCardToSortedTrumps(string card);

			// Removes a card from the hand
			void RemoveCardFromHand(string card);

			// Removes a card from the tricks
			void RemoveCardFromTricks(string card);

			// Removes a card from the sorted trumps
			void RemoveCardFromSortedTrumps(string card);

		public:
			// Player constructor
			Player(vector<string> hand);

			// Player cloning constructor
			Player(const Player &player);

			// Returns the current total score of the player
			float GetScore();

			// Removes a card from the hand
			void PlayCard(string card);

			// Adds cards into the hand
			void ReceiveDog(vector<string> dog);

			// Takes the cards from the hand and put them into the tricks
			void MakeAside(vector<string> aside);

			// Adds cards into the tricks
			void WinCards(vector<string> trick);

			// Returns the least valuable card of the tricks (or empty string if not card)
			string GetDumbCard();

			// Takes the `dumbCard` from the current player tricks and add it to the `player` tricks (needed to exchange the fool against a dumb card)
			void GiveDumbCardTo(string dumbCard, Player* player);


			// Returns True if the player can have this card in his hand (based on public statistics)
			bool CanHave(Card* card);

			// Returns True if the player can have this suit in his hand (based on public statistics)
			bool CanHaveSuit(Suit suit);

			// Returns True if the player can have a trump higher than this card in his hand (based on public statistics)
			bool CanHaveHigherTrump(Card* trump);

			// Defines the fact that the player has no more card of this suit (based on public statistics)
			void HasNoMoreSuit(Suit suit);

			// Defines the fact that the player has already (or not) played this suit (based on public statistics)
			bool HasPlayedSuit(Suit suit);

			// Defines the fact that the player has played this suit just one time (based on public statistics)
			bool HasPlayedSuitOnce(Suit suit);

			// Defines the fact that the player has no higher trump than this trump (based on public statistics)
			void HasNoHigherTrump(Card* trump);

			// Returns the number of cuts the player has (based on public statistics)
			int GetCutsCount();

			// Returns the number of singletons the player has (based on public statistics)
			int GetSingletonsCount();


			// Returns the play constraints of the player relative to the baseCard and highestCard cards (based on private statistics)
			pair<string, Card*> Player::GetPlayConstraints(Card* baseCard, Card* highestCard);

			// Returns all the playable cards in the hand of the player relative to the baseCard and highestCard cards (based on private statistics)
			vector<string> GetPlayableCards(Card* baseCard, Card* highestCard);
	};
}
