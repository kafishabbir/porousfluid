#include "incongen/manager.h"

/**
 * @file exe/incongen
 * @brief incongen.exe - initial conditions generator
 * Compiles into an executable therefore contains int main()
 * incongen::Manager::run() to start the program.
 *
 * In simple,
 * 		reads run/input/incongen-config.txt
 * 		if the file is valid, generates:
 * 		tlength.txt, tradius.txt, tmns.txt and simulation-config.txt
 * 		if there is some problem,
 * 		then opens to interactive mode.
 */

int main()
{
	incongen::Manager::run();
	return 0;
}
