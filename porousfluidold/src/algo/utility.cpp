#include "algo/utility.h"


std::pair<std::string, std::string> algo::Utility::split(const std::string& s)
{
	return
	{
		s.substr(0, s.find("=")),
		s.substr(s.find("=") + 1)
	};
}
