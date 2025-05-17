
math::Random::seed();


	char command_main_menu;
	const std::string text_promt_main_menu = "f)iltration-mode g)enerate, m)odify, i)mhibition-generator";
	while(!initcon::Mode::Main::exit_code_main_menu(text_promt_main_menu, command_main_menu))
	{
		if(command_main_menu == 'f')
		{
			std::cout << "-filtration-mode-new" << std::endl;
			initcon::Mode::Main::generate_for_filtration();
		}
		else if(command_main_menu == 'g')
		{
			std::cout << "-generate mode" << std::endl;
			initcon::Mode::Main::generate();
		}
		else if(command_main_menu == 'm')
		{
			std::cout << "-modify mode" << std::endl;
			initcon::Mode::Main::modify();
		}
		else if(command_main_menu == 'i')
		{
			std::cout << "-imhibition_generator mode" << std::endl;
			initcon::Mode::Main::imhibition_generator();
		}
		else
		{
			std::cout << "-ERR-IPT-input command_char is not valid" << std::endl;
			continue;
		}
		// Display the status of the files
		const fileio::Data data = fileio::Read::all();
		if(data.success)
		{
			std::cout << "-FDK-All files are good" << std::endl;
		}
		else
		{
			std::cout << "-ERR-problems with input files" << std::endl;
		}
	}

	std::cout << "program exited: " << PROGRAM_PROPERTY_NAME << std::endl;


void initcon::Mode::Generate::radius(const network::Dimension& dimension)
{
	const auto def_radius = cmdio::Read::command_general<double>(
		"default val of radius");
	const tdouble_type r(dimension.rows, std::vector<double>(
		dimension.cols, def_radius));

	fileio::Write::run(r);
}

void initcon::Mode::Generate::mns(const network::Dimension& dimension)
{
	const tmns_type m(dimension.rows,
		std::vector<dst::Mns>(dimension.cols));

	fileio::Write::run(m);
}

void initcon::Mode::Main::generate()
{
	cmdio::Print::dimension();
	// Ask for the dimensions
	std::cout << std::endl << "-CIN- (nrows, ncols): ";
	int nrows, ncols;
	std::cin >> nrows >> ncols;

	const network::Dimension dimension(nrows, ncols);

	// Ask which file to rewrite
	const char cmd_file_regen = cmdio::Read::command_char(
		"r)adius, m)eniscus_configuration, b)oth, any_other_char)exit");

	if(cmd_file_regen == 'r')
	{
		Generate::radius(dimension);
	}
	else if(cmd_file_regen == 'm')
	{
		Generate::mns(dimension);
	}
	else if(cmd_file_regen == 'b')
	{
		Generate::radius(dimension);
		Generate::mns(dimension);
	}
	std::cout << "-EXT-exited generate" << std::endl;
}

void initcon::Mode::Main::modify()
{
	// Only works if the files are okay
	const char cmd_file_modify = cmdio::Read::command_char(
		"r)adius, m)eniscus, a)dd_random_to_radius, e)xit_or_other_char");

	if(cmd_file_modify == 'r')
	{
		Modify::radius();
	}
	else if(cmd_file_modify == 'm')
	{
		Modify::mns();
	}
	else if(cmd_file_modify == 'a')
	{
		Modify::add_random_to_radius();
	}
	std::cout << "-EXT-exited modify" << std::endl;
}

tdouble_type initcon::Mode::Modify::add_random_temporary(tdouble_type radius)
{
	const double random = declconst::FINE_RADIUS_RANDOMNESS;
	for(auto& row: radius)
	{
		for(auto& cell: row)
		{
			cell += utility::Random::fraction(random);
		}
	}

	return radius;
}

void initcon::Mode::Modify::add_random_to_radius()
{
	const std::string file_name = declfilename::FILE_RADIUS;
	const std::pair<tdouble_type, bool> data = fileio::Read::read_radius();

	if(data.second == false)
	{
		std::cout << "-ERR-CORRUPTED file, fix the input files and try again, or generate first." << std::endl;
		return;
	}

	tdouble_type radius = data.first;
	cmdio::Print::pmat(file_name + " original", radius);

	char command_char = 'r';
	do
	{
		if(command_char == 'r')
		{
			radius = add_random_temporary(radius);
			cmdio::Print::pmat(file_name, radius);
		}
		else if(command_char == 's')
		{
			fileio::Write::run(radius);
			std::cout << "-FDK-File saved successful" << std::endl;
		}
		else
		{
			std::cout << "-ERR-CIN invalid command_char" << std::endl;
		}
	} while(!cmdio::Read::command_char_exit_true("r)egenerate, s)ave", command_char));
}

void initcon::Mode::Modify::mns()
{
	const std::string file_name = declfilename::FILE_mns;
	const std::pair<tmns_type, bool> data = fileio::Read::read_mns();

	if(data.second == false)
	{
		std::cout << "-ERR-CORRUPTED file, fix the input files and try again, or generate first." << std::endl;
		return;
	}

	cmdio::Print::pmat(file_name, data.first);

	const auto modified_dst = modify_dst_from_cin(data.first);
	if(modified_dst.second)
	{
		std::cout << "-FDK-writing new data to file " << file_name << std::endl;
		fileio::Write::run(modified_dst.first);
	}
	else
	{
		std::cout << "-FDK-exited modify mode without saving changes" << std::endl;
	}

}

bool initcon::Mode::Modify::exit_code_modify_dst_save(char& save_yes_or_no)
{
	save_yes_or_no = cmdio::Read::command_char("WRR- Save before exit y/n");

	if(save_yes_or_no == 'y')
	{
		return true;
	}
	if(save_yes_or_no == 'n')
	{
		return true;
	}

	return false;
}

bool initcon::Mode::Modify::exit_code_modify_dst(const std::string& text_promt_modify_type_dst, char& command_char, bool& saved_dst)
{
	if(!cmdio::Read::command_char_exit_true(text_promt_modify_type_dst, command_char))
	{
		return false;
	}

	if(saved_dst)
	{
		return true;
	}

	char save_yes_or_no;
	while(!exit_code_modify_dst_save(save_yes_or_no))
	{
		std::cout << "-ERR-CIN invalid command_char." << std::endl;
	}

	if(save_yes_or_no == 'y')
	{
		saved_dst = true;
	}

	return true;
}

void initcon::Mode::Modify::radius()
{
	const std::string file_name = declfilename::FILE_RADIUS;
	const std::pair<tdouble_type, bool> data = fileio::Read::read_radius();

	if(data.second == false)
	{
		std::cout << "-ERR-CORRUPTED file, fix the input files and try again, or generate first." << std::endl;
		return;
	}

	cmdio::Print::pmat(file_name, data.first);

	const auto modified_dst = modify_dst_from_cin(data.first);
	if(modified_dst.second)
	{
		std::cout << "-FDK-writing new data to file " << file_name << std::endl;
		fileio::Write::run(modified_dst.first);
	}
	else
	{
		std::cout << "-FDK-exited modify mode without saving changes" << std::endl;
	}
}

bool initcon::Mode::Main::exit_code_main_menu(const std::string& text_promt_main_menu, char& command_char)
{
	return cmdio::Read::command_char_exit_true(text_promt_main_menu, command_char);
}

/*
void initcon::Mode::Main::imhibition_generator()
{
	const int size = 10;
	const int leave = 2;
	const double rad_outer = 3;
	const double rad_inner = 1;
	const double initial_fill = 0.30; //from the blue side

	tdouble_type radius(size, std::vector<double>(size, rad_outer));
	for(int row = leave; row + leave < size; ++ row)
	{
		for(int col = leave; col + leave < size; ++ col)
		{
			radius[row][col] = rad_inner;
		}
	}

	fileio::Write::run(radius);

	const dst::Mns mns_blue(0, 0, -1, -1);
	tmns_type mns(size, std::vector<dst::Mns>(size, mns_blue));

	const dst::Mns mns_grey(0, 1, -1, -1);
	for(int row = leave; row + leave < size; ++ row)
	{
		for(int col = leave; col + leave < size; ++ col)
		{
			mns[row][col] = mns_grey;
		}
	}

	const dst::Mns mns_up_facing(1, 0, initial_fill, -1);
	const dst::Mns mns_down_facing(1, 1, 1.0f - initial_fill, -1);


	for(int col = leave - 1; col + leave - 1 < size; ++ col)
	{
		mns[leave - 1][col] = mns_down_facing;
		mns[size - leave][col] = mns_up_facing;
	}

	std::vector<dst::Mns> v{mns_up_facing, mns_down_facing};
	for(int row = leave; row + leave < size; ++ row)
	{
		const dst::Mns& copy_ref_mns =v[row % 2];

		mns[row][leave - 1] = copy_ref_mns;
		mns[row][size - leave] = copy_ref_mns;
	}

	fileio::Write::run(mns);
}
*/

/*
void initcon::Mode::Main::imhibition_generator()
{
	const int size = 26;
	const int leave = 2;
	const double rad_outer = 3;
	const double rad_inner = 1;
	const double initial_fill = 0.20; //from the blue side

	tdouble_type radius(size, std::vector<double>(size, rad_outer));
	for(int row = leave; row + leave < size; ++ row)
	{
		for(int col = leave; col + leave < size; ++ col)
		{
			radius[row][col] = rad_inner;
		}
	}

	fileio::Write::run(radius);

	const dst::Mns mns_blue(0, 0, -1, -1);
	tmns_type mns(size, std::vector<dst::Mns>(size, mns_blue));

	const dst::Mns mns_grey(0, 1, -1, -1);
	for(int row = leave; row + leave < size; ++ row)
	{
		for(int col = leave; col + leave < size; ++ col)
		{
			mns[row][col] = mns_grey;
		}
	}

	const dst::Mns mns_up_facing(1, 0, initial_fill, -1);
	const dst::Mns mns_down_facing(1, 1, 1.0f - initial_fill, -1);


	for(int col = leave + 1; col + leave + 1 < size; ++ col)
	{
		mns[leave - 1][col] = mns_down_facing;
		mns[size - leave][col] = mns_up_facing;
	}

	std::vector<dst::Mns> v{mns_up_facing, mns_down_facing};
	for(int row = leave + 1; row + leave + 1 < size; ++ row)
	{
		const dst::Mns& copy_ref_mns =v[row % 2];

		mns[row][leave - 1] = copy_ref_mns;
		mns[row][size - leave] = copy_ref_mns;
	}

	mns[leave][leave] = mns_down_facing;
	mns[leave][size - leave - 1] = mns_down_facing;
	mns[size - 1 - leave][leave] = mns_up_facing;
	mns[size - 1 - leave][size - leave - 1] = mns_up_facing;

	fileio::Write::run(mns);
}
*/

std::vector<double> ThickNessSmoothener(const std::vector<double>& thick_old_v)
{
	std::vector<double> v(thick_old_v.cbegin() + 1, thick_old_v.cend() - 1);
	v.insert(v.end(), thick_old_v.crbegin(), thick_old_v.crend() - 2);
	return v;
}

bool DecideIfMainDiagonal(const int row, const int col)
{
	bool val = (col % 2 == 0);
	if(row % 2 == 0)
	{
		return val;
	}

	return !val;
}

double FuncThickAsCoordinate(
	const int row,
	const int col,
	const int size,
	const std::vector<double>& thick_old_v)
{
	const std::vector<double> thick_v = ThickNessSmoothener(thick_old_v);
	const int thick_len = thick_v.size();
	bool is_main_directed_diagonal = DecideIfMainDiagonal(row, col);

	int col_of_main_diagonal = size - 1 - row;
	if(is_main_directed_diagonal)
	{
		col_of_main_diagonal = row;
	}

	const int distance = std::abs(col - col_of_main_diagonal) / 2;
	return thick_v[distance % thick_len];
}

tdouble_type GenerateBiscuitTypeGridSystemAlterThickThin(
	const int size,
	const int leave)
{
	const std::vector<double> biscuit_thickness_v{6, 5, 4, 3, 2};
	const std::vector<double> filler_row(size, biscuit_thickness_v.front());
	tdouble_type radius(size, filler_row);

	for(int row = leave; row + leave < size; ++ row)
	{
		for(int col = leave; col + leave < size; ++ col)
		{
			const int local_row = row - leave;
			const int local_col = col - leave;
			const int local_size = size - 2 * leave;
			radius[row][col] = FuncThickAsCoordinate(
				local_row,
				local_col,
				local_size,
				biscuit_thickness_v);
		}
	}

	return radius;
}

tmns_type GenerateMnsDistibWithInterfaceInThinnerRegion(
	const int size,
	const int leave)
{
	const double initial_fill = 0.80; //from the blue side

	const dst::Mns mns_blue(0, 0, -1, -1);
	tmns_type mns(size, std::vector<dst::Mns>(size, mns_blue));

	const dst::Mns mns_grey(0, 1, -1, -1);
	for(int row = leave; row + leave < size; ++ row)
	{
		for(int col = leave; col + leave < size; ++ col)
		{
			mns[row][col] = mns_grey;
		}
	}

	const dst::Mns mns_up_facing(1, 0, initial_fill, -1);
	const dst::Mns mns_down_facing(1, 1, 1.0f - initial_fill, -1);


	for(int col = leave; col + leave < size; ++ col)
	{
		mns[leave][col] = mns_down_facing;
		mns[size - leave - 1][col] = mns_up_facing;
	}

	std::vector<dst::Mns> v{mns_down_facing, mns_up_facing};
	for(int row = leave; row + leave < size; ++ row)
	{
		const dst::Mns& copy_ref_mns = v[(row + leave) % 2];

		mns[row][leave] = copy_ref_mns;
		mns[row][size - leave - 1] = copy_ref_mns;
	}


	return mns;
}

void initcon::Mode::Main::imhibition_generator()
{
	const int size = 30;
	const int leave = 0;


	//const tdouble_type radius = GenerateBiscuitTypeGridSystemAlterThickThin(size, leave);
	//fileio::Write::run(radius);

	const tmns_type mns = GenerateMnsDistibWithInterfaceInThinnerRegion(size, leave);
	fileio::Write::run(mns);
}


tdouble_type sinosodial_radius_generator(const int rows, const int cols)
{
	const double l =1;
	const double delta_small = std::sqrt(2) * l;
	const double lambda = (rows / 4) * delta_small;

	const double k_x = 2 * declconst::PI / lambda;
	const double k_y = 2 * declconst::PI / lambda;

	const double A = 4;
	const double B = 0.8;

	const network::Dimension dimension(rows, cols);
	auto radius = dimension.empty_table();
	for(int row = 0; row < dimension.rows; ++ row)
	{
		for(int col = 0; col < dimension.cols; ++ col)
		{
			const double x = (0.5 + col) / 2 * delta_small;
			const double y = (0.5 + row) / 2 * delta_small;

			const auto r = A * (1.0 + B * std::cos(k_x * x) * std::cos(k_y * y));
			radius[row][col] = r;
		}
	}
	return radius;
}

void initcon::Mode::Main::generate_for_filtration()
{
	const int rows = 6;
	const int cols = 6;

	const dst::Mns mns_blue(0, 0, -1, -1);
	const dst::Mns mns_grey(0, 1, -1, -1);
	tmns_type mns(
			rows,
			std::vector<dst::Mns>(cols, mns_grey)
		);


	const double initial_fill = 0.30; //from the blue side
	const int leave = 1;
	const dst::Mns mns_up_facing(1, 0, initial_fill, -1);
	const dst::Mns mns_down_facing(1, 1, 1.0f - initial_fill, -1);


	std::vector<dst::Mns> v{mns_down_facing, mns_up_facing};
	for(int row = 0; row < rows; ++ row)
	{
		const dst::Mns& copy_ref_mns = v[(row + leave) % 2];

		mns[row][leave] = copy_ref_mns;
		mns[row][0] = mns_blue;
	}

	fileio::Write::run(mns);

	const auto radius = sinosodial_radius_generator(rows, cols);
	fileio::Write::run(radius);
}
