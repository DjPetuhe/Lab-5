#pragma once
#include <vector>
#include <string>

class WorkWithCode
{
public:
	static void fromCodeToExp(std::vector<std::string>&, std::vector<std::string>&);
	static void fromExpToTokens(std::string, std::vector<std::string>&);
	static bool expressionIsIf(std::string);
	static bool expressionIsAssign(std::string);
	static bool expressionIsReturn(std::string);
	static bool expressionConsistElse(std::string);
	static void fromIfToElse(std::string);
};