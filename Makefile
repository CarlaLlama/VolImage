CXX=g++

volimg:	volimage.o driver.o
	$(CXX) volimage.o driver.o -o volimage

volimage.o:	volimage.cpp volimage.h
	$(CXX) volimage.cpp -c

driver.o: driver.cpp volimage.h
	$(CXX) driver.cpp -c

clean:
	@rm -f *.o volimage
