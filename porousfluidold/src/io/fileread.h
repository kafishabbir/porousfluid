#ifndef IO_FILEREAD_H
#define IO_FILEREAD_H

#include "dst/head.h"
#include "global/head.h"
#include "config_files/incongen.h"


namespace io
{
	class FileRead
	{

		template<class T>
		static std::pair<std::vector<std::vector<T>>, bool> table(
			const std::string& file_name
		);

		template<class T>
		static std::pair<T, bool> config_file_template(
			const std::string& file_name
		);

	public:
		static std::pair<config_file::Simulation, bool> simulation_config();
		static std::pair<config_file::Incongen, bool> incongen_config();
		static std::pair<dst::Tlength, bool> tlength();
		static std::pair<dst::Tradius, bool> tradius();
		static std::pair<dst::Tmns, bool> tmns();
		static std::pair<dst::SimulationInput, bool> simulation_input();

	};
}


template<class T>
std::pair<T, bool> io::FileRead::config_file_template(const std::string& file_name)
{
	T buffer;
	std::ifstream fin(file_name);
	if(!fin)
	{
		std::cout << "-ERR- cound not open " << file_name << std::endl;
		return {buffer, false};
	}

	std::string buffer_line;
	while(fin >> buffer_line)
	{
		const bool success = buffer.set(buffer_line);
		if(!success)
		{
			std::cout << "-ERR- " << file_name
				<< " is corrupted, failure reading" << buffer_str << std::endl;
			return {buffer, false};
		}
	}
	return {buffer, buffer.valid()};
}

template<class T>
std::pair<std::vector<std::vector<T>>, bool> io::FileRead::table(const std::string& file_name)
{
	std::vector<std::vector<T>> buffer;

	std::ifstream fin(file_name);
	if(!fin)
	{
		std::cout << "-ERR-" << file_name << " does not exist, create using generate or restore manually." << std::endl;
		return {buffer, false};
	}

	int rows, cols;
	fin >> rows >> cols;

	std::vector<T> buffer_vec;
	T ipt;
	while(fin >> ipt)
	{
		buffer_vec.push_back(ipt);
	}

	if(buffer_vec.size() != size_t(rows * cols))
	{
		std::cout << "-ERR-in file " << file_name << " rows, cols are declared differently than the actual data in them." << std::endl;
		return {buffer, false};
	}

	buffer = std::vector<std::vector<T>>(rows, std::vector<T>(cols));
	int count = 0;
	for(auto& row: buffer)
	{
		for(auto& cell: row)
		{
			cell = buffer_vec[count ++];
		}
	}

	return {buffer, true};
}

#endif
