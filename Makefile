# Makefile for obfusimg project

ifeq ($(OS),Windows_NT)
    RM = del /Q /F
    EXE = .exe
else
    RM = rm -f
    EXE =
endif

CXX = g++
CXXFLAGS = -std=c++23 -O3 -Wall
LDFLIBS = -lstdc++exp
DOC_DIR = doc
DOC = obfusimg-doc
TEXFLAGS = -cd -xelatex -interaction=nonstopmode -halt-on-error

all: obfusimg$(EXE) doc

obfusimg$(EXE): obfusimg.o permutation.o gilbert_curve.o chaos.o stb_image.o stb_image_write.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLIBS)

obfusimg.o: obfusimg.cpp permutation.h gilbert_curve.h chaos.h stb_image.h stb_image_write.h
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(LDFLIBS)

permutation.o: permutation.cpp permutation.h
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(LDFLIBS)

gilbert_curve.o: gilbert_curve.cpp gilbert_curve.h
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(LDFLIBS)

chaos.o: chaos.cpp chaos.h
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(LDFLIBS)

stb_image.o: stb_image.cpp stb_image.h
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(LDFLIBS)

stb_image_write.o: stb_image_write.cpp stb_image_write.h
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(LDFLIBS)

$(DOC_DIR)/$(DOC).pdf: $(DOC_DIR)/$(DOC).tex
	latexmk $(TEXFLAGS) $(DOC_DIR)/$(DOC).tex

doc: $(DOC_DIR)/$(DOC).pdf

clean:
	-$(RM) *.o
	latexmk -cd -c $(DOC_DIR)/$(DOC).tex

distclean: clean
	-$(RM) obfusimg$(EXE)
	latexmk -cd -C $(DOC_DIR)/$(DOC).tex

.PHONY: all clean distclean doc