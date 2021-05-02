#include <iostream>
#include <string>
#pragma once
using namespace std;

class Stack
{
private:
    string* array;
    int size;
    int realSize;

public:
    Stack(int);
    Stack();
    ~Stack();
    void push(string);
    void pop();
    string top();
    bool isEmpty();
};
