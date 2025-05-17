#ifndef FUNCINTEGRATION_H
#define FUNCINTEGRATION_H

#include "head/decl.h"
#include "dstdimension.h"
#include <algorithm>

namespace func
{
	class Integration
	{
		struct Fluid
		{
			double blue = 0;
			double grey = 0;
		};

		typedef std::vector<std::vector<Fluid>> TFluid;

		struct Tube_FromNode
		{
			double rad;
			int row;
			int col;
		};

		class Tank
		{
			Fluid fluid;
			bool blue_present = false;
			bool grey_present = false;

		public:
			void add_fluid(const std::vector<double>& add);
			Fluid pour_out_fluid(const double vol);
			double show_blue() const;
			double show_grey() const;
			std::string yes_blue() const;
			std::string yes_grey() const;

		};

		struct CalculateFluidTableResult
		{
			TFluid fluid_table;
			std::vector<double> injection;
			std::vector<double> expulsion;
		};

		static CalculateFluidTableResult calculate_fluid_table(
			const tdouble_type& radius,
			const tmns_type& mns,
			const tdouble_type& velocity,
			const tdouble_type& volume,
			const network::Dimension& dimension,
			const double time_step
			);

		static bool compare_where_wetting_fluid_go_first(
			const Tube_FromNode& first,
			const Tube_FromNode& second
			);

		static tmns_type combine_fluid_additions(
			const tdouble_type& radius,
			tmns_type mns,
			const tdouble_type& velocity,
			const network::Dimension& dimension,
			const TFluid& fluid_addition_table
			);


	public:
		struct IntegrationResult
		{
			tmns_type new_mns;
			std::vector<double> fluid_injected;
			std::vector<double> fluid_expelled;
		};

		static IntegrationResult integrate(
			const tdouble_type& radius,
			const tmns_type& mns,
			const tdouble_type& velocity,
			const tdouble_type& volume,
			const network::Dimension& dimension,
			const double time_step
			);

	};
}



#endif
