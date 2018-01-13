//
//  main.cpp
//  BullCowGame
//
//  Created by Rasha Saadeh on 1/5/18.
//  Copyright © 2018 Rasha Saadeh. All rights reserved.
//

/* This is the console executable, that makes use of the BullCow class
 This acts as the view in the MVC pattern, and is responsible for all
 user interaction. For game logic see the FBullCowGame class.
 */
#include <iostream>
#include <string>
#include "FBullCowGame.hpp"
 // #pragma once //make sure we don't import duplicate files

//to make syntax unreal friendly
using FText = std :: string; // subsitution for standard string to ftext
using int32 = int;
//allows you to not consistently write std:: in code

//these are called prototype which make the functions global
void PlayGame();
void PrintIntro(); //allows you to move PrintInto() into the bottom
void PrintGameSummary();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; //instantiate a new game
//the entry point for our application
int main() {
    
    do {
        PrintIntro();
        PlayGame();
        
        std:: cout << std:: endl;
    }
    while(AskToPlayAgain());
    
    return 0;
}

//introduce the game
void PrintIntro() {
    

    
    std :: cout << "Welcome to Bulls and Cows, a fun word game.\n";
    std::cout << std::endl;
        std::cout << "          }   {         ___ " << std::endl;
        std::cout << "          (o o)        (o o) " << std::endl;
        std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
        std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
        std::cout << " *  |-,--- |              |------|  * " << std::endl;
        std::cout << "    ^      ^              ^      ^ " << std::endl;
    
    FText Response = "";
    do {
    std:: cout<< "Pick a number between 3 - 6 for the length of your isogram.";
    std :: getline(std :: cin, Response);
    
        
    }while(std:: stoi(Response) > 6 || std:: stoi(Response) < 3);
    
    
    BCGame.LengthOfIsogram(Response);
    std :: cout << "Can you guess the " << BCGame.GetHiddenWordLength();
    std :: cout << " letter isogram that I'm thinking of?\n";
    std :: cout << std :: endl;
    
}

//plays a single game to completion
void PlayGame() {
    
    BCGame.Reset();
    int32 MaxTries = BCGame.GetMaxTries();
    
    
    //loop asking for guesses while the game
    // is NOT won and there are still tries remaining
    while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
        FText Guess = GetValidGuess();
        
        
        
        // submit valid guess to the game and receive counts
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
       
        // print number of bulls and cows
        std::cout << "Bulls = " << BullCowCount.Bulls;
        std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
    }
    
    
 
    PrintGameSummary();
    
    return; //No real affect but it is good practice for coding
}

//loop continually until the user submits a valid guess
FText GetValidGuess() {
    EGuessStatus Status = EGuessStatus::Invalid_Status;
    FText Guess = "";
    do {
        //get the guess from the player
        int32 CurrentTry = BCGame.GetCurrentTry();
        std :: cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
        
        std:: getline(std :: cin, Guess); //reads the the whole input stream Ex: "donkey kong"

        Status = BCGame.CheckGuessValidity(Guess);
        switch(Status)
        {
            case EGuessStatus::Not_Isogram:
                std::cout << "Please enter a word without repeating letters.\n\n";
                break;
            
            case  EGuessStatus::Wrong_Length:
                std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
                break;
            case EGuessStatus::Not_Lower_Case:
                std::cout << "Please enter an all lowercase letters.\n\n";
                break;
            
            
            default:
                // assuming the guess is valid
                break;
        }

    } while(Status != EGuessStatus::OK); //keep looping until we get no errors
    return Guess;
}


bool AskToPlayAgain(){
    std :: cout << "Do you want to play again with the same hidden word?(y/n)";
    FText Response = "";
    std :: getline(std :: cin, Response);
    std:: cout << "\n\n";
    return (Response[0]  == 'y'  || Response[0]  == 'Y' );
}

void PrintGameSummary()
{
    if(BCGame.IsGameWon())
    {
        std:: cout<< "\nWELL DONE - YOU WIN!";
    }
    else
    {
        std:: cout << "\nBetter luck next time!";
    }

}


