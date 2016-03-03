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

	if(argc == 1){
		cout << "Incorrect program entry." << endl;
		cout << "Correct usage: volimage <imageBase> [-d i j output_file_name] [-x i output_file_name]" << endl;
		return 0;
	}
	if(argc < 4){
		int img;
		int bytes;
		img = 1;
		bytes = 3;
		// go ahead and build the internal representation and then exit after
		// ensuring memory is correctly cleaned up
		VolImage volimg;
		prefix = string(argv[1]);
		volimg.readImages(prefix);
		cout << "Number of images: " + img << endl;
		cout << "Number of bytes required: " + bytes << endl;
	} else {
		string outfile;
		VolImage volimg;
		prefix = string(argv[1]);
		volimg.readImages(prefix);
		if(string(argv[2]) == "-d"){
			int imgi;
			int imgj;
			istringstream is(argv[3]);
			is >> imgi;
			istringstream iss(argv[4]);
			iss >> imgj;
			outfile = string(argv[5]);
			volimg.diffmap(imgi, imgj, outfile);
		}
		else if(string(argv[2]) == "-x"){
			int slice;
			istringstream is(argv[3]);
			is >> slice;
			outfile = string(argv[4]);
			volimg.extract(slice, outfile);
		}else if(string(argv[2]) == "-g"){

		} 
	}
	return 0;
};