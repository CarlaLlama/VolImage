/**
*.h Header file
* Carla Wilby 01/03/2016
*/

#ifndef VOLIMAGE_H
#define VOLIMAGE_H
#include <iostream>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <sstream>

class VolImage
{
private:

	int width, height; // width and height of image stack
	std::vector<u_char**> slices; // data for each slice, in order

public:

	VolImage();
	~VolImage();

	// Populate the object with images in stack
	bool readImages(std::string baseName);

	// Compute difference map and write to output file
	void diffmap(int sliceI, int sliceJ, std::string output_prefix);

	// Extract slice sliceId and write to output file
	void extract(int sliceId, std::string output_prefix);

	// Extract an image across row, across all slices and write to output file
	void extractRow(int imgi, std::string output_prefix);

	// Number of bytes uses to store image data bytes and pointers
	int volImageSize(void);

	// Number of images in stack
	int volNumberImages(void);
};
#endif
