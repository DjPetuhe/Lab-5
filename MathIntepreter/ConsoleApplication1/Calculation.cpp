#include <iostream>
#include<stack>
#include <string>
#include "Calculation.h"

using namespace std;

double calculationStr (string exp) {
    double res = 0; 
    int size = exp.size();
    string *s = new string[size];
    expressionSeparate(exp, s, &size);
    res = calculate(s, size);
    return res;
}

void expressionSeparate(string args, string* expression, int* expressionSize)
{
    int count = 0;
    for (int i = 0; i < args.length(); i++)
    {
        if ((args[i] >= 48 && args[i] <= 57) || args[i] == 46)
        {
            if (count > 0 && !(expression[count][0] >= 48 && expression[count][0] <= 57))
            {
                count++;
            }
            expression[count] += args[i];
        }
        else
        {
            if (args[i] != ' ')
            {
                count++;
                expression[count] += args[i];
            }
        }
    }
    *expressionSize = count + 1;
}

float do_operation(stack<string>& nums, stack<string>& operations)
{

    float a, b;
    char c;

    b = stof(nums.top());
    nums.pop();
    a = stof(nums.top());
    nums.pop();
    c = operations.top()[0];
    operations.pop();

    if (c == '+')
    {
        return a + b;
    }
    else if (c == '-')
    {
        return a - b;
    }
    else if (c == '*')
    {
        return a * b;
    }
    else if (c == '/')
    {
        return a / b;
    }
    else if (c == '^')
    {
        float res = 1;
        for (int i = 1; i <= (int)b; i++)
        {
            res *= a;
        }
        return res;
    }
    return 0;
}

float calculate(string* s, int size)
{
    stack<string> nums, operations;
    float res;

    for (int i = 0; i < size; i++)
    {
        if (s[i][0] >= '0' && s[i][0] <= '9')
        {
            nums.push(s[i]);
        }
        else if (s[i] == "+" || s[i] == "-")
        {
            if (!operations.empty() && (operations.top() == "*" || operations.top() == "/" || operations.top() == "-" || operations.top() == "+" || operations.top() == "^"))
            {
                while (!operations.empty() && (operations.top() == "*" || operations.top() == "/" || operations.top() == "-" || operations.top() == "+" || operations.top() == "^"))
                {
                    res = do_operation(nums, operations);
                    nums.push(to_string(res));
                }
            }

            if ((i == 0 || !(s[i - 1][0] >= '0' && s[i - 1][0] <= '9')) && s[i - 1] != ")")
            {
                nums.push("0");
            }

            operations.push(s[i]);
        }
        else if (s[i] == "*" || s[i] == "/")
        {
            if (!operations.empty() && (operations.top() == "*" || operations.top() == "/" || operations.top() == "^"))
            {
                while (operations.top() == "*" || operations.top() == "/" || operations.top() == "^")
                {
                    res = do_operation(nums, operations);
                    nums.push(to_string(res));
                }
            }

            operations.push(s[i]);
        }
        else if (s[i] == "(")
        {
            operations.push(s[i]);
        }
        else if (s[i] == ")")
        {
            while (operations.top() != "(")
            {
                res = do_operation(nums, operations);
                nums.push(to_string(res));
            }

            operations.pop();
        }
        else if (operations.top() != "^" && s[i] == "^")
        {
            operations.push(s[i]);
        }
    }

    while (!operations.empty() && !nums.empty())
    {
        res = do_operation(nums, operations);
        nums.push(to_string(res));
    }

    return stof(nums.top());
}