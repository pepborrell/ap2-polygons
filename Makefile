# Defines the flags for compiling with C++.
CXXFLAGS = -Wall -std=c++11 -O2 -DNO_FREETYPE -I $(HOME)/libs/include 

# Rule to compile everything (make all).
# Because it is the first rule, it is also the default rule (make).
all: polygon_calculator

# Rule to clean object and executable files (make clean).
clean:
	rm -f polygon_calculator *.o *.png


# Rule to link the executable from then object files.
#
# The following default variables are used:
# 		$^ is the names of all the prerequisites
# 		$@ is the name of the target of the rule
# 		$(CXX) is the name of the C++ compiler

polygon_calculator: Point.o ConvexPolygon.o
	$(CXX) $^ -L $(HOME)/libs/lib -l PNGwriter -l png -o $@ -DNO_FREETYPE -I $(HOME)/libs/include 


## Dependencies between files
# (we don't need to precise how to produce them, Makefile already knows)

polygon_calculator: polygon_calculator.cc ConvexPolygon.h

Point.o: Point.cc Point.hh

ConvexPolygon.o: ConvexPolygon.cc ConvexPolygon.h