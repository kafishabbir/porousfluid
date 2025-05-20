#include "incongen/tradius.h"

void incongen::TRadius::write_to_file(const std::pair<std::string, double>& cat_and_val)
{
	io::FileWrite::tradius(generate_based_on_cat(p));
}


tdouble_type incongen::TRadius::generate_based_on_cat(const std::pair<std::string, double>& cat_and_val)
{
	const std::string& cat = cat_and_val.first;
	const std::string& val = cat_and_val.second;
	if(cat == dst::decls_incongen_nps::possible_nps::vals_nps::radius_nps::constant)
	{



	}
	if(cat == dst::decls_incongen_nps::possible_nps::vals_nps::radius_nps::function)
	{



	}
	if(cat == dst::decls_incongen_nps::possible_nps::vals_nps::radius_nps::imbibition)
	{


	}

	std::cout << "-ERR- unknown cat, incongen/tradius.cpp" << std::endl;
	return;
}
