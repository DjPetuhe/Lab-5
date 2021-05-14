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

Node* Node::makenode(string data, vector<string> childs)
{
	Node* node = new Node(data);
	for (int i = 0; i < childs.size(); i++)
	{
		node->childrens.push_back(makenode(childs[i]));
	}
	return node;
}