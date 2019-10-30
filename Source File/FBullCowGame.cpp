#include "FBullCowGame.h"
#include <vector>
#include <cstdlib> 
#include<ctime> 
#include <map>
#define TMap std::map

using FString = std::string;
using int32 = int;


FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const {
	TMap<int32, int32> WordLengthToMaxTries{ {3,4} , {4,7} , {5,10} , {6,12} , {7,14} , {8,18} , {9,30} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset() {

	std::vector<FString> collectionwords{ "planet", "plant", "above", "shaving", "dons", "donkey", "plan", "play", "rely", "day", "say", "may", "face", "mesh",
		"side", "ride", "rides", "mild", "faint", "pain", "sad", "lad", "mad", "word", "isogram", "six", "four", "five",
		"ready", "shady", "blond", "chemistry", "sir", "failure", "record" };

	srand(time(NULL));
	int32 collectionsize = collectionwords.size();
	int32 LuckyNo = rand() % collectionsize;
	const FString HIDDEN_WORD = collectionwords[LuckyNo];



	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

FString FBullCowGame::GetHiddenWord()
{
	return MyHiddenWord;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {

	if (!IsIsogram(Guess)) {
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLower(Guess)) {
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) {
		return EGuessStatus::Wrong_Length;
	}
	else {
		return EGuessStatus::OK;
	}

}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	int32 HiddenWordLength = MyHiddenWord.length();

	for (int32 i = 0; i < HiddenWordLength; i++) {
		for (int32 j = 0; j < HiddenWordLength; j++) {
			if (Guess[j] == MyHiddenWord[i]) {
				if (i == j) {
					BullCowCount.Bulls++;
				}
				else {
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == HiddenWordLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() < 2) {
		return true;
	}

	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) {
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) {
			return false;
		}
		else {
			LetterSeen[Letter] = true;
		}
	}
	return true;
}

bool FBullCowGame::IsLower(FString Word) const
{
	for (auto c : Word) {
		if (!islower(c)) {
			return false;
		}
	}
	return true;

}

