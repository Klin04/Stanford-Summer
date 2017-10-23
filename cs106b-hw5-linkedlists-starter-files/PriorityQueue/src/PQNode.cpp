
/*
 * CS 106B Priority Queue
 * This file implements the members of the PQNode structure.
 * See PQNode.h for declaration and documentation of each member.
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * Version: 2016/07/20 Wed
 * Author : Marty Stepp
 */

#include "PQNode.h"

PQNode::PQNode(string value, int priority, PQNode* next) {
    this->value = value;
    this->priority = priority;
    this->next = next;
}

bool operator <(const PQNode& node1, const PQNode& node2) {
    return node1.priority < node2.priority ||
            (node1.priority == node2.priority && node1.value < node2.value);
}

bool operator <=(const PQNode& node1, const PQNode& node2) {
    return node1 < node2 || node1 == node2;
}

bool operator ==(const PQNode& node1, const PQNode& node2) {
    return node1.priority == node2.priority && node1.value == node2.value;
}

bool operator !=(const PQNode& node1, const PQNode& node2) {
    return !(node1 == node2);
}

bool operator >(const PQNode& node1, const PQNode& node2) {
    return !(node1 <= node2);
}

bool operator >=(const PQNode& node1, const PQNode& node2) {
    return !(node1 < node2);
}

ostream& operator <<(ostream& out, const PQNode& node) {
    out << "\"" << node.value << "\":" << node.priority;
    return out;
}
