# Development instructions
## makefilegen
- __makefilegen__ is the __makefile-generator__
- The Makefile opens the editor with all source-code, and helps compile them.

### relocate to porousfluid/makefilegen
##
	cd makefilegen

- To work with makefilegen, you must go into the folder:

### Regenerate porousfluid/Makefile without recompilation
##
	make

- object files are produced into makefilegen/build
- object files are linked and build/makefilegen.exe is produced
- starts running ./build/makefilegen.exe
- reads makefilegen-config.txt
- outputs file, build/Makefile, it is put in build folder so that it does not replace makefilegen/Makefile
- moves build/Makefile to porousfluid/Makefile, replacing the existing Makefile

### edit makefilegen

##
	make edit
To open the source code of makefilegen.exe


### Force compile and run
##
	make force

- deletes makefilegen/build/, which forces to rebuild all object files

### Files and folders of porousfluid/makefilegen/:
- __src__: source code of makefilegen
- __build__: exe and object files of makefilegen
- __Makefile__: basic scripts to edit, run, and force compile makefilegen.exe
- __makefilegen-config.txt__: configuration input file about the organization of the libraries in porousfluid/src












# File and folder organization
## build/
Object files of all ".cpp" source code

## docs/
Documents, articles, publications related to this application.

## makefilegen/
Additional program that takes in the order and structure of files in porousfluid/src/ and regenerates porousfluid/Makefile

## run/
### *.exe
#### simulate.exe
Execuable to begin the simulation

#### incongen.exe
Generates the initial distributions

### input

### output

### output-old
Contains files from previous simulations

## src/






