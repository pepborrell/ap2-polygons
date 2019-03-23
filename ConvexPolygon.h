#ifndef ConvexPolygon_h
#define ConvexPolygon_h

#include <vector>
#include <algorithm>
#include <cmath>
#include <pngwriter.h>
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

	// Constructor
	ConvexPolygon(vector<Point>& points, bool points_sorted);

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

	// Sets and returns this as the smallest rectangle that contains all polygons. It also changes the coordinates
	// of the lower lefts and upper right.
	ConvexPolygon bounding_box (const vector<ConvexPolygon>& polygons, Point& LL, Point& UR); 

	// Tells whether a point is inside this polygon.
	bool p_is_inside (const Point& p) const;

	// Tells whether this polygon is inside a polygon.
	bool is_inside (const ConvexPolygon& cpol) const;

	// Draws the list of polygons given as input.
	void draw (const char* img_name, const vector<ConvexPolygon>& lpol);

	// Intersects this polygon with another one and returns this polygon.
	ConvexPolygon& operator*= (const ConvexPolygon& cpol);

	// Returns the intersection of this polygon with another one.
	ConvexPolygon operator* (const ConvexPolygon& cpol) const;

/**

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
	
	// Tells whether a point is inside a triangle by checking if all
	// vertex-vertex-point turns are counter-clockwise
	bool p_inside_triangle (const Point& p) const;

	// Returns the points of a polygon that are inside of this polygon.
	vector<Point> list_points_inside (const ConvexPolygon& cpol) const;

};

#endif
