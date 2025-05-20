#ifndef FILEIOWRITE_H
#define FILEIOWRITE_H

#include "head/decl.h"
#include "head/type.h"
#include "dst/txtincongen"
//~ #include <string>
//~ #include <vector>
//~ #include <fstream>

namespace io
{
	class FileWrite
	{
		template <class T>
		static void write_base(
			const std::string& file_name,
			const std::vector<std::vector<T>>& table);

	public:
		static void radius(const tdouble_type& tradius);
		static void length(const tmns_type& tlength);
		static void mns(const tmns_type& tmns);
		static void parameter();
		static void sample_txt_incongen();
		static void fluid_ppr(
			const std::vector<std::string>& header,
			const std::vector<std::vector<double>>& table);
	};
}

template <class T>
void io::FileWrite::write_base(const std::string& file_name,
	const std::vector<std::vector<T>>& table)
{
	std::ofstream fout(file_name);
	fout << table.size() << ' ' << table.front().size() << '\n';

	for(const auto& row: table)
	{
		for(const auto& cell: row)
		{
			fout << cell << ' ';
		}
		fout << '\n';
	}
}
#endif
