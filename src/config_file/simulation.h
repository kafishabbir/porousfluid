#ifndef CONFIG_FILE_SIMULATION_H
#define CONFIG_FILE_SIMULATION_H

#include "algo/utility.h"
#include <iostream>

namespace config_file
{

	class Simulation
	{
		static const std::string sigma_str;
		static const std::string mu_water_str;
		static const std::string mu_oil_str;
		static const std::string total_volumetric_flow_rate_str;

		bool sigma_set = false;
		bool mu_water_set = false;
		bool mu_oil_set = false;
		bool total_volumetric_flow_rate_set = false;

	public:
		double sigma;
		double mu_water;
		double mu_oil;
		double total_volumetric_flow_rate;

		bool set(const std::string& buffer_line);
		bool valid() const;
	};
}










#endif
