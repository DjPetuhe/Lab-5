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
	for (int i = 0; i < all.size(); i++)
	{
		if (all[i] != ' ' && all[i] != '\t' && all[i] != '\n')
		{
			exp += all[i];
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
		if (isif && all[i] == '}')
		{
			if (all.size() > i + 5 && !iselse && all[i+1] == 'e' && all[i+2] == 'l' && all[i+3] == 's' && all[i+4] == 'e' && all[i+5] == '{')
			{
				iselse = true;
			}
			if (all.size() <= i + 5 || all[i+1] != 'e' || all[i+2] != 'l' || all[i+3] != 's' || all[i+4] != 'e' || all[i+5] != '{')
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