#pragma once

namespace Tarot {

	// Defines all the card suits into the Tarot game
	enum Suit { Club, Diamond, Heart, Spade, Trump };

	// Defines all the card ranks into the Tarot game
	enum Rank { Fool, One, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Eleven, Twelve, Thirteen, Fourteen, Fifteen, Sixteen, Seventeen, Eighteen, Nineteen, Twenty, TwentyOne, Jack, Knight, Queen, King };
	
	class Card
	{
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
			Card();

			// Card destructor
			~Card();

			// Returns the card suit
			Suit GetSuit();

			// Returns the card rank
			Rank GetRank();

			// Returns the card score
			float GetScore();
	};
}

