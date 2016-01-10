#pragma once
#include <map>
#include <functional>
#include "Card.h"

using namespace std;

namespace Tarot {
	class Deck {
		private:
			// Defines the full deck of the Tarot game
			static map<string, Card> deck;

		public:
			// Loops through the deck and give the key/value pair of each card to the callback
			static void Foreach(function<void (string key, Card value)> callback);

			// Returns the card referenced by this key
			static Card* Get(string key);
	};
}
