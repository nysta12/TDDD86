/*
 * TDDD86 Boggle
 * This file contains the I/O stream of the program
 *
 * Author: Victor Nyström
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"

void createBoard(Boggle& boggle){
    if(yesOrNo("do you want to generate a random board? (y/n): ")){
        boggle.randomBoard();
    }
    else{
        while(true){
            cout << "Type the 16 letters to appear on the board: ";
            string s;
            getline(cin, s);
            s = trim(toUpperCase(s));
            if(boggle.validInputString(s)){
                boggle.choosenBoard(s);
                break;
            }
            else{
                cout << "Not a valid string, "
                        "the string should be 16 characters long and "
                        "consisting of letters from A-Z." << endl;
            }
        }
    }
}

void gameLoop(Boggle &boggle){
    while(true){
        cout << "It's your turn!" << endl;

        cout << boggle.boardToString() << endl;

        cout << "Your words (" << boggle.getFoundWords().size() << "): " << boggle.getFoundWords() << endl;

        cout << "Your score: " << boggle.getScore() << endl;

        cout << "Type a word (or press Enter to end your turn): ";
        string word;
        getline(cin, word);
        word = trim(toUpperCase(word));
        clearConsole();
        if(!word.empty()){
            if(!boggle.checkWordInLexicon(word)){
                cout << "The word isn't in the lexicon" << endl;
            }
            else if(!boggle.checkWordLenght(word)){
                cout << "The word isn't long enough" << endl;
            }
            else if(!boggle.checkWordInBoard(word)){
                cout << "The word can't be generated in the board" << endl;
            }
            else if(boggle.checkWordInFoundWords(word)){
                cout << "Sorry, you can't find a word twice" << endl;
            }
            else{
                cout << "You found a new word! " << word << endl;
                boggle.update(word);
            }
        }
        else{
            break;
        }
    }
}

void computer(Boggle &boggle){
    cout << "It's my turn!" << endl;

    boggle.checkWordsInBoard();
    boggle.updateComputerScore();

    cout << "My words (" << boggle.getAllWords().size() << "): " << boggle.getAllWords() << endl;

    cout << "My score: " << boggle.getComputerScore() << endl;
}

void result(Boggle &boggle){
    if(boggle.getComputerScore() > boggle.getScore()){
        cout << "Ha ha ha, I destroyed you. Better luck next time, puny human!" << endl;
    }
    else{
        cout << "WOW, you defeated me! Congratulations!" << endl;
    }
}

/*
 * Plays one game of Boggle using the given boggle game state object.
 */
void playOneGame(Boggle& boggle) {
    // creates the board
    createBoard(boggle);

    clearConsole();

    // runs the game for the user
    gameLoop(boggle);

    // runs the game for the computer
    computer(boggle);

    // calculates and displays the results
    result(boggle);

    // resets the game
    boggle.reset();
}

/*
 * Erases all currently visible text from the output console.
 */
void clearConsole() {
#if defined(_WIN32) || defined(_WIN64)
    std::system("CLS");
#else
    // assume POSIX
    std::system("clear");
#endif
}
