# Makefile for obfusimg project

CXX = g++
CXXFLAGS = -std=c++23 -O3 -Wall
LDFLIBS = -lstdc++exp

all: obfusimg

obfusimg: obfusimg.o gilbert_curve.o stb_image.o stb_image_write.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLIBS)

obfusimg.o: obfusimg.cpp gilbert_curve.h stb_image.h stb_image_write.h
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(LDFLIBS)

gilbert_curve.o: gilbert_curve.cpp gilbert_curve.h
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(LDFLIBS)

stb_image.o: stb_image.cpp stb_image.h
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(LDFLIBS)

stb_image_write.o: stb_image_write.cpp stb_image_write.h
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(LDFLIBS)

clean:
	rm -f *.o

distclean: clean
	rm -f obfusimg

.PHONY: all clean distclean