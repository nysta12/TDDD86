// This is the .h file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header and replace it with your own

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "set.h"
#include "lexicon.h"
#include "grid.h"

using namespace std;

class Boggle {
public:
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;
    const Lexicon LEXICON = Lexicon(DICTIONARY_FILE);
    const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // Constructor
    Boggle();

    // randomized board is created
    void randomBoard();

    // user chooses a board
    void choosenBoard(const string &s);

    // returns proper output of board
    string boardToString();

    // checks if the string is 16 characters long and letter from A-Z
    bool validInputString(const string &s);

    // check that the word has a minimum length if 4
    bool checkWordLenght(const string &word);

    // check that the word is in the lexicon
    bool checkWordInLexicon(const string &word);

    // check if the word can be found in the board
    bool checkWordInBoard(const string &word);

    // check that the word isn't already among the found words
    bool checkWordInFoundWords(const string &word);

    // main function to find all the words
    void checkWordsInBoard();

    // register the points for the given word
    void registerPoints(const string &word);

    // reset game
    void reset();

    // update score and add word to found words
    void update(const string &word);

    // update the computers score
    void updateComputerScore();

    // show found words
    Set<string> getFoundWords();

    // return all possible words
    Set<string> getAllWords();

    // returns the board
    Grid<char> getBoard();

    // return the current score
    int getScore();

    // return the computers score
    int getComputerScore();


private:
    Grid<char> board;
    Grid<bool> visited;
    bool wordFound;
    int score;
    int computerScore;
    Set<string> foundWords;
    Set<string> allWords;

    // return random character from cube
    char rollDice(const string &cube);

    // sets up visited grid by filling it with false
    void setUpVisited();

    // recursive search algorithm for one word
    void findWord(const string &word, string s, int &i, int &j);

    // recursive search algorithm for all words
    void findAllWords(string s, int &i, int &j);
};

#endif
