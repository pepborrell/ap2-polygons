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

	// Sets the color of the polygon.
	void set_color (double R, double G, double B);

	// Enlarges this, so it becomes a convex union of this with another polygon.
	ConvexPolygon& operator+= (const ConvexPolygon& cpol);

	// Returns the convex union of this and another polygon.
	ConvexPolygon operator+ (const ConvexPolygon& cpol) const;

	// Returns the smallest rectangle (as a polygon of 4 vertices) that contains all polygons.
	ConvexPolygon bounding_box (const vector<ConvexPolygon>& polygons);

/**

	// Intersects this polygon with another one and returns this polygon.
	ConvexPolygon& operator*= (const ConvexPolygon& p);

	// Returns the intersection of this polygon with another one.
	ConvexPolygon operator* (const ConvexPolygon& p) const;

	// Tells whether a point is inside this polygon.
	bool p_is_inside (const Point& p) const;

	// Tells whether one polygon is inside this polygon.
	bool cp_is_inside (const ConvexPolygon& cpol) const;

	// Tells whether one of the two polygons given as input is inside the other.
	bool is_inside (const ConvexPolygon& cp1, const ConvexPolygon& cp2);

	// Tells whether the polygon is regular or not.
	bool regular () const;

*/

private:

	// Collection of the vertices of the polygon ordered counter-clockwise.
	vector<Point> theVertices;

	// Colour of the polygon
	double r, g, b;

	// Calculates the convex hull of a given set of points.
	vector<Point> convex_hull(vector<Point>& points);
	
	// Removes last point of the vector of vertices.
	void remove_last_vertex ();

};

#endif
