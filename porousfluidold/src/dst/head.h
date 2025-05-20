#ifndef DST_HEAD_H
#define DST_HEAD_H

#include "network/mns.h"
#include "network/dimension.h"
#include "config_file/simulation.h"

namespace dst
{
	typedef std::vector<std::vector<double>> Tradius;
	typedef std::vector<std::vector<double>> Tlength;
	typedef std::vector<std::vector<double>> Tdouble;
	typedef std::vector<std::vector<network::Mns>> Tmns;

	struct SimulationInput
	{
		Tradius tradius;
		Tlength tlength;
		Tmns tmns;
		network::Dimension dimension;
		config_file::Simulation simulation_config;
	};


	struct SimulationConstState
	{
		Tradius tradius;
		Tlength tlength;
		config_file::Simulation simulation_config;
		network::Dimension dimension;
	};

}

#endif
