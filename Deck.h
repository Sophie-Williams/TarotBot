#pragma once
#include <map>
#include "Card.h"

using namespace std;

namespace Tarot {
	class Deck {
		private:
			// Defines the full deck of the Tarot game
			static map<string, Card> deck;

		public:
			// Returns the card referenced by this key
			static Card Get(string key);
	};
}

