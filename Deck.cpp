#include "Deck.h"

map<string, Tarot::Card> Tarot::Deck::deck = {
	{ "club-1", Card(Club, One) },
	{ "club-2", Card(Club, Two) },
	{ "club-3", Card(Club, Three) },
	{ "club-4", Card(Club, Four) },
	{ "club-5", Card(Club, Five) },
	{ "club-6", Card(Club, Six) },
	{ "club-7", Card(Club, Seven) },
	{ "club-8", Card(Club, Eight) },
	{ "club-9", Card(Club, Nine) },
	{ "club-10", Card(Club, Ten) },
	{ "club-11", Card(Club, Jack) },
	{ "club-12", Card(Club, Knight) },
	{ "club-13", Card(Club, Queen) },
	{ "club-14", Card(Club, King) },

	{ "diamond-1", Card(Diamond, One) },
	{ "diamond-2", Card(Diamond, Two) },
	{ "diamond-3", Card(Diamond, Three) },
	{ "diamond-4", Card(Diamond, Four) },
	{ "diamond-5", Card(Diamond, Five) },
	{ "diamond-6", Card(Diamond, Six) },
	{ "diamond-7", Card(Diamond, Seven) },
	{ "diamond-8", Card(Diamond, Eight) },
	{ "diamond-9", Card(Diamond, Nine) },
	{ "diamond-10", Card(Diamond, Ten) },
	{ "diamond-11", Card(Diamond, Jack) },
	{ "diamond-12", Card(Diamond, Knight) },
	{ "diamond-13", Card(Diamond, Queen) },
	{ "diamond-14", Card(Diamond, King) },

	{ "heart-1", Card(Heart, One) },
	{ "heart-2", Card(Heart, Two) },
	{ "heart-3", Card(Heart, Three) },
	{ "heart-4", Card(Heart, Four) },
	{ "heart-5", Card(Heart, Five) },
	{ "heart-6", Card(Heart, Six) },
	{ "heart-7", Card(Heart, Seven) },
	{ "heart-8", Card(Heart, Eight) },
	{ "heart-9", Card(Heart, Nine) },
	{ "heart-10", Card(Heart, Ten) },
	{ "heart-11", Card(Heart, Jack) },
	{ "heart-12", Card(Heart, Knight) },
	{ "heart-13", Card(Heart, Queen) },
	{ "heart-14", Card(Heart, King) },

	{ "spade-1", Card(Spade, One) },
	{ "spade-2", Card(Spade, Two) },
	{ "spade-3", Card(Spade, Three) },
	{ "spade-4", Card(Spade, Four) },
	{ "spade-5", Card(Spade, Five) },
	{ "spade-6", Card(Spade, Six) },
	{ "spade-7", Card(Spade, Seven) },
	{ "spade-8", Card(Spade, Eight) },
	{ "spade-9", Card(Spade, Nine) },
	{ "spade-10", Card(Spade, Ten) },
	{ "spade-11", Card(Spade, Jack) },
	{ "spade-12", Card(Spade, Knight) },
	{ "spade-13", Card(Spade, Queen) },
	{ "spade-14", Card(Spade, King) },

	{ "trump-fool", Card(Trump, Fool) },
	{ "trump-1", Card(Trump, One) },
	{ "trump-2", Card(Trump, Two) },
	{ "trump-3", Card(Trump, Three) },
	{ "trump-4", Card(Trump, Four) },
	{ "trump-5", Card(Trump, Five) },
	{ "trump-6", Card(Trump, Six) },
	{ "trump-7", Card(Trump, Seven) },
	{ "trump-8", Card(Trump, Eight) },
	{ "trump-9", Card(Trump, Nine) },
	{ "trump-10", Card(Trump, Ten) },
	{ "trump-11", Card(Trump, Eleven) },
	{ "trump-12", Card(Trump, Twelve) },
	{ "trump-13", Card(Trump, Thirteen) },
	{ "trump-14", Card(Trump, Fourteen) },
	{ "trump-15", Card(Trump, Fifteen) },
	{ "trump-16", Card(Trump, Sixteen) },
	{ "trump-17", Card(Trump, Seventeen) },
	{ "trump-18", Card(Trump, Eighteen) },
	{ "trump-19", Card(Trump, Nineteen) },
	{ "trump-20", Card(Trump, Twenty) },
	{ "trump-21", Card(Trump, TwentyOne) }
};

void Tarot::Deck::Foreach(function<void(string key, Tarot::Card value)> callback) {
	for (map<string, Card>::iterator iterator = deck.begin(); iterator != deck.end(); iterator++) {
		callback(iterator->first, iterator->second);
	}
}

Tarot::Card* Tarot::Deck::Get(string key) {
	return &deck[key];
}
