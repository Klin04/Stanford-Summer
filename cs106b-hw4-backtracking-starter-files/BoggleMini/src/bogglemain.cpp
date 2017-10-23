/*
 * CS 106B Boggle mini
 * This instructor-provided file contains the main program and
 * user interface for running your Boggle game.
 *
 * Please DO NOT MODIFY this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * Version: 2016/07/12 Tue
 * Author : Marty Stepp
 */

#include <fstream>
#include <iomanip>
#include <iostream>
#include "boggle.h"
#include "console.h"
#include "simpio.h"
#include "strlib.h"
using namespace std;

// global constants
static const int WORD_DISPLAY_WIDTH = 14;
static const string DICTIONARY_FILE = "dictionary.txt";
int BOARD_SIZE = 4;
int MIN_WORD_LENGTH = 4;

// function prototype declarations
bool makeBoard(Grid<char>& board, string boardText);
void computerTurn(Grid<char>& board);
void humanTurn(Grid<char>& board);
void intro();

int main() {
    intro();
    
    // set up board
    Grid<char> board(BOARD_SIZE, BOARD_SIZE);
    string boardText;
    do {
        boardText = trim(toUpperCase(getLine("Type the "
                + integerToString(BOARD_SIZE * BOARD_SIZE)
                + " letters to appear on the board: ")));
    } while (!makeBoard(board, boardText));
    
    humanTurn(board);
    computerTurn(board);
    
    cout << "Have a nice day!" << endl;
    return 0;
}

/*
 * Prints intro message at start of program.
 */
void intro() {
    cout << "Welcome to CS 106B Boggle Mini!" << endl
         << "This game is a search for words" << endl
         << "on a 2-D board of letter cubes." << endl
         << "See how many words you can find," << endl
         << "and then I will reveal them all." << endl << endl;
}

/*
 *
 */
bool makeBoard(Grid<char>& board, string boardText) {
    if (boardText.length() != BOARD_SIZE * BOARD_SIZE) {
        return false;
    }
    boardText = toUpperCase(boardText);
    
    ostringstream out;
    out << "{";
    for (int i = 0, len = (int) boardText.length(); i < len; i++) {
        if (!isalpha(boardText[i])) {
            return false;
        }
        if (i % BOARD_SIZE == 0) {
            out << "{";
        }
        out << boardText[i];
        if (i % BOARD_SIZE == BOARD_SIZE-1) {
            out << "}";
        }
        if (i < len - 1) {
            out << ", ";
        }
    }
    out << "}";
    
    istringstream in(out.str());
    if (in >> board) {
        // display board
        cout << board.toString2D(
                /* rowStart */     "",
                /* rowEnd */       "",
                /* colSeparator */ " ",
                /* rowSeparator */ "\n")
             << endl
             << endl;
        return true;
    } else {
        return false;
    }
}

/*
 * Performs one human turn, calling the student's humanWordSearch
 * recursive function.
 */
void humanTurn(Grid<char>& board) {
    // prompt for words
    cout << "Human player's turn:" << endl;
    int wordsFound = 0;
    while (true) {
        string word = trim(getLine("Type a word (or Enter to stop): "));
        if (word.length() == 0) {
            break;
        }
        
        // calls your recursive function
        bool result = humanWordSearch(board, word);
        
        if (result) {
            cout << "You found a new word! \"" << word << "\"" << endl;
            wordsFound++;
        } else {
            cout << "Invalid word or not found on the board." << endl;
        }
    }
    cout << "You found " << wordsFound << " total words." << endl;
    cout << endl;
}

/*
 * Performs one computer turn, calling the student's computerWordSearch
 * recursive function.
 */
void computerTurn(Grid<char>& board) {
    cout << "Computer player's turn:" << endl;
    Lexicon dictionary(DICTIONARY_FILE);   // read dictionary

    // calls your recursive function
    Set<string> allWords = computerWordSearch(board, dictionary);
    
    cout << "There were " << allWords.size() << " total words:" << endl;
    int i = 0;
    for (string word : allWords) {
        cout << setw(WORD_DISPLAY_WIDTH) << left << word;
        i++;
        if (i % 5 == 0 || i == allWords.size()) {
            cout << endl;
        }
    }
}
