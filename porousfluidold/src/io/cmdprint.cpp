#include "cmdioprint.h"

void cmdio::Print::pmat(const std::string& s, const tdouble_type& matrix)
{
	const int n = matrix.size();
	const int m = matrix.front().size();

	std::cout << std::endl << s << std::string(100, '-') << std::endl;

	std::cout << std::setw(7) << -1 << " | ";
	for(int j = 0; j < m; ++ j)
	{
		std::cout << std::setw(7) << (double)j << ' ';
	}
	std::cout << '\n';
	for(int i = 0; i < n; ++ i)
	{
		std::cout << std::setw(7) << (double)i << " | ";
		for(int j = 0; j < m; ++ j)
		{
			std::cout << std::setw(7) << matrix[i][j] << ' ';
		}
		std::cout << '\n';
	}

	std::cout << std::endl;
}


void cmdio::Print::pmat(const std::string& s, const std::vector<double>& v, const int n, const int m)
{
	std::cout << std::endl << s << std::string(100, '-') << std::endl;

	int count = 0;
	for(int i = 0; i <= n; ++ i)
	{
		int mt = m / 2 - i % 2;
		if(i%2)
		{
			std::cout << "        ";
		}
		for(int j = 0; j <= mt; ++ j)
		{
			std::cout << std::setw(12) << v[count++] << ' ';
		}
		std::cout << '\n';
	}
	std::cout << "THE END";
	std::cout << std::endl;
}


void cmdio::Print::pmat(const std::string& s, const tmns_type& matrix)
{
	std::cout << std::endl << s << std::string(100, '-') << std::endl;

	const int n = matrix.size();
	const int m = matrix.front().size();

	std::cout << std::setw(7) << -1 << " | ";
	for(int j = 0; j < m; ++ j)
	{
		std::cout << std::setw(7) << (double)j << ' ';
	}
	std::cout << '\n';
	for(int i = 0; i < n; ++ i)
	{
		std::cout << std::setw(7) << (double)i << " | ";
		for(int j = 0; j < m; ++ j)
		{
			std::cout << std::setw(7) << matrix[i][j].printable() << ' ';
		}
		std::cout << '\n';
	}

	std::cout << std::endl;
}


void cmdio::Print::pmns(const tmns_type& matrix)
{
	std::cout << std::endl << "mns LONG" << std::string(100, '-') << std::endl;

	for(size_t i = 0; i < matrix.size(); ++ i)
	{
		for(size_t j = 0; j < matrix[i].size(); ++ j)
		{
			const auto& a = matrix[i][j];
			std::cout << "(" << i << ", " << j << "): " << a.n << " " << a.type << " {" << a.pos.front() << ", " << a.pos.back() << "}" << std::endl;
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
}


void cmdio::Print::dimension()
{
	const std::map<std::string, network::Dimension> lst_dimension =
		fileio::Read::dimension();

	for(const auto& [file_name, d]: lst_dimension)
	{
		std::cout << "-IFR-dimension " << file_name << " (r, c) = (" << d.rows << ", " << d.cols << ")" << std::endl;
	}
}
