# Project: Implementation of the ConvexPolygon class

This project was required for the Algorithmics and Programming 2 course in the Data Science and Engineering Degree.

This project mainly consists of an implementation of the class `ConvexPolygon` (which, as its name might suggest, represents a 2-dimensional convex polygon in the plane) and a polygon calculator which performs operations with the previously implemented class. The specification and implementation of the class is found in the files called `ConvexPolygon.h` and `ConvexPolygon.cc`.

In order to complement the two main parts of the project, some test cases of different kind have been written. They are located in the folder named `test_cases`.

The class `Point` has been used as a means to make the implementation easier. This class was provided by [Jordi Petit](https://www.cs.upc.edu/~jpetit/) ([source](https://github.com/jordi-petit/ap2-moduls)) and further developed in order to satisfy some needs.

## Instructions for the installation and running of the project
These instructions are aimed at installing the files in a Unix-based operative system (namely Linux and Mac OS). The instructions given have to be performed using a terminal or a terminal emulator.

1. Create a temporary directory and download the pngwriter library:
```
git clone https://github.com/pngwriter/pngwriter.git
```

2. Compile the library:
```
# enter the newly downloaded repository
cd pngwriter

# prepare the compilation with some configuration
cmake -DPNGwriter_USE_FREETYPE=OFF -DCMAKE_INSTALL_PREFIX=$HOME/libs .

# compile the library
make

# install the library
make install
```

Now the downloaded code is no longer useful. You can delete the files by performing:
```
cd ..
rm -rf pngwriter
```

Now that the additional libraries needed have been installed, the compilation of the files in the project must be performed.

3. Assuming that the files are stored in the desired directory, execute the following commands:
```
make
```

Now the files must have been created. The calculator can now be tested using some of the test cases provided.

4. To use a test case and see its output:
```
./polygon_calculator < ./test_cases/<test_case_name>/input
```

To pipe its output to an output file:
```
./polygon_calculator < ./test_cases/<test_case_name>/input > ./test_cases/<test_case_name>/output
```

To compare its performance with the expected output:
```
diff ./test_cases/<test_case_name>/output ./test_cases/<test_case_name>/exptd_output -y
```

The lines that differ are indicated with a bar (`|`). The only thing that can differ a bit are the error messages because they are not fixed and depend on the implementation.

### Some additional tools
Some tools may be required during the compilation of the project:

+ Mac OS users: the following lines are a guide to installing `cmake` and `libpng`:
```
# installing brew (a package manager)
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"

# installing cmake and libpng
brew install cmake libpng
```

+ Ubuntu/Debian (or similar Linux distros) users: some packages may have to be installed:
```
sudo apt-get install cmake libpng16-tools libpng16-devtools
```

## Brief explanation of the commands and methods
The methods implemented in the `ConvexPolygon` class provide some useful operations that can be done with convex polygons, as well as tools to represent them and save them in files. The main scope of each method is documented in the implementation files. Here some explanation about the main algorithms used will be provided.

+ Convex Hull: The convex hull is computed using [Andrew's monotone chain algorithm](https://www.algorithmist.com/index.php/Monotone_Chain_Convex_Hull), which has `O(n log n)` complexity.

+ Area: It is calculated by a substract and conquer approach to the problem. It works by substracting triangles to the polygon, computing the area of each triangle and then adding all results. It has `O(n)` complexity.

+ Convex union: To find it, the Convex Hull of the points of both input polygons is computed. The result is the convex union of both. Complexity `O(n+m)`, where n and m are the vertices of both polygons.

+ Bounding box: Finds the higher and lower X and Y coordinates and returns the rectangle described by these coordinates.

+ Inside: To find whether a polygon is inside another one, the algorithm checks if each point of the polygon is inside the other. To see if a point is inside a polygon, the algorithm works by recursively dividing the polygon into two smaller polygons and a triangle and checking if the point is inside any of these. Overall computational cost: `O(n log n)`.

+ Intersection: It finds all vertices of each polygon that lay inside the other. Then checks for all possible intersection between sides of polygons. After this, the algorithm lists all these points and computes their Convex Hull. Complexity: `O(m n)`.

+ Regular: Checks if all sides and angles are the same.

The commands used to work with the calculator are those specified at the [formulation of the project](https://github.com/jordi-petit/ap2-poligons-2019#details-of-the-polygon-calculator). They have been implemented in such a way that nothing is changed and the instructions given are perfectly valid. The instructions will be listed below (for the exact behaviour of each command, see the project formulation). No information about the implementation of these commands is given, as they are simple applications for the already specified methods of the `ConvexPolygon` class.

+ polygon
+ print
+ area
+ perimeter
+ vertices
+ centroid
+ list
+ save
+ load
+ setcol
+ draw
+ intersection
+ union
+ inside
+ bbox
