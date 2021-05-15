#include <iostream>
#include <cmath>
#include <map>
#include "AST.h"
#include "Node.h"
#include "WorkWithCode.h"
#include "Calculation.h"

using namespace std;

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
		string else_expression;
		WorkWithCode::fromIfToElse(if_expression, else_expression);
		if_node->childrens.push_back(createElseBody(else_expression));
	}
	return if_node;
}

Node* AST::createAssignExpression(string assign_expression)
{
	Node* assign_node = new Node(":=");
	string assigned = assign_expression.substr(0, assign_expression.find(':'));
	string assignment = assign_expression.substr(assign_expression.find('=') + 1, assign_expression.find(';') - 1);
	assign_node->childrens.push_back(Node::makenode(assigned));
	assign_node->childrens.push_back(createExpression(assignment));
	return assign_node;
}

Node* AST::createReturnExpression(string return_expression)
{
	Node* return_node = new Node("return");
	string returnment = return_expression.substr(7, return_expression.find(')') - 7);
	return_node->childrens.push_back(createExpression(returnment));
	return return_node;
}

Node* AST::createCondition(string if_expression)
{
	int startpos = if_expression.find('(');
	int endpos = if_expression.find(')');
	string condition = if_expression.substr(startpos + 1, endpos - startpos - 1);
	return createExpression(condition);
}

Node* AST::createIfBody(string if_expression)
{
	Node* ifBody_node = new Node("if body");
	int deep = 0;
	int endpos;
	for (int i = 0; i < if_expression.size(); i++)
	{
		if (if_expression[i] == '{')
		{
			deep++;
		}
		if (if_expression[i] == '}')
		{
			if (deep == 1)
			{
				endpos = i;
				i = if_expression.size();
			}
			deep--;
		}
	}
	vector<string> ifBody;
	vector<string> expressions;
	ifBody.push_back(if_expression.substr(if_expression.find('{') + 1, endpos - if_expression.find('{')-1));
	WorkWithCode::fromCodeToExp(ifBody,expressions);
	for (int i = 0; i < expressions.size(); i++)
	{
		if (WorkWithCode::expressionIsIf(expressions[i]))
		{
			ifBody_node->childrens.push_back(createIfExpression(expressions[i]));
		}
		else if (WorkWithCode::expressionIsAssign(expressions[i]))
		{
			ifBody_node->childrens.push_back(createAssignExpression(expressions[i]));
		}
		else if (WorkWithCode::expressionIsReturn(expressions[i]))
		{
			ifBody_node->childrens.push_back(createReturnExpression(expressions[i]));
		}
	}
	return ifBody_node;
}

Node* AST::createElseBody(string else_expression)
{
	Node* elseBody_node = new Node("else body");
	int deep = 0;
	int endpos;
	for (int i = 0; i < else_expression.size(); i++)
	{
		if (else_expression[i] == '{')
		{
			deep++;
		}
		if (else_expression[i] == '}' && deep == 1)
		{
			endpos = i;
			i = else_expression.size();
		}
	}
	vector<string> elseBody;
	vector<string> expressions;
	elseBody.push_back(else_expression.substr(else_expression.find('{') + 1, endpos - else_expression.find('{') - 1));
	WorkWithCode::fromCodeToExp(elseBody, expressions);
	for (int i = 0; i < expressions.size(); i++)
	{
		if (WorkWithCode::expressionIsIf(expressions[i]))
		{
			elseBody_node->childrens.push_back(createIfExpression(expressions[i]));
		}
		else if (WorkWithCode::expressionIsAssign(expressions[i]))
		{
			elseBody_node->childrens.push_back(createAssignExpression(expressions[i]));
		}
		else if (WorkWithCode::expressionIsReturn(expressions[i]))
		{
			elseBody_node->childrens.push_back(createReturnExpression(expressions[i]));
		}
	}
	return elseBody_node;
}

Node* AST::createExpression(string expression)
{
	vector<string> tokens;
	WorkWithCode::fromExpToTokens(expression, tokens);
	vector<string> operatorStack;
	vector<Node*> NodeStack;
	for (int i = 0; i < tokens.size(); i++)
	{
		if (tokens[i] == "(")
		{
			operatorStack.push_back(tokens[i]);
		}
		else if ((tokens[i][0] >= 65 && tokens[i][0] <= 90) || (tokens[i][0] >= 97 && tokens[i][0] <= 122) || (tokens[i][0] >= 48 && tokens[i][0] <= 57))
		{
			NodeStack.push_back(Node::makenode(tokens[i]));
		}
		else if (WorkWithCode::isOperator(tokens[i]))
		{
			while (!operatorStack.empty() && WorkWithCode::givePriority(operatorStack.back()) >= WorkWithCode::givePriority(tokens[i]))
			{
				string op = operatorStack.back();
				operatorStack.pop_back();
				vector<Node*> Childs;
				Childs.push_back(NodeStack.back());
				NodeStack.pop_back();
				Childs.push_back(NodeStack.back());
				NodeStack.pop_back();
				NodeStack.push_back(Node::makenode(op,Childs));
			}
			operatorStack.push_back(tokens[i]);
		}
		else if (tokens[i] == ")")
		{
			while (!operatorStack.empty() && operatorStack.back() != "(")
			{
				string op = operatorStack.back();
				operatorStack.pop_back();
				vector<Node*> Childs;
				Node * save = NodeStack.back();
				NodeStack.pop_back();
				Childs.push_back(NodeStack.back());
				NodeStack.pop_back();
				Childs.push_back(save);
				NodeStack.push_back(Node::makenode(op, Childs));

			}
			operatorStack.pop_back();
		}
	}
	while (!operatorStack.empty())
	{
		string op = operatorStack.back();
		operatorStack.pop_back();
		vector<Node*> Childs;
		Node* save = NodeStack.back();
		NodeStack.pop_back();
		Childs.push_back(NodeStack.back());
		NodeStack.pop_back();
		Childs.push_back(save);
		NodeStack.push_back(Node::makenode(op, Childs));
	}
	return NodeStack.back();
}

void AST::StartImplementation () {
	Implementation (root);
}

void AST::Implementation (Node *node) {
	//cout << node->data << endl;

	for (int i = 0; i < node->childrens.size(); i++) {
		//Implementation (node->childrens[i], variables);

		if (node->childrens[i]->data == ":=") {
			assign (node->childrens[i]);
		}
		else if (node->childrens[i]->data == "if") {
			if  (condiction (node->childrens[i]->childrens[0])) {
				Implementation (node->childrens[i]->childrens[1]);
			}
			else {
				Implementation (node->childrens[i]->childrens[2]);
			}
		}
		else if (node->childrens[i]->data == "return") {
			cout << calculate (node->childrens[i]->childrens[0]) << endl;
			return;
		}
		
	}
}

void AST::assign (Node *node) {

	if (variables.find(node->childrens[0]->data) == variables.end()) {
		variables.emplace(node->childrens[0]->data, calculate (node->childrens[1]));
	} else {
		variables.find(node->childrens[0]->data)->second = calculate (node->childrens[1]);
	}

	//calculate (node->childrens[1]);
}

double AST::calculate (Node *node) {
	double res = 0;
	string exp;

	if (node != nullptr)
		add_exp (node, exp);

	

	res = calculationStr(exp);
	
	//cout << exp << endl;

	//res = do_calculation(node);

	return res;
}

void AST::add_exp (Node *node, string &exp) {

	
	if (node->childrens.size() > 0 && node->childrens[0] != nullptr) {
		add_exp (node->childrens[0], exp);
	}

	
	if (isNumber(node->data) || node->data == "+" || node->data == "-" || node->data == "*" || node->data == "/" || node->data == "^") {
		exp += node->data;
	} else {
		exp += to_string(variables.find(node->data)->second);
	}

	

	if (node->childrens.size() > 1 && node->childrens[1] != nullptr) {
		add_exp (node->childrens[1], exp);
	}
}

/*double AST::do_calculation (Node *node) {
	double res = 0;

	if (node->data == "+") {
		res = do_calculation(node->childrens[0]) + do_calculation(node->childrens[1]);
	} else if (node->data == "-") {
		res = do_calculation(node->childrens[0]) - do_calculation(node->childrens[1]);
	} else if (node->data == "/") {
		res = do_calculation(node->childrens[0]) / do_calculation(node->childrens[1]);
	} else if (node->data == "*") {
		res = do_calculation(node->childrens[0]) * do_calculation(node->childrens[1]);
	} else if (node->data == "^") {
		res = pow (do_calculation(node->childrens[0]), do_calculation(node->childrens[1]));
	} else if (isNumber(node->data)) {
		res = stof(node->data);
	} else {
		res = variables.find(node->data)->second;
	}

	return res;
}*/

bool AST::isNumber (string s) {
	for (int i = 0; i < s.size(); i++)
        if((s[i] < '0' || s[i] > '9') && s[i] != '-' && s[i] != '.') 
        	return false; 
    return true;
}

bool AST::condiction (Node *node) {
	bool res = false;

	if (node->data == ">") {
		res = calculate(node->childrens[0]) > calculate(node->childrens[1]);
	}
	else if (node->data == "<") {
		res = calculate(node->childrens[0]) < calculate(node->childrens[1]);
	} 
	else if (node->data == "=") {
		res = calculate(node->childrens[0]) == calculate(node->childrens[1]);
	}
	else if (node->data == "!=") {
		res = calculate(node->childrens[0]) != calculate(node->childrens[1]);
	} 
	else if (isNumber(node->data)) {
		res = stof(node->data);
	} else {
		res = variables.find(node->data)->second;
	}

	return res;
}