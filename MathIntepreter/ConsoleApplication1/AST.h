#pragma once
#include "Node.h"
class Node;
class AST
{
	Node* root;
	Node* createIfExpression(std::string);
	Node* createAssignExpression(std::string);
	Node* createReturnExpression(std::string);
public:
	AST();
	void createTree(std::vector<std::string> &);
};