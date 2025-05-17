#ifndef MAKEFILE_GEN_PRINT_H
#define MAKEFILE_GEN_PRINT_H

#include <fstream>
#include <vector>
#include <string>

class Print
{
public:
	static void echo(std::ofstream& fout,
		const std::string& echo_message_str);

	static void cmd(
		std::ofstream& fout,
		const std::string& command_name_str,
		const std::vector<std::string>& dependencies_vec = {});

	static void script(std::ofstream& fout, const std::string& str_script);
};

#endif
