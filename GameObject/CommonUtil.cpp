#include "CommonUtil.h"
namespace SGA {

	bool replaceLastString(std::string & str, const std::string & from, const std::string & to) {
		size_t start_pos = str.rfind(from);
		if (start_pos == std::string::npos)
			return false;
		str.replace(start_pos, from.length(), to);
		return true;
	}
}