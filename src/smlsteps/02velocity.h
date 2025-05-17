#ifndef FUNCVELOCITY_H
#define FUNCVELOCITY_H

#include "head/decl.h"
#include "dstdimension.h"

namespace func
{
	class Velocity
	{

	public:
		static tdouble_type calculate_velocity(
			const tdouble_type& radius,
			const tmns_type& mns,
			const std::vector<std::vector<int>>& add_mns,
			const std::vector<double>& pressure,
			const network::Dimension& dimension
		);

		static tdouble_type refine_velocity(tdouble_type v);
	};
}

#endif
