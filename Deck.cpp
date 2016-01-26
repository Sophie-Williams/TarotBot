#include "Deck.h"

map<string, Tarot::Card*> Tarot::Deck::deck = {
	{ "club-1", new Card(Club, One) },
	{ "club-2", new Card(Club, Two) },
	{ "club-3", new Card(Club, Three) },
	{ "club-4", new Card(Club, Four) },
	{ "club-5", new Card(Club, Five) },
	{ "club-6", new Card(Club, Six) },
	{ "club-7", new Card(Club, Seven) },
	{ "club-8", new Card(Club, Eight) },
	{ "club-9", new Card(Club, Nine) },
	{ "club-10", new Card(Club, Ten) },
	{ "club-11", new Card(Club, Jack) },
	{ "club-12", new Card(Club, Knight) },
	{ "club-13", new Card(Club, Queen) },
	{ "club-14", new Card(Club, King) },

	{ "diamond-1", new Card(Diamond, One) },
	{ "diamond-2", new Card(Diamond, Two) },
	{ "diamond-3", new Card(Diamond, Three) },
	{ "diamond-4", new Card(Diamond, Four) },
	{ "diamond-5", new Card(Diamond, Five) },
	{ "diamond-6", new Card(Diamond, Six) },
	{ "diamond-7", new Card(Diamond, Seven) },
	{ "diamond-8", new Card(Diamond, Eight) },
	{ "diamond-9", new Card(Diamond, Nine) },
	{ "diamond-10", new Card(Diamond, Ten) },
	{ "diamond-11", new Card(Diamond, Jack) },
	{ "diamond-12", new Card(Diamond, Knight) },
	{ "diamond-13", new Card(Diamond, Queen) },
	{ "diamond-14", new Card(Diamond, King) },

	{ "heart-1", new Card(Heart, One) },
	{ "heart-2", new Card(Heart, Two) },
	{ "heart-3", new Card(Heart, Three) },
	{ "heart-4", new Card(Heart, Four) },
	{ "heart-5", new Card(Heart, Five) },
	{ "heart-6", new Card(Heart, Six) },
	{ "heart-7", new Card(Heart, Seven) },
	{ "heart-8", new Card(Heart, Eight) },
	{ "heart-9", new Card(Heart, Nine) },
	{ "heart-10", new Card(Heart, Ten) },
	{ "heart-11", new Card(Heart, Jack) },
	{ "heart-12", new Card(Heart, Knight) },
	{ "heart-13", new Card(Heart, Queen) },
	{ "heart-14", new Card(Heart, King) },

	{ "spade-1", new Card(Spade, One) },
	{ "spade-2", new Card(Spade, Two) },
	{ "spade-3", new Card(Spade, Three) },
	{ "spade-4", new Card(Spade, Four) },
	{ "spade-5", new Card(Spade, Five) },
	{ "spade-6", new Card(Spade, Six) },
	{ "spade-7", new Card(Spade, Seven) },
	{ "spade-8", new Card(Spade, Eight) },
	{ "spade-9", new Card(Spade, Nine) },
	{ "spade-10", new Card(Spade, Ten) },
	{ "spade-11", new Card(Spade, Jack) },
	{ "spade-12", new Card(Spade, Knight) },
	{ "spade-13", new Card(Spade, Queen) },
	{ "spade-14", new Card(Spade, King) },

	{ "trump-fool", new Card(Trump, Fool) },
	{ "trump-1", new Card(Trump, One) },
	{ "trump-2", new Card(Trump, Two) },
	{ "trump-3", new Card(Trump, Three) },
	{ "trump-4", new Card(Trump, Four) },
	{ "trump-5", new Card(Trump, Five) },
	{ "trump-6", new Card(Trump, Six) },
	{ "trump-7", new Card(Trump, Seven) },
	{ "trump-8", new Card(Trump, Eight) },
	{ "trump-9", new Card(Trump, Nine) },
	{ "trump-10", new Card(Trump, Ten) },
	{ "trump-11", new Card(Trump, Eleven) },
	{ "trump-12", new Card(Trump, Twelve) },
	{ "trump-13", new Card(Trump, Thirteen) },
	{ "trump-14", new Card(Trump, Fourteen) },
	{ "trump-15", new Card(Trump, Fifteen) },
	{ "trump-16", new Card(Trump, Sixteen) },
	{ "trump-17", new Card(Trump, Seventeen) },
	{ "trump-18", new Card(Trump, Eighteen) },
	{ "trump-19", new Card(Trump, Nineteen) },
	{ "trump-20", new Card(Trump, Twenty) },
	{ "trump-21", new Card(Trump, TwentyOne) }
};

void Tarot::Deck::Foreach(function<void(string key, Tarot::Card* value)> callback) {
	for (map<string, Card*>::iterator iterator = deck.begin(); iterator != deck.end(); iterator++) {
		callback(iterator->first, iterator->second);
	}
}

Tarot::Card* Tarot::Deck::Get(string key) {
	return deck[key];
}
