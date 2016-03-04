/**
*.cpp Volimage File
* Carla Wilby 01/03/2016
*/

#include "volimage.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

	VolImage::VolImage(){
		width = 0;
		height = 0;
		vector<u_char**> slices;

	}

	VolImage::~VolImage(){
		// do we put deletes in here?
		// where do we call deconstructor?
		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
    			delete slices[i][j]; // Calls ~VolImage and deallocates *tmp[i][j]
    		}
		}
		slices.clear();
  	}

	// populate the object with images in stack
	bool VolImage::readImages(string baseName){
		string filename;
		filename = baseName + ".dat";
		cout << filename << endl; //PRINT
		ifstream ifs(filename.c_str());

		if(!ifs){
			cout << "File not found.";
			return 0;
		}

		
		// Stream header file contents
		int number_images;
		string contents;
		getline(ifs, contents);
		istringstream iss(contents);
		string current;
		int cnt = 1;
		while(getline(iss, current, ' ')){
			int curr;
			cout << current << endl; //PRINT
			istringstream ss(current);
			ss >> curr;
			if(cnt == 1){
				width = curr;
				cnt++;
			}else if(cnt == 2){
				height = curr;
				cnt++;
			}else if (cnt == 3){
				number_images = curr;
				cnt++;
			}
		}
		ifs.close();

		// Dynamically allocate 2D array
		// Do this here?
		u_char **frame;
		frame = new u_char* [height];
		for(int i = 0; i < height; i++){
			// This is a pointer too?
			frame[i] = new u_char[width];
		}
		cout << "Done making 2D array" << endl; //PRINT

		// Stream .raw file contents
		// Change to i < number_images
		for(int i = 0; i < 1; i++){
			// Make filename
			string filenum;
			stringstream ss;
			ss << i;
			filenum = ss.str();
			filename = baseName + filenum + ".raw";
			cout << "Filename: " + filename << endl; //PRINT
			// Worry about file path later too
			ifstream binfile(filename.c_str(), ios::in|ios::binary|ios::ate);
			// ios::ate flag - get pointer positioned at end of the file;
			// how tellg gets size. Do we need this?
			if(!binfile){
				cout << "File " + filename + " not found.";
				return 0;
			}

			//memblock holds whole file
			char * memblock;
			streampos size;
			// Stream header file contents
			if(binfile.is_open()){
				size = binfile.tellg();
				memblock = new char [size];
				binfile.seekg (0, ios::beg);
				// get position at beginning of file (with pointer thing)
				// read everything into memblock
				binfile.read (memblock, size);
				cout << "Hopefully everything in dynamic memblock" << endl; //PRINT
				binfile.close();
			}

			// Now put in array
			int counter = 0;
			for(int i = 0; i < height; i++){
				for(int j = 0; j < width; j++){
					frame[i][j] = memblock[counter];
					counter++;
				}
			}
			cout << "First thing in file: "+ frame[0][0] << endl; //PRINT NOT WORKING
			
			// Getting rid of binary chunk
			delete[] memblock;

		}
		return 0;
	}

	// compute difference map and write out
	void VolImage::diffmap(int sliceI, int sliceJ, string output_prefix){

	}

	// extract slice sliceId and write to output
	void VolImage::extract(int sliceId, string output_prefix){

	}

	// number of bytes used to store image data bytes
	// and pointers (ignore vector<> container, dims etc)
	int VolImage::volImageSize(void){
		int size = height*width;
		return size;
	}
