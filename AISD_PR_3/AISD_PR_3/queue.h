#pragma once
#include "vector.h"
using namespace std;

class Queue
{
private:
    MyVector array;
    int first, last;

public:
    Queue() : first(0), last(0) {}

    void put(int num)
    {
        array.pushInt(num);
        last++;
    }

    int get()
    {
        if (empty())
            return -1;
        int result = array[first];
        array[first] = 0;
        first++;
        return result;
    }

    void clear()
    {
        first = 0;
        last = 0;
        array.deleteData();
    }

    bool empty() const
    {
        return first == last;
    }
};