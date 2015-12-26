#include <node.h>
#include <string>
#include "Game.h"

namespace Tarot {

	using v8::FunctionCallbackInfo;
	using v8::Isolate;
	using v8::Local;
	using v8::Object;
	using v8::String;
	using v8::Value;
	using v8::Array;
	using namespace std;

	Game game;

	int ToInt(Local<Value> arg) {
		return (int)arg->IntegerValue();
	}

	double ToDouble(Local<Value> arg) {
		return arg->NumberValue();
	}

	bool ToBool(Local<Value> arg) {
		return arg->BooleanValue();
	}

	string ToString(Local<Value> arg) {
		return string(*String::Utf8Value(arg->ToString()));
	}

	vector<string> ToStringVector(Local<Value> arg) {
		Local<Array> inputArray = Local<Array>::Cast(arg);
		unsigned int inputLength = inputArray->Length();
		vector<string> result = vector<string>(inputLength);
		for (unsigned int i = 0; i < inputLength; i++) {
			result[i] = ToString(inputArray->Get(i));
		}
		return result;
	}

	void NewGame(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();

		vector<vector<string>> playersHands = vector<vector<string>>(4);
		for (unsigned int i = 0; i < 4; i++) {
			playersHands[i] = ToStringVector(args[i]);
		}

		game = Game(playersHands[0], playersHands[1], playersHands[2], playersHands[3]);
	}

	void SetTakerPosition(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();

		int takerPosition = ToInt(args[0]);

		game.SetTakerPosition(takerPosition);
	}

	void PlayCard(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();

		int playerPosition = ToInt(args[0]);
		string card = ToString(args[1]);

		game.PlayCard(playerPosition, card);
	}

	void AddCards(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();

		int playerPosition = ToInt(args[0]);
		vector<string> cards = ToStringVector(args[1]);

		game.AddCards(playerPosition, cards);
	}

	void AddTrick(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();

		int playerPosition = ToInt(args[0]);
		vector<string> trick = ToStringVector(args[1]);

		game.AddTrick(playerPosition, trick);
	}

	void MakeAside(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();

		int playerPosition = ToInt(args[0]);
		vector<string> aside = ToStringVector(args[1]);

		game.MakeAside(playerPosition, aside);
	}

	void Initialize(Local<Object> exports) {
		NODE_SET_METHOD(exports, "newGame", NewGame);
		NODE_SET_METHOD(exports, "setTakerPosition", SetTakerPosition);
		NODE_SET_METHOD(exports, "playCard", PlayCard);
		NODE_SET_METHOD(exports, "addCards", AddCards);
		NODE_SET_METHOD(exports, "addTrick", AddTrick);
		NODE_SET_METHOD(exports, "makeAside", MakeAside);
	}

	NODE_MODULE(TarotBot, Initialize)

}
