#ifndef MAKEFILE_GEN_MENU_H
#define MAKEFILE_GEN_MENU_H

#include "decl.h"
#include "print.h"
#include <utility>
#include <algorithm>
#include <sstream>
#include <functional>


class Menu
{
	enum file_type {file_type_head, file_type_lib, file_type_exe};

	static file_type determine_type(const std::string& file);
	static std::pair<std::string, std::string> split(const std::string& s);

	// conversions
	static std::string convert_to_cpp(const std::string& file);
	static std::string convert_to_exe(const std::string& file);
	static std::string convert_to_head(const std::string& file);
	static std::string convert_to_object(const std::string& file);
	static std::string convert_to_str(const std::vector<std::string>& file_vec);
	static std::vector<std::string> convert_vec(
		std::vector<std::string> v,
		std::function<std::string(const std::string&)> f);

	static std::vector<std::string> expand_with_extensions(const std::string& file);

	// list formations
	static std::vector<std::string> list_custom(const std::vector<std::string>& file_vec, file_type file_type_val);
	static std::vector<std::string> list_exe(const std::vector<std::string>& file_vec);
	static std::vector<std::string> list_head(const std::vector<std::string>& file_vec);
	static std::vector<std::string> list_lib(const std::vector<std::string>& file_vec);
	static std::vector<std::string> list_object(const std::vector<std::string>& file_vec);



public:
	static std::vector<std::string> read_file_structure();
	static void all(std::ofstream& fout);
	static void run(std::ofstream& fout);
	static void necessary_compile(std::ofstream& fout, const std::vector<std::string>& file_vec);
	static void folder_check(std::ofstream& fout);
	static void force(std::ofstream& fout);
	static void clean(std::ofstream& fout);
	static void edit(std::ofstream& fout, const std::vector<std::string>& file_vec);
	static void exe(std::ofstream& fout, const std::vector<std::string>& file_vec);
	static void object(std::ofstream& fout, const std::vector<std::string>& file_vec);
};

#endif
