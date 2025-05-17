#include "fileioread.h"
#include "fileioplot.h"


int main()
{
	fileio::Data data = fileio::Read::loop_until_proper_files();
	fileio::Plot::with_radius(data.mns, data.radius, 1, 1);
	fileio::Plot::without_radius(data.mns, 1);

	return 0;
}
