#include "io/fileread.h"

std::pair<dst::Tradius, bool> io::FileRead::tradius()
{
	return io::FileRead::table<double>(global::file::input::RADIUS);
}

std::pair<dst::Tlength, bool> io::FileRead::tlength()
{
	return io::FileRead::table<double>(global::file::input::LENGTH);
}

std::pair<dst::Tmns, bool> io::FileRead::tmns()
{
	return io::FileRead::table<dst::Mns>(global::file::input::MNS);
}


std::pair<config_file::Incongen, bool> io::FileRead::incongen_config()
{
	return config_file_template<config_file::Incongen>(
		global::file::input::INCONGEN_CONFIG
	);
}

std::pair<config_file::Simulation, bool> io::FileRead::simulation_config()
{
	return config_file_template<config_file::Simulation>(
		global::file::input::SIMULATION_CONFIG
	);
}


std::pair<dst::SimulationInput, bool> io::FileRead::simulation_input()
{
	dst::SimulationInput input_files;

	// STEP-1.1 read radius
	const auto& buffer_radius = io::FileRead::tradius();
	if(!buffer_radius.second)
	{
		std::cout << "-ERR-radius.txt is corrupted" << std::endl;
		return {input_files, false};
	}
	input_files.tradius = buffer_radius.first;

	// STEP-1.2 read mns
	const auto& buffer_mns = io::FileRead::tmns();
	if(!buffer_mns.second)
	{
		std::cout << "-ERR-mns.txt meniscus configuration file is corrupted" << std::endl;
		return {input_files, false};
	}
	input_files.tmns = buffer_mns.first;

	// STEP-1.3 read length
	const auto& buffer_length = io::FileRead::tlength();
	if(!buffer_length.second)
	{
		std::cout << "-ERR-length.txt meniscus file is corrupted" << std::endl;
		return {input_files, false};
	}
	input_files.tlength = buffer_length.first;

	// STEP-1.4 read simulation_config
	const auto& buffer_simulation_config = io::FileRead::simulation_config();
	if(!buffer_simulation_config.second)
	{
		std::cout << "-ERR-simulation_config meniscus file is corrupted" << std::endl;
		return {input_files, false};
	}
	input_files.simulation_config = buffer_simulation_config.first;


	input_files.dimension = network::Dimension(input_files.tradius);
	const network::Dimension dmns(input_files.tmns);
	const network::Dimension dlength(input_files.tlength);

	// STEP-2.1 check if tmns_type dimensions are okay
	if(!(input_files.dimension == dmns))
	{
		std::cout << "-ERR-Dimensions of tmns_type.txt is not correct" << std::endl;
		return {input_files, false};
	}

	// STEP-2.2 check if tlength dimensions are okay
	if(!(input_files.dimension == dlength))
	{
		std::cout << "-ERR-Dimensions of tlength.txt is not correct" << std::endl;
		return {input_files, false};
	}

	std::cout << "--FDK-All input files read correctly" << std::endl;
	return {input_files, true};
}


