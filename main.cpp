#include<iostream>
#include<string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;	//instance of FBullCowGame

int main() {
	bool PlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		PrintGameSummary();
		PlayAgain = AskToPlayAgain();
	} while (PlayAgain);
	return 0;
 }


void PrintIntro() {
	//Introduce the game

	std::cout << "\n\n Welcome to Bulls and Cows, a fun word game!" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking?" << std::endl;

	return;
}

void PlayGame(){

	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	std::cout << "MAX TRIES:" << MaxTries << std::endl;
	
	//loop for required turns
	
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ".Cows = " << BullCowCount.Cows << std::endl;

		//repeat back the guess
		std::cout << "Your guess was :" << Guess << std::endl << std::endl;
	}

	return;
}

FText GetValidGuess() {

	int32 CurrentTry = BCGame.GetCurrentTry();
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";

	do {
		//get a guess from player
		std::cout << std::endl;
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() ;
		std::cout<<" . Enter your Guess:";
		
		std::getline(std::cin, Guess);


		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " length word." << std::endl;
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Not isogram! Please enter a word without repeating letters." << std::endl;
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters." << std::endl;
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::OK);
	return Guess;
}

bool AskToPlayAgain(){

	std::cout << "Do You want to play again? (Y or N) : ";
	FText Response = " ";
	std::getline(std::cin, Response);

	return ((Response[0] == 'y') || (Response[0] == 'Y'));
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon()) {
		std::cout << "Well Done- YOU WON !" << std::endl;
	}
	else {
		std::cout << "Better Luck Next Time!" << std::endl;
	}
	return;
}
