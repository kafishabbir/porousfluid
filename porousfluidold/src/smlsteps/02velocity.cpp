#include "funcvelocity.h"


tdouble_type func::Velocity::calculate_velocity
(
	const tdouble_type& radius,
	const tmns_type& mns,
	const std::vector<std::vector<int>>& add_mns,
	const std::vector<double>& pressure,
	const network::Dimension& dimension
)
{
	tdouble_type velocity = dimension.empty_table();
	for(int row = 0; row < dimension.rows; ++ row)
	{
		for(int col = 0; col < dimension.cols; ++ col)
		{
			const std::pair<int, int> linear_nodes_pair = dimension.linear_node_at_ends_of_tube(row, col);


			const double delp = pressure[linear_nodes_pair.second] - pressure[linear_nodes_pair.first];
			const double rad = radius[row][col];
			const double tube_length = declconst::TUBE_LENGTH_CONST / (rad * rad);
			const double mu = mns[row][col].mu(declconst::MU1, declconst::MU2);
			const double sign_of_capll_pressure = mns[row][col].sign_of_capll_pressure(0) + add_mns[row][col];
			velocity[row][col] = rad / 8 / mu / tube_length * (delp * rad + sign_of_capll_pressure * 2 * declconst::SIGMA);

			//std::cout << "tr=" << row << " tc=" << col << " up=" << linear_nodes_pair.second
			//<< " dn=" << linear_nodes_pair.first << " dp=" << delp << " r=" << rad
			//<< " sig= " << sign_of_capll_pressure << " v=" << velocity[row][col] << std::endl;
		}

		//std::cout << std::endl;
	}

	return refine_velocity(velocity);
}

tdouble_type func::Velocity::refine_velocity(tdouble_type v)
{
	double max = -1;
	for(const auto& row: v)
	{
		for(auto x: row)
		{
			max = std::max(max, std::abs(x));
		}
	}

	max /= declconst::IGNORE_VEL;
	for(auto& row: v)
	{
		for(auto &x: row)
		{
			if(std::abs(x) < max)
			{
				x = 0;
			}
		}
	}

	return v;
}
