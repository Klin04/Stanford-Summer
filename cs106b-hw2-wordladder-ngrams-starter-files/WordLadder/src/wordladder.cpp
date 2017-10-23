// This wordladder is made by Kaijun Lin.
// This program transform a given word into another through a path that consists of words that exists.

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "hashset.h"
#include "simpio.h"
#include "stack.h"
#include "strlib.h"
#include "queue.h"
using namespace std;

void describe();
void setup(HashSet<string>& dictionary);
void setWords(string& word1, string& word2);
void isGoodToOperate(string& word1, string& word2,HashSet<string>& book);
void wordLadder(string& word1, string& word2, HashSet<string>& book);
//All parameters are passed by reference.
//If not, the recursive method in the "isGoodToOperate" cannot work well.

int main()
{
    describe();
    string word1;
    string word2;
    HashSet<string> dictionary;
    setup(dictionary);
    setWords(word1,word2);
    isGoodToOperate(word1,word2,dictionary);
    cout << "Have a nice day." << endl;
    return 0;
}

//void describe()
//This welcomes the users and decribes the game.
//This function takes in no parameter; it prints out descriptions.
void describe()
{
    cout << "Welcome to CS 106B Word Ladder." << endl;
    cout << "Please give me two English words, and I will change the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << "" << endl;
}

//void setup(HashSet<string>& dictionary);
//This function receives a hashset and then stores the dictionary in the hashset.
//This function has no output, simply initializing a dictionary for later use.
void setup(HashSet<string>& dictionary)
{
    ifstream input;
    string filename;
    filename = promptUserForFile(input,"Dictionary file name?");
    string line;
    while(getline(input,line)){
        dictionary.add(line);
    }
    cout << "" << endl;
    input.close();
}

//void setWords(string& word1,string& word2);
//This function receives two words and gives them initial value while determining whether their sizes are of standard.
//This function has no output;it initializes the values of word1 and word2.
void setWords(string& word1, string& word2)
{
    word1 = getLine("Word #1 (or Enter to quit):");
    if(word1.size() != 0){
    word1 = toLowerCase(word1);       //Here we make the whole program case-insensitive.
    word2 = getLine("Word #2 (or Enter to quit):");
    word2 = toLowerCase(word2);
 }
}

//void wordLadder(string word1,string word2,HashSet<string>& book);
//This is the most significant function, which idicates how the word ladder develops.
//This function takes in two words and a hashset which stores a dictionary to operate on the words and checks their validity.
//Then it tries to build a ladder through a stack; if succeeds, print the ladder out; if not, then there's no ladder。
//It employs a compound selection of a queue of stacks.
void wordLadder(string& word1,string& word2,HashSet<string>& book)
{
   Queue<Stack<string> > storage;
   Stack<string> store;
   store.push(word1);
   storage.enqueue(store);
   HashSet<string> origin;
   origin = book;
   bool yes = false;  //This boolean value is used to determine whether to leave the while loop and whether the word
   string change;     //ladder exists.
   book.remove(word1);
   while(yes == false && !storage.isEmpty()){  //This part is according to the algorithm of spec.pdf given.
     Stack<string> store1 = storage.dequeue();
     for(int i = 0;i < word1.size();i++){
       for(char ch = 'a';ch <= 'z';ch++){
         change = store1.peek();
         change[i] = ch;
         if(book.contains(change)){
         book.remove(change);   //This prevents redundant stacks of strings from appearing.
         if(change == word2){
           cout << "A ladder from " << word2 << " back to " << word1 << ":" << endl;
           cout << word2 << " ";
           while(!store1.isEmpty()){
               cout << store1.pop() << " ";
           }
           cout << "" << endl;
           yes = true;
           break;   //Leaves the for loop after successfully generating one word ladder.
         }          //Prevents more word ladders from being created and printed.
         else{
             Stack<string> store2 = store1;  //This creates a new stack and copy store1.
             store2.push(change);            //Then enqueues it.
             storage.enqueue(store2);
           }
         }
       }
       if(yes == true){
         break;
       }
     }
   }
   book = origin;
  if(yes == false){
      cout << "No word ladder found from " << word2 << " back to " << word1 << endl;
  }
}

//void isGoodToOperate(string& word1, string& word2, HashSet<string>& book);
//This function checks whether the two words are of our standard with the dictionary input.
//If not,reprompts users;If yes,then tells the program to operate on them.
//This function calls wordLadder function to generate wordlatter.
void isGoodToOperate(string& word1, string& word2, HashSet<string>& book)
{
    bool in = book.contains(word1)&&book.contains(word2);
    if(word1.size() == 0){
        cout << "";
    }
    else if(word2.size() == 0){
        cout << "";
    }
    else{    //We use recursive here to provide continuity for the game.
    if(in == false){
        cout << "The two words must be found in the dictionary" << endl;
        cout << "" << endl;
        setWords(word1,word2);
        isGoodToOperate(word1,word2,book);//do not use recursion, instead, use a while loop to re-prompt
    }
    while(word1.size() != 0 && word2.size() != 0){
    if(word1.size() != word2.size()){
        cout << "The two words must be the same length." << endl;
        cout << "" << endl;
        setWords(word1,word2);
        isGoodToOperate(word1,word2,book);
    }
   else if(word1 == word2){
        cout << "The two words must be different." << endl;
        cout << "" << endl;
        setWords(word1,word2);
        isGoodToOperate(word1,word2,book);
    }
    else{
        wordLadder(word1,word2,book);
        cout << "" << endl;
        setWords(word1,word2);
        isGoodToOperate(word1,word2,book);
    }
  }
 }
}

