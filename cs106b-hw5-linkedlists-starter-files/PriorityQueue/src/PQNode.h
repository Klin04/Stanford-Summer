/*
 * CS 106B Priority Queue
 * This file declares and implements the PQNode structure.
 * Each PQNode structure represents a single node in a linked list for a
 * priority queue, storing a string of data, an int of priority, and
 * a pointer to a next node (NULL if none).
 *
 * PQNodes know how to compare themselves to each other using standard
 * relational operators like <, >=, ==, !=.  Note that comparing nodes is NOT
 * the same as comparing pointers to nodes, which simply compares the memory
 * addresses as integers and ignores the objects' inner state.
 * Nodes can also be printed to the console using the << operator.  Again, this
 * is not the same as printing a pointer to a node, which would just print its
 * memory address as an integer.
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * Version: 2016/07/20 Wed
 * Author : Marty Stepp
 */

#ifndef _pqnode_h
#define _pqnode_h

#include <iostream>
#include <string>
using namespace std;

struct PQNode {
public:
    string value;   // data in each node
    int priority;
    PQNode* next;   // pointer to next node (NULL if none)

    /*
     * Constructor to initialize a new node with the given value, priority,
     * and next node pointer.
     * If any values are omitted, zero-equivalents will be used.
     */
    PQNode(string value = "", int priority = 0, PQNode* next = NULL);
};

/*
 * Overloaded operators for comparing nodes.
 * Note that these operators work on nodes, not on pointers to nodes.
 */
bool operator <(const PQNode& node1, const PQNode& node2);
bool operator <=(const PQNode& node1, const PQNode& node2);
bool operator ==(const PQNode& node1, const PQNode& node2);
bool operator !=(const PQNode& node1, const PQNode& node2);
bool operator >(const PQNode& node1, const PQNode& node2);
bool operator >=(const PQNode& node1, const PQNode& node2);

/*
 * Overloaded operator to print a node to an output stream for debugging.
 */
ostream& operator <<(ostream& out, const PQNode& node);

#endif
