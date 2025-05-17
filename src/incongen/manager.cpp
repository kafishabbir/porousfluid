#include "incongen/manager.h"

const std::string incongen::Manager::PROGRAM_NAME =
	"incongen: INitial_CONditions_GENerator";


/**
 * @brief generates all input files for simulation if a valid config
 * is detected, otherwise runs in interactive mode.
 *
 *
 */
void incongen::Manager::run()
{
	std::cout << PROGRAM_NAME << std::endl;

	const std::pair<config_file::Incongen, bool>& buffer =
		io::FileRead::incongen_config();

	const config_file::Incongen& incongen_config = buffer.first;
	bool success_reading_incongen_config = buffer.second;

	if(success_reading_incongen_config)
	{
		incongen::Manager::generate_from_incongen_config(incongen_config);
		return;
	}

	incongen::Manager::write_default_incongen_config();
	incongen::Manager::interactive_mode();
}



void incongen::Manager::generate_from_incongen_config(
	const config_file::Incongen& config
)
{
	SimulationInput state;
	state.dimension = network::Dimension(config.nrows, config.ncols);

	if(config.tradius.first == config_file::Incongen::val_tradius::constant)
	{


	}
	else if(config.tradius.first == config_file::Incongen::val_tradius::imbibiton)
	{


	}
	else if(config.tradius.first == config_file::Incongen::val_tradius::function)
	{


	}
	else
	{
		std::cout << "-ERR-incongen::Manager::generate_from_incongen_config() radius type unknown" << std::endl;
	}

	if(config.tmns == config_file::Incongen::val_tmns::imbibition)
	{

	}
	else if(config.tmns == config_file::Incongen::val_tmns::saturate_oil)
	{


	}
	else if(config.tmns == config_file::Incongen::val_tmns::saturate_water)
	{


	}
	else
	{
		std::cout << "-ERR-incongen::Manager::generate_from_incongen_config() mns type unknown" << std::endl;
	}

	if(config.tlength == config_file::Incongen::val_tlength::constant)
	{


	}
	else if(config.tlength == config_file::Incongen::val_tlength::constant




}



void incongen::Manager::interactive_mode()
{
	std::cout << "Under construction" << std::endl;
}



