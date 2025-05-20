#ifndef FUNCDETERMINE_H
#define FUNCDETERMINE_H

#include "head/decl.h"
#include "dstdimension.h"

namespace func
{
	class Determine
	{
		static int cap_press_contb_from_direc(const int direction);

	public:

		static tdouble_type determine_volume(const tdouble_type& radius, const tdouble_type& velocity, const double time_step, const network::Dimension& dimension);

		static std::vector<std::vector<int>> gen_add_mns(
			const tmns_type& mns,
			const network::Dimension& dimension
		);
	};
}

#endif
