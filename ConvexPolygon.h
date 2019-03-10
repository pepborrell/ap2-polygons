#ifndef ConvexPolygon_h
#define ConvexPolygon_h

#include <vector>
#include <algorithm>
#include "Point.hh"

#include <iostream> // Remove this along with all cout's and cerr's

using namespace std;

/* 	This class stores a two dimensional convex polygon
	and provides some operations that can be done with it.
*/

class ConvexPolygon {

public:

	// Constructor
	ConvexPolygon(vector<Point> points);

	vector<Point> return_vertices () const;


private:

	// Collection of the vertices of the polygon ordered counter-clockwise.
	vector<Point> vertices;

	// Calculates the convex hull of a given set of points.
	vector<Point> convex_hull(vector<Point>& points);

};

#endif