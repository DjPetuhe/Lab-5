#pragma once
#include <vector>
#include <string>

class WorkWithCode
{
public:
	static void fromCodeToExp(std::vector<std::string>&, std::vector<std::string>&);
	static void fromExpToTokens(std::string, std::vector<std::string>&);
};