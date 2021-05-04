#pragma once
#include <string>
#include <vector>
#include "AST.h"

class Node
{
	friend AST;
	std::string data;
	std::vector<Node*> childrens;
	Node(std::string);
};
