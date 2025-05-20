#include "config_file/incongen.h"

bool config_file::Incongen::valid() const
{
	const bool validity =
		nrows_set &&
		ncols_set &&
		tradius_set &&
		tlength_set &&
		tmns_set;

	return validity;
}

bool config_file::Incongen::set(const std::string& buffer_line)
{
	const std::pair<std::string, std::string>& buffer =
		algo::Utility::split(buffer_line);

	const std::string& category = buffer.first;
	const std::string& value = buffer.second;

	if(category == "nrows")
	{
		return set_nrows(value);
	}
	if(category == "ncols")
	{
		return set_ncols(value);
	}
	if(category == "tradius")
	{
		return set_tradius(value);
	}
	if(category == "tlength")
	{
		return set_tlength(value);
	}
	if(category == "tmns")
	{
		return set_tmns(value);
	}

	std::cout << "-Err- in incongen-config.txt, category not recognized";
	return false;
}

bool config_file::Incongen::set_nrows(const std::string& value)
{
	nrows = std::stoi(value);
	nrows_set = true;

	return true;
}

bool config_file::Incongen::set_ncols(const std::string& value)
{
	ncols = std::stoi(value);
	ncols_set = true;

	return true;

}

std::pair<double, bool> config_file::Incongen::const_extraction(
	const std::string& s
)
{
	const std::string c = "constant";
	if(s.size() < c.size())
	{
		return {-1, false};
	}

	if(s.substr(0, c.size()) != c)
	{
		return {-1, false};
	}

	const double value_double = std::stod(algo::Utility::split(s).second);

	return {value_double, true};
}

bool config_file::Incongen::set_tradius(const std::string& value)
{
	const std::pair<double, bool> try_const =
		const_extraction(value);

	if(try_const.second)
	{
		tradius.first = val_tradius::constant;
		tradius.second = try_const.first;
		tradius_set = true;
		return true;
	}

	if(value == "imbibition")
	{
		tradius.first = val_tradius::imbibiton;
		tradius_set = true;
		return true;
	}

	if(value == "function")
	{
		tradius.first =  val_tradius::function;
		tradius_set = true;
		return true;
	}

	std::cout << "-Err- config_file::set_tradius(), value not recognized." << std::endl;
	return false;
}

bool config_file::Incongen::set_tlength(const std::string& value)
{
	const std::pair<double, bool> try_const =
		const_extraction(value);

	if(try_const.second)
	{
		tlength.first = val_tlength::constant;
		tlength.second = try_const.first;
		tlength_set = true;
		return true;
	}

	if(value == "inverse_radius")
	{
		tlength.first =  val_tlength::inverse_radius;
		tlength_set = true;
		return true;
	}

	std::cout << "-Err- config_file::set_tlength(), value not recognized." << std::endl;
	return false;
}

bool config_file::Incongen::set_tmns(const std::string& value)
{
	if(value == "saturate_oil")
	{
		tmns =  val_tmns::saturate_oil;
		tmns_set = true;
		return true;
	}

	if(value == "saturate_water")
	{
		tmns =  val_tmns::saturate_water;
		tmns_set = true;
		return true;
	}

	if(value == "imbibition")
	{
		tmns =  val_tmns::imbibition;
		tmns_set = true;
		return true;
	}

	std::cout << "-Err- config_file::set_tmns(), value not recognized." << std::endl;
	return false;
}
