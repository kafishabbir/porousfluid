#ifndef FUNCPRESSURE_H
#define FUNCPRESSURE_H

#include "head/decl.h"
#include "declconst.h"
#include "dstdimension.h"
#include "cmdioprint.h"
#include "mathlinear.h"
#include <vector>

namespace func
{
	class Pressure
	{
		static tdouble_type generate_equations_aug_matrix(
				const tdouble_type& radius,
				const tmns_type& mns,
				const std::vector<std::vector<int>>& add_mns,
				const network::Dimension& dimension,
				const double total_flow_rate
			);

		static int calc_sign_capll_pressure(
			const int internal,
			const int add_table,
			const int direction
		);

	public:
		static std::vector<double> calculate_pressure(
			const tdouble_type& radius,
			const tmns_type& mns,
			const std::vector<std::vector<int>>& add_mns,
			const network::Dimension& dimension,
			const double total_flow_rate
		);
	};
}

#endif
