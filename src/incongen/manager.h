#ifndef INCONGEN_MANAGER_H
#define INCONGEN_MANAGER_H


#include "io/fileread.h"
#include "io/filewrite.h"

/**
 * incongen: working modes
 *
 * nrows=n
 * ncols=n
 * tradius={const=0.1, imbibition, function}
 * tlength={const=1.0, inverse_radius}
 * tmns={saturate_oil, saturate_water, imbibition}
 */

namespace incongen
{
	class Manager
	{
		static const std::string PROGRAM_NAME;

		static void generate_from_incongen_config(
			const config_file::Incongen& incongen_config
		);

		static void interactive_mode();

	public:
		static void run();
	};

}

#endif
