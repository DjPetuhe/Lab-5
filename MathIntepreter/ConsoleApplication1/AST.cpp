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
		if_node->childrens.push_back(createElseBody(if_expression));
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
		if (if_expression[i] = '}' && deep == 1)
		{
			endpos = i;
			i = if_expression.size();
		}
	}
	vector<string> ifBody;
	vector<string> expressions;
	ifBody.push_back(if_expression.substr(if_expression.find('{'), endpos));
	WorkWithCode::fromCodeToExp(ifBody,expressions);
}

Node* AST::createElseBody(string if_expression)
{

}

Node* AST::createExpression(string expression)
{

}