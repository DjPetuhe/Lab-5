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
	map <string, double> variables;

	AST();
	void createTree(std::vector<std::string> &);
	void Implementation (Node *node);
	void StartImplementation ();
	void assign (Node *node);
	double calculate (Node *node);
	double do_calculation (Node *node);
	bool isNumber (string s);
	bool condiction (Node *node);
	void add_exp (Node *node, string &expression);
};