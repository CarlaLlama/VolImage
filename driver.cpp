/**
*.cpp Volimage Driver File
* Carla Wilby 01/03/2016
*/
#include "volimage.h"
#include <iostream>
#include <sstream>

using namespace std;


int main(int argc, char* argv[])
{
	string prefix;
	string outfile;
	int img_no;
	int bytes_no;
	string operation_message;

	if(argc < 2){
		cout << "Incorrect program entry." << endl;
		cout << "Correct usage: volimage <imageBase> [-d i j output_file_name] [-x i output_file_name] [-g i output_file_name]" << endl;
		return 0;
	}

	// Make volimage Object, read in images
	VolImage volimg;
	prefix = string(argv[1]);
	volimg.readImages(prefix);

	if(argc == 2){
		// build the internal representation and then exit after memory is correctly cleaned up
		operation_message = "Built internal representation, now exiting.";
	}else if((argc == 5) && (string(argv[2]) == "-g")){
		int imgi;
		istringstream is(argv[3]);
		is >> imgi;
		outfile = string(argv[4]);

		volimg.extractRow(imgi, outfile);
		operation_message = "Extract image along row " + string(argv[3]) + " across all slices.";
	}else if((argc == 5) && (string(argv[2]) == "-x")){
		int slice;
		istringstream is(argv[3]);
		is >> slice;
		outfile = string(argv[4]);

		volimg.extract(slice, outfile);
		operation_message = "Retrieved slice and wrote slice to output file";
	}else if((argc == 6) && (string(argv[2]) == "-d")){
		int imgi;
		int imgj;
		istringstream is(argv[3]);
		is >> imgi;
		istringstream iss(argv[4]);
		iss >> imgj;
		outfile = string(argv[5]);

		volimg.diffmap(imgi, imgj, outfile);
		operation_message = "Computed difference map between slices " + string(argv[3]) + " and " + string(argv[4]) + " to output file";
	}else{
		cout << "Incorrect program entry." << endl;
		cout << "Correct usage: volimage <imageBase> [-d i j output_file_name] [-x i output_file_name] [-g i output_file_name]" << endl;
		return 0;
	}

	// Print number of images and bytes required
	img_no = volimg.volNumberImages();
	bytes_no = volimg.volImageSize();

	ostringstream oss;
	oss << img_no;
	cout << "Number of images: " + oss.str() << endl;

	ostringstream ss;
	ss << bytes_no;
	cout << "Number of bytes required: " + ss.str() << endl;

	cout << "Operation achieved: " << operation_message << endl;

	return 0;

};