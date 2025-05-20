TIMESTAMP := $(shell date +"%Y%m%d_%H%M%S")

all: necessary_compile run_program
	@echo "Command executed = all"


necessary_compile: folder_check run/incongen.exe run/plot.exe run/simulate.exe run/test.exe
	@echo "Command executed = necessary_compile"


folder_check:
	rm -rf run/output
	mkdir -p build/
	mkdir -p run/
	mkdir -p run/input
	mkdir -p run/output
	mkdir -p run/output-old
	mkdir -p run/output/simulation-data
	mkdir -p run/output/simulation-calculations
	mkdir -p run/output/plots
	mkdir -p run/output/plots/pressure
	mkdir -p run/output/plots/velocity
	mkdir -p run/output/plots/fluids-nothick
	mkdir -p run/output/plots/fluids-thick
	mkdir -p run/output/plots/saturation
	@echo "Command executed = folder_check"


run_program: folder_check
	./run/simulate.exe
	./run/plot.exe
	zip -r run/results-old/$(TIMESTAMP).zip run/output/


force: clean necessary_compile
	@echo "Command executed = force"


clean:
	rm -rf build/


edit:
	geany -i  src/algo/determine.h src/algo/determine.cpp src/algo/utility.h src/algo/utility.cpp src/config_file/incongen.h src/config_file/incongen.cpp src/config_file/simulation.h src/config_file/simulation.cpp src/drw/bmp.h src/drw/bmp.cpp src/dst/head.h src/exe/incongen.cpp src/exe/plot.cpp src/exe/simulate.cpp src/exe/test.cpp src/global/head.h src/incongen/garbage.h src/incongen/garbage.cpp src/incongen/manager.h src/incongen/manager.cpp src/incongen/parameter.h src/incongen/parameter.cpp src/incongen/tlength.h src/incongen/tlength.cpp src/incongen/tmns.h src/incongen/tmns.cpp src/incongen/tradius.h src/incongen/tradius.cpp src/io/cmdprint.h src/io/cmdprint.cpp src/io/cmdread.h src/io/cmdread.cpp src/io/fileplot.h src/io/fileplot.cpp src/io/fileread.h src/io/fileread.cpp src/io/filewrite.h src/io/filewrite.cpp src/math/gausslinear.h src/math/gausslinear.cpp src/math/random.h src/math/random.cpp src/measure/measure.h src/measure/measure.cpp src/network/dimension.h src/network/dimension.cpp src/network/mns.h src/network/mns.cpp src/simulate/manager.h src/simulate/manager.cpp src/smlsteps/01pressure.h src/smlsteps/01pressure.cpp src/smlsteps/02velocity.h src/smlsteps/02velocity.cpp src/smlsteps/03timestep.h src/smlsteps/03timestep.cpp src/smlsteps/04displacement.h src/smlsteps/04displacement.cpp


run/incongen.exe: build/exe_incongen.o build/algo_determine.o build/algo_utility.o build/config_file_incongen.o build/config_file_simulation.o build/drw_bmp.o build/incongen_garbage.o build/incongen_manager.o build/incongen_parameter.o build/incongen_tlength.o build/incongen_tmns.o build/incongen_tradius.o build/io_cmdprint.o build/io_cmdread.o build/io_fileplot.o build/io_fileread.o build/io_filewrite.o build/math_gausslinear.o build/math_random.o build/measure_measure.o build/network_dimension.o build/network_mns.o build/simulate_manager.o build/smlsteps_01pressure.o build/smlsteps_02velocity.o build/smlsteps_03timestep.o build/smlsteps_04displacement.o
	g++  build/exe_incongen.o build/algo_determine.o build/algo_utility.o build/config_file_incongen.o build/config_file_simulation.o build/drw_bmp.o build/incongen_garbage.o build/incongen_manager.o build/incongen_parameter.o build/incongen_tlength.o build/incongen_tmns.o build/incongen_tradius.o build/io_cmdprint.o build/io_cmdread.o build/io_fileplot.o build/io_fileread.o build/io_filewrite.o build/math_gausslinear.o build/math_random.o build/measure_measure.o build/network_dimension.o build/network_mns.o build/simulate_manager.o build/smlsteps_01pressure.o build/smlsteps_02velocity.o build/smlsteps_03timestep.o build/smlsteps_04displacement.o -o run/incongen.exe
	@echo "run/incongen.exe created."


run/plot.exe: build/exe_plot.o build/algo_determine.o build/algo_utility.o build/config_file_incongen.o build/config_file_simulation.o build/drw_bmp.o build/incongen_garbage.o build/incongen_manager.o build/incongen_parameter.o build/incongen_tlength.o build/incongen_tmns.o build/incongen_tradius.o build/io_cmdprint.o build/io_cmdread.o build/io_fileplot.o build/io_fileread.o build/io_filewrite.o build/math_gausslinear.o build/math_random.o build/measure_measure.o build/network_dimension.o build/network_mns.o build/simulate_manager.o build/smlsteps_01pressure.o build/smlsteps_02velocity.o build/smlsteps_03timestep.o build/smlsteps_04displacement.o
	g++  build/exe_plot.o build/algo_determine.o build/algo_utility.o build/config_file_incongen.o build/config_file_simulation.o build/drw_bmp.o build/incongen_garbage.o build/incongen_manager.o build/incongen_parameter.o build/incongen_tlength.o build/incongen_tmns.o build/incongen_tradius.o build/io_cmdprint.o build/io_cmdread.o build/io_fileplot.o build/io_fileread.o build/io_filewrite.o build/math_gausslinear.o build/math_random.o build/measure_measure.o build/network_dimension.o build/network_mns.o build/simulate_manager.o build/smlsteps_01pressure.o build/smlsteps_02velocity.o build/smlsteps_03timestep.o build/smlsteps_04displacement.o -o run/plot.exe
	@echo "run/plot.exe created."


run/simulate.exe: build/exe_simulate.o build/algo_determine.o build/algo_utility.o build/config_file_incongen.o build/config_file_simulation.o build/drw_bmp.o build/incongen_garbage.o build/incongen_manager.o build/incongen_parameter.o build/incongen_tlength.o build/incongen_tmns.o build/incongen_tradius.o build/io_cmdprint.o build/io_cmdread.o build/io_fileplot.o build/io_fileread.o build/io_filewrite.o build/math_gausslinear.o build/math_random.o build/measure_measure.o build/network_dimension.o build/network_mns.o build/simulate_manager.o build/smlsteps_01pressure.o build/smlsteps_02velocity.o build/smlsteps_03timestep.o build/smlsteps_04displacement.o
	g++  build/exe_simulate.o build/algo_determine.o build/algo_utility.o build/config_file_incongen.o build/config_file_simulation.o build/drw_bmp.o build/incongen_garbage.o build/incongen_manager.o build/incongen_parameter.o build/incongen_tlength.o build/incongen_tmns.o build/incongen_tradius.o build/io_cmdprint.o build/io_cmdread.o build/io_fileplot.o build/io_fileread.o build/io_filewrite.o build/math_gausslinear.o build/math_random.o build/measure_measure.o build/network_dimension.o build/network_mns.o build/simulate_manager.o build/smlsteps_01pressure.o build/smlsteps_02velocity.o build/smlsteps_03timestep.o build/smlsteps_04displacement.o -o run/simulate.exe
	@echo "run/simulate.exe created."


run/test.exe: build/exe_test.o build/algo_determine.o build/algo_utility.o build/config_file_incongen.o build/config_file_simulation.o build/drw_bmp.o build/incongen_garbage.o build/incongen_manager.o build/incongen_parameter.o build/incongen_tlength.o build/incongen_tmns.o build/incongen_tradius.o build/io_cmdprint.o build/io_cmdread.o build/io_fileplot.o build/io_fileread.o build/io_filewrite.o build/math_gausslinear.o build/math_random.o build/measure_measure.o build/network_dimension.o build/network_mns.o build/simulate_manager.o build/smlsteps_01pressure.o build/smlsteps_02velocity.o build/smlsteps_03timestep.o build/smlsteps_04displacement.o
	g++  build/exe_test.o build/algo_determine.o build/algo_utility.o build/config_file_incongen.o build/config_file_simulation.o build/drw_bmp.o build/incongen_garbage.o build/incongen_manager.o build/incongen_parameter.o build/incongen_tlength.o build/incongen_tmns.o build/incongen_tradius.o build/io_cmdprint.o build/io_cmdread.o build/io_fileplot.o build/io_fileread.o build/io_filewrite.o build/math_gausslinear.o build/math_random.o build/measure_measure.o build/network_dimension.o build/network_mns.o build/simulate_manager.o build/smlsteps_01pressure.o build/smlsteps_02velocity.o build/smlsteps_03timestep.o build/smlsteps_04displacement.o -o run/test.exe
	@echo "run/test.exe created."


build/algo_determine.o: src/algo/determine.h src/algo/determine.cpp src/dst/head.h src/global/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/algo/determine.cpp -o build/algo_determine.o
	@echo "build/algo_determine.o created."


build/algo_utility.o: src/algo/utility.h src/algo/utility.cpp src/dst/head.h src/global/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/algo/utility.cpp -o build/algo_utility.o
	@echo "build/algo_utility.o created."


build/config_file_incongen.o: src/config_file/incongen.h src/config_file/incongen.cpp src/dst/head.h src/global/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/config_file/incongen.cpp -o build/config_file_incongen.o
	@echo "build/config_file_incongen.o created."


build/config_file_simulation.o: src/config_file/simulation.h src/config_file/simulation.cpp src/dst/head.h src/global/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/config_file/simulation.cpp -o build/config_file_simulation.o
	@echo "build/config_file_simulation.o created."


build/drw_bmp.o: src/drw/bmp.h src/drw/bmp.cpp src/dst/head.h src/global/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/drw/bmp.cpp -o build/drw_bmp.o
	@echo "build/drw_bmp.o created."


build/exe_incongen.o: src/exe/incongen.cpp src/dst/head.h src/global/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/exe/incongen.cpp -o build/exe_incongen.o
	@echo "build/exe_incongen.o created."


build/exe_plot.o: src/exe/plot.cpp src/dst/head.h src/global/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/exe/plot.cpp -o build/exe_plot.o
	@echo "build/exe_plot.o created."


build/exe_simulate.o: src/exe/simulate.cpp src/dst/head.h src/global/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/exe/simulate.cpp -o build/exe_simulate.o
	@echo "build/exe_simulate.o created."


build/exe_test.o: src/exe/test.cpp src/dst/head.h src/global/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/exe/test.cpp -o build/exe_test.o
	@echo "build/exe_test.o created."


build/incongen_garbage.o: src/incongen/garbage.h src/incongen/garbage.cpp src/dst/head.h src/global/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/incongen/garbage.cpp -o build/incongen_garbage.o
	@echo "build/incongen_garbage.o created."


build/incongen_manager.o: src/incongen/manager.h src/incongen/manager.cpp src/dst/head.h src/global/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/incongen/manager.cpp -o build/incongen_manager.o
	@echo "build/incongen_manager.o created."


build/incongen_parameter.o: src/incongen/parameter.h src/incongen/parameter.cpp src/dst/head.h src/global/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/incongen/parameter.cpp -o build/incongen_parameter.o
	@echo "build/incongen_parameter.o created."


build/incongen_tlength.o: src/incongen/tlength.h src/incongen/tlength.cpp src/dst/head.h src/global/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/incongen/tlength.cpp -o build/incongen_tlength.o
	@echo "build/incongen_tlength.o created."


build/incongen_tmns.o: src/incongen/tmns.h src/incongen/tmns.cpp src/dst/head.h src/global/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/incongen/tmns.cpp -o build/incongen_tmns.o
	@echo "build/incongen_tmns.o created."


build/incongen_tradius.o: src/incongen/tradius.h src/incongen/tradius.cpp src/dst/head.h src/global/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/incongen/tradius.cpp -o build/incongen_tradius.o
	@echo "build/incongen_tradius.o created."


build/io_cmdprint.o: src/io/cmdprint.h src/io/cmdprint.cpp src/dst/head.h src/global/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/io/cmdprint.cpp -o build/io_cmdprint.o
	@echo "build/io_cmdprint.o created."


build/io_cmdread.o: src/io/cmdread.h src/io/cmdread.cpp src/dst/head.h src/global/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/io/cmdread.cpp -o build/io_cmdread.o
	@echo "build/io_cmdread.o created."


build/io_fileplot.o: src/io/fileplot.h src/io/fileplot.cpp src/dst/head.h src/global/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/io/fileplot.cpp -o build/io_fileplot.o
	@echo "build/io_fileplot.o created."


build/io_fileread.o: src/io/fileread.h src/io/fileread.cpp src/dst/head.h src/global/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/io/fileread.cpp -o build/io_fileread.o
	@echo "build/io_fileread.o created."


build/io_filewrite.o: src/io/filewrite.h src/io/filewrite.cpp src/dst/head.h src/global/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/io/filewrite.cpp -o build/io_filewrite.o
	@echo "build/io_filewrite.o created."


build/math_gausslinear.o: src/math/gausslinear.h src/math/gausslinear.cpp src/dst/head.h src/global/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/math/gausslinear.cpp -o build/math_gausslinear.o
	@echo "build/math_gausslinear.o created."


build/math_random.o: src/math/random.h src/math/random.cpp src/dst/head.h src/global/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/math/random.cpp -o build/math_random.o
	@echo "build/math_random.o created."


build/measure_measure.o: src/measure/measure.h src/measure/measure.cpp src/dst/head.h src/global/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/measure/measure.cpp -o build/measure_measure.o
	@echo "build/measure_measure.o created."


build/network_dimension.o: src/network/dimension.h src/network/dimension.cpp src/dst/head.h src/global/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/network/dimension.cpp -o build/network_dimension.o
	@echo "build/network_dimension.o created."


build/network_mns.o: src/network/mns.h src/network/mns.cpp src/dst/head.h src/global/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/network/mns.cpp -o build/network_mns.o
	@echo "build/network_mns.o created."


build/simulate_manager.o: src/simulate/manager.h src/simulate/manager.cpp src/dst/head.h src/global/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/simulate/manager.cpp -o build/simulate_manager.o
	@echo "build/simulate_manager.o created."


build/smlsteps_01pressure.o: src/smlsteps/01pressure.h src/smlsteps/01pressure.cpp src/dst/head.h src/global/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/smlsteps/01pressure.cpp -o build/smlsteps_01pressure.o
	@echo "build/smlsteps_01pressure.o created."


build/smlsteps_02velocity.o: src/smlsteps/02velocity.h src/smlsteps/02velocity.cpp src/dst/head.h src/global/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/smlsteps/02velocity.cpp -o build/smlsteps_02velocity.o
	@echo "build/smlsteps_02velocity.o created."


build/smlsteps_03timestep.o: src/smlsteps/03timestep.h src/smlsteps/03timestep.cpp src/dst/head.h src/global/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/smlsteps/03timestep.cpp -o build/smlsteps_03timestep.o
	@echo "build/smlsteps_03timestep.o created."


build/smlsteps_04displacement.o: src/smlsteps/04displacement.h src/smlsteps/04displacement.cpp src/dst/head.h src/global/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/smlsteps/04displacement.cpp -o build/smlsteps_04displacement.o
	@echo "build/smlsteps_04displacement.o created."
