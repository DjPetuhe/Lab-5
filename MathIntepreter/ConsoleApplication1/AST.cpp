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

}

Node* AST::createReturnExpression(string return_expression)
{

}

Node* AST::createCondition(std::string)
{

}

Node* AST::createIfBody(std::string)
{

}

Node* AST::createElseBody(std::string)
{

}