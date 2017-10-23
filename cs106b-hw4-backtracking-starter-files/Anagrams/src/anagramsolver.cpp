//This part of the program is written by Kaijun Lin.
//It will generate all the anagrams of a given phrase or word.
//Anagrams will be stored in a vector of Vectors.
//Anagrams will be printed out in the given form.

#include <iostream>
#include <string>
#include "letterinventory.h"
#include "strlib.h"
#include "exceptions.h"
#include "vector.h"
#include "hashset.h"
#include "set.h"
using namespace std;

void findAnagramsHelper(int max, HashSet<string>& toUse, LetterInventory& store, Vector<string>& chosen, int &total);

//int findAnagrams(string phrase, int max, Set<string>& dictionary);
//This function takes in a phrase containing all letters we are
//going to use to form anagrams.
//Spaces will be ignored.
//Integer max indicates the maximum number of the anagrams.
//The set taken in works as a dictionary to exam if the
//generated words are valid.
//It returns the total number of the anagrams.
int findAnagrams(string phrase, int max, Set<string>& dictionary) {
    if(max < 0){
        throw max;
    }
    int total = 0;
    LetterInventory store = LetterInventory(phrase);
    HashSet<string> canUse;
    for(string word : dictionary){//generate a hashset of words that can be chosen
        if(store.contains(word)){
             canUse += word;
        }
    }
    Vector<string> each;
    for(string word : canUse){//generate each vector and print them out
        each += word;//offer the starting word
        store.subtract(word);
        findAnagramsHelper(max, canUse, store, each, total);
        store = LetterInventory(phrase);//re-initialize
        each = {};
    }
    return total;
}

//void findAnagramsHelper(Vector<string>& toUse, LetterInventory& store, Vector<string>& chosen);
//This function helps to generate anagrams.
//The phrase is needed for base case.
//It takes in additional parameters, a letterInventory by reference and a integer
//implying the total number of anagrams.
//It also takes in a vector of vectors to store the anagrams.
//It takes in a letterinventory object which stores all the letters we are gonna use.
//Most of its part will work to generate anagrams.
//It has no output.
void findAnagramsHelper(int max, HashSet<string>& toUse, LetterInventory& store, Vector<string>& chosen, int& total){
    //probably we just return the total instead of passing it by reference
    //every time return 1 + (int) findAnagramsHelper(...);
     if(store.isEmpty()){//base case
         cout << chosen << endl;
         total++;
     }
     else{
         for(string word : toUse){//recursive case
             if(store.contains(word)){//choose
                 if(max == 0){//case 1
                     chosen.add(word);
                     store.subtract(word);
                     findAnagramsHelper(max, toUse, store, chosen, total);
                     store.add(chosen[chosen.size() - 1]);
                     chosen.remove(chosen.size() - 1);//backtracking
                 }
                 else if(chosen.size() <= max - 1){//gets out as soon as the size gets too big
                     chosen.add(word);
                     store.subtract(word);
                     findAnagramsHelper(max, toUse, store, chosen, total);
                     store.add(chosen[chosen.size() - 1]);//backtracking
                     chosen.remove(chosen.size() - 1);
                 }
             }
         }
     }
}


