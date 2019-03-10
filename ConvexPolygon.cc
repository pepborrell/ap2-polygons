#include "ConvexPolygon.h"


using namespace std;


/*	Computes the 2D cross product of ab and ac vectors (z component).
 *	Returns a positive value if abc makes a counter-clockwise turn
 *	Returns a negative value if abc makes a clockwise turn
 */
static double cross(const Point& a, const Point& b, const Point& c) {
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

	// Lower hull
	vector<Point> conv_hull(2*n);
	int k = 0;	// The size of the hull
	for (int i=0; i<n; ++i) {
		while (k >= 2 and cross(conv_hull[k-2], conv_hull[k-1], points[i]) <= 0) {
			conv_hull.pop_back(); --k;
		}
		conv_hull[k++] = points[i];
	}

	conv_hull.pop_back();	// The last point of the lower hull is the first of the upper one

	// Upper hull
	for (int i=n-1; i>=0; --i) {
		while (k >= 2 and cross(conv_hull[k-2], conv_hull[k-1], points[i]) <= 0) {
			conv_hull.pop_back(); --k;
		}
		conv_hull[k++] = points[i];
	}
	
	cerr << k << endl;

	conv_hull.resize(k-1);
	return conv_hull;
}

ConvexPolygon::ConvexPolygon(vector<Point> points) {
	vertices = convex_hull(points);
}

vector<Point> ConvexPolygon::return_vertices () const {
	return vertices;
}