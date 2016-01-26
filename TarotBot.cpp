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
	using v8::Number;
	using namespace std;

	Game* game;

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
		int inputLength = inputArray->Length();
		vector<string> result = vector<string>(inputLength);
		for (int i = 0; i < inputLength; i++) {
			result[i] = ToString(inputArray->Get(i));
		}
		return result;
	}

	void NewGame(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();

		int firstPlayer = ToInt(args[0]);
		vector<vector<string>> playersHands = vector<vector<string>>(4);
		for (int i = 1; i < 5; i++) {
			playersHands[i - 1] = ToStringVector(args[i]);
		}

		game = new Game(firstPlayer, playersHands[0], playersHands[1], playersHands[2], playersHands[3]);
	}

	void SetTakerPosition(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();

		int takerPosition = ToInt(args[0]);

		game->SetTakerPosition(takerPosition);
	}

	void PlayCard(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();

		int playerPosition = ToInt(args[0]);
		string card = ToString(args[1]);

		game->PlayCard(playerPosition, card);
	}

	void ReceiveDog(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();

		int playerPosition = ToInt(args[0]);
		vector<string> cards = ToStringVector(args[1]);
		int takeLevelId = ToInt(args[2]);
		Bid takeLevel;
		switch (takeLevelId) {
			case 0:
				takeLevel = Pass;
				break;
			case 1:
				takeLevel = Take;
				break;
			case 2:
				takeLevel = Guard;
				break;
			case 3:
				takeLevel = GuardWithout;
				break;
			case 4:
				takeLevel = GuardAgainst;
				break;
		}

		game->ReceiveDog(playerPosition, cards, takeLevel);
	}

	void MakeAside(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();

		int playerPosition = ToInt(args[0]);
		vector<string> aside = ToStringVector(args[1]);

		game->MakeAside(playerPosition, aside);
	}

	void GetNextMinMaxCard(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();

		Local<String> bestCard = String::NewFromUtf8(isolate, game->GetNextMinMaxCard().c_str());

		args.GetReturnValue().Set(bestCard);
	}

	void GetNextFoolHeuristicCard(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();

		Local<String> bestCard = String::NewFromUtf8(isolate, game->GetNextFoolHeuristicCard().c_str());

		args.GetReturnValue().Set(bestCard);
	}

	void GetNextTrumpHeuristicCard(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();

		Local<String> bestCard = String::NewFromUtf8(isolate, game->GetNextTrumpHeuristicCard().c_str());

		args.GetReturnValue().Set(bestCard);
	}

	void GetNextCutHeuristicCard(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();

		Local<String> bestCard = String::NewFromUtf8(isolate, game->GetNextCutHeuristicCard().c_str());

		args.GetReturnValue().Set(bestCard);
	}

	void GetNextSingletonHeuristicCard(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();

		Local<String> bestCard = String::NewFromUtf8(isolate, game->GetNextSingletonHeuristicCard().c_str());

		args.GetReturnValue().Set(bestCard);
	}

	void GetAttackersScore(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();

		Local<Number> attackersScore = Number::New(isolate, game->GetAttackersScore());

		args.GetReturnValue().Set(attackersScore);
	}

	void GetDefendersScore(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();

		Local<Number> defendersScore = Number::New(isolate, game->GetDefendersScore());

		args.GetReturnValue().Set(defendersScore);
	}

	void Initialize(Local<Object> exports) {
		NODE_SET_METHOD(exports, "newGame", NewGame);
		NODE_SET_METHOD(exports, "setTakerPosition", SetTakerPosition);
		NODE_SET_METHOD(exports, "playCard", PlayCard);
		NODE_SET_METHOD(exports, "receiveDog", ReceiveDog);
		NODE_SET_METHOD(exports, "makeAside", MakeAside);
		NODE_SET_METHOD(exports, "getNextMinMaxCard", GetNextMinMaxCard);
		NODE_SET_METHOD(exports, "getNextFoolHeuristicCard", GetNextFoolHeuristicCard);
		NODE_SET_METHOD(exports, "getNextTrumpHeuristicCard", GetNextTrumpHeuristicCard);
		NODE_SET_METHOD(exports, "getNextCutHeuristicCard", GetNextCutHeuristicCard);
		NODE_SET_METHOD(exports, "getNextSingletonHeuristicCard", GetNextSingletonHeuristicCard);
		NODE_SET_METHOD(exports, "getAttackersScore", GetAttackersScore);
		NODE_SET_METHOD(exports, "getDefendersScore", GetDefendersScore);
	}

	NODE_MODULE(TarotBot, Initialize)

}
