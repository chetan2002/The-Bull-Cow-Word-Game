#include "FBullCowGame.h"
#include <vector>
#include <cstdlib> 
#include<ctime> 
#include <map>
#define TMap std::map



FBullCowGame::FBullCowGame() { Reset(); }

int FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int FBullCowGame::GetMaxTries() const {
	TMap<int, int> WordLengthToMaxTries{ {3,4} , {4,7} , {5,10} , {6,12} , {7,14} , {8,18} , {9,30} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset() {

	std::vector<std::string> collectionwords{ "planet", "plant", "above", "shaving", "dons", "donkey", "plan", "play", "rely", "day", "say", "may", "face", "mesh",
		"side", "ride", "rides", "mild", "faint", "pain", "sad", "lad", "mad", "word", "isogram", "six", "four", "five",
		"ready", "shady", "blond", "chemistry", "sir", "failure", "record" };

	srand(time(NULL));
	int collectionsize = collectionwords.size();
	int LuckyNo = rand() % collectionsize;
	const std::string HIDDEN_WORD = collectionwords[LuckyNo];



	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

std::string FBullCowGame::GetHiddenWord()
{
	return MyHiddenWord;
}

EGuessStatus FBullCowGame::CheckGuessValidity(std::string Guess) const {

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

FBullCowCount FBullCowGame::SubmitValidGuess(std::string Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	int HiddenWordLength = MyHiddenWord.length();

	for (int i = 0; i < HiddenWordLength; i++) {
		for (int j = 0; j < HiddenWordLength; j++) {
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

bool FBullCowGame::IsIsogram(std::string Word) const
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

bool FBullCowGame::IsLower(std::string Word) const
{
	for (auto c : Word) {
		if (!islower(c)) {
			return false;
		}
	}
	return true;

}

