//
//  FBullCowGame.hpp
//  BullCowGame
//
//  Created by Rasha Saadeh on 1/5/18.
//  Copyright © 2018 Rasha Saadeh. All rights reserved.
//


/* The game logic (no view code or direct user interaction)
 The game is a simple guess the word game based on Mastermind */

#ifndef FBullCowGame_hpp
#define FBullCowGame_hpp

#include <stdio.h>
#include <string>

// to make the syntax Unreal friendly
using int32 = int;
using FString = std :: string; //functions the same way as FText in terms of substition, replaces the standard string (std:: string), more compatible with Unreal

//all values initialized to zero
struct FBullCowCount {
    int32 Bulls = 0; //int32 = a 32 bit integer
    int32 Cows = 0;
    
};

enum class EGuessStatus
{
    Invalid_Status,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lower_Case,
};



class FBullCowGame {
public:
    FBullCowGame(); //constructor
    
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;
    bool IsGameWon() const;
    EGuessStatus CheckGuessValidity(FString) const;
    int32 LengthOfIsogram(FString);
    void Reset(); 
    
    
    //count bulls & cows, and increases try # assuming valid guess
    FBullCowCount SubmitValidGuess(FString); //BullCowCount is a richer return type
    
    
    
    
    // Please try and ignore this and focuse on the interface above ^^
private:
    //see constructor for initialization
    int32 MyCurrentTry;
    FString MyHiddenWord; //FString because it is something we want to manipulate
    bool bGameIsWon;
    bool IsIsogram(FString) const;
    bool IsLowerCase(FString) const;
    int32 IsogramLength;
    
    
};

#endif /* FBullCowGame_hpp */


