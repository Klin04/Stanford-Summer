/*
 * CS 106B Boggle mini
 * This instructor-provided file declares some constants and function
 * prototypes used by the Boggle game.
 *
 * Please DO NOT MODIFY this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 * If you need to declare other function prototypes, declare them at the
 * top of your .cpp file, NOT here in this file.
 *
 * Version: 2016/07/12 Tue
 * Author : Marty Stepp
 */

#ifndef _boggle_h
#define _boggle_h

#include <string>
#include "grid.h"
#include "lexicon.h"
#include "set.h"
using namespace std;

extern int MIN_WORD_LENGTH;
extern int BOARD_SIZE;

// below are the functions you must implement in bogglesearch.cpp
bool humanWordSearch(Grid<char>& board, string word);
Set<string> computerWordSearch(Grid<char>& board, Lexicon& dictionary);

#endif
