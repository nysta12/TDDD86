/* This file is a simulation that with the two given words,
   creates a wordchain going from the first to the second word */
//vicny135
#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <unordered_set>
#include <list>

using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";


// saves the words from the english dictionary with correct length in a set
void createDictionary(unordered_set<string> &dictionary, const int wordLength){
    ifstream file;
    file.open("dictionary.txt");
    string line;

    while(getline(file, line)){
        int length = line.size();
        if(length == wordLength){
            dictionary.insert(line);
        }
    }
    file.close();
}


//print the word chain from given stack
void printWordChain(stack<string>&finalStack, const string &w1, const string &w2){
    cout << "Chain from " << w2 << " back to " << w1 << ": " << endl;
    while(!finalStack.empty()){
        cout << finalStack.top() << " ";
        finalStack.pop();
    }
    cout << "\n";
    cout << "Have a nice day." << endl;
}


/* creates the queue containing stacks that contain word chains,
   if w2 is reached, a valid word chain has been found and is sent to print */
void wordchain(const string &w1, const string &w2, const unordered_set<string> &dictionary){
    queue<stack<string>>stackQueue;
    unordered_set<string>alreadyUsedWords;
    stack<string>initialStack;

    bool wordChainFound = false;

    // sets up the first stack and queue
    alreadyUsedWords.insert(w1);
    initialStack.push(w1);
    stackQueue.push(initialStack);

    while(!stackQueue.empty()){
        // dequeue first stack from queue
        stack<string>frontStack = stackQueue.front();
        stackQueue.pop();

        // final word reached
        if(w2 == frontStack.top()){
            printWordChain(frontStack, w1, w2);
            wordChainFound = true;
            break;
        }

        /* if word is a valid neighbour and has not already been used,
           copies current stack and pushes word to that stack and adds to queue */
        else{
            string word = frontStack.top();
            int length = word.size();
            for(int i = 0; i < length; i++){
                int lenghtAlphabet = ALPHABET.size();
                for(int j = 0; j < lenghtAlphabet; j++){
                    string tWord = word;
                    tWord[i] = ALPHABET[j];
                    if(!alreadyUsedWords.count(tWord) && dictionary.count(tWord)){
                        alreadyUsedWords.insert(tWord);
                        stack<string>newStack = frontStack;
                        newStack.push(tWord);
                        stackQueue.push(newStack);
                    }
                }
            }
        }
    }
    if(!wordChainFound){
        cout << "Sorry, no word chain found between " << w1 << " and " << w2 << endl;
    }
}


int main() {
    cout << "Welcome to TDDD86 Word Chain.\n";
    cout << "If you give me two English words, I will transform the\n";
    cout << "first into the second by changing one letter at a time.\n" << endl;

    cout << "Please type two words: ";

    string w1;
    cin >> w1;
    string w2;
    cin >> w2;

    int wordLength = w1.size();
    unordered_set<string>dictionary;
    createDictionary(dictionary, wordLength);
    wordchain(w1, w2, dictionary);


    return 0;
}
