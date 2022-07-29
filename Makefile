CXX ?= clang++
CXXFLAGS ?= -std=c++1y -c -g -O0 -Wall -Wextra -pedantic 
LD = $(CXX)
LDFLAGS ?= -std=c++1y -lpthread -lm

EXE = pngquadtree
EXECOMP = pngquadtree-comp
EXETEST = pngquadtree-test

OBJS = src/RGBAPixel.o src/lodepng.o src/PNG.o src/qtvar.o src/qtcount.o src/quadtree.o src/stats.o
OBJS_EXE = src/main.o
OBJS_COMP = src/compare.o
OBJS_EXETEST = src/test.o

all : $(EXE) $(EXECOMP) $(EXETEST)

$(EXE) : $(OBJS) $(OBJS_EXE)
	$(LD) $^ $(LDFLAGS) -o $@

$(EXECOMP) : $(OBJS) $(OBJS_COMP)
	$(LD) $^ $(LDFLAGS) -o $@

$(EXETEST) : $(OBJS) $(OBJS_EXETEST)
	$(LD) $^ $(LDFLAGS) -o $@

#object files
src/RGBAPixel.o : src/cs221util/RGBAPixel.cpp src/cs221util/RGBAPixel.h
	$(CXX) $(CXXFLAGS) $< -o $@

src/PNG.o : src/cs221util/PNG.cpp src/cs221util/PNG.h src/cs221util/RGBAPixel.h src/cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) $< -o $@

src/lodepng.o : src/cs221util/lodepng/lodepng.cpp src/cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) $< -o $@

src/stats.o : src/stats.cpp src/stats.h src/cs221util/RGBAPixel.h src/cs221util/PNG.h
	$(CXX) $(CXXFLAGS) $< -o $@

src/quadtree.o : src/quadtree.cpp src/quadtree.h src/stats.h src/cs221util/PNG.h src/cs221util/RGBAPixel.h
	$(CXX) $(CXXFLAGS) $< -o $@

src/qtvar.o : src/qtvar.cpp src/qtvar.h src/quadtree.h src/stats.h src/cs221util/PNG.h src/cs221util/RGBAPixel.h
	$(CXX) $(CXXFLAGS) $< -o $@

src/qtcount.o : src/qtcount.cpp src/qtcount.h src/quadtree.h src/stats.h src/cs221util/PNG.h src/cs221util/RGBAPixel.h
	$(CXX) $(CXXFLAGS) $< -o $@

src/main.o : src/main.cpp src/cs221util/PNG.h src/cs221util/RGBAPixel.h src/quadtree.h src/qtcount.h src/qtvar.h
	$(CXX) $(CXXFLAGS) $< -o $@

src/compare.o : src/compare.cpp src/cs221util/PNG.h src/cs221util/RGBAPixel.h src/quadtree.h src/qtcount.h src/qtvar.h
	$(CXX) $(CXXFLAGS) $< -o $@

src/test.o : src/test.cpp src/cs221util/PNG.h src/cs221util/RGBAPixel.h src/quadtree.h src/qtcount.h src/qtvar.h
	$(CXX) $(CXXFLAGS) $< -o $@

clean :
	-rm -f $(OBJS) $(OBJS_EXE) $(OBJS_COMP) $(OBJS_EXETEST) $(EXE) $(EXECOMP) $(EXETEST)
