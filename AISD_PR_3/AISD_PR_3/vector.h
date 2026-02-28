#pragma once

class MyVector
{
private:
    int *array;
    int size;
    int current; // текущее количество элементов в массиве

public:
    MyVector() : array(new int[1]), size(1), current(0) {}

    explicit MyVector(int size) : array(new int[size]), size(size), current(0) {}

    MyVector(int size, int initValue) : array(new int[size]), size(size), current(size)
    {
        for (int i = 0; i < size; i++)
        {
            array[i] = initValue;
        }
    }

    int getNumElements() const
    {
        return current;
    }

    void pushInt(int arrData)
    {
        int *additional = nullptr;
        if (current == size)
        {
            additional = new int[2 * size];
            for (int i = 0; i < size; i++)
            {
                additional[i] = array[i];
            }
            delete[] array;
            array = additional;
            size = size * 2;
        }
        array[current] = arrData;
        current += 1;
    }

    int &operator[](int i)
    {
        static int defValue = 0;
        if (i < current)
        {
            return array[i];
        }
        return defValue; // if out of bounds
    }

    void deleteData()
    {
        delete[] array;
        array = new int[1];
        size = 1;
        current = 0;
    }

    ~MyVector() { delete[] array; }
};