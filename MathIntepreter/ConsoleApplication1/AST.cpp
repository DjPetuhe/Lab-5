#include "AST.h"
#include "Node.h"
using namespace std;

AST::AST()
{
	this->root = Node::makenode("Calculation");
}

void AST::insertNode(string data)
{

}