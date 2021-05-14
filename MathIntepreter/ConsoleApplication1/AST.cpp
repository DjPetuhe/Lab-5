#include <iostream>
using namespace std;
#include "AST.h"
#include "Node.h"
#include "WorkWithCode.h"

AST::AST()
{
	this->root = Node::makenode("Calculation");
}

void AST::createTree(vector<string> &code)
{
	vector<string> expressions;
	vector<string> tokens;
	WorkWithCode::fromCodeToExp(code, expressions);
	for (int i = 0; i < expressions.size(); i++)
	{
		if (WorkWithCode::expressionIsIf(expressions[i]))
		{
			root->childrens.push_back(createIfExpression(expressions[i]));
		}
		else if (WorkWithCode::expressionIsAssign(expressions[i]))
		{
			root->childrens.push_back(createAssignExpression(expressions[i]));
		}
		else if (WorkWithCode::expressionIsReturn(expressions[i]))
		{
			root->childrens.push_back(createReturnExpression(expressions[i]));
		}
	}
}

Node* AST::createIfExpression(string if_expression)
{
	Node* if_node = new Node("if");
	if_node->childrens.push_back(createCondition(if_expression));
	if_node->childrens.push_back(createIfBody(if_expression));
	if (WorkWithCode::expressionConsistElse(if_expression))
	{
		string else_expression;
		WorkWithCode::fromIfToElse(if_expression, else_expression);
		if_node->childrens.push_back(createElseBody(else_expression));
	}
	return if_node;
}

Node* AST::createAssignExpression(string assign_expression)
{
	Node* assign_node = new Node(":=");
	string assigned = assign_expression.substr(0, assign_expression.find(':'));
	string assignment = assign_expression.substr(assign_expression.find('=') + 1, assign_expression.find(';') - 1);
	assign_node->childrens.push_back(Node::makenode(assigned));
	assign_node->childrens.push_back(createExpression(assignment));
	return assign_node;
}

Node* AST::createReturnExpression(string return_expression)
{
	Node* return_node = new Node("return");
	string returnment = return_expression.substr(return_expression.find("return") + 6, return_expression.find(';') - 1);
	return_node->childrens.push_back(Node::makenode(returnment));
	return return_node;
}

Node* AST::createCondition(string if_expression)
{
	int startpos = if_expression.find('(');
	int endpos = if_expression.find(')');
	string condition = if_expression.substr(startpos, endpos);
	return createExpression(condition);
}

Node* AST::createIfBody(string if_expression)
{
	Node* ifBody_node = new Node("if body");
	int deep = 0;
	int endpos;
	for (int i = 0; i < if_expression.size(); i++)
	{
		if (if_expression[i] = '{')
		{
			deep++;
		}
		if (if_expression[i] = '}')
		{
			if (deep == 1)
			{
				endpos = i;
				i = if_expression.size();
			}
			deep--;
		}
	}
	vector<string> ifBody;
	vector<string> expressions;
	ifBody.push_back(if_expression.substr(if_expression.find('{'), endpos));
	WorkWithCode::fromCodeToExp(ifBody,expressions);
	for (int i = 0; i < expressions.size(); i++)
	{
		if (WorkWithCode::expressionIsIf(expressions[i]))
		{
			ifBody_node->childrens.push_back(createIfExpression(expressions[i]));
		}
		else if (WorkWithCode::expressionIsAssign(expressions[i]))
		{
			ifBody_node->childrens.push_back(createAssignExpression(expressions[i]));
		}
		else if (WorkWithCode::expressionIsReturn(expressions[i]))
		{
			ifBody_node->childrens.push_back(createReturnExpression(expressions[i]));
		}
	}
}

Node* AST::createElseBody(string else_expression)
{
	Node* elseBody_node = new Node("else body");
	int deep = 0;
	int endpos;
	for (int i = 0; i < else_expression.size(); i++)
	{
		if (else_expression[i] = '{')
		{
			deep++;
		}
		if (else_expression[i] = '}' && deep == 1)
		{
			endpos = i;
			i = else_expression.size();
		}
	}
	vector<string> elseBody;
	vector<string> expressions;
	elseBody.push_back(else_expression.substr(else_expression.find('{'), endpos));
	WorkWithCode::fromCodeToExp(elseBody, expressions);
	for (int i = 0; i < expressions.size(); i++)
	{
		if (WorkWithCode::expressionIsIf(expressions[i]))
		{
			elseBody_node->childrens.push_back(createIfExpression(expressions[i]));
		}
		else if (WorkWithCode::expressionIsAssign(expressions[i]))
		{
			elseBody_node->childrens.push_back(createAssignExpression(expressions[i]));
		}
		else if (WorkWithCode::expressionIsReturn(expressions[i]))
		{
			elseBody_node->childrens.push_back(createReturnExpression(expressions[i]));
		}
	}
}

Node* AST::createExpression(string expression)
{
	vector<string> tokens;
	WorkWithCode::fromExpToTokens(expression, tokens);
	vector<string> operatorStack;
	vector<Node*> NodeStack;
	for (int i = 0; i < tokens.size(); i++)
	{
		if (tokens[i] == "(")
		{
			operatorStack.push_back(tokens[i]);
		}
		else if ((tokens[i][0] >= 65 && tokens[i][0] <= 90) || (tokens[i][0] >= 97 && tokens[i][0] <= 122) || (tokens[i][0] >= 48 && tokens[i][0] <= 57))
		{
			NodeStack.push_back(Node::makenode(tokens[i]));
		}
		else if (WorkWithCode::isOperator(tokens[i]))
		{
			while (WorkWithCode::givePriority(operatorStack.back()) >= WorkWithCode::givePriority(tokens[i]))
			{
				string op = operatorStack.back();
				operatorStack.pop_back();
				vector<Node*> Childs;
				Childs.push_back(NodeStack.back());
				NodeStack.pop_back();
				Childs.push_back(NodeStack.back());
				NodeStack.pop_back();
				NodeStack.push_back(Node::makenode(op,Childs));
			}
			operatorStack.push_back(tokens[i]);
		}
		else if (tokens[i] == ")")
		{
			while (operatorStack.back() != "(")
			{
				string op = operatorStack.back();
				operatorStack.pop_back();
				vector<Node*> Childs;
				Node * save = NodeStack.back();
				NodeStack.pop_back();
				Childs.push_back(NodeStack.back());
				NodeStack.pop_back();
				Childs.push_back(save);
				NodeStack.push_back(Node::makenode(op, Childs));

			}
			operatorStack.pop_back();
		}
	}
	return NodeStack.back();
}