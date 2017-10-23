/*
 * CS 106B Anagram Solver
 * This instructor-provided file contains the main program and user interface
 * for running your anagram solver.
 *
 * Please DO NOT MODIFY this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * Version: Sun 2015/10/18
 * Author : Marty Stepp
 */

#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "lexicon.h"
#include "letterinventory.h"
#include "random.h"
#include "set.h"
#include "simpio.h"
#include "strlib.h"
using namespace std;

// constant for default dictionary file name to use if the user leaves it blank
static const string DICTIONARY_FILE_DEFAULT = "dict1.txt";

// constants for maximum phrase length or # of words found in it to avoid long/slow searches
// static const int MAX_PHRASE_LENGTH = 16;
static const int MAX_SMALL_DICTIONARY_SIZE = 400;

// function prototype declarations
int findAnagrams(string phrase, int max, Set<string>& dictionary);   // written by you, in anagramsolver.cpp
string promptForDictionaryFile();
int promptForMax();
void pruneDictionary(Lexicon& dictionary, string phrase, Set<string>& smallDictionary);
bool scrambleOnePhrase(Lexicon& dictionary);

int main() {
    cout << "Welcome to the CS 106B Anagram Solver!" << endl;

    // read dictionary of words from a file
    string dictionaryFile = promptForDictionaryFile();
    cout << "Reading dictionary ..." << endl;
    Lexicon dictionary(dictionaryFile);

    while (scrambleOnePhrase(dictionary)) {
        // empty
    }

    cout << "Have a nice day." << endl;
    return 0;
}

/*
 * Repeatedly prompts the user until they type a dictionary file name for
 * a file that exists in the res/ folder, then returns that file name.
 * Or if the user types a blank line, the default file is returned.
 */
string promptForDictionaryFile() {
    string dictionaryFile;
    while (dictionaryFile.empty() || !fileExists(dictionaryFile)) {
        dictionaryFile = trim(getLine("Dictionary file name (blank for "
                                             + DICTIONARY_FILE_DEFAULT + ")? "));
        if (dictionaryFile.empty()) {
            dictionaryFile = DICTIONARY_FILE_DEFAULT;
        } else if (!stringContains(dictionaryFile, ".")) {
            dictionaryFile += ".txt";   // default .txt extension
        }
    }
    return dictionaryFile;
}

/*
 * Repeatedly prompts the user until they type a non-negative max integer,
 * then returns that integer.
 * Or if the user types a blank line, 0 is returned.
 */
int promptForMax() {
    int max = 0;
    while (true) {
        string maxStr = trim(getLine("Max words to include (Enter for none)? "));
        if (maxStr.empty()) {
            max = 0;
            break;
        } else if (stringIsInteger(maxStr)) {
            max = stringToInteger(maxStr);
            if (max >= 0) {
                break;
            }
        }
    }
    return max;
}

/*
 * Performs one anagram search, prompting for the phrase and max words,
 * and then printing all anagrams along with a count of how many were printed.
 * Returns true if the user wants to keep going or false to quit.
 */
bool scrambleOnePhrase(Lexicon& dictionary) {
    // prompt for phrase to find anagrams of, and max # words
    cout << endl;
    string phrase = trim(getLine("Phrase to scramble (or Enter to quit)? "));
    if (phrase.empty()) {
        return false;
    }
    int max = promptForMax();
    
    // create a smaller "pruned" dictionary of only the relevant words
    Set<string> smallDictionary;
    pruneDictionary(dictionary, phrase, smallDictionary);
    
    // bail-out option if phrase or dict are too big (avoid long loops)
    if ( // phrase.length() > MAX_PHRASE_LENGTH ||
            smallDictionary.size() > MAX_SMALL_DICTIONARY_SIZE) {
        bool yesNo = getYesOrNo("Phrase contains many words. Search may be slow. Are you sure? (Y/n) ",
                                /* reprompt */ "",
                                /* defaultValue */ "Y");
        if (!yesNo) {
            return true;
        }
    }
    
    // call student's function to find and print the anagrams
    cout << "Searching for anagrams ..." << endl << endl;
    int count = findAnagrams(phrase, max, smallDictionary);
    cout << "Total anagrams found: " << count << endl;
    return true;
}

/*
 * Reduces the given dictionary lexicon into a smaller set of words that
 * contains only words that are found in the given phrase.
 * This helps optimize the process of searching for anagrams by
 * avoiding words that are not relevant to the phrase in question.
 */
void pruneDictionary(Lexicon& dictionary, string phrase, Set<string>& smallDictionary) {
    smallDictionary.clear();
    LetterInventory letters(phrase);
    for (string word : dictionary) {
        if (letters.contains(word)) {
            smallDictionary.add(word);
        }
    }
}
