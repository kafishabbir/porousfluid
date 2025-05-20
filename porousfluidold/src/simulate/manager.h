#ifndef FUNCGLOBAL_H
#define FUNCGLOBAL_H

#include "cmdioprint.h"
#include "fileioplot.h"
#include "fileiowrite.h"
#include "dstdimension.h"

#include "funcdetermine.h"
#include "funcintegration.h"
#include "funcmeasure.h"
#include "funcpressure.h"
#include "functimestep.h"
#include "funcvelocity.h"

#include "head/decl.h"
#include "declconst.h"

struct ConfigAtMomentTime
{
	double clock;
	tmns_type mns;
	double pressure_input;
	double volume_injected;
	double flow_rate_at_this_step;
	double volume_blue_in_system;
};

namespace func
{
	class Global
	{
		static void makeplot
		(
			const tdouble_type& radius,
			const tmns_type& mns,
			const int count,
			const double clock
		);

		static bool within_limits_fluid_first_type
		(
			const tdouble_type& radius,
			const tmns_type& mns,
			double& proportion
		);

		static void SmartPrint(
				const std::vector<ConfigAtMomentTime>& vec,
				const tdouble_type& radius
		);
	public:
		static void simulate(const tdouble_type& radius,
			tmns_type& mns, const network::Dimension& dimension);
	};
}

#endif
