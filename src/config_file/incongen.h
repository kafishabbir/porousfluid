#ifndef CONFIG_FILE_INCONGEN_H
#define CONFIG_FILE_INCONGEN_H

#include "algo/utility.h"
#include <vector>
#include <iostream>


/**
 * incongen: working modes
 *
 * nrows = n
 * ncols = n
 * tradius = {constant=0.1, imbibition, function}
 * tlength = {constant=1.0, inverse_radius}
 * tmns = {saturate_oil, saturate_water, imbibition}
 */

namespace config_file
{
	class Incongen
	{
		bool nrows_set = false;
		bool ncols_set = false;
		bool tradius_set = false;
		bool tlength_set = false;
		bool tmns_set = false;

		bool set_nrows(const std::string& value);
		bool set_ncols(const std::string& value);
		bool set_tradius(const std::string& value);
		bool set_tlength(const std::string& value);
		bool set_tmns(const std::string& value);

		static std::pair<double, bool> const_extraction(const std::string& s);

	public:
		enum class val_tradius {constant, imbibiton, function};
		enum class val_tlength {constant, inverse_radius};
		enum class val_tmns {saturate_oil, saturate_water, imbibition};

		int nrows;
		int ncols;
		std::pair<val_tradius, double> tradius;
		std::pair<val_tlength, double> tlength;
		val_tmns tmns;
		bool set(const std::string& buffer_line);
		bool valid() const;
	};

}

#endif
