#include "funcglobal.h"
//#include <algorithm>

// Configuration of the system at certain moment in time



void PrintSatVSsX(
	std::vector<double> time,
	std::vector<std::vector<double>> sat
	)
{
	std::reverse(time.begin(), time.end());
	std::reverse(sat.begin(), sat.end());

	std::ofstream fout("output_files/sat-vs-x.txt");
	const int time_n = std::min<int>(time.size(), sat.size());
	const int x_n = sat.front().size();

	fout << "x";
	for(int i = 0; i < time_n; ++ i)
	{
		fout << '\t' << "t=" << time[i];
	}

	for(int i = 0; i < x_n; ++ i)
	{
		fout << '\n' << i;
		for(int j = 0; j < time_n; ++ j)
		{
			fout << '\t' << sat[j][i];
		}
	}
}

double CalculateBlue(const tdouble_type& radius, const tmns_type& mns, const network::Dimension& dimension)
{
	double volume_total = 0;
	for(int row = 0; row < dimension.rows; ++ row)
	{
		for(int col = 0; col < dimension.cols; ++ col)
		{
			//const double r = radius[row][col];
			//const double rsq = std::pow(r, 2);
			const dst::Mns& mns = mns[row][col];
			volume_total += mns.sum_type_first();
		}
	}

	//const double pseudo_length = declconst::TUBE_LENGTH_CONST / (rad * rad);

	return declconst::PI * volume_total * declconst::TUBE_LENGTH_CONST;
}

std::vector<double> SaturationsForEachX(const tdouble_type& radius, const tmns_type& mns)
{
	const int y_total = radius.size();
	const int x_total = radius.front().size();

	std::vector<double> s_for_that_x_vec;
	for(int x_i = 0; x_i < x_total; ++ x_i)
	{
		double total = 0;
		double type_first = 0;
		for(int y_i = 0; y_i < y_total; ++ y_i)
		{
			//const double r = radius[y_i][x_i];
			const dst::Mns& mns = mns[y_i][x_i];

			//const double rsq = std::pow(r, 2);
			type_first += mns.sum_type_first();
			total += 1;
		}
		const double sat = type_first / total;
		s_for_that_x_vec.push_back(sat);
	}

	return s_for_that_x_vec;
}

const double CalculateTotalVolumeOfSystem(
		const network::Dimension& dimension)
{
	double total_volume_system = 0;
	for(int row = 0; row < dimension.rows; ++ row)
	{
		for(int col = 0; col < dimension.cols; ++ col)
		{

			const double vol = declconst::PI * declconst::TUBE_LENGTH_CONST;
			total_volume_system += vol;
		}

	}

	return total_volume_system;
}

std::vector<int> SmartPrintSelectMoments(
		const std::vector<ConfigAtMomentTime>& vec
	)
{
	int index_time = 1;

	std::vector<int> index_vec;
	const int total_index = vec.size();
	for(int i = 0; i < total_index; ++ i)
	{
		const double iteration_time = (1000 * index_time);
		const double time = vec[i].clock;
		if(time >= iteration_time)
		{
			index_vec.push_back(i);
			++ index_time;
		}
	}

	return index_vec;
}


void SmartPrintPressureVsTime(
		const std::vector<double>& time,
		const std::vector<double>& pressures,
		const std::string& file_name
	)
{
	std::ofstream fout(file_name);
	fout << "time" << '\t' << "pressure";

	int max_it = time.size();
	for(int i = 0; i < max_it; ++ i)
	{
		fout << '\n' << time[i] << '\t' << pressures[i];
	}
}

void SmartPrintSmoothPressureVsTime(
		const std::vector<double>& time,
		const std::vector<double>& pressures
	)
{
	SmartPrintPressureVsTime(
			time,
			pressures,
			"output_files/p_vs_t_smooth.txt"
		);
}

void SmartPrintRoughPressureVsTime(
		const std::vector<double>& time,
		const std::vector<double>& pressures
	)
{
	SmartPrintPressureVsTime(
			time,
			pressures,
			"output_files/p_vs_t_rough.txt"
		);
}


void func::Global::SmartPrint(
		const std::vector<ConfigAtMomentTime>& vec,
		const tdouble_type& radius
	)
{
	//std::cout << "work here" << std::endl;

	const std::vector<int> index_vec = SmartPrintSelectMoments(
			vec
		);

	std::vector<ConfigAtMomentTime> selected_vec;
	for(const int x: index_vec)
	{
		selected_vec.push_back(vec[x]);
	}


	//std::vector<ConfigAtMomentTime> selected_vec = vec;

	int plot_count = 1000;
	std::vector<double> time;
	std::vector<std::vector<double>> saturations;
	std::vector<double> pressures;
	for(const ConfigAtMomentTime& config: selected_vec)
	{
		time.push_back(config.clock);
		saturations.push_back(SaturationsForEachX(radius, config.mns));
		pressures.push_back(config.pressure_input);
		//std::cout << "work here" << std::endl;
		func::Global::makeplot(radius, config.mns, plot_count++, config.clock);
	}

	PrintSatVSsX(time, saturations);
	SmartPrintRoughPressureVsTime(time, pressures);

	/*
	std::ofstream fout("output_files/debug.txt");
	fout << "time" << '\t' << "pressure" << '\t' << "volume_injected" << '\t' << "flow_rate" << '\t' << "volume_blue";

	for(const ConfigAtMomentTime& config: vec)
	{
		fout	<< '\n' << config.clock
				<< '\t' << config.pressure_input
				<< '\t' << config.volume_injected
				<< '\t' << config.flow_rate_at_this_step
				<< '\t' << config.volume_blue_in_system;
	}
	*/
}

void ShowProgress(const double progress, int& last_count)
{
	double proportion = last_count;
	proportion /= 10;
	if(progress >= proportion)
	{
		std::cout << "simulation-progress=" << progress * 100 << "%" << std::endl;
		++ last_count;
	}
}


void func::Global::simulate(const tdouble_type& radius, tmns_type& mns, const network::Dimension& dimension)
{

	int count = 10000;
	int plot_count = 1000;
	//const int steps = 1600; // 1600


	//std::vector<std::vector<double>> fluid_ppr_vec;

	//func::Global::makeplot(radius, mns, count, clock);
	//cmdio::Print::pmat("radius", radius);

	/*
	double wetting_fluid_proportion;
	while(within_limits_fluid_first_type(radius, mns, wetting_fluid_proportion))
	*/

	const double total_volume_of_system = CalculateTotalVolumeOfSystem(
			dimension
		);
	std::cout << "total-vol=" << total_volume_of_system << std::endl;

	const double total_flow_rate = 1000; // volume / time
	// a vector of configuration of the system at certain moments in time
	std::vector<ConfigAtMomentTime> config_at_moment_time_vec;

	double clock = 0;

	//for(int step = 0; step < steps; ++ step)
	//{
		/*
		const func::Measure::FluidPpr fluid_ppr
			= func::Measure::fluid_ppr(
				radius,
				mns,
				clock,
				declconst::ROW_THIN_B,
				declconst::COL_THIN_B,
				declconst::ROW_THIN_E,
				declconst::COL_THIN_E,
				dimension
			);
		*/

	//int plot_count = 1000;
	int last_count = 0;
	double total_volume_injected = 0;
	const double proportion_of_injection = 1.1;
	while(total_volume_injected <=  proportion_of_injection * total_volume_of_system)
	{
		ShowProgress(total_volume_injected/(proportion_of_injection * total_volume_of_system), last_count);
		//std::cout << std::endl << std::endl << std::string(50, '-') << std::endl;
		//std::cout << "clock=" << clock << " vol_inj=" << total_volume_injected << std::endl;

		// step-0 Generate add_msn table

		const std::vector<std::vector<int>> add_msn
			= func::Determine::gen_add_mns(mns, dimension);

		// step-1 PRESSURE
		const std::vector<double> pressure
			= func::Pressure::calculate_pressure(
				radius, mns, add_msn, dimension, total_flow_rate);

		//cmdio::Print::pmat("pressure", pressure, radius.size(), radius.front().size());

		// step-2 VELOCITY
		const tdouble_type velocity
			= func::Velocity::calculate_velocity(
				radius, mns, add_msn, pressure, dimension);

		//cmdio::Print::pmat("velocity", velocity);

		// step-3 TIME STEP
		const double time_step
			= func::TimeStep::decide_time_step(radius,
				velocity, dimension);

		// step-4 VOLUME
		const auto volume
			= func::Determine::determine_volume(radius,
				velocity, time_step, dimension);

		//cmdio::Print::pmat("volume", volume);

		// step-5 INTEGRATION

		// old one used to model imbibition
		//mns = func::Integration::integrate(radius,
		//	mns, velocity, volume, dimension, time_step);

		const auto integration_result = func::Integration::integrate(
			radius,	mns, velocity, volume, dimension, time_step);


		mns = integration_result.new_mns;
		clock += time_step;
		const auto fluid_injected = integration_result.fluid_injected;
		const auto fluid_expelled = integration_result.fluid_expelled;

		/*
		std::cout << "time_ste=" << time_step << '\n';
		std::cout << "injection-table:" << '\n';
		for(size_t i = 1; i < fluid_injected.size(); i += 2)
		{
			std::cout << fluid_injected[i - 1] << ' ' << fluid_injected[i] << '\n';
		}
		std::cout << std::endl;

		std::cout << "expulsion-table:" << '\n';
		for(size_t i = 1; i < fluid_expelled.size(); i += 2)
		{
			std::cout << fluid_expelled[i - 1] << ' ' << fluid_expelled[i] << '\n';
		}
		std::cout << std::endl;
		*/

		/*
		std::cout << "[count-frame=" << count << "], [clock="
			<< clock << "], [ppr=" << wetting_fluid_proportion
			<< "]" << std::endl;
		*/


		double volume_injected_at_this_step = 0;
		for(size_t i = 1; i < fluid_injected.size(); i += 2)
		{
			volume_injected_at_this_step += fluid_injected[i - 1];
		}

		total_volume_injected += volume_injected_at_this_step;
		ConfigAtMomentTime config_at_moment_time;
		config_at_moment_time.clock = clock;
		config_at_moment_time.mns = mns;
		config_at_moment_time.pressure_input = pressure.back();


		config_at_moment_time.volume_injected = total_volume_injected;
		config_at_moment_time.flow_rate_at_this_step = volume_injected_at_this_step / time_step;
		config_at_moment_time.volume_blue_in_system = CalculateBlue(radius, mns, dimension);

		//std::cout << "clock=" << config_at_moment_time.clock << std::endl;
		//std::cout << "input_pressure=" << config_at_moment_time.pressure_input << std::endl;
		//std::cout << "vol_injected=" << config_at_moment_time.volume_injected << std::endl;
		//std::cout << "flow_rate_now=" << config_at_moment_time.flow_rate_at_this_step << std::endl;
		//std::cout << "total_blue=" << config_at_moment_time.volume_blue_in_system << std::endl;

		config_at_moment_time_vec.push_back(config_at_moment_time);

		if((count++) % declconst::PLOT_EACH_N)
		{
			continue;
		}


		//cmdio::Print::pmns(mns);
		func::Global::makeplot(radius, mns, plot_count++, clock);
		//fluid_ppr_vec.push_back(fluid_ppr.val_vec());
		//fileio::Write::fluid_ppr(func::Measure::FluidPpr::header(), fluid_ppr_vec);
	}
	//std::cout << "while exit" << std::endl;
	SmartPrint(config_at_moment_time_vec, radius);

	//PrintInjectionVsTime(fil_time, fil_total_fluid_injected);


	//fileio::Write::fluid_ppr(func::Measure::FluidPpr::header(), fluid_ppr_vec);
}

void func::Global::makeplot(const tdouble_type& radius, const tmns_type& mns, const int count, const double clock)
{
	fileio::Plot::with_radius(mns, radius, clock, count);
	fileio::Plot::without_radius(mns, count);
}

bool func::Global::within_limits_fluid_first_type(const tdouble_type& radius, const tmns_type& mns, double& proportion)
{
	proportion = func::Measure::measure_wetting_fluid_proportion(radius, mns);
	return proportion <= declconst::MAX_WETTING_PROPORTION;
}





