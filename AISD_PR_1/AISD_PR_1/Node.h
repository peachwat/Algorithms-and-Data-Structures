#pragma once
#include "OnpElements.h"
using namespace std;

struct Node {

    int num;
    Tokens token;
    Node* next = nullptr;

    Node(Tokens t, int n = 0) : num(n), token(t), next(nullptr) {}
};

ostream& operator<<(std::ostream& os, const Node& node) {
    if (node.token == Tokens::integer) {
        os << node.num << " ";
    }
    else if (node.token == Tokens::min || node.token == Tokens::max) {
        os << node.token << node.num << " ";
    }
    else {
        os << node.token;
    }
    return os;
}