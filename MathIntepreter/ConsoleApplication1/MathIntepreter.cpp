#include <iostream>
#include "Calculation.h"
#include "Stack.h"
using namespace std;

int main(int argc, char* argv[])
{
    string args;
    for (int i = 1; i < argc; i++)
    {
        args += argv[i];
    }
    string* expression = new string[args.size() + 1];

    int expression_size;
    expressionSeparate(args, expression, &expression_size);
    cout << calculate(expression, expression_size) << endl;
    delete[] expression;
}
