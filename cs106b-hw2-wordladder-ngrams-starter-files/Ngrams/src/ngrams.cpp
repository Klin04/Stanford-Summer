//This is made by Kaijun Lin.
//This programthat reads an input file and uses it to build a large data structure of word groups
//called "Ngrams" as a basis for randomly generating new text
//that sounds like it came from the same author as that file.

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "simpio.h"
#include "random.h"
#include "map.h"
using namespace std;

void welcome();
int setupMap(Map<Vector<string>, Vector<string> >& start);
void displayMenu(int N, Map<Vector<string>, Vector<string> > &start);
void generateWords(int num, int N, Map<Vector<string>, Vector<string> > &start);

int main(){
    welcome();
    Map<Vector<string>, Vector<string> > initial;
    int N = setupMap(initial);
    displayMenu(N,initial);
    cout << "Exiting." << endl;
    return 0;
}

//void welcome()
//This function welcomes the players and describes how this game works.
//no parameters take in
//print descriptions
void welcome(){
    cout << "Welcome to CS 106B Random Writer ('N-Grams')." << endl;
    cout << "This program makes random text based on a document." << endl;
    cout << "Give me an input file and an 'N' value for groups" << endl;
    cout << "of words, and I'll create random text for you." << endl;
    cout << "" << endl;
}

//setupMap(Map<Vector<string>,Vector<string> >& start);
//This function takes in a map and stores the given text in it.
//It initializes the environment of the game.
//It returns the value of N for later use.
int setupMap(Map<Vector<string>,Vector<string> >& start){
    ifstream input;
    string filename = promptUserForFile(input,"Input file name?");
    int N = getInteger("Value of N?");
    while(N < 2){
        cout << "N must be 2 or greater." << endl;
        N = getInteger("Value of N?");
    }
    cout << "" << endl;
    Vector<string> window;
    string next;
    string record;
    for(int j = 0;j < N-1;j++){
        input >> record;
        window.add(record);
    }
    while(input >> next){  //Here we keep a window which always refreshes as the program reads the words.
    start[window].add(next);  //These windows will be stored as the keys of the map.
    for(int i = 0;i < N-2;i++){
        window[i] = window[i+1];
    }
    window[N-2] = next;
    }
    input.close();      //To make the map wrap around, we close it and then reopen it to take in new words.
    input.open(filename);
    for(int i = 0;i < N-1;i++){//We iterate N times to create enough new maps.
        input >> next;
        start[window].add(next);
        for(int i = 0;i < N-2;i++){
            window[i] = window[i+1];
        }
        window[N-2] = next;
    }
    input.close();
    return N;
}

//void displayMenu(int N,Map<Vector<string>,Vector<string> >& start)
//This function takes in the N and the map.
//It asks players for the number of words generated.
//It reprompts users if the number is not of standard.
void displayMenu(int N,Map<Vector<string>,Vector<string> >& start){
    int count = getInteger("# of random words to generate (0 to quit)?");
    if(count == 0){
        cout<<"";
    }
    else if(count < N){
        cout << "Must be at least "<< N <<" words." << endl;
        cout << "" << endl;
        displayMenu(N,start);
    }
    else{
        generateWords(count,N,start);
        displayMenu(N,start);
    }
}

//void generateWords(int num,int N,Map<Vector<string>,Vector<string> >& start);
//This function takes in two intergers and a map.
//It generates words and stores them in a string according to our given rule.
//It prints out the words at last.
void generateWords(int num,int N,Map<Vector<string>,Vector<string> >& start){
    int index1 = randomInteger(0,start.size()-1);
    Vector<Vector<string> > store;
    Vector<string> origin;
    Vector<string> change;
    store = start.keys();
    change = store[index1];
    origin = store[index1];
    Vector<string> text;
    for(int i = 0;i < N-1;i++){
        text.add(origin.get(i));
    }
    while(text.size() < num){
        int index2 = randomInteger(0,start[origin].size()-1);  //We keep change refreshing to add new string to the text.
        for(int j = 0;j < N-2;j++){                            //The reason we should make the map wrap around is here.
            change[j] = change[j+1];                           //If we don't do so, some "change"s do not have elements and the program crushes.
        }
        change[N-2] = start[origin].get(index2);
        origin = change;
        text.add(change[N-2]);
    }
    cout << "...";
    for(string s:text){
        cout << s << " ";
    }
    cout << "..." << endl;
    cout << "" << endl;
}
