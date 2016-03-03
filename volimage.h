/**
*.h Header file
* Carla Wilby 01/03/2016
*/

#ifndef VOLIMAGE_H
#define VOLIMAGE_H
#include <iostream>
#include <cstdlib>
#include <vector>

class VolImage
{
private:

	int width, height; // width and height of image stack
	std::vector<u_char**> slices; // data for each slice, in order

public:

	VolImage();
	~VolImage();

	// populate the object with images in stack
	bool readImages(std::string baseName);

	// compute difference map and write out
	void diffmap(int sliceI, int sliceJ, std::string output_prefix);

	// extract slice sliceId and write to output
	void extract(int sliceId, std::string output_prefix);

	// number of bytes uses to store image data bytes
	//and pointers (ignore vector<> container, dims etc)
	int volImageSize(void);
};
#endif
