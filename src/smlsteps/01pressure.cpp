#include "funcpressure.h"

tdouble_type func::Pressure::generate_equations_aug_matrix(
	const tdouble_type& radius,
	const tmns_type& mns,
	const std::vector<std::vector<int>>& add_mns,
	const network::Dimension& dimension,
	const double total_flow_rate
)
{
	tdouble_type equations_matrix = dimension.empty_aug_matrix();
	const int linear_node_input_pressure = dimension.total_nodes() - 1;
	for(int row = 0; row < dimension.node_rows(); ++ row)
	{
		for(int col = 0; col < dimension.node_cols(row); ++ col)
		{
			const int linear_node = dimension.linear_node_from_coordinate(row, col);
			std::vector<double>& equation = equations_matrix[linear_node];

			if(dimension.is_this_an_open_node(row, col))
			{
				equation[linear_node] = 1;
				equation.back() = declconst::PRESSURE_RIGHT;
				continue;
			}
			if(dimension.is_this_an_injector_plate_node(row, col))
			{
				equation[linear_node] = 1;
				equation[linear_node_input_pressure] = -1;
				continue;
			}
			const std::vector<dst::Tube> tubes_connected_vec =
				dimension.generate_tubes_connected_to_node(row, col);

			const int total_directions = tubes_connected_vec.size();
			for(int direction = 0; direction < total_directions; ++ direction)
			{
				const dst::Tube& connection = tubes_connected_vec[direction];
				if(connection.active)
				{
					const double r = radius[connection.row][connection.col];
					const dst::Mns& mns = mns[connection.row][connection.col];
					const double tube_length = declconst::TUBE_LENGTH_CONST / (r * r);

					const int sign_of_capll_pressure
						= calc_sign_capll_pressure(
							mns.sign_of_capll_pressure(direction),
							add_mns[connection.row][connection.col],
							direction
						);


					const double K = std::pow(r, 3) / mns.mu(declconst::MU1, declconst::MU2) / tube_length;

					equation[linear_node] += r * K;
					equation[connection.linear_node] -= r * K;
					equation.back() -= declconst::SIGMA * 2 * sign_of_capll_pressure  * K;

				}
			}
		}
	}


	//std::cout << "node_rows=" << dimension.node_rows() << std::endl;
	for(int row = 0; row < dimension.node_rows(); row += 2)
	{
		const int col = 0;
		std::vector<double>& equation = equations_matrix.back();

		const std::vector<dst::Tube> tubes_connected_vec =
			dimension.generate_tubes_connected_to_node(row, col);

		const int total_directions = tubes_connected_vec.size();
		for(int direction = 0; direction < total_directions; ++ direction)
		{
			const dst::Tube& connection = tubes_connected_vec[direction];
			//std::cout << "row:" << row << " col:" << col << " direction: " << direction << " active=";
			if(connection.active)
			{
				const double r = radius[connection.row][connection.col];
				const dst::Mns& mns = mns[connection.row][connection.col];
				const double tube_length = declconst::TUBE_LENGTH_CONST / (r * r);

				const double A = declconst::PI * std::pow(r, 4)
					/ (
						8.0
						* mns.mu(declconst::MU1, declconst::MU2)
						* tube_length
					);

				const int sign_of_capll_pressure
						= calc_sign_capll_pressure(
							mns.sign_of_capll_pressure(direction),
							add_mns[connection.row][connection.col],
							direction
						);

				//std::cout << "true" << " A=" << A;
				equation[linear_node_input_pressure] += A;
				equation[connection.linear_node] -= A;
				const double B = A * declconst::SIGMA * 2 * sign_of_capll_pressure / r;
				equation.back() -= B;
			}
			//std::cout << std::endl;
			//cmdio::Print::pmat("set-of-linear-equations-before", equations_matrix);
			//std::cout << std::endl << "x-x--x-x-x-x-x-x-x-x--x-x-x-x-x-x" << std::endl;
		}
	}
	equations_matrix.back().back() += total_flow_rate;

	//std::cout << "can-readh-here-240425" << std::endl;

	// The special adder is activated for an open system.
	/*
	const double adder = 1;
	const int special_row = dimension.rows / 2;
	const int special_col = dimension.cols / 4;
	const int special_linear = dimension.linear_node_from_coordinate(
		special_row, special_col);

	for(int row = 0; row < dimension.total_nodes(); ++ row)
	{
		equations_matrix[row][special_linear] += adder;
	}
	*/

	return equations_matrix;
}

std::vector<double> func::Pressure::calculate_pressure(
	const tdouble_type& radius,
	const tmns_type& mns,
	const std::vector<std::vector<int>>& add_mns,
	const network::Dimension& dimension,
	const double total_flow_rate
)
{
	const tdouble_type equations
		= func::Pressure::generate_equations_aug_matrix(
				radius,
				mns,
				add_mns,
				dimension,
				total_flow_rate
			);

	//cmdio::Print::pmat("set-of-linear-equations", equations);

	const std::vector<double> solution_of_equation = math::Linear::gauss_elimination(equations);
	return solution_of_equation;
}

int func::Pressure::calc_sign_capll_pressure(
	const int internal,
	const int add_table,
	const int direction
)
{
	int add = add_table;
	if(direction > 1)
	{
		add *= -1;
	}
	return internal + add;
}
