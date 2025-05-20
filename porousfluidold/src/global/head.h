#ifndef GLOBAL_HEAD_H
#define GLOBAL_HEAD_H

#include <cmath>
#include <limits>
#include <string>
// Handbook of physical constants:
// sigma = 7.56e-2 water at 20C in SI units
// mu_water = 1e-3 viscosity in SI units



namespace global
{
	namespace file
	{
		namespace input
		{
			const std::string FOLDER = "run/input/";
			const std::string RADIUS = FOLDER + "tradius.txt";
			const std::string LENGTH = FOLDER + "tlength.txt";
			const std::string MNS = FOLDER + "tmns.txt";
			const std::string SIMULATION_CONFIG = FOLDER + "simulation_config.txt";
			const std::string INCONGEN_CONFIG = FOLDER + "incongen_config.txt";
		}

		namespace output
		{
			const std::string FOLDER = "run/output/";
			const std::string CALCULATIONS = FOLDER + "calculations/";
			const std::string DATA_RAW = FOLDER + "data-raw/";

			const std::string GRAPH = FOLDER + "graph/";

			const std::string INITIAL_CONDITIONS = FOLDER + "initial-conditions/";
			const std::string PRESSURE = FOLDER + "pressure/";
			const std::string VELOCITY = FOLDER + "velocity/";

			const std::string VISUALIZATION_THICK = FOLDER + "visualization-thick/";
			const std::string VISUALIZATION_NOTHICK  = FOLDER + "visualization-thick/";

		}
	}

	namespace math
	{
		const double PI = std::acos(-1);
		const double HUGE = std::numeric_limits<double>::max();
	}

	namespace computation
	{
		const double TRIMMER_PRECISION = 1e-6; // FINDOUT
		const double TIME_DIV = 10;	// resolution while selecting time step
		const double IGNORE_VEL = 1e8; // If any velocity in the porous body is IGNORE_VEL times less than the max velocity then it is forced to be 0
	}

	namespace plot
	{
		const int IMAGE_SIZE = 1000;
	}
}

#endif
