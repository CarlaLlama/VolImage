VOLUMETRIC IMAGE READER
------------------------

To compile this project:
	Extract project to desired directory
	cd into project directory
	run:
		$ make

To run this project:
	Ensure it has been compiled correctly
	cd into project directory
	run:
		$ volimage <imageBase> [-d i j output_file_name] [-x i output_file_name] [-g i output_file_name]
	Follow prompts.

To clean project:
	run:
		$ make clean

HELP
----

There are a number of things to ensure or this program will not work:
1. Ensure the binary and header files of the image to be processed are inside 
a directory within the program directory.
2. The name of this directory MUST be the same as the name of the prefix of the files: eg MRI
3. All image header files MUST have the suffix .dat
4. All image binary files MUST have the suffix .raw

DIRECTORY STRUCTURE
-------------------

Here is an example of the working directory structure:

/volimage
	/driver.cpp
	/volimage.cpp
	/volimage.h
	/Makefile
	/README.txt
	/.gitignore
	/scan 			-- example of image files in directory
		/scan.dat
		/scan0.raw
		/scan1.raw
		...


FILE STRUCTURE
--------------

Makefile:
	Used to correctly compile source files.
driver.cpp:
	Source file containing main() method, called at start of project.
	Reads in arguments from user.
volimage.h:
	Header file containing method and vector declaration.
volimage.cpp:
	Source file containing method implementation.

MAINTAINERS
-----------

Current Maintainers:
* Carla Wilby (carlallama) - https://github.com/CarlaLlama