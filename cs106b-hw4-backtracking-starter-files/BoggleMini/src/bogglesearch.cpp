//This program is made by Kaijun Lin.
//It will both see if the word
//a human player types in can be formed
//(when as a human, no need to concern the validity of the words)
//and output all valid words in a dictionary as a computer.
//This program will simulate the boggle game in daily life.
//This program will be using recursion techniques.
//Helper function are written in the program.

// Please feel free to add any other #includes you need!
#include <string>
#include "boggle.h"
#include "grid.h"
#include "lexicon.h"
#include "strlib.h"
using namespace std;


void humanWordSearchHelper(Grid<char>& board, int row, int col, string& toDo, Grid<char>& mark);
void computerWordSearchHelper(Grid<char>& board, string& curr, Lexicon& dic, Grid<char>& mark, Set<string>& all, int row, int col);

//bool humanWordSearch(Grid<char>& board, string word)
//This function exams the word that human player types in
//to see if it can be formed with letters in the board.
//It takes in a grid implying the board and a string to be examed.
//It returns true if the word can be found and false if cannot.
//It returns false when the length of the string is less than four.
bool humanWordSearch(Grid<char>& board, string word) {
    if(word.length() < MIN_WORD_LENGTH){
        return false;
    }
    else{
        Grid<char> mark(board.numRows(), board.numCols());
        mark.fill('-'); //initializes the mark grid
        word = toUpperCase(word);
        string phrase = word;
        char last = phrase[phrase.size() - 1];
        for(int i = 0;i < board.numRows();i++){//from the back to the front
            for(int j = 0;j < board.numCols();j++){//hence easier to add char in the helper
                if(board[i][j] == last){//find the last character and start exploring
                    humanWordSearchHelper(board, i, j, phrase, mark);
                    if(phrase.size() == 0){
                        return true;//true indication
                    }
                }
            }
        }
    }
    return false;
}

//Set<string> computerWordSearch(Grid<char>& board, Lexicon& dictionary);
//This function takes in a board and a dictionary.
//It will find out all the valid words that can be formed
//with the characters on the board
//and store them in a set.
//Then it returns the set.
Set<string> computerWordSearch(Grid<char>& board, Lexicon& dictionary) {
    Set<string> allWords;
    string curr;
    Grid<char> mark(board.numRows(), board.numCols());//initialization
    mark.fill('-');
    for(int i = 0;i < board.numRows();i++){//start from every grid on the board
        for(int j = 0;j < board.numCols();j++){
            computerWordSearchHelper(board, curr, dictionary, mark, allWords, i, j);
            mark.fill('-');
            curr = "";
        }
    }
    return allWords;
}

//void humanWordSearchHelper(Grid<char>& board, int row, int col, string& toDo, Grid<char>& mark);
//It takes in two gird, one for the characters and the other for mark.
//It takes in two integers indicating the given row number and column number.
//It takes a string to test.
//If the string finally becomes empty, then it can be formed with the characters on the board.
//It has no ouput.
//It helps the humanWordSearch function.
void humanWordSearchHelper(Grid<char>& board, int row, int col, string& toDo, Grid<char>& mark){
    if(board.inBounds(row, col)){//recursive case
        if(toDo[toDo.size() - 1] == board[row][col] && mark[row][col] == '-'){//we start from the end of the string
            char now = toDo[toDo.size() - 1];
            toDo = toDo.substr(0, toDo.size() - 1);
            mark[row][col] = 'x';//mark
            for(int i = row + 1; i >= row - 1;i--){
                for(int j = col + 1;j >= col - 1;j--){
                    if((i != row) || (j != col)){
                        humanWordSearchHelper(board, i, j, toDo, mark);
                    }
                }
            }
//            humanWordSearchHelper(board, row + 1, col, toDo, mark);//recursion
//            humanWordSearchHelper(board, row + 1, col + 1, toDo, mark);
//            humanWordSearchHelper(board, row + 1, col - 1, toDo, mark);
//            humanWordSearchHelper(board, row - 1, col + 1, toDo, mark);
//            humanWordSearchHelper(board, row - 1, col - 1, toDo, mark);
//            humanWordSearchHelper(board, row - 1, col, toDo, mark);
//            humanWordSearchHelper(board, row, col + 1, toDo, mark);
//            humanWordSearchHelper(board, row, col - 1, toDo, mark);
            if(toDo.size() == 0){//base case
                return;
            }
            else{
                mark[row][col] = '-';//backtracking
                toDo += now;
            }
        }
        else{//exception case
            return;
        }
    }
}


//void computerWordSearchHelper(Grid<char>& board, string& curr, Lexicon& dic, Grid<char>& mark, Set<string>& all, int row, int col)；
//This function takes in two boards, one for characters and one for marks.
//It takes in a lexicon indicating dictionary to exam the validity of the word.
//It also receives a set to store all the words that are valid.
//It accepts two integers which show the starting position.
//It also takes in a string to follow the most current creation.
//It has no output.
//It helps the computerWordSearch function.
void computerWordSearchHelper(Grid<char>& board, string& curr, Lexicon& dic, Grid<char>& mark, Set<string>& all, int row, int col){
    if(board.inBounds(row, col)){//recursive case
        if(mark[row][col] == '-'){
            curr += board[row][col];
            mark[row][col] = 'x';//mark
            if(dic.containsPrefix(curr)){//go through all the neighbours
                for(int i = row + 1; i >= row - 1;i--){
                    for(int j = col + 1;j >= col - 1;j--){
                        if((i != row) || (j != col)){
                            computerWordSearchHelper(board, curr, dic, mark, all, i, j);
                        }
                    }
                }
//                computerWordSearchHelper(board, curr, dic, mark, all, row + 1, col + 1);
//                computerWordSearchHelper(board, curr, dic, mark, all, row + 1, col);
//                computerWordSearchHelper(board, curr, dic, mark, all, row + 1, col - 1);
//                computerWordSearchHelper(board, curr, dic, mark, all, row, col + 1);
//                computerWordSearchHelper(board, curr, dic, mark, all, row, col - 1);
//                computerWordSearchHelper(board, curr, dic, mark, all, row - 1, col + 1);
//                computerWordSearchHelper(board, curr, dic, mark, all, row - 1, col);
//                computerWordSearchHelper(board, curr, dic, mark, all, row - 1, col - 1);
            }
            if(curr.size() >= MIN_WORD_LENGTH && dic.contains(curr)){//base case
               all.add(curr);
               computerWordSearchHelper(board, curr, dic, mark, all, row, col);//to avoid substring case
               curr = curr.substr(0, curr.size() - 1);//backtracking
               mark[row][col] = '-';
            }
            else{
                curr = curr.substr(0, curr.size() - 1);//backtracking
                mark[row][col] = '-';
            }
        }
        else{//exception case
            return;
        }
    }
}

