#pragma once
#include "Node.h"
#include <map>

using namespace std;

class Node;

class AST
{
public:
	Node* root;
	Node* createIfExpression(std::string);
	Node* createAssignExpression(std::string);
	Node* createReturnExpression(std::string);
	Node* createCondition(std::string);
	Node* createIfBody(std::string);
	Node* createElseBody(std::string);
	Node* createExpression(std::string);

	AST();
	void createTree(std::vector<std::string> &);
	void Implementation (Node *node, map <string, double> &variables);
	void StartImplementation (map <string, double> &variables);
	void assign (Node *node, map <string, double> &variables);
	double calculate (Node *node, map <string, double> &variables);
	double do_calculation (Node *node, map <string, double> &variables);
	bool isNumber (string s);
};