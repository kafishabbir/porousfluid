# Instructions
## Compile instructions
### makefilegen
makefilegen short form for makefile-generator

This is a completely separate program that creates a Makefile for the main code.

##
	cd makefilegen

#### edit makefilegen
To open the source code of makefilegen
##
	make edit

#### read new file structure of porous fluid without compiltaion
Reads config file and regenerate porousfluid/Makefile again without compilation
##
	make

#### Force compile and run
##
	make force


#### How makefilegen works
Files and folders of makefilegen:
- porousfluid/makefilegen/src: source code of makefilegen
- porousfluid/makefilegen/build: build, object files of makefilegen
- porousfluid/makefilegen/Makefile: basic code to edit, run, and force compile makefilegen
- porousfluid/makefilegen/makefilegen-config: organization of the libraries in porousfluid/src

-The source code is located




