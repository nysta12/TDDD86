/*
 * TDDD86 Boggle
 * This file contains the implementation of the Boggle class
 *
 * Author: Victor Nyström
 */

#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"

static const int NUM_CUBES = 16;   // the number of cubes in the game
static const int CUBE_SIDES = 6;   // the number of sides on each cube
static string CUBES[NUM_CUBES] = {        // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

Boggle::Boggle(){
    board.resize(BOARD_SIZE, BOARD_SIZE);
    visited.resize(BOARD_SIZE, BOARD_SIZE);
    score = 0;
    computerScore = 0;
}

void Boggle::setUpVisited(){
    for(int row = 0; row < visited.numRows(); row++){
        for(int col = 0; col < visited.numCols(); col++){
            visited.set(row, col, false);
        }
    }
}

char Boggle::rollDice(const string &cube){
    char c = cube[randomInteger(0, CUBE_SIDES - 1)];
    return c;
}

void Boggle::randomBoard(){
    shuffle(CUBES, NUM_CUBES);
    int i = 0;

    for(int row = 0; row < board.numRows(); row++){
        for(int col = 0; col < board.numCols(); col++){

            // gets a char from the cube
            char c = rollDice(CUBES[i]);

            // places the char on the board
            board.set(row, col, c);

            // next cube
            i++;
        }
    }
}

void Boggle::choosenBoard(const string &s){
    int i = 0;

    for(int row = 0; row < board.numRows(); row++){
        for(int col = 0; col < board.numCols(); col++){

            // places the char on the board from the provided string
            board.set(row, col, s[i]);

            i++;
        }
    }
}

string Boggle::boardToString(){
    string s;
    for(int row = 0; row < board.numRows(); row++){
        for(int col = 0; col < board.numCols(); col++){
            s += board.get(row, col);
        }
        s += '\n';
    }
    return s;
}

bool Boggle::validInputString(const string &s){
    if(s.size() == 16){
        for(char c : s){
            if(ALPHABET.find(c) == string::npos){
                // the char couldn't be found, npos is returned
                return false;
            }
        }
        return true;
    }
    return false;
}

bool Boggle::checkWordLenght(const string &word){
    int wordLength = word.length();
    return wordLength >= MIN_WORD_LENGTH;
}

bool Boggle::checkWordInLexicon(const string &word){
    return LEXICON.contains(word);
}

bool Boggle::checkWordInFoundWords(const string &word){
    return foundWords.contains(word);
}

void Boggle::findWord(const string &word, string &s, const int r, const int c){

    if(word.compare(s) == 0){
        // compare the words, if the word has been found,
        // change boolean value of wordFound to true
        wordFound = true;
        return;
    }

    // loop through surrounding cells for given coordinates
    for(int row = r-1; row <= r+1 && row < BOARD_SIZE; row++){
       for(int col = c-1; col <= c+1 && col < BOARD_SIZE; col++){

           if(board.inBounds(row,col) && !visited.get(row, col)){
               // char is in bounds and it's coordinates has not been visited

               int index = s.length();
               if(board.get(row, col) == word[index]){
                   // if correct letter, recall method with updated string
                   // and updated visited grid
                   s += board.get(row, col);
                   visited.set(row, col, true);
                   findWord(word, s, row, col);
               }
           }
       }
   }
   // backtrack, check alternative paths
   s.pop_back();
   visited.set(r, c, false);
}

bool Boggle::checkWordInBoard(const string &word){
    // sets up visited grid by assigning false to all cells
    setUpVisited();

    for(int r = 0; r < board.numRows(); r++){
        for(int c = 0; c < board.numCols(); c++){

            if(board.get(r, c) == word[0]){
                // first letter in the word is found
                string s = "";
                s += board.get(r, c);
                visited.set(r, c, true);

                // call findWord method with a string for checking if the word has been found
                // and with the coordinates for the first letter in the word and the word itself
                findWord(word, s, r, c);

                if(wordFound){
                    return true;
                }
            }
        }
    }
    return false;
}

void Boggle::findAllWords(string s, const int i, const int j){
    s += board.get(i, j);
    visited.set(i, j, true);

    if(!LEXICON.containsPrefix(s)){
        // a prefix for s isn't in the lexicon,
        // exit method with return
        visited.set(i, j, false);
        return;
    }

    int stringLength = s.length();
    if((stringLength >= MIN_WORD_LENGTH) && LEXICON.contains(s) && !allWords.contains(s) && !foundWords.contains(s)){
        // if s upholds all the criterias it's added to allWords
        allWords.add(s);
    }

    for(int row = i-1; row <= i+1 && row < BOARD_SIZE; row++){
       for(int col = j-1; col <= j+1 && col < BOARD_SIZE; col++){
           if(board.inBounds(row, col) && !visited.get(row, col)){
               // recall method with updated string and updated visited grid
               findAllWords(s, row, col);
           }
       }
   }
   // backtrack
   visited.set(i, j,false);
}

void Boggle::checkWordsInBoard(){
    // sets up visited grid by assigning false to all cells
    setUpVisited();

    for(int row = 0; row < board.numRows(); row++){
        for(int col = 0; col < board.numCols(); col++){
            string s = "";

            // for every cell in the board, call method to find words
            findAllWords(s, row, col);
        }
    }
}

void Boggle::reset(){
    foundWords.clear();
    allWords.clear();
    computerScore = 0;
    score = 0;
    setUpVisited();
}

void Boggle::update(const string &word){
    foundWords.add(word);
    score += word.length() - 3;
}

void Boggle::updateComputerScore(){
    for(string word : allWords){
        computerScore += (word.length() - 3);
    }
}

int Boggle::getScore(){
    return this->score;
}

int Boggle::getComputerScore(){
    return this->computerScore;
}

Set<string> Boggle::getFoundWords(){
    return this->foundWords;
}

Set<string> Boggle::getAllWords(){
    return this->allWords;
}


Grid<char> Boggle::getBoard(){
    return this->board;
}
