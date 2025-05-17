#include "network/dimension.h"


network::Dimension::Dimension(const int rows, const int cols):
	rows(rows), cols(cols) {}


network::Dimension::Dimension(): rows(0), cols(0) {}


std::pair<int, int> network::Dimension::linear_node_at_ends_of_tube(const int row, const int col) const
{
	const int first_linear_node = this->linear_node_from_coordinate(row, col / 2 + (col % 2) * ((row + 1) % 2));
	const int second_linear_node = this->linear_node_from_coordinate(row + 1, col / 2 + (col % 2) * (row % 2));
	return {first_linear_node, second_linear_node};
}

int network::Dimension::node_rows() const
{
	return this->rows + 1;
}

int network::Dimension::node_cols(const int row) const
{
	return this->cols / 2 - (row % 2) + 1;
}

int network::Dimension::total_nodes() const
{
	// 1 + added to make constant injection rate
	return 1 + ((this->rows + 1) * (this->cols + 1) + 1) / 2;
}

int network::Dimension::linear_node_from_coordinate(const int row, const int col) const
{
	return (row * (this->cols + 1) + (row % 2)) / 2 + col;
}


bool network::Dimension::operator== (const Dimension& other) const
{
	return (this->rows == other.rows) && (this->cols == other.cols);
}


std::vector<network::Tube> network::Dimension::generate_tubes_connected_to_node(int row, int col) const
{
	const auto linear_node = this->linear_node_from_coordinate(row, col);

	std::vector<network::Tube> tubes_connected_vec(4);

	tubes_connected_vec[0].row = row - 1;
	tubes_connected_vec[0].col = 2 * col - 1 + row % 2;
	tubes_connected_vec[0].linear_node = linear_node - cols / 2 - 1;

	tubes_connected_vec[1].row = row - 1;
	tubes_connected_vec[1].col = 2 * col + row % 2;
	tubes_connected_vec[1].linear_node = linear_node - cols / 2 ;

	tubes_connected_vec[2].row = row;
	tubes_connected_vec[2].col = 2 * col + row % 2;
	tubes_connected_vec[2].linear_node = linear_node + cols / 2 + 1;

	tubes_connected_vec[3].row = row;
	tubes_connected_vec[3].col = 2 * col - 1 + row % 2;
	tubes_connected_vec[3].linear_node = linear_node + cols / 2;


	if(row % 2)
	{
		return tubes_connected_vec;
	}

	if(row == 0)
	{
		tubes_connected_vec[0].active = false;
		tubes_connected_vec[1].active = false;
	}
	if(col == 0)
	{
		tubes_connected_vec[0].active = false;
		tubes_connected_vec[3].active = false;
	}
	if(2 * col == this->cols)
	{
		tubes_connected_vec[1].active = false;
		tubes_connected_vec[2].active = false;
	}
	if(row == this->rows)
	{
		tubes_connected_vec[2].active = false;
		tubes_connected_vec[3].active = false;
	}

	return tubes_connected_vec;
}

std::vector<std::vector<double>> network::Dimension::empty_table() const
{
	return empty_table(this->rows, this->cols);
}

std::vector<std::vector<double>> network::Dimension::empty_table(const int rows, const int cols) const
{
	return tdouble_type(rows, std::vector<double>(cols));
}

std::vector<std::vector<double>> network::Dimension::empty_aug_matrix() const
{
	const int total_num_nodes = this->total_nodes();
	return empty_table(total_num_nodes, total_num_nodes + 1);
}

std::ostream& operator<< (std::ostream& cout, const network::Tube& tube)
{
	cout << "Tube a=" << tube.active << ", (r=" << tube.row << ", c=" << tube.col << "), ln=" << tube.linear_node;
	return cout;
}


bool network::Dimension::is_this_an_open_node(const int row, const int col) const
{
	if(row % 2)
	{
		return false;
	}

	//row must be even
	/*
	if(col == 0)
	{
		return true;
	}
	*/
	if(col == (this->node_cols(row) - 1))
	{
		return true;
	}

	return false;

}

bool network::Dimension::is_this_any_open_node(const int row, const int col) const
{
	return is_this_an_open_node(row, col) || is_this_an_injector_plate_node(row, col);
}


bool network::Dimension::is_this_an_injector_plate_node(const int row, const int col) const
{
	if(row % 2)
	{
		return false;
	}

	if(col == 0)
	{
		return true;
	}

	return false;
}


