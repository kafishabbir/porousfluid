#include "algo/determine.h"

tdouble_type func::Determine::determine_volume
(
	const tdouble_type& radius,
	const tdouble_type& velocity,
	const double time_step,
	const network::Dimension& dimension
)
{
	tdouble_type volume = dimension.empty_table();

	for(int row = 0; row < dimension.rows; ++ row)
	{
		for(int col = 0; col < dimension.cols; ++ col)
		{
			const double vel_abs = std::abs(velocity[row][col]);
			const double area_tube = std::pow(radius[row][col], 2) * declconst::PI;
			volume[row][col] = vel_abs * area_tube * time_step;
		}
	}

	return volume;
}

std::vector<std::vector<int>> func::Determine::gen_add_mns(const tmns_type& mns, const network::Dimension& dimension)
{
	std::vector<std::vector<int>> add_mns = dimension.empty_table_templated<int>();

	for(int nrow = 0; nrow < dimension.node_rows(); ++ nrow)
	{
		for(int ncol = 0; ncol < dimension.node_cols(nrow); ++ ncol)
		{
			const std::vector<dst::Tube> cons
				= dimension.generate_tubes_connected_to_node(nrow, ncol);

			const int directions = cons.size();

			std::vector<bool> need_to_add(directions, false);

			bool blue_fluid_present = false;

			for(int direction = 0; direction < directions; ++ direction)
			{
				const dst::Tube& con = cons[direction];
				if(con.active)
				{
					const int end_type_fluid = mns[con.row][con.col].type_near_node(direction);
					if(end_type_fluid) // grey fluid
					{
						need_to_add[direction] = true;
					}
					else
					{
						blue_fluid_present = true;
					}
				}
			}

			if(blue_fluid_present == false)
			{
				continue;
			}

			for(int direction = 0; direction < directions; ++ direction)
			{
				const dst::Tube& con = cons[direction];
				if(con.active && need_to_add[direction])
				{
					add_mns[con.row][con.col] += cap_press_contb_from_direc(direction);
				}
			}

		}
	}

	return add_mns;
}


int func::Determine::cap_press_contb_from_direc(const int direction)
{
	if(direction > 1)
	{
		return -1;
	}

	return 1;
}
