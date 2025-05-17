#include "io/fileread.h"

void fileio::FileWrite::tradius(const tdouble_type& tradius)
{
	write_base(decl::file::input::RADIUS, tradius);
}

void fileio::FileWrite::tlength(const tdouble_type& tlength)
{
	write_base(decl::file::input::LENGTH, tlength);
}

void fileio::FileWrite::tmns_type(const tmns_type& tmns_type)
{
	write_base(decl::file::input::MNS, tmns_type); 
}

void fileio::FileWrite::sample_incongen_txt()
{
	std::ofstream fout(decl::file::input::INCONGEN);

	for(const dst::catAndvals& cat_and_vals:
		dst::txt_incongen_cat_and_vals_vec)
	{
		const std::string& cat
			= cat_and_vals.cat;
		const std::vector<std::string>& vals
			= cat_and_vals.vals;

		fout << cat << "=";
		for(int i = 0; i < int(vals.size()); ++ i)
		{
			if(i) fout << "/";
			fout << vals[i];
		}

		fout << '\n';
	}

}

void fileio::FileWrite::fluid_ppr(
	const std::vector<std::string>& header,
	const std::vector<std::vector<double>>& table
)
{
	std::ofstream fout(declfilename::FILE_FLUID_PPR);

	for(const std::string& head: header)
	{
		fout << head << '\t';
	}
	fout << '\n';

	for(const auto& row: table)
	{
		for(const auto x: row)
		{
			fout << x << '\t';
		}
		fout << '\n';
	}
}
