#pragma once
#include "Node.h"
using namespace std;

class Stack {
private:
    Node* top;

public:

    Stack() : top(nullptr) {}

    void Push(Tokens token) {
        Node* nNode = new Node(token);
        nNode->next = top;
        top = nNode;
    }

    void Push(int num) {
        Node* nNode = new Node(Tokens::integer, num);
        nNode->next = top;
        top = nNode;
    }

    int Popint() {
        Node* temp = top;

        int result = temp->num;
        top = top->next;
        delete temp;
        return result;
    }

    Tokens Poptoken() {
        Node* temp = top;

        Tokens token = temp->token;
        top = top->next;
        delete temp;
        return token;
    }

    bool Empty() const{
        return top == nullptr;
    }

        ~Stack() {
        while (!Empty()) {
            if (top->token == Tokens::integer) {
                Popint();
            }
            else {
                Poptoken();
            }
        }
    }
    friend ostream& operator<<(std::ostream& os, const Stack& stack) {
         Node* current = stack.top;
         while (current != nullptr) {
             os << *current;
             current = current->next;
         }
         return os;
    }
};