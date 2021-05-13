#pragma once
#include <string>
#include <vector>
#include "AST.h"

class Node
{
	std::string data;
	std::vector<Node*> childrens;
public:
	Node(std::string);
	static Node* makenode(std::string data);
	friend class AST;
};
