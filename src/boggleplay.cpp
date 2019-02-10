// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <string>
#include <iostream>
#include "lexicon.h"
#include "simpio.h"
#include "strlib.h"
#include "bogglegui.h"
#include "Boggle.h"
#include "console.h"

using namespace std;
string userSpecifiesBoard();
void showGridInConsole(string grid);
const int PLAYEREN = 0;
void userGuesses(string grid, Boggle boggle);
void computerExostiveSearch(Boggle & boggle);

void playOneGame(Lexicon& dictionary) {
    if(!BoggleGUI :: isInitialized()){
        BoggleGUI ::initialize(4,4);
    }
    // choosing random board or user types in board chars
    string customBoard = userSpecifiesBoard();
    Boggle boggle(dictionary, customBoard);
    string grid = boggle.getboardCubes();
    BoggleGUI :: labelAllCubes(grid);
    userGuesses(grid, boggle);
    computerExostiveSearch(boggle);
}
void computerExostiveSearch(Boggle & boggle){
    cout << "Now it is my turn! " << endl;
    Set<string> computerWords = boggle.computerWordSearch();
    cout << computerWords << endl;
    cout << "Computer score = " << boggle.getScoreComputer() << endl;
}

void userGuesses(string grid, Boggle boggle){
    while(true){
        clearConsole();
        showGridInConsole(grid);
        cout << "Your words: " << boggle.getGuessedWords(PLAYEREN) << endl;
        cout << "Your score: " << boggle.getScoreHuman()<<endl;
        string possibleGuess = getLine("Type a word (or Enter to stop)");
        if(possibleGuess == ""){
            break;
        }
        bool valid = boggle.checkWord(possibleGuess);
        if(valid){
            bool canBeFormedFromBoard = boggle.humanWordSearch(possibleGuess);
            if(canBeFormedFromBoard){
                boggle.addToGuessed(possibleGuess, PLAYEREN);
            }
        }
    }
}



void showGridInConsole(string grid){
    for(int i = 1; i <= grid.length(); i++){
        cout << grid[i - 1];
        if(i % 4 == 0){
            cout << endl;
        }
    }
}
string userSpecifiesBoard(){
    string customBoard = "";
    bool computerGeneratedBoard = getYesOrNo("Do you want to initialize a random board (Y/N)? ");
    if (!computerGeneratedBoard) {
        bool nonAlphabet = false;
        while(customBoard.length() != 16 || nonAlphabet){
            customBoard = getLine("Enter 16 characters for a custom board: ");
            string upperBoard = toUpperCase(customBoard);
            for(char c : upperBoard){
                if(c < 'A' || c > 'Z'){
                    nonAlphabet = true;
                }
            }
        }
    }
    return customBoard;
}
