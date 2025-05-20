#include "menu.h"
#include "decl.h"

/*!
 * How the program makefilegen.exe works,
 * when we run make in the root folder of makefilegen/
 * 		porousfluid/makefilegen$ make
 * 		1. compilation and generation of makefilegen.exe,
 * 			porousfluid/makefilegen/build/makefilegen.exe
 * 		2. execution of the exe which produces build/Makefile
 *			porousfluid/makefilegen$ ./build/makefilegen.exe
 * 		3. moves build/Makefile to the root folder
 */

int main()
{
	// read porous-fluid/makefile-gen/file-structure.txt
	const std::vector<std::string> file_vec = Menu::read_file_structure();

	// the output will be written to porous-fluid/makefile-gen/build/
	std::ofstream fout(decl::target_output);

	const std::string time_stamp_format = "\"%Y%m%d_%H%M%S\"";
	fout << "TIMESTAMP := $(shell date +" + time_stamp_format + ")";
	/*
	 * all: necessary_compile run_program
	 */
	Menu::all(fout);

	/*
	 * necessary_compile: run/ext1 run/exe2
	 * clean up the plot folder
	 */
	Menu::necessary_compile(fout, file_vec);


	Menu::folder_check(fout);


	Menu::run(fout);

	/*
	 * force: clean_build, necessary_compile
	 */
	Menu::force(fout);

	/*
	 * rm -rf build
	 * mkdir build
	 */
	Menu::clean(fout);

	/*
	 * geany -i src/lib/lib.h src/lib/lib.cpp
	 */
	Menu::edit(fout, file_vec);

	/*
	 * exe1: obj1.o obj2.o exe1.o
	 * 		g++ a.o b.o -o run/exe1
	 */
	Menu::exe(fout, file_vec);

	/*
	 * build/obj1.o: obj1.cpp obj1.h headers.h
	 * 		g++ -c Wall -o obj1.o
	 */
	Menu::object(fout, file_vec);

	return 0;
}
