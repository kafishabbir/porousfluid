#ifndef CMDIOPRINT_H
#define CMDIOPRINT_H

#include "head/decl.h"
#include "fileioread.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <map>

namespace cmdio
{
	class Print
	{

	public:
		// print matrix := pmat
		static void pmat(const std::string& s, const tdouble_type& matrix);
		static void pmat(const std::string& s, const tmns_type& mns); // compressed to a double
		static void pmat(const std::string& s,
			const std::vector<double>& v, const int n, const int m); //linear pressure vector printed as a matrix

		static void pmns(const tmns_type& matrix); // matric vals are printed in a new line
		static void dimension(); // read and print the dimension of each file

		template<class T>
		static void table(const std::vector<std::vector<T>>& v);
	};
}


template<class T>
void cmdio::Print::table(const std::vector<std::vector<T>>& v)
{
	const int width = 6;
	for(const auto& row: v)
	{
		for(const auto& cell: row)
		{
			std::cout << std::setw(width) << cell << ' ';
		}
		std::cout << std::endl;
	}
}

#endif


