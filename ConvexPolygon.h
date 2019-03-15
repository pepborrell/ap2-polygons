#ifndef ConvexPolygon_h
#define ConvexPolygon_h

#include <vector>
#include <algorithm>
#include <cmath>
#include "Point.hh"

#include <iostream> // Delete this and all cerr's

using namespace std;

/* 	This class stores a two dimensional convex polygon
 *	and provides some operations that can be done with it.
 */

class ConvexPolygon {

public:

	// Default constructor
	ConvexPolygon();

	// Constructor
	ConvexPolygon(vector<Point>& points);

	// Returns the vertices of the polygon in counter-clockwise order.
	vector<Point> vertices () const;

	// Returns the perimeter of the polygon.
	double perimeter () const;

	// Returns the area of the polygon.
	double area () const;

	// Returns the centroid of the polygon.
	Point centroid () const;

/**

	// Sets the color of the polygon.
	void set_color (double R, double G, double B);

	// Intersects this polygon with another one and returns this polygon.
	ConvexPolygon& operator*= (const ConvexPolygon& p);

	// Returns the intersection of this polygon with another one.
	ConvexPolygon operator* (const ConvexPolygon& p) const;

	// Enlarges this, so it becomes a convex union of this with another polygon.
	ConvexPolygon& operator+= (const ConvexPolygon& p);

	// Returns the convex union of this and another polygon.
	ConvexPolygon operator+ (const ConvexPolygon& p) const;

	// Tells whether a point is inside this polygon.
	bool is_inside (const Point& p) const;

*/

private:

	// Collection of the vertices of the polygon ordered counter-clockwise.
	vector<Point> ord_vertices;

	// Colour of the polygon
	double r, g, b;

	// Calculates the convex hull of a given set of points.
	vector<Point> convex_hull(vector<Point>& points);
	
	// Removes last point of the vector of vertices.
	void remove_last_vertex ();

};

#endif
