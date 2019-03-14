#include "ConvexPolygon.h"


using namespace std;


/*	Computes the 2D cross product of ab and ac vectors (z component).
 *	Returns a positive value if abc makes a counter-clockwise turn
 *	Returns a negative value if abc makes a clockwise turn
 */
static double cross_p(const Point& a, const Point& b, const Point& c) {
	return (b.X() - a.X()) * (c.Y() - a.Y()) - (b.Y() - a.Y()) * (c.X() - a.X());
}

/*	Compares two points using the x-coordinate first
 */
static bool compare(const Point& p, const Point& q) {
    if (p.X() < q.X() + 1e-12 and p.X() > q.X() - 1e-12) return p.Y() < q.Y();
    else return p.X() < q.X();
}

/* 	Returns the convex hull as a list of points in counter-clockwise order
 *	The convex hull of the points given is computed using 
 *	Andrew's monotone chain algorithm (n log n complexity)
 */
vector<Point> ConvexPolygon::convex_hull(vector<Point>& points) {
	sort(points.begin(), points.end(), compare);
	int n = points.size();

	// If the polygon has 2 or fewer points, points is already the desired output.
	if (n <= 2) return points;

	// Lower hull
	vector<Point> conv_hull(0);
	int hn = 0;	// The size of the hull
	for (int i=0; i<n; ++i) {
		while (hn >= 2 and cross_p(conv_hull[hn-2], conv_hull[hn-1], points[i]) <= 0) {
			conv_hull.pop_back(); --hn;
		}
		conv_hull.push_back(points[i]);
		++hn;
	}

	int lohusize = hn;	// Size of the lower hull

	// Upper hull
	for (int i=n-2; i>=0; --i) {
		while (hn > lohusize and cross_p(conv_hull[hn-2], conv_hull[hn-1], points[i]) <= 0) {
			conv_hull.pop_back(); --hn;
		}
		conv_hull.push_back(points[i]);
		++hn;
	}

	// The first and last points are the same
	conv_hull.pop_back();

	return conv_hull;
}



// Default constructor
ConvexPolygon::ConvexPolygon() {}

// Constructor
ConvexPolygon::ConvexPolygon(vector<Point>& points) {
	ord_vertices = convex_hull(points);
}

// Returns the vertices of the polygon in counter-clockwise order.
vector<Point> ConvexPolygon::vertices () const {
	return ord_vertices;
}

// Returns the perimeter of the polygon.
double ConvexPolygon::perimeter () const {
	double perim = 0;
	int n = ord_vertices.size();
	for (int i=0; i<n-1; ++i) {
		perim += ord_vertices[i].distance(ord_vertices[i+1]);
	}
	perim += ord_vertices[n-1].distance(ord_vertices[0]); // The distance between the first and last vertices
	return perim;
}

/* Returns the area of the polygon.
 * Substract and conquer approach. O(n) complexity.
 * Calculates the area of the triangles using Heron's formula.
 */
double ConvexPolygon::area () const {
	int n = ord_vertices.size();
	if (n < 3) return 0;
	if (n == 3) {
		double a = ord_vertices[0].distance(ord_vertices[1]);	// Lengths of
		double b = ord_vertices[1].distance(ord_vertices[2]);	// the sides of
		double c = ord_vertices[2].distance(ord_vertices[0]);	// the triangle
		double s = 0.5*perimeter();
		return sqrt(s*(s-a)*(s-b)*(s-c));
	}
	vector<Point> aux_vec = {ord_vertices[n-2], ord_vertices[n-1], ord_vertices[0]};
	vector<Point> aux_vec2 (&ord_vertices[0], &ord_vertices[n-1]);
	return (ConvexPolygon(aux_vec).area() + ConvexPolygon(aux_vec2).area());
}

// Returns the centroid of the polygon.
Point ConvexPolygon::centroid () const {
	double sum_x = 0, sum_y = 0;
	for (const Point& p : ord_vertices) {
		sum_x += p.X(); sum_y += p.Y();
	}
	int n = ord_vertices.size();
	sum_x /= n; sum_y /= n;
	return Point(sum_x, sum_y);
}

/* YET TO BE IMPLEMENTED */

/**
// Sets the color of the polygon.
void ConvexPolygon::set_color (double R, double G, double B) {
}

// Intersects this polygon with another one and returns this polygon.
ConvexPolygon& ConvexPolygon::operator*= (const ConvexPolygon& p) {
}

// Returns the intersection of this polygon with another one.
ConvexPolygon ConvexPolygon::operator* (const ConvexPolygon& p) const {
}

// Enlarges this, so it becomes a convex union of this with another polygon.
ConvexPolygon& ConvexPolygon::operator+= (const ConvexPolygon& p) {
}

// Returns the convex union of this and another polygon.
ConvexPolygon ConvexPolygon::operator+ (const ConvexPolygon& p) const {
}

// Tells whether a point is inside this polygon.
bool ConvexPolygon::is_inside (const Point& p) const {
}
*/
