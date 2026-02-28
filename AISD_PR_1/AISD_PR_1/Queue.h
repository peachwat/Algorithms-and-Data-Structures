#pragma once
#include "Node.h"
using namespace std;

class Queue {
private:
    Node* top = nullptr;
    Node* bottom = nullptr;

public:
    Queue() : top(nullptr) {}

    void Put(int num) {
        Node* nNode = new Node(Tokens::integer,num);
        if (top == nullptr) {
            top = bottom = nNode;
        }
        else {
            bottom->next = nNode;
            bottom = nNode;
        }
    }

    void Put(Tokens token, int num = 0) {//override
        Node* nNode = new Node(token, num);
        if (top == nullptr) {
            top = bottom = nNode;
        }
        else {
            bottom->next = nNode;
            bottom = nNode;
        }
    }

    Node Get() {
        Node* temp = top;

        Node result = *temp; 
        top = top->next;
        delete temp;
        return result;
    }

    int GetInt() {
        Node* temp = top;
        
        int result = temp->num;
        top = top->next;
        delete temp;
        return result;
    }

    Tokens GetToken() {
        Node* temp = top;

        Tokens token = temp->token;
        top = top->next;
        delete temp;
        return token;
    }

    bool Empty() const{
        return top == nullptr;
    }

    ~Queue() {
        while (!Empty()) {
            Get();
        }
    }

    friend ostream& operator<<(std::ostream& os, const Queue& queue) {
        Node* current = queue.top;
        while (current != nullptr) {
            os << *current;
            current = current->next;
        }
        return os;
    }
};