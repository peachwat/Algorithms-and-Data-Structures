#include <iostream>
#include "OnpElements.h"
#include "Node.h"
#include "Stack.h"
#include "Queue.h"

#define STR_SIZE 10 // zakres int
using namespace std;

bool isNumber(char token[]) {
    for (int i = 0; i < STR_SIZE && token[i] != '\0'; ++i) {
        if (!isdigit(token[i])) {
            return false;
        }
    }
    return true;
}

int priority(Tokens op) {

    if (op == Tokens::pls || op == Tokens::mns) {
        return 0;
    }
    else if (op == Tokens::dz || op == Tokens::mn) {
        return 1;
    }
    else if (op == Tokens::iff) {
        return 2;
    }
    else if (op == Tokens::n) {
        return 3;
    }
    else if (op == Tokens::min || op == Tokens::max) {
        return 4;
    }
    else if (op == Tokens::open || op == Tokens::close) {
        return 5;
    }
    return -1; 
}

Tokens toToken(char token[]) {
    switch (token[0]) {
    case ' ': return Tokens::space;
    case '+': return Tokens::pls;
    case '-': return Tokens::mns;
    case '*': return Tokens::mn;
    case '/': return Tokens::dz;
    case 'N': return Tokens::n;
    case 'I': return Tokens::iff;
    case '(': return Tokens::open;
    case ')': return Tokens::close;
    case '.': return Tokens::dot;
    case ',': return Tokens::comma;
    case 'M':
        if (token[1] == 'I') {
            return Tokens::min;
        }
        else {
            return Tokens::max;
        }
    }
    return Tokens::integer;
}

int minimum(Queue& args) {
    int min = args.GetInt();
    while (!args.Empty()) {
        int num = args.GetInt();
        if (num < min) {
            min = num;
        }
    }
    return min;
}

int maximum(Queue& args) {
    int max = args.GetInt();
    while (!args.Empty()) {
        int num = args.GetInt();
        if (num > max) {
            max = num;
        }
    }
    return max;
}

int Calculations(Queue& args, Tokens& operation) {
    switch (operation) {
    case Tokens::pls:
        return args.GetInt() + args.GetInt();
    case Tokens::mns: {
        int a = args.GetInt();
        int b = args.GetInt();
        return b - a;
    }
    case Tokens::mn:
        return args.GetInt() * args.GetInt();
    case Tokens::dz: {
        int a = args.GetInt();
        int b = args.GetInt();
        if (a == 0) {
            return std::numeric_limits<int>::max();//returns max int, that cant be exceeded
        } 
        return b / a;
    }
    case Tokens::iff: {
        int a = args.GetInt();
        int b = args.GetInt();
        int c = args.GetInt();
        return (c > 0) ? b : a;
    }
    case Tokens::n:
        return -args.GetInt();
    case Tokens::min:
        return minimum(args);
    case Tokens::max:
        return maximum(args);
    default:
        return 0;
    }
}

void Math(Queue& onp) {

    Stack calc;
    Queue args;

    while (!onp.Empty()) {
        Node node = onp.Get();
        Tokens token = node.token;
        int value = node.num;
        if (token == Tokens::integer) {
            calc.Push(value);
        }
        else {
            switch (token) {
            case Tokens::iff:
                cout << token << calc;
                for (int i = 0; i < 3; i++) {
                    int number = calc.Popint();
                    args.Put(number);
                }
                calc.Push(Calculations(args, token));
                cout << endl;
            break;
            case Tokens::min:
                cout << token << value << " " << calc;
                for (int i = 0; i < value; i++) {
                    int number = calc.Popint();
                    args.Put(number);
                }
                calc.Push(Calculations(args, token));
                cout << endl;
            break;
            case Tokens::max:
                cout << token << value << " " << calc;
                for (int i = 0; i < value; i++) {
                    int number = calc.Popint();
                    args.Put(number);
                }
                calc.Push(Calculations(args, token));
                cout << endl;
            break;
            case Tokens::n:
                cout << token << calc;
                for (int i = 0; i < 1; i++) {
                    int number = calc.Popint();
                    args.Put(number);
                }
                calc.Push(Calculations(args, token));
                cout << endl;
                break;
            case Tokens::dz: {
                cout << token << calc;
                for (int i = 0; i < 2; i++) {
                    int number = calc.Popint();
                    args.Put(number);
                }
                int result = Calculations(args, token);
                if (result == std::numeric_limits<int>::max()) {
                    cout << endl << "ERROR" << endl;
                    while (!onp.Empty()) {
                        onp.Get();
                    }
                    return;
                }
                calc.Push(result);
                cout << endl;
                break;
            }
            case Tokens::mn:
                cout << token << calc;
                for (int i = 0; i < 2; i++) {
                    int number = calc.Popint();
                    args.Put(number);
                }
                calc.Push(Calculations(args, token));
                cout << endl;
                break;
            case Tokens::pls:
                cout << token << calc;
                for (int i = 0; i < 2; i++) {
                    int number = calc.Popint();
                    args.Put(number);
                }
                calc.Push(Calculations(args, token));
                cout << endl;
                break;
            case Tokens::mns:
                cout << token << calc;
                for (int i = 0; i < 2; i++) {
                    int number = calc.Popint();
                    args.Put(number);
                }
                calc.Push(Calculations(args, token));
                cout << endl;
                break;
            }
        }
    }
    if (!calc.Empty()) {
        std::cout << calc.Popint() << std::endl;
    }
}

void onpConversion(int n, Stack& operators, Stack& counter, Queue& onp, char tokenStr[STR_SIZE]) {

    for (int i = 0; i < n; ++i) {
        cin >> tokenStr;
        while (tokenStr[0] != '.') {
            Tokens token = toToken(tokenStr);

            if (token == Tokens::min || token == Tokens::max || token == Tokens::iff) {
                counter.Push(1);
            }
            if (isNumber(tokenStr)) {
                onp.Put(atoi(tokenStr));//ascii to int
            }
            else if (token == Tokens::open) {
                operators.Push(token);
            }
            else if (token == Tokens::close) {
                while (!operators.Empty()) {
                    Tokens top = operators.Poptoken();
                    if (top == Tokens::open) {
                        break;
                    }
                    if (top == Tokens::comma) {
                        if (!counter.Empty()) {
                            int topCounter = counter.Popint();
                            counter.Push(topCounter + 1);
                        }
                    }
                    if (top == Tokens::min || top == Tokens::max || top == Tokens::iff) {
                        if (!counter.Empty()) {
                            int topCounter = counter.Popint();
                            if (top != Tokens::iff) {
                                onp.Put(top, topCounter);
                            }
                            else onp.Put(top);
                        }
                    }
                    else onp.Put(top);
                }
            }
            else {
                int pr = priority(token);
                while (!operators.Empty()) {
                    Tokens top = operators.Poptoken();
                    if (top == Tokens::open || priority(top) < pr) {
                        operators.Push(top);
                        break;
                    }
                    if (top == Tokens::min || top == Tokens::max || top == Tokens::iff) {
                        if (!counter.Empty()) {
                            int topCounter = counter.Popint();
                            if (top != Tokens::iff) {
                                onp.Put(top, topCounter);
                            }
                            else onp.Put(top);
                        }
                    }
                    else {
                        if (top == Tokens::comma) {
                            if (!counter.Empty()) {
                                int topCounter = counter.Popint();
                                counter.Push(topCounter + 1);
                            }
                        }
                        if (top == Tokens::n && (token == Tokens::n || token == Tokens::iff)) {
                            operators.Push(top);
                            break;
                        }
                        onp.Put(top);
                    }
                }
                operators.Push(token);
            }
            cin >> tokenStr;
        }
        while (!operators.Empty()) {
            Tokens top = operators.Poptoken();
            if (top == Tokens::min || top == Tokens::max || top == Tokens::iff) {
                if (!counter.Empty()) {
                    int topCounter = counter.Popint();
                    if (top != Tokens::iff) {
                        onp.Put(top, topCounter);
                    }
                    else onp.Put(top);
                }
            }
            else onp.Put(top);
        }
        std::cout << onp << endl;
        Math(onp);
    }
}

int main() {
    int n = 0;
    cin >> n;

    Stack operators;
    Stack counter;
    Queue onp;
    char tokenStr[STR_SIZE] = {0};
    
    onpConversion(n, operators, counter, onp, tokenStr);

    return 0;
}
