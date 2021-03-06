var tarotBot = require('./build/Debug/TarotBot');

// Set-up the distribution of the cards
var dog = ['trump-7', 'trump-13', 'club-8', 'spade-4', 'diamond-6', 'diamond-13'];
var playersHands = [
	['spade-8', 'diamond-7', 'club-7', 'trump-3', 'heart-7', 'trump-17', 'spade-2', 'trump-8', 'diamond-2', 'club-14', 'club-4', 'club-10', 'club-3', 'diamond-10', 'club-1', 'heart-6', 'diamond-5', 'trump-16'],
	['club-5', 'trump-12', 'trump-20', 'heart-1', 'diamond-12', 'trump-10', 'trump-14', 'heart-4', 'trump-18', 'heart-3', 'spade-14', 'heart-12', 'club-11', 'heart-2', 'club-6', 'spade-7', 'spade-6', 'spade-5'],
	['trump-21', 'trump-15', 'diamond-9', 'spade-9', 'spade-10', 'trump-fool', 'spade-3', 'diamond-1', 'trump-19', 'heart-11', 'heart-13', 'heart-14', 'heart-5', 'heart-10', 'club-9', 'club-12', 'trump-11', 'trump-9'],
	['trump-2', 'heart-8', 'trump-5', 'diamond-11', 'diamond-8', 'heart-9', 'spade-12', 'club-13', 'spade-13', 'club-2', 'trump-1', 'spade-11', 'diamond-3', 'trump-4', 'diamond-4', 'diamond-14', 'trump-6', 'spade-1']
];
var firstPlayer = 1;
tarotBot.newGame(firstPlayer, playersHands[0], playersHands[1], playersHands[2], playersHands[3]);

// set-up the taker position
var takerPosition = 2;
tarotBot.setTakerPosition(takerPosition);

// Set-up the aside
// Take (taker make is own aside)
tarotBot.receiveDog(takerPosition, dog, 1);
tarotBot.makeAside(takerPosition, ['club-8', 'club-9', 'club-12', 'diamond-6', 'diamond-9', 'diamond-13']);

// Guard (taker make is own aside)
//tarotBot.receiveDog(takerPosition, dog, 2);
//tarotBot.makeAside(takerPosition, ['club-8', 'club-9', 'club-12', 'diamond-6', 'diamond-9', 'diamond-13']);

// Guard Without (give dog to taker and aside it)
//tarotBot.receiveDog(takerPosition, dog, 3);
//tarotBot.makeAside(takerPosition, dog);

// Guard Against (give dog to any other player (the 0th in this case) and aside it)
//tarotBot.receiveDog(0, dog, 4);
//tarotBot.makeAside(0, dog);

// Round 1
tarotBot.playCard(1, 'heart-1');
tarotBot.playCard(2, 'heart-14');
tarotBot.playCard(3, 'heart-8');
tarotBot.playCard(0, 'heart-6');

// Round 2
tarotBot.playCard(2, 'heart-13');
tarotBot.playCard(3, 'heart-9');
tarotBot.playCard(0, 'heart-7');
tarotBot.playCard(1, 'heart-2');

// Round 3
tarotBot.playCard(2, 'heart-5');
tarotBot.playCard(3, 'trump-1');
tarotBot.playCard(0, 'trump-3');
tarotBot.playCard(1, 'heart-12');

// Round 4
tarotBot.playCard(0, 'diamond-2');
tarotBot.playCard(1, 'diamond-12');
tarotBot.playCard(2, 'diamond-1');
tarotBot.playCard(3, 'diamond-14');

// Round 5
tarotBot.playCard(3, 'diamond-3');
tarotBot.playCard(0, 'diamond-5');
tarotBot.playCard(1, 'trump-10');
tarotBot.playCard(2, 'trump-fool'); // The fool will be exchanged against a dumb card at the end of the game

// Round 6
tarotBot.playCard(1, 'club-5');
tarotBot.playCard(2, 'trump-7');
tarotBot.playCard(3, 'club-2');
tarotBot.playCard(0, 'club-1');

// Round 7
tarotBot.playCard(2, 'heart-10');
tarotBot.playCard(3, 'trump-2');
tarotBot.playCard(0, 'trump-8');
tarotBot.playCard(1, 'heart-3');

// Round 8
tarotBot.playCard(0, 'club-3');
tarotBot.playCard(1, 'club-6');
tarotBot.playCard(2, 'trump-9');
tarotBot.playCard(3, 'club-13');

// Round 9
tarotBot.playCard(2, 'spade-3');
tarotBot.playCard(3, 'spade-13');
tarotBot.playCard(0, 'spade-2');
tarotBot.playCard(1, 'spade-14');

// Round 10
tarotBot.playCard(1, 'spade-5');
tarotBot.playCard(2, 'spade-4');
tarotBot.playCard(3, 'spade-12');
tarotBot.playCard(0, 'spade-8');

// Round 11
tarotBot.playCard(3, 'diamond-4');
tarotBot.playCard(0, 'diamond-7');
tarotBot.playCard(1, 'trump-12');
tarotBot.playCard(2, 'trump-13');

// Round 12
tarotBot.playCard(2, 'spade-9');
tarotBot.playCard(3, 'spade-11');
tarotBot.playCard(0, 'trump-16');
tarotBot.playCard(1, 'spade-6');

// Round 13
tarotBot.playCard(0, 'club-4');
tarotBot.playCard(1, 'club-11');
tarotBot.playCard(2, 'trump-11');
tarotBot.playCard(3, 'trump-4');

// Round 14
tarotBot.playCard(2, 'trump-15');
tarotBot.playCard(3, 'trump-5');
tarotBot.playCard(0, 'trump-17');
tarotBot.playCard(1, 'trump-18');

// Round 15
tarotBot.playCard(1, 'spade-7');
tarotBot.playCard(2, 'spade-10');
tarotBot.playCard(3, 'spade-1');
tarotBot.playCard(0, 'diamond-10');

// Round 16
tarotBot.playCard(2, 'trump-19');
tarotBot.playCard(3, 'trump-6');
tarotBot.playCard(0, 'club-7');
tarotBot.playCard(1, 'trump-20');

// Round 17
tarotBot.playCard(1, 'heart-4');
tarotBot.playCard(2, 'heart-11');
tarotBot.playCard(3, 'diamond-8');
tarotBot.playCard(0, 'club-10');

// Round 18
tarotBot.playCard(2, 'trump-21');
tarotBot.playCard(3, 'diamond-11');
tarotBot.playCard(0, 'club-14');
tarotBot.playCard(1, 'trump-14');

// Final scores
console.log("Attackers score : "+tarotBot.getAttackersScore()); // Taker wins with 51pts
console.log("Defenders score : "+tarotBot.getDefendersScore()); // Defenders lose with 40pts
