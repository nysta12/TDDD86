/* This file is a simulation of the game hangman,
   but a more difficult version where a word isn't chosen
   until it has to be. Instead word families of possilbe words
   created to make it more difficult to guess a "chosen" word*/
// vicny135
#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <map>

using namespace std;
const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

// saves dictionary to set
void createDictionary(set<string> &dictionary){
    ifstream file;
    file.open("dictionary.txt");
    string line;
    while(getline(file, line)){
            dictionary.insert(line);
    }
    file.close();
}

// asks for length of word and checks if the word is valid
int wordLength(const set<string> &dictionary){
    while(true){
        int wordLength;
        cout << "Choose a word length: ";
        cin >> wordLength;
        for(string word : dictionary){
            int length = word.size();
            if(wordLength == length){
                return length;
            }
        }
        cout << "Sorry, no word of that length exists in our dictionary" << endl;
    }
}

// returns the input of wanted nr of guesses
int nrOfGuesses(){
    while(true){
        int guesses;
        cout << "Choose your number of guesses: ";
        cin >> guesses;
        if(guesses > 0){
            return guesses;
        }
        else{
            cout << "Please choose a number of guesses more than zero" << endl;
        }
    }
}

// checks that the letter is in the alphabet and that it has not been guessed previously
char guessLetter(set<char> &letters){
    string letter;
    while(true){
        cout << "Guess a letter: ";
        cin >> letter;
        int lengthAlphabet = ALPHABET.size();
        for(int i = 0; i < lengthAlphabet; i++){
            if((letter[0] == ALPHABET[i]) && (!letters.count(letter[0])) && (letter.size() == 1)){
                letters.insert(letter[0]);
                return letter[0];
            }
        }
    }
}

/* separate words into families, where the representation of the word, for example: "_E__"
 is the key in the map and the values are vectors containing the words */
void wordFamilies(vector<string> &wordList, const char letter, const int length){
    map<string, vector<string>> allWordFamilies;
    // create the representation of a wordfamily
    for(string word : wordList){
        string wordRepresentation;
        for(int i = 0; i < length; i++){
            if(word[i] == letter){
                wordRepresentation += letter;
            }
            else{
                wordRepresentation += "_";
            }
        }
        // if the map contains the wordrepresentation then add the word to the vector
        if(allWordFamilies.find(wordRepresentation) != allWordFamilies.end()){
            allWordFamilies.at(wordRepresentation).push_back(word);
        }
        // add a new key value pair to the map
        else{
            vector<string>tempVec;
            tempVec.push_back(word);
            allWordFamilies.insert({wordRepresentation, tempVec});
            tempVec.clear();
        }
    }
    // save largest family as wordList
    int largestFamily = 0;
    for(auto wordFamily : allWordFamilies){
        int sizeFamily = wordFamily.second.size();
        if(sizeFamily >= largestFamily){
            largestFamily = sizeFamily;
            wordList = wordFamily.second;
        }
    }
}

// updates the gameWord
void updateGameWord(const int length, const char letter, string &gameWord, const vector<string> &wordList){
    for(int i = 0; i < length; i++){
        if(wordList.at(0)[i] == letter){
            gameWord[i] = letter;
        }
    }
}

// checks if gameWord is complete
bool checkGameWord(const string &gameWord){
    for(char c : gameWord){
        if(c == '_'){
            return false;
        }
    }
    return true;
}

int main() {
    cout << "Welcome to Hangman." << endl;
    set<string>dictionary;
    createDictionary(dictionary);
    string answer, gameWord, input;
    set<char>letters;
    int length = wordLength(dictionary);
    int guesses = nrOfGuesses();
    for(int i = 0; i < length; i++){
        gameWord += "_";
    }
    cout << "Do you want to see the remaining amount of possible words after every guess?\n";
    cout << "Answer: yes / no " << endl;
    cin >> answer;
    vector<string> wordList;
    for(string word : dictionary){
        int wordLength = word.size();
        if((wordLength == length) && (wordList.size() <= 250)){
            wordList.push_back(word);
        }
    }
    while(guesses > 0){
        cout << "Remaining guesses: " << guesses << endl;
        cout << "Guessed letters: ";
        for(char l : letters){
            cout << l << ", ";}
        cout << "\n";
        cout << "Current word: " << gameWord << endl;
        char letter = guessLetter(letters);
        wordFamilies(wordList, letter, length);
        if(answer == "yes"){
            cout << "\n";
            cout << "Possible words: ";
            for(string possibleWord : wordList){
                cout << possibleWord << " ";
            }
            cout << "\n";
        }
        string tempWord = gameWord;
        updateGameWord(length, letter, gameWord, wordList);
        if(tempWord == gameWord){
            guesses --;
        }
        if(checkGameWord(gameWord)){
            cout << "Congrats, YOU WIN!!!" << endl;
            cout << "Word: " << gameWord << endl;
            break;
        }
    }
    if(!checkGameWord(gameWord)){
        cout << "You lose! \n";;
        cout << "The correct word was: " << wordList.front() << endl;
    }
    cout << "\n" << "Want to play again? yes / no:" << endl;
    cin >> answer;
    if(answer == "yes"){
        wordList.clear();
        main();
    }
    else{
        cout << "Goodbye!!!" << endl;
    }
    return 0;
}
