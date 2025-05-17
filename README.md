# Development instructions
## makefilegen
- makefilegen short form for makefile-generator
To work with makefilegen, you must go into the folder:
### relocate to porousfluid/makefilegen
##
	cd makefilegen

### Regenerate porousfluid/Makefile without recompilation
##
	make

- Runs makefilegen/build/makefilegen.exe
- Which reads makefilegen-config.txt
- This produces makefilegen/build/Makefile, it is put in build folder so that it does not replace makefilegen/Makefile
- Moves porousfluid/makefilegen/build Makefile -> porousfluid/Makefile

### edit makefilegen

##
	make edit
To open the source code of makefilegen.exe


### Force compile and run
##
	make force

- deletes makefilegen/build, which forces to rebuild all object files

### Files and folders of porousfluid/makefilegen/:
- __src__: source code of makefilegen
- __build__: exe and object files of makefilegen
- __Makefile__: basic scripts to edit, run, and force compile makefilegen.exe
- __makefilegen-config.txt__: configuration input file about the organization of the libraries in porousfluid/src

### Working Mechanism
- object files are produced into makefilegen/build
- object files are linked and build/makefilegen.exe is produced
- start running ./build/makefilegen.exe
- reads makefilegen-config.txt
- outputs file, build/Makefile
- moves build/Makefile to porousfluid/Makefile, replacing the existing Makefile




