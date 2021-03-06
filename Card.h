#pragma once

namespace Tarot {

	// Defines all the card suits into the Tarot game
	const enum Suit { Club, Diamond, Heart, Spade, Trump };
	static const Suit Colors[] = { Club, Diamond, Heart, Spade };
	static const Suit Suits[] = { Club, Diamond, Heart, Spade, Trump };

	// Defines all the card ranks into the Tarot game
	enum Rank { Fool, One, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Eleven, Twelve, Thirteen, Fourteen, Fifteen, Sixteen, Seventeen, Eighteen, Nineteen, Twenty, TwentyOne, Jack, Knight, Queen, King };

	class Card {
		private:
			// The current card suit
			Suit suit;

			// The current card rank
			Rank rank;

			// The current card score
			float score;

		public:
			// Card constructor
			Card(Suit suit, Rank rank);

			// Returns the card suit
			Suit GetSuit();

			// Returns the card rank
			Rank GetRank();

			// Returns the card score
			float GetScore();

			// Returns True if the current card is an oudler
			bool IsOudler();

			// Returns True if the current card is the fool
			bool IsFool();

			// Returns True if the current card is the petit
			bool IsPetit();

			// Returns True if the current card is the world
			bool IsWorld();

			// Returns True if the current card is equal to the given card
			bool Equals(Card* card);

			// Returns True if the current card is higher than the given card
			bool IsHigher(Card* card);
	};
}
