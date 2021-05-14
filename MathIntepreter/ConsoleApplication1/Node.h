#pragma once
#include <string>
#include <vector>
#include "AST.h"

class Node
{
public:
	std::string data;
	std::vector<Node*> childrens;

	Node(std::string);
	static Node* makenode(std::string );
	static Node* makenode(std::string, std::vector<Node*>);
	friend class AST;
};
