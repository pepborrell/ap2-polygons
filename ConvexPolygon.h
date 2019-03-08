#ifndef ConvexPolygon_h
#define ConvexPolygon_h

#include <vector>
#include <algorithm>
#include "Point.hh"

using namespace std;

/* 	This class stores a two dimensional convex polygon
	and provides some operations that can be done with it.
*/

class ConvexPolygon {

public:

	// Constructor
	ConvexPolygon(vector<Point>& points);


private:

	// Collection of the vertices of the polygon ordered counter-clockwise.
	vector<Point> vertices;

	vector<Point> convex_hull(vector<Point>& points);

};

#endif