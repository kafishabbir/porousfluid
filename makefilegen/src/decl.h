#ifndef MAKEFILE_GEN_DECL_H
#define MAKEFILE_GEN_DECL_H

#include <string>
#include <vector>
namespace decl
{
	const std::string target_output = "build/Makefile";
	const std::string path_src_folder = "src/";
	const std::string path_run_folder = "run/";
	const std::string path_build_folder = "build/";

	const std::string terminal_mkdir = "mkdir -p " ;
	const std::string terminal_rmrf = "rm -rf ";
	const std::string terminal_geany_open = "geany -i ";

	const std::string compile_command_object = "g++ -c -Wall -std=c++17 -Isrc/ ";
	const std::string compile_command_exe = "g++ ";
	const std::string input_file_name = "makefilegen-config.txt";

	const std::vector<std::string> folder_exist_check
	{
		path_build_folder,
		path_run_folder,
		path_run_folder + "input",
		path_run_folder + "output",
		path_run_folder + "output-old",
		path_run_folder + "output/simulation-data",
		path_run_folder + "output/simulation-calculations",
		path_run_folder + "output/plots",
		path_run_folder + "output/plots/pressure",
		path_run_folder + "output/plots/velocity",
		path_run_folder + "output/plots/fluids-nothick",
		path_run_folder + "output/plots/fluids-thick",
		path_run_folder + "output/plots/saturation",
	};
}

#endif
