#include <iostream>
#include <vector>
#include "FileWork.h"
#include "AST.h"
#include <map>

using namespace std;

int main()
{
	vector<string> code;
	FileWork::file_read(code);
	AST tree1;
	tree1.createTree(code);
	
	tree1.StartImplementation();
}