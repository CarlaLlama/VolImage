/**
*.cpp Volimage File
* Carla Wilby 01/03/2016
*/

#include "volimage.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>

using namespace std;

	VolImage::VolImage(){
		width = 0;
		height = 0;
		vector<u_char**> slices;
	}

	VolImage::~VolImage(){
		for(int mem = 0; mem < slices.size(); mem++){
			for (int i = 0; i < height; i++) {
			   	delete[] slices[mem][i];
			}
			delete [] slices[mem];
		}
		cout << "Dynamically allocated memory cleaned." << endl;
  	}

	// populate the object with images in stack
	bool VolImage::readImages(string baseName){
		string filename;
		filename = baseName + "/" + baseName + ".dat";
		ifstream ifs(filename.c_str());

		if(!ifs){
			cout << "File not found." << endl;
			cout << "Please ensure files are inside a folder with the same name as the prefix." << endl;
			cout << "Please ensure header files have the suffix .dat" << endl;
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

		// Stream .raw file contents
		for(int i = 0; i < number_images; i++){
			// Make filename
			string filenum;
			stringstream ss;
			ss << i;
			filenum = ss.str();
			filename = baseName + "/" + baseName + filenum + ".raw";
			ifstream binfile(filename.c_str(), ios::in|ios::binary|ios::ate);
			// ios::ate flag - get pointer positioned at end of the file;
			if(!binfile){
				cout << "File " + filename + " not found.";
				cout << "Please ensure files are inside a folder with the same name as the prefix." << endl;
				cout << "Please ensure binary files have the suffix .raw" << endl;
				return 0;
			}

			// Dynamically allocate 2D frame array for slice
			u_char **frame = new u_char* [height];
			for(int i = 0; i < height; i++){
				frame[i] = new u_char[width];
			}

			// Stream header file contents
			char * blck;
			streampos size;
			if(binfile.is_open()){
				size = binfile.tellg();
				blck = new char[size];
				binfile.seekg(0, ios::beg);
				// get position at beginning of file
				// read everything into blck
				binfile.read(blck, size);
				binfile.close();
			}

			// Now put in array
			int counter = 0;
			for(int i = 0; i < height; i++){
				for(int j = 0; j < width; j++){
					frame[i][j] = blck[counter];
					counter++;
				}
			}

			// Now put array in vector as a slice
			slices.push_back(frame);

			// Getting rid of binary chunk
			delete[] blck;
		}
		return 0;
	}

	// compute difference map and write out
	void VolImage::diffmap(int sliceI, int sliceJ, string output_prefix){
		// make header file
		string header_filename = output_prefix + ".dat";
		ofstream ofile(header_filename.c_str());
		string out;
		ostringstream oss;
		oss << width;
		ostringstream os;
		os << height;
		out = oss.str() + " " + os.str() + " 1";
		ofile << out;

		// make difference map output file
		string output_filename = output_prefix + ".raw";
		// open with binary flag
		ofstream offile(output_filename.c_str(), ios::out | ios::binary);

		int size = height*width;
		ostringstream ods;
		ods << size;
		char output[size];
		int buff_cnt;
		for(int r = 0; r < height; r++){
			for(int c = 0; c < width; c++){
				output[buff_cnt] = (u_char)(fabs((float)slices[sliceI][r][c] - (float)slices[sliceJ][r][c])/2);
				buff_cnt++;
			}
		}
		
		offile.write(output, size);
		offile.close();
	}

	// extract slice sliceId and write to output
	void VolImage::extract(int sliceId, string output_prefix){
		// make header file
		string header_filename = output_prefix + ".dat";
		ofstream ofile(header_filename.c_str());
		string out;
		ostringstream oss;
		oss << width;
		ostringstream os;
		os << height;
		out = oss.str() + " " + os.str() + " 1";
		ofile << out;

		// make output file
		string output_filename = output_prefix + ".raw";
		// open with binary flag
		ofstream offile(output_filename.c_str(), ios::out | ios::binary);

		int size = height*width;
		ostringstream ods;
		ods << size;
		char output[size];
		int buff_cnt;
		for(int i = 0; i < height; i++){
			for(int j = 0; j < width; j++){
				output[buff_cnt] = slices[sliceId][i][j];
				buff_cnt++;
			}
		}
		offile.write(output, size);
		offile.close();
	}

	// extract an image across row, across all slices and write to output file
	void VolImage::extractRow(int imgi, string output_prefix){
		// make header file
		string header_filename = output_prefix + ".dat";
		ofstream ofile(header_filename.c_str());
		string out;
		ostringstream oss;
		oss << width;
		ostringstream os;
		//height is now number of images
		os << slices.size();
		out = oss.str() + " " + os.str() + " 1";
		ofile << out;

		// make output file
		string output_filename = output_prefix + ".raw";
		// open with binary flag
		ofstream offile(output_filename.c_str(), ios::out | ios::binary);
		int num = volNumberImages();
		int size = width*num;

		char output[size];
		int buff_cnt;
		for(int i = 0; i < num; i++){
			for(int j = 0; j < width; j++){
				output[buff_cnt] = slices[i][imgi][j];
				buff_cnt++;
			}
		}
		offile.write(output, size);
		offile.close();
	}

	// number of bytes used to store image data bytes and pointers
	int VolImage::volImageSize(void){
		int size = height*width;
		return size;
	}

	// number of images
	int VolImage::volNumberImages(void){
		int number = slices.size();
		return number;
	}