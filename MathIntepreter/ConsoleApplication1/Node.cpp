#include "Node.h"
using namespace std;

Node::Node(string data)
{
	this->data = data;
}

Node* Node::makenode(string data)
{
	Node* node = new Node(data);
	return node;
}