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

To clean project:
	run:
		$ make clean

COMMAND LINE ARGUMENTS
----------------------

volimage : name of executable
<imageBase> : name of images prefix i.e. MRI

[-d i j output_file_name] :
	-d : differential mapping flag
	i : first image index
	j : second image index
	output_file_name : name of file to print result to

[-x i output_file_name] :
	-x : extract image flag
	i : index of image to extract
	output_file_name : name of file to print result to

[-g i output_file_name] :
	-g : extract image along row flag
	i : row number to extract from all files
	output_file_name : name of file to print result to

HELP
----

There are a number of things to ensure or this program will not work:

1. Only one of the operations (flags) can be used in each run!
2. Ensure the binary and header files of the image to be processed are INSIDE A DIRECTORY within the program directory.
3. The name of this directory MUST be the same as the name of the prefix of the files: eg MRI
4. All image header files MUST have the suffix .dat
5. All image binary files MUST have the suffix .raw
6. Image binary files must be indexed from 0, 
	i.e. the first image is [prefix]0.raw
		 the second image is [prefix]1.raw etc
7. if "command not found: volimage" you may need to add volimage to your path
	Otherwise you can just use ./volimage ... instead.

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