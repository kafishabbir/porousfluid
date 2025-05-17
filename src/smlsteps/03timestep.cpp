#include "functimestep.h"

double func::TimeStep::decide_time_step(const tdouble_type& radius, const tdouble_type& velocity, const network::Dimension& dimension)
{
	double max_vel = 0;

	for(int row = 0; row < dimension.rows; ++ row)
	{
		for(int col = 0; col < dimension.cols; ++ col)
		{
			const double r = radius[row][col];
			const double len = declconst::TUBE_LENGTH_CONST / (r * r);
			max_vel = std::max(std::abs(velocity[row][col]) / len, max_vel);
		}
	}

	return 1.0 / max_vel / declconst::TIME_DIV;
}
