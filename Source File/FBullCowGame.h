#pragma once
#include<string>

using FString = std::string;
using int32 = int;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame {
private:
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;
	bool IsIsogram(FString) const;
	bool IsLower(FString) const;

public:
	FBullCowGame();
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;

	EGuessStatus CheckGuessValidity(FString) const;
	void Reset(); //TODO make a more rich RV
	FString GetHiddenWord();
	FBullCowCount SubmitValidGuess(FString);
};