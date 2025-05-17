#include "fileioplot.h"

void fileio::Plot::without_radius(tmns_type mns, int count)
{

	std::reverse(mns.begin(), mns.end());

	const int image_size = declconst::IMAGE_SIZE;
	const int cols = mns.front().size();
	const int rows = mns.size();

	const int length = image_size / (std::max(rows, cols) + 2);

	drw::bmp a(image_size, image_size);

	const int start_y = length;
	const int start_x = length;
	const int thick = length / 10;


	int y = start_y;
	for(int row = 0; row < rows; ++ row)
	{
		const auto& w = mns[row];
		int x = start_x + length * (row % 2);
		for(int col = 0; col < cols; ++ col)
		{
			int sign = ((row % 2) ^ (col % 2) ? -1 : 1);
			a.drawStrip(x, y, length, thick, sign, w[col].gen_pos_long(), w[col].type);
			x += 2 * length * (sign > 0);
		}
		y += length;
	}

	a.save(declfilename::FOLDER_PLOTS + "stp-" + std::to_string(count) + ".bmp");
}

//Tested works Correctly
void fileio::Plot::with_radius(tmns_type mns, tdouble_type radius, double clock, int count)
{
	const int rows = radius.size();
	const int cols = radius.front().size();
	std::reverse(mns.begin(), mns.end());
	std::reverse(radius.begin(), radius.end());

	double max_radius = -1;
	double min_radius = 1e12;

	for(const auto& x: radius)
	{
		for(auto y: x)
		{
			max_radius = std::max(max_radius, y);
			min_radius = std::min(min_radius, y);
		}
	}

	const int image_size = declconst::IMAGE_SIZE;
	const int length = mns.front().size();
	const int height = mns.size();

	const int effective_length = image_size / (std::max(length, height) + 2);

	drw::bmp a(image_size, image_size);

	const int start_y = effective_length;
	const int start_x = effective_length;
	const double max_thick = effective_length / 2.0;
	const double min_thick = effective_length / 6.0;


	int y = start_y;
	for(int row = 0; row < rows; ++ row)
	{
		const auto& w = mns[row];
		int x = start_x + effective_length * (row % 2);
		for(int col = 0; col < cols; ++ col)
		{
			int sign = (1 - 2 * (row % 2)) * (1 - 2 * (col % 2));
			const double r = radius[row][col];
			double thick = min_thick;
			if(max_radius != min_radius)
			{
				thick  += (r - min_radius) * (max_thick - min_thick) / (max_radius - min_radius);
			}

			a.drawVector(x, y, effective_length, thick, sign, w[col].n, w[col].pos, w[col].type);

			x += 2 * effective_length * (sign > 0);
		}

		y += effective_length;
	}

	a.save(declfilename::FOLDER_PLOTS + "pic-" + std::to_string(count) + ".bmp");
}

