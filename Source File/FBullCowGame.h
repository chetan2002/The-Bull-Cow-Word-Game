#pragma once
#include<string>


struct FBullCowCount {
	int Bulls = 0;
	int Cows = 0;
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
	int MyCurrentTry;
	std::string MyHiddenWord;
	bool bGameIsWon;
	bool IsIsogram(std::string) const;
	bool IsLower(std::string) const;

public:
	FBullCowGame();
	int GetMaxTries() const;
	int GetCurrentTry() const;
	int GetHiddenWordLength() const;
	bool IsGameWon() const;

	EGuessStatus CheckGuessValidity(std::string) const;
	void Reset(); //TODO make a more rich RV
	std::string GetHiddenWord();
	FBullCowCount SubmitValidGuess(std::string);
};