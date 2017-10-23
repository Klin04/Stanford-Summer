//This file is modified by Kaijun Lin.
//It is used to implement the linked List(priority list).
//I add a private variable front inside the file.
//I also add a private helper function to get the front in the class.

#ifndef _linkedpriorityqueue_h
#define _linkedpriorityqueue_h

#include <cstddef>    // for NULL
#include <iostream>
#include <string>
#include "PQNode.h"
using namespace std;

class LinkedPriorityQueue {
public:
    LinkedPriorityQueue();
    ~LinkedPriorityQueue();
    void changePriority(string value, int newPriority);
    void clear();
    string dequeue();
    void enqueue(string value, int priority);
    bool isEmpty() const;
    string peek() const;
    int peekPriority() const;
    int size() const;
    friend ostream& operator <<(ostream& out, const LinkedPriorityQueue& queue);

private:
    PQNode* front;
    void getFront(PQNode*& temp) const;
};

#endif
