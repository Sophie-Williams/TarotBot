var tarotBot = require('./build/Release/TarotBot');

// Set-up the distribution of the cards
var dog = ['trump-7', 'trump-13', 'club-8', 'spade-4', 'diamond-6', 'diamond-13'];
var playersHands = [
	['spade-8', 'diamond-7', 'club-7', 'trump-3', 'heart-7', 'trump-17', 'spade-2', 'trump-8', 'diamond-2', 'club-14', 'club-4', 'club-10', 'club-3', 'diamond-10', 'club-1', 'heart-6', 'diamond-5', 'trump-16'],
	['club-5', 'trump-12', 'trump-20', 'heart-1', 'diamond-12', 'trump-10', 'trump-14', 'heart-4', 'trump-18', 'heart-3', 'spade-14', 'heart-12', 'club-11', 'heart-2', 'club-6', 'spade-7', 'spade-6', 'spade-5'],
	['trump-21', 'trump-15', 'diamond-9', 'spade-9', 'spade-10', 'trump-fool', 'spade-3', 'diamond-1', 'trump-19', 'heart-11', 'heart-13', 'heart-14', 'heart-5', 'heart-10', 'club-9', 'club-12', 'trump-11', 'trump-9'],
	['trump-2', 'heart-8', 'trump-5', 'diamond-11', 'diamond-8', 'heart-9', 'spade-12', 'club-13', 'spade-13', 'club-2', 'trump-1', 'spade-11', 'diamond-3', 'trump-4', 'diamond-4', 'diamond-14', 'trump-6', 'spade-1']
];
tarotBot.newGame(playersHands[0], playersHands[1], playersHands[2], playersHands[3]);

// set-up the taker position
var takerPosition = 2;
tarotBot.setTakerPosition(takerPosition);

// Set-up the aside
// Take or Guard (taker make is dog)
tarotBot.addCards(takerPosition, dog);
tarotBot.makeAside(takerPosition, ['club-8', 'club-9', 'club-12', 'diamond-6', 'diamond-9', 'diamond-13']);

// Guard Without (give dog to taker)
///tarotBot.addTrick(takerPosition, dog);

// Guard Against (give dog to any other player)
//tarotBot.addTrick(0, dog);

// Round 1
tarotBot.playCard(1, 'heart-1');
tarotBot.playCard(2, 'heart-14');
tarotBot.playCard(3, 'heart-8');
tarotBot.playCard(0, 'heart-6');
tarotBot.winTheRound(2, ['heart-1', 'heart-14', 'heart-8', 'heart-6']);

// Round 2
tarotBot.playCard(2, 'heart-13');
tarotBot.playCard(3, 'heart-8');
tarotBot.playCard(0, 'heart-6');
tarotBot.playCard(1, 'heart-2');
tarotBot.winTheRound(2, ['heart-13', 'heart-8', 'heart-6', 'heart-2']);

// Round 3
tarotBot.playCard(2, 'heart-5');
tarotBot.playCard(3, 'trump-1');
tarotBot.playCard(0, 'trump-3');
tarotBot.playCard(1, 'heart-12');
tarotBot.winTheRound(0, ['heart-5', 'trump-1', 'trump-3', 'heart-12']);

// Round 4
tarotBot.playCard(0, 'diamond-2');
tarotBot.playCard(1, 'diamond-12');
tarotBot.playCard(2, 'diamond-1');
tarotBot.playCard(3, 'diamond-14');
tarotBot.winTheRound(3, ['diamond-2', 'diamond-12', 'diamond-1', 'diamond-14']);

// Round 5
tarotBot.playCard(3, 'diamond-3');
tarotBot.playCard(0, 'diamond-5');
tarotBot.playCard(1, 'trump-10');
tarotBot.playCard(2, 'trump-fool');
tarotBot.winTheRound(1, ['diamond-3', 'diamond-5', 'trump-10']);
// The Fool has been played (we changed a dumb card against the Fool)
tarotBot.addTrick(2, ['trump-fool']);
tarotBot.addTrick(1, ['heart-9']);

// Round 6
tarotBot.playCard(1, 'club-5');
tarotBot.playCard(2, 'trump-7');
tarotBot.playCard(3, 'club-2');
tarotBot.playCard(0, 'club-1');
tarotBot.winTheRound(2, ['club-5', 'trump-7', 'club-2', 'club-1']);

// Round 7
tarotBot.playCard(2, 'heart-10');
tarotBot.playCard(3, 'trump-2');
tarotBot.playCard(0, 'trump-8');
tarotBot.playCard(1, 'heart-3');
tarotBot.winTheRound(0, ['heart-10', 'trump-2', 'trump-8', 'heart-3']);

// Round 8
tarotBot.playCard(0, 'club-3');
tarotBot.playCard(1, 'club-6');
tarotBot.playCard(2, 'trump-9');
tarotBot.playCard(3, 'club-13');
tarotBot.winTheRound(2, ['club-3', 'club-6', 'trump-9', 'club-13']);

// Round 9
tarotBot.playCard(2, 'spade-3');
tarotBot.playCard(3, 'spade-13');
tarotBot.playCard(0, 'spade-2');
tarotBot.playCard(1, 'spade-14');
tarotBot.winTheRound(1, ['spade-3', 'spade-13', 'spade-2', 'spade-14']);

// Round 10
tarotBot.playCard(1, 'spade-5');
tarotBot.playCard(2, 'spade-4');
tarotBot.playCard(3, 'spade-12');
tarotBot.playCard(0, 'spade-8');
tarotBot.winTheRound(3, ['spade-5', 'spade-4', 'spade-12', 'spade-8']);

// Round 11
tarotBot.playCard(3, 'diamond-4');
tarotBot.playCard(0, 'diamond-7');
tarotBot.playCard(1, 'trump-12');
tarotBot.playCard(2, 'trump-13');
tarotBot.winTheRound(2, ['diamond-4', 'diamond-7', 'trump-12', 'trump-13']);

// Round 12
tarotBot.playCard(2, 'spade-9');
tarotBot.playCard(3, 'spade-11');
tarotBot.playCard(0, 'trump-16');
tarotBot.playCard(1, 'spade-6');
tarotBot.winTheRound(0, ['spade-9', 'spade-11', 'trump-16', 'spade-6']);

// Round 13
tarotBot.playCard(0, 'club-4');
tarotBot.playCard(1, 'club-11');
tarotBot.playCard(2, 'trump-11');
tarotBot.playCard(3, 'trump-4');
tarotBot.winTheRound(2, ['club-4', 'club-11', 'trump-11', 'trump-4']);

// Round 14
tarotBot.playCard(2, 'trump-15');
tarotBot.playCard(3, 'trump-5');
tarotBot.playCard(0, 'trump-17');
tarotBot.playCard(1, 'trump-18');
tarotBot.winTheRound(1, ['trump-15', 'trump-5', 'trump-17', 'trump-18']);

// Round 15
tarotBot.playCard(1, 'spade-7');
tarotBot.playCard(2, 'spade-10');
tarotBot.playCard(3, 'spade-1');
tarotBot.playCard(0, 'diamond-10');
tarotBot.winTheRound(2, ['spade-7', 'spade-10', 'spade-1', 'diamond-10']);

// Round 16
tarotBot.playCard(2, 'trump-19');
tarotBot.playCard(3, 'trump-6');
tarotBot.playCard(0, 'club-7');
tarotBot.playCard(1, 'trump-20');
tarotBot.winTheRound(1, ['trump-19', 'trump-6', 'club-7', 'trump-20']);

// Round 17
tarotBot.playCard(1, 'heart-4');
tarotBot.playCard(2, 'heart-11');
tarotBot.playCard(3, 'diamond-8');
tarotBot.playCard(0, 'club-10');
tarotBot.winTheRound(2, ['heart-4', 'heart-11', 'diamond-8', 'club-10']);

// Round 18
tarotBot.playCard(2, 'trump-21');
tarotBot.playCard(3, 'diamond-11');
tarotBot.playCard(0, 'club-14');
tarotBot.playCard(1, 'trump-14');
tarotBot.winTheRound(2, ['trump-21', 'diamond-11', 'club-14', 'trump-14']);

// Final scores
// Taker wins with 51pts for 41pts
