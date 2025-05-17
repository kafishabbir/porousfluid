#include "print.h"

void Print::echo(
	std::ofstream& fout,
	const std::string& echo_message_str)
{
	fout << '\t' << "@echo " << '\"' << echo_message_str << '\"' << '\n';
}

void Print::cmd(
	std::ofstream& fout,
	const std::string& command_name_str,
	const std::vector<std::string>& dependencies_vec)
{
	fout << "\n\n";
	fout << command_name_str << ':';
	for(const std::string& dependency_str: dependencies_vec)
	{
		fout << ' ' << dependency_str;
	}
	fout << '\n';
}

void Print::script(std::ofstream& fout, const std::string& str_script)
{
	fout << '\t' << str_script << '\n';
}

