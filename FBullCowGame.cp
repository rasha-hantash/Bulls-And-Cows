//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by Rasha Saadeh on 1/5/18.
//  Copyright © 2018 Rasha Saadeh. All rights reserved.
//

#include "FBullCowGame.hpp"
#include <map>
#include <algorithm>


//make syntax Unreal friendly
#define TMap std:: map
using int32 = int;


FBullCowGame::FBullCowGame() { Reset(); } //default constructor

bool FBullCowGame::IsGameWon() const { return bGameIsWon; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetHiddenWordLength() const {return IsogramLength; }



int32 FBullCowGame::GetMaxTries() const {
    
    TMap<int32, int32> WordLengthToMaxTries {{3, 4}, {4, 7}, {5,10}, {6,15}};
    return WordLengthToMaxTries[MyHiddenWord.length()]; //if wordlength is 3 return 5 tries
}

//returns a rich return value so that hidden word is absolutely an isogram
void FBullCowGame::Reset() { 
    
    FString HIDDEN_WORD = "";
    switch(IsogramLength)
    {
        case 3 :
            HIDDEN_WORD = "mat";
            break;
        case 4 :
            HIDDEN_WORD = "plan";
            break;
        case 5 :
            HIDDEN_WORD = "plane";
            break;
        case 6 :
            HIDDEN_WORD = "planet";
            break;
    }
    
  //  const FString HIDDEN_WORD = "plane"; //this MUST be an isogram
    
    MyHiddenWord = HIDDEN_WORD;
    MyCurrentTry = 1;
    bGameIsWon = false;
    return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
    
    if(!IsIsogram(Guess)) //if the guess isn't an isogram
    {
        return EGuessStatus::Not_Isogram; //TODO write function
    }
    else if (!IsLowerCase(Guess))
    {
        return EGuessStatus::Not_Lower_Case; //TODO write function
    }
    else if(Guess.length() != GetHiddenWordLength())
    {
        return EGuessStatus::Wrong_Length;
        
    }
    else
    {
        return EGuessStatus::OK;
    }
}

//receives a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
    std::transform(Guess.begin(), Guess.end(), Guess.begin(), ::tolower);
    MyCurrentTry++;
    
    FBullCowCount BullCowCount;
    int32 WordLength = MyHiddenWord.length(); //assuming the same length as guess
    
    // loop through all the letters in the hidden word
    for(int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
        for(int32 GChar = 0; GChar < WordLength; GChar++)
        {
            
            //compare letters against the guess word
            if(Guess[GChar] == MyHiddenWord[MHWChar])
            {
                //if they match at the same index
                if(MHWChar == GChar)
                {
                BullCowCount.Bulls++;
                }
                else{ //if they matched at different index
                BullCowCount.Cows++;
                    
                }
            }
        }
    }
    
    if(BullCowCount.Bulls == WordLength)
    {
        bGameIsWon = true;
    }
    
    return BullCowCount;
}


bool FBullCowGame::IsIsogram(FString Word) const {
    
    //treat 0 and 1 letter words as isograms
    if(Word.length() <2) { return true; }
    
    TMap<char, bool> LetterSeen;  //setup our map
    
    for(auto Letter : Word) //for all letters of the word
    {
        Letter = tolower(Letter); //handle mixed case
        
   
        if(LetterSeen[Letter]) //if the letter is in the map, bool is true
        {
            
            return false; //word is not an isogram
        }
        else
        {
            LetterSeen[Letter] = true;
        }
        
    }

    return true; //for example in cases where /0 is entered (which is an escape code
}

bool FBullCowGame::IsLowerCase(FString Word) const {
    
    for(auto Letter : Word)
    {
        if(!islower(Letter))
        {
            return false;
        }
    }
    return true;
}


int32 FBullCowGame::LengthOfIsogram(FString lengthOfWord) {
    
    IsogramLength = std::stoi(lengthOfWord);
    return IsogramLength;
}
















