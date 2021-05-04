#include "FileWork.h"
#include <iostream>
#include <fstream>
using namespace std;

void FileWork::file_read(std::string* filedata)
{
	cout << "Enter your file directory:" << endl;
	string directory;
	if (cin.peek() == '\n')
	{
		cin.ignore();
	}
	getline(cin, directory);
	ifstream filetext(directory);
	if (!filetext.is_open())
	{
		cout << "Error! cant open a file" << endl;
	}
	else
	{
		int i = 0;
		while (!filetext.eof())
		{
			getline(filetext, filedata[i]);
			i++;
		}
	}
	
	filetext.close();

}

void FileWork::file_write(float result)
{
	cout << "Enter directory, where you want to create result file:" << endl;
	string directory;
	if (cin.peek() == '\n')
	{
		cin.ignore();
	}
	getline(cin, directory);
	cout << endl << "Enter name of ther file" << endl;
	string filename;
	if (cin.peek() == '\n')
	{
		cin.ignore();
	}
	getline(cin, filename);
	string create = directory + filename;
	ofstream filetext(create);
	if (!filetext.is_open())
	{
		cout << "Error! cant create a file";
	}
	else
	{
		filetext << "result: " << result;
	}
	filetext.close();
}