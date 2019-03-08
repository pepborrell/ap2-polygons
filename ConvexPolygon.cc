#include "ConvexPolygon.h"


using namespace std;


/*	Computes the 2D cross product of ab and ac vectors (z component).
 *	Returns a positive value if abc makes a counter-clockwise turn
 *	Returns a negative value if abc makes a clockwise turn
 */
static double cross(const Point& a, const Point& b, const Point& c) {
	return (b.X() - a.X()) * (c.Y() - a.Y()) - (b.Y() - a.Y()) * (c.X() - a.X());
}

static bool compare(const Point& p, const Point& q) {
    if (p.X() < q.X() + 1e-12 and p.X() > q.X() - 1e-12) return p.Y() < q.Y();
    else return p.X() < q.X();
}


/* 	Returns the convex hull as a list of points in counter-clockwise order
 *	The convex hull of the points given is computed using 
 *	Andrew's monotone chain algorithm
 */
vector<Point> ConvexPolygon::convex_hull(vector<Point>& points) {
	sort(points.begin(), points.end(), compare);
	int n = points.size();

	vector<Point> lower_hull;
	int k = 0;	// The size of the lower hull
	for (int i=0; i<n; ++i) {
		while (k >= 2 and cross(lower_hull[k-2], lower_hull[k-1], points[i]) <= 0) {
			lower_hull.pop_back(); --k;
		}
		lower_hull[k++] = points[i];
	}

	vector<Point> upper_hull;
	k = 0;	// The size of the upper hull
	for (int i=n-1; i>=0; --i) {
		while (k >= 2 and cross(upper_hull[k-2], upper_hull[k-1], points[i]) <= 0) {
			upper_hull.pop_back(); --k;
		}
		upper_hull[k++] = points[i];
	}

	lower_hull.pop_back();	// The last point of each list is the first of the other
	upper_hull.pop_back();

	lower_hull.insert(lower_hull.end(), upper_hull.begin(), upper_hull.end());

	return lower_hull;
}

ConvexPolygon::ConvexPolygon(vector<Point>& points) {
	vertices = convex_hull(points);
}