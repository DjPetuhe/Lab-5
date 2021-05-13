#pragma once
#include "Node.h"
class Node;
class AST
{
	Node* root;
	Node* createIfExpression(std::string);
	Node* createAssignExpression(std::string);
	Node* createReturnExpression(std::string);
	Node* createCondition(std::string);
	Node* createIfBody(std::string);
	Node* createElseBody(std::string);
	Node* createExpression(std::string);
public:
	AST();
	void createTree(std::vector<std::string> &);
};