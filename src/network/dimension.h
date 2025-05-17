#ifndef NETWORK_DIMENSION_H
#define NETWORK_DIMENSION_H

#include <iostream>

namespace network
{

	// x, y, lenght, raidus,
	struct Tube
	{
		bool active = true;
		int row;
		int col;
		int linear_node;
	};

	class Dimension
	{
	public:
		int rows;
		int cols;

		Dimension();
		Dimension(const int rows, const int cols);

		template<class T>
		Dimension(const std::vector<std::vector<T>>& table);

		int node_rows() const;
		int node_cols(const int row) const;

		int total_nodes() const;

		int linear_node_from_coordinate(const int row, const int col) const;

		std::pair<int, int> linear_node_at_ends_of_tube(
			const int row,
			const int col) const;

		std::vector<network::Tube> generate_tubes_connected_to_node(int row, int col) const;

		template<class T>
		std::vector<std::vector<T>> empty_table_templated() const;

		std::vector<std::vector<double>> empty_table() const;
		std::vector<std::vector<double>> empty_table(const int rows, const int cols) const;
		std::vector<std::vector<double>> empty_aug_matrix() const;

		bool operator== (const Dimension& other) const;

		bool is_this_an_open_node(const int row, const int col) const;
		bool is_this_any_open_node(const int row, const int col) const;
		bool is_this_an_injector_plate_node(const int row, const int col) const;
	};
}

template<class T>
network::Dimension(const std::vector<std::vector<T>>& table):
	rows(table.size()), cols(table.front().size()) {}

template<class T>
std::vector<std::vector<T>> network::Dimension::empty_table_templated() const
{
	return std::vector<std::vector<T>>(this->rows, std::vector<T>(this->cols));
}

std::ostream& operator<< (std::ostream& cout, const network::Tube& tube);
#endif
