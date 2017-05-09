#include "CommonUtil.h"
namespace SGA {

	bool replaceLastString(std::string & str, const std::string & from, const std::string & to) {
		size_t start_pos = str.rfind(from);
		if (start_pos == std::string::npos)
			return false;
		str.replace(start_pos, from.length(), to);
		return true;
	}

	int findNthOccurenceString(std::string input, std::string token, int n, bool reverse, int offset)
	{
		size_t pos;
		for (int i = 0; i < n; i++) {
			
			if (reverse)
				pos = input.rfind(token, offset);
			else
				pos = input.find(token, offset);
			if (pos == std::string::npos) {
				return -1;
			}
			if (reverse)
				offset = pos - 1;
			else
				offset = pos + 1;
		}
		return pos;
	}
	bool isEndWidthString(std::string input, std::string token)
	{
		int offset = input.size() - token.size();
		if (offset < 0) {
			return false;
		}
		for (int i = 0; i < token.size(); i++) {
			if (input[offset + i] != token[i]) {
				return false;
			}
		}
		return true;
	}
}