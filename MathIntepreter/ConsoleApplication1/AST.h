#pragma once
#include "Node.h"

class AST
{
	Node* root;
public:
	AST();
	void insertNode(string);
};