#include "menu.h"


std::vector<std::string> Menu::read_file_structure()
{
	std::ifstream fin(decl::input_file_name);
	std::vector<std::string> file_vec;
	std::string input_str_buffer;
	while(fin >> input_str_buffer)
	{
		file_vec.push_back(input_str_buffer);
	}

	std::sort(file_vec.begin(), file_vec.end());

	return file_vec;
}


std::pair<std::string, std::string> Menu::split(const std::string& s)
{
	return {s.substr(0, s.find('/')), s.substr(s.find('/') + 1)};
}

Menu::file_type Menu::determine_type(const std::string& file)
{
	const std::string& parent_folder = split(file).first;
	const std::string& file_name = split(file).second;

	if(parent_folder == "exe")
	{
		return file_type_exe;
	}

	if(file_name == "head")
	{
		return file_type_head;
	}

	return file_type_lib;
}

std::vector<std::string> Menu::list_custom(const std::vector<std::string>& file_vec, Menu::file_type file_type_val)
{
	std::vector<std::string> return_vec;
	for(const std::string& file: file_vec)
	{
		if(determine_type(file) == file_type_val)
		{
			return_vec.push_back(file);
		}
	}

	return return_vec;
}

std::vector<std::string> Menu::list_exe(const std::vector<std::string>& file_vec)
{
	return list_custom(file_vec, file_type_exe);
}

std::vector<std::string> Menu::list_lib(const std::vector<std::string>& file_vec)
{
	return list_custom(file_vec, file_type_lib);
}

std::vector<std::string> Menu::list_head(const std::vector<std::string>& file_vec)
{
	return list_custom(file_vec, file_type_head);
}

std::vector<std::string> Menu::list_object(const std::vector<std::string>& file_vec)
{
	std::vector<std::string> object_vec;
	for(const std::string& file: file_vec)
	{
		if(Menu::determine_type(file) == file_type_head)
		{
			continue;
		}

		object_vec.push_back(file);
	}

	return object_vec;
}


void Menu::all(std::ofstream& fout)
{
	Print::cmd(fout, "all", {"necessary_compile", "run_program"});
	Print::echo(fout, "Command executed = all");
}

void Menu::run(std::ofstream& fout)
{
	Print::cmd(fout, "run_program", {"folder_check"});
	Print::script(fout, "./" + decl::path_run_folder + "simulate.exe");
	Print::script(fout, "./" + decl::path_run_folder + "plot.exe");
	Print::script(fout, "zip -r run/results-old/$(TIMESTAMP).zip run/output/");
}


void Menu::folder_check(std::ofstream& fout)
{
	Print::cmd(fout, "folder_check");

	Print::script(fout, decl::terminal_rmrf + "run/output");

	for(const std::string& folder: decl::folder_exist_check)
	{
		Print::script(fout, decl::terminal_mkdir + folder);
	}

	Print::echo(fout, "Command executed = folder_check");
}


void Menu::necessary_compile(std::ofstream& fout, const std::vector<std::string>& file_vec)
{
	std::vector<std::string> deps =
		Menu::convert_vec(
			list_exe(file_vec),
			Menu::convert_to_exe);

	deps.insert(deps.begin(), "folder_check");

	Print::cmd(fout, "necessary_compile", deps);

	Print::echo(fout, "Command executed = necessary_compile");
}

void Menu::force(std::ofstream& fout)
{
	Print::cmd(fout, "force", {"clean", "necessary_compile"});
	Print::echo(fout, "Command executed = force");

}

void Menu::clean(std::ofstream& fout)
{
	Print::cmd(fout, "clean", {});
	Print::script(fout, decl::terminal_rmrf +  decl::path_build_folder);
}

std::vector<std::string> Menu::expand_with_extensions(const std::string& file)
{
	std::string parent_folder = split(file).first;
	std::string file_name = split(file).second;

	const std::vector<std::pair<bool, std::string>> all_vec
	{
		{determine_type(file) != file_type_exe, Menu::convert_to_head(file)},
		{determine_type(file) != file_type_head, Menu::convert_to_cpp(file)}
	};


	std::vector<std::string> extended_vec;
	for(const auto& file: all_vec)
	{
		if(file.first)
		{
			extended_vec.push_back(file.second);
		}
	}

	return extended_vec;
}

std::string Menu::convert_to_str(const std::vector<std::string>& file_vec)
{
	std::stringstream ss;
	for(const std::string& file: file_vec)
	{
		ss << " " << file;
	}

	return ss.str();
}

std::string Menu::convert_to_object(const std::string& file)
{
	std::string parent_folder = split(file).first;
	std::string file_name = split(file).second;

	return decl::path_build_folder + parent_folder + "_" + file_name + ".o";
}

std::string Menu::convert_to_exe(const std::string& file)
{
	return decl::path_run_folder + split(file).second + ".exe";
}

std::string Menu::convert_to_head(const std::string& file)
{
	return decl::path_src_folder + file + ".h";
}

std::string Menu::convert_to_cpp(const std::string& file)
{
	return decl::path_src_folder + file + ".cpp";
}


void Menu::edit(std::ofstream& fout, const std::vector<std::string>& file_vec)
{
	std::vector<std::string> edit_vec;
	for(const std::string& file_str: file_vec)
	{
		const std::vector<std::string>& expanded_vec = expand_with_extensions(file_str);
		edit_vec.insert(edit_vec.end(), expanded_vec.cbegin(), expanded_vec.cend());
	}

	Print::cmd(fout, "edit");
	Print::script(fout, decl::terminal_geany_open + convert_to_str(edit_vec));
}

std::vector<std::string> Menu::convert_vec(std::vector<std::string> v, std::function<std::string(const std::string&)> f)
{
	for(std::string& s: v)
	{
		s = f(s);
	}

	return v;
}

void Menu::exe(std::ofstream& fout, const std::vector<std::string>& file_vec)
{
	const std::vector<std::string>& exe_vec = Menu::list_exe(file_vec);
	const std::vector<std::string>& lib_vec = Menu::convert_vec(Menu::list_lib(file_vec), Menu::convert_to_object);

	for(std::string file_exe: exe_vec)
	{
		std::vector<std::string> deps(lib_vec);
		deps.insert(deps.begin(), Menu::convert_to_object(file_exe));
		Print::cmd(fout, Menu::convert_to_exe(file_exe), deps);
		Print::script(fout, decl::compile_command_exe + Menu::convert_to_str(deps) + " -o " + Menu::convert_to_exe(file_exe));
		Print::echo(fout, Menu::convert_to_exe(file_exe) + " created.");
	}
}


void Menu::object(std::ofstream& fout, const std::vector<std::string>& file_vec)
{
	const std::vector<std::string>& object_vec = Menu::list_object(file_vec);
	const std::vector<std::string>& head_vec = Menu::convert_vec(Menu::list_head(file_vec), Menu::convert_to_head);

	for(const std::string& file: object_vec)
	{
		std::vector<std::string> deps(head_vec);
		const std::vector<std::string>& expanded = Menu::expand_with_extensions(file);
		deps.insert(deps.begin(), expanded.cbegin(), expanded.cend());

		Print::cmd(fout, Menu::convert_to_object(file), deps);
		Print::script(fout, decl::compile_command_object + Menu::convert_to_cpp(file) + " -o " + Menu::convert_to_object(file));
		Print::echo(fout, Menu::convert_to_object(file) + " created.");
	}
}
