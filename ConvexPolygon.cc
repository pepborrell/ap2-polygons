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

// Constructor
ConvexPolygon::ConvexPolygon(vector<Point>& points) {
	vertices = convex_hull(points);
}

// Another constructor
ConvexPolygon::ConvexPolygon() {
}

// Returns the vertices of the polygon in counter-clockwise order.
vector<Point> ConvexPolygon::return_vertices () const {
	return vertices;
}