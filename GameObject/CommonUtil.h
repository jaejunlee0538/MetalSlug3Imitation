#pragma once
#include <string>
namespace SGA {

	bool replaceLastString(std::string& str, const std::string& from, const std::string& to);
	int findNthOccurenceString(std::string input, std::string token, int n, bool reverse, int offset);
	bool isEndWidthString(std::string input, std::string token);
}