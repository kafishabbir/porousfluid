#include "config_file/simulation.h"

const std::string config_file::Simulation::sigma_str = "sigma";
const std::string config_file::Simulation::mu_water_str = "mu_water";
const std::string config_file::Simulation::mu_oil_str = "mu_oil";
const std::string config_file::Simulation::total_volumetric_flow_rate_str = "total_volumetric_flow_rate";


bool config_file::Simulation::set(const std::string& buffer_line)
{
	const std::pair<std::string, std::string>& buffer = algo::Utility::split(buffer_line);

	const std::string& category = buffer.first;
	const double value = std::stod(buffer.second);

	if(category == sigma_str)
	{
		sigma = value;
		sigma_set = true;
		return true;
	}

	if(category == mu_water_str)
	{
		mu_water = value;
		mu_water_set = true;
		return true;
	}

	if(category == mu_oil_str)
	{
		mu_oil = value;
		mu_oil_set = true;
		return true;
	}

	if(category == total_volumetric_flow_rate_str)
	{
		total_volumetric_flow_rate = value;
		total_volumetric_flow_rate_set = true;
		return true;
	}

	std::cout << "-Err- in config_file::Simulation::set(), unrecognized category" << std::endl;

	return false;
}


bool config_file::Simulation::valid() const
{
	const bool validity =
		sigma_set &&
		mu_oil_set &&
		mu_water_set &&
		total_volumetric_flow_rate_set;

	return validity;
}
