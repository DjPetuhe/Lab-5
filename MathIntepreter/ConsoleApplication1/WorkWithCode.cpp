#include "WorkWithCode.h"
#include <vector>
#include <string>
using namespace std;

void WorkWithCode::fromCodeToExp(vector<string> &code, vector<string> &expressions)
{
	string all;
	for (int i = 0; i < code.size(); i++)
	{
		all += code[i];
	}
	string exp;
	bool isif = false;
	bool iselse = false;
	int inif = 0;
	for (int i = 0; i < all.size(); i++)
	{
		if (all[i] != ' ' && all[i] != '\t' && all[i] != '\n')
		{
			exp += all[i];
		}
		if (all[i] == '{')
		{
			inif++;
		}
		if (all[i] == '}')
		{
			inif--;
		}
		if ((exp.size() > 2) && (exp[2] == '(') && (exp[1] == 'f') && (exp[0] == 'i'))
		{
			isif = true;
		}
		if (all[i] == ';' && !isif)
		{
			expressions.push_back(exp);
			exp.clear();
		}
		if (isif && all[i] == '}' && inif == 0)
		{
			if (all.size() > i + 5 && !iselse && all[i+1] == 'e' && all[i+2] == 'l' && all[i+3] == 's' && all[i+4] == 'e' && all[i+5] == '{')
			{
				iselse = true;
			}
			if (inif == 0 &&(all.size() <= i + 5 || all[i+1] != 'e' || all[i+2] != 'l' || all[i+3] != 's' || all[i+4] != 'e' || all[i+5] != '{'))
			{
				expressions.push_back(exp);
				exp.clear();
				isif = false;
				iselse = false;
			}
		}
	}
}

void WorkWithCode::fromExpToTokens(string expression, vector<string>& tokens)
{
	string token;
	bool name = false;
	bool digit = false;
	for (int i = 0; i < expression.size(); i++)
	{
		if ((expression[i] >= 65 && expression[i] <= 90) || (expression[i] >= 97 && expression[i] <= 122))
		{
			token += expression[i];
			name = true;
		}
		if (name && !((expression[i] >= 65 && expression[i] <= 90) || (expression[i] >= 97 && expression[i] <= 122)))
		{
			tokens.push_back(token);
			token.clear();
			name = false;
		}
		if (expression[i] >= 48 && expression[i] <= 57)
		{
			token += expression[i];
			digit = true;
		}
		if (digit && !(expression[i] >= 48 && expression[i] <= 57))
		{
			tokens.push_back(token);
			token.clear();
			digit = false;
		}
		if (i > 1 && expression[i] == '=' && expression[i - 1] == ':')
		{
			token += expression[i - 1];
			token += expression[i];
			tokens.push_back(token);
			token.clear();
		}
		if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '^' || expression[i] == '/' || expression[i] == '(' || expression[i] == ')')
		{
			token = expression[i];
			tokens.push_back(token);
			token.clear();
		}
	}
}

bool WorkWithCode::expressionIsIf(string expression)
{
	if (expression.size() > 2)
	{
		if (expression[0] == 'i' && expression[1] == 'f' && expression[2] == '(')
		{
			return true;
		}
	}
	return false;
}

bool WorkWithCode::expressionIsAssign(string expression)
{
	for (int i = 0; i < expression.size(); i++)
	{
		if (i != 0)
		{
			if (expression[i] == '=' && expression[i - 1] == ':')
			{
				return true;
			}
		}
	}
	return false;
}

bool WorkWithCode::expressionIsReturn(string expression)
{
	if (expression.size() > 6)
	{
		if (expression.find("return"))
		{
			int pos = expression.find("return");
			if (pos == 0 && (!isalpha(expression[6])))
			{
				return true;
			}
		}
	}
	return false;
}

bool WorkWithCode::expressionConsistElse(string if_expression)
{
	if (if_expression.find("else"))
	{
		if (if_expression.size() > if_expression.find("else") + 4)
		{
			if (if_expression[if_expression.find("else") + 5] == '{')
			{
				return true;
			}
		}
	}
	return false;
}