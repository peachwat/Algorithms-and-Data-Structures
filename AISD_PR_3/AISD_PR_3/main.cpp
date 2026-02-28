#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include "vector.h"
#include "queue.h"
using namespace std;

#define black 1
#define noValue -1

void merge(MyVector &degree, int start, int mid, int end)
{
    int index1 = start;
    int index2 = mid + 1;
    MyVector temp;

    while (index1 <= mid && index2 <= end)
    {
        if (degree[index1] >= degree[index2])
        {
            temp.pushInt(degree[index1]);
            index1++;
        }
        else
        {
            temp.pushInt(degree[index2]);
            index2++;
        }
    }

    while (index1 <= mid)
    {
        temp.pushInt(degree[index1]);
        index1++;
    }

    while (index2 <= end)
    {
        temp.pushInt(degree[index2]);
        index2++;
    }

    for (int i = start; i <= end; i++)
    {
        degree[i] = temp[i - start];
    }
}

void sorting(MyVector &degree, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        sorting(degree, left, mid);
        sorting(degree, mid + 1, right);
        merge(degree, left, mid, right);
    }
}

void printDegrees(MyVector &degree, int &biggestDegree)
{
    sorting(degree, 0, degree.getNumElements() - 1);
    biggestDegree = degree[0];
    for (int i = 0; i < degree.getNumElements(); i++)
    {
        printf("%d ", degree[i]);
    }
    printf("\n");
    degree.deleteData();
}

void notDone()
{
    for (int i = 0; i < 2; i++)
    {
        printf("?\n");
    }
}

void DFS(int node, int &n, MyVector graf[], MyVector &visited)
{
    if (node < 0 || node >= n)
    {
        return;
    }

    visited[node] = 1;

    for (int i = 0; i < graf[node].getNumElements(); i++)
    {
        int child = graf[node][i];
        if (visited[child] == 0)
        {
            DFS(child, n, graf, visited);
        }
    }
}

int searchForNeighbours(int &n, MyVector graf[])
{
    MyVector visited;
    for (int i = 0; i < n; i++)
    {
        visited.pushInt(0);
    }
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (visited[i] == 0)
        {
            DFS(i, n, graf, visited);
            count++;
        }
    }
    return count;
}

long long int countNumberOfEdges(MyVector graf[], long long int n)
{
    long long int count = 0;
    for (int i = 0; i < n; i++)
    {
        count += graf[i].getNumElements();
    }
    return count / 2; // because we count twice
}

long long int countDopelnienieGrafu(long long int n, MyVector graf[])
{
    long long int sumOfEdges = n * (n - 1) / 2;
    long long int graphEdges = countNumberOfEdges(graf, n);

    return sumOfEdges - graphEdges;
}

void dwudzielnoscBFS(MyVector *graf, int n)
{
    int *color = new int[n];
    for (int i = 0; i < n; i++)
    {
        color[i] = noValue;
    }
    Queue q;

    for (int i = 0; i < n; i++)
    {
        if (color[i] == noValue)
        {
            color[i] = black;
            q.put(i);

            while (!q.empty())
            {
                int u = q.get();

                for (int k = 0; k < graf[u].getNumElements(); k++)
                {
                    if (graf[u][k] == u)
                    {
                        printf("F\n");
                        return;
                    }
                }

                for (int l = 0; l < graf[u].getNumElements(); l++)
                {
                    int v = graf[u][l];
                    if (color[v] == noValue)
                    {
                        color[v] = 1 - color[u]; // 1 - 1 = 0 (white), 1 - 0 = 1(black)
                        q.put(v);
                    }
                    else if (color[v] == color[u])
                    {
                        printf("F\n");
                        return;
                    }
                }
            }
        }
    }
    printf("T\n");
}

void coloringA(MyVector *graf, int &n)
{
    int *numbers = new int[n];
    numbers[0] = 1;

    for (int i = 1; i < n; i++)
    {
        numbers[i] = -1;
    }

    bool *notAccessibleNum = new bool[n];
    for (int i = 0; i < n; i++)
    {
        notAccessibleNum[i] = false;
    }

    for (int k = 1; k < n; k++)
    {
        for (int i = 0; i < graf[k].getNumElements(); i++)
        {
            if (numbers[graf[k][i]] != noValue)
                notAccessibleNum[numbers[graf[k][i]] - 1] = true;
        }

        int clr;
        for (clr = 0; clr < n; clr++)
            if (notAccessibleNum[clr] == false)
                break;

        numbers[k] = clr + 1;

        for (int i = 0; i < graf[k].getNumElements(); i++)
            if (numbers[graf[k][i]] != noValue)
                notAccessibleNum[numbers[graf[k][i]] - 1] = false;
    }
    delete[] notAccessibleNum;

    for (int l = 0; l < n; l++)
    {
        printf("%d ", numbers[l]);
    }

    printf("\n");
    delete[] numbers;
}

void coloringLF(MyVector *graf, int &n, int &biggestDegree)
{
    int *numbers = new int[n];
    int *degree = new int[n];
    int *order = new int[n];

    for (int i = 0; i < n; i++)
    {
        degree[i] = graf[i].getNumElements();
        order[i] = i;
        numbers[i] = noValue;
    }

    for (int a = 1; a < n; a++) // insertion sort
    {
        int key = order[a];
        int b = a - 1;

        while (b >= 0 && degree[order[b]] < degree[key])
        {
            order[b + 1] = order[b];
            b = b - 1;
        }
        order[b + 1] = key;
    }

    for (int a = 0; a < n; a++)
    {
        int v = order[a];
        bool *accessibleNum = new bool[biggestDegree + 1];
        for (int b = 0; b < biggestDegree + 1; b++)
        {
            accessibleNum[b] = false;
        }

        for (int b = 0; b < graf[v].getNumElements(); b++)
        {
            int u = graf[v][b];
            if (numbers[u] != noValue)
                accessibleNum[numbers[u] - 1] = true;
        }

        int clr;
        for (clr = 0; clr < biggestDegree + 1; clr++)
            if (accessibleNum[clr] == false)
                break;

        numbers[v] = clr + 1;
        delete[] accessibleNum;
    }

    for (int a = 0; a < n; a++)
    {
        printf("%d ", numbers[a]);
    }
    printf("\n");
    delete[] numbers;
    delete[] degree;
    delete[] order;
}

void acentrycznosc(MyVector *graf, int n)
{
    Queue q;
    bool *prev = new bool[n];
    int *odleglosc = new int[n];

    for (int i = 0; i < n; i++)
    {
        if (graf[i].getNumElements() == 0)
        {
            printf("0 ");
            continue;
        }
        for (int j = 0; j < n; j++)
        {
            prev[j] = false;
        }

        q.clear();
        prev[i] = true;
        odleglosc[i] = 0;
        q.put(i);

        int visitedNum = 1;
        int accentrycznosc = 0;
        while (!q.empty())
        {
            if (visitedNum == n)
            {
                while (!q.empty())
                {
                    q.get();
                }
                break;
            }

            int v = q.get();

            for (int j = 0; j < graf[v].getNumElements(); j++)
            {
                int s = graf[v][j];

                if (prev[s] == false)
                {
                    odleglosc[s] = odleglosc[v] + 1;
                    q.put(s);
                    prev[s] = true;
                    visitedNum++;
                    if (odleglosc[s] > accentrycznosc)
                    {
                        accentrycznosc = odleglosc[s];
                    }
                }
            }
        }
        printf("%d ", accentrycznosc);
    }
    printf("\n");
    delete[] prev;
    delete[] odleglosc;
}

void output(int &n, MyVector *&graf, MyVector &degree, int &biggestDegree)
{
    printf("\n");
    printf("\n");
    printDegrees(degree, biggestDegree);
    printf("%d\n", searchForNeighbours(n, graf));
    dwudzielnoscBFS(graf, n);
    acentrycznosc(graf, n);
    printf("?\n");
    coloringA(graf, n);
    coloringLF(graf, n, biggestDegree);
    notDone();
    printf("%lld\n", countDopelnienieGrafu(n, graf));
    printf("\n");
    printf("\n");
}

void inputAndOutput(int &k, int &n, MyVector *&graf, MyVector &degree, int &biggestDegree)
{
    for (int i = 0; i < k; i++)
    {
        scanf("%d", &n);
        graf = new MyVector[n];
        for (int j = 0; j < n; j++)
        {
            int neighNum = 0;
            scanf("%d", &neighNum);
            degree.pushInt(neighNum);

            for (int l = 0; l < neighNum; l++)
            {
                int neighbours = 0;
                scanf("%d", &neighbours);
                graf[j].pushInt(neighbours - 1); // i - node, k - neighbours
            }
        }
        output(n, graf, degree, biggestDegree);
    }
}

int main()
{
    int k, n; // k - graphs, n - nodes
    scanf("%d", &k);

    MyVector *graf;
    MyVector degree;
    int biggestDegree;
    inputAndOutput(k, n, graf, degree, biggestDegree);

    return 0;
}