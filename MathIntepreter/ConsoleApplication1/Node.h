#pragma once
#include <string>
#include <vector>
#include "AST.h"

class Node
{
	friend AST;
	std::string data;
	std::vector<Node*> childrens;
public:
	Node(std::string);
	static Node* makenode(std::string data);
};
