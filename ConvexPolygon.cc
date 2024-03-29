#include "ConvexPolygon.h"


using namespace std;


/**	Computes the 2D cross product of ab and ac vectors (z component).
 *	Returns a positive value if abc makes a counter-clockwise turn
 *	Returns a negative value if abc makes a clockwise turn.
 *	| i   j   k   |
 *	| abx aby abz |
 *	| acx acy acz |
 */
static double cross_p(const Point& a, const Point& b, const Point& c) {
	return (b.X() - a.X()) * (c.Y() - a.Y()) - (b.Y() - a.Y()) * (c.X() - a.X());
}

/**	Compares two points using the x-coordinate first
 */
static bool compare(const Point& p, const Point& q) {
    if (p.X() < q.X() + 1e-12 and p.X() > q.X() - 1e-12) return p.Y() < q.Y();
    else return p.X() < q.X();
}

/** Returns the convex hull as a list of points in counter-clockwise order
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

/** Void constructor */
ConvexPolygon::ConvexPolygon() {}

/** Constructor */
ConvexPolygon::ConvexPolygon(vector<Point>& points) {
	theVertices = convex_hull(points);
}

/** Constructor */
ConvexPolygon::ConvexPolygon(vector<Point>& points, bool points_sorted) {
	if (not points_sorted) theVertices = convex_hull(points);
	else theVertices = points;
}

/** Returns the vertices of the polygon in counter-clockwise order. */
vector<Point> ConvexPolygon::vertices () const {
	return theVertices;
}

/** Removes last vertex of the vector of vertices. */
void ConvexPolygon::remove_last_vertex() {
	theVertices.pop_back();
}


/** Returns the perimeter of the polygon. 
 *  It does so by adding the distance between each two adjacent vertices.
 */
double ConvexPolygon::perimeter () const {
	double perim = 0;
	int n = theVertices.size();
	for (int i=0; i<n-1; ++i) {
		perim += theVertices[i].distance(theVertices[i+1]);
	}
	perim += theVertices[n-1].distance(theVertices[0]); // The distance between the first and last vertices
	return perim;
}

/* Returns the area of the polygon.
 * Substract and conquer approach. O(n) complexity.
 * Calculates the area of the triangles using Heron's formula.
 */
double ConvexPolygon::area () const {
	int n = theVertices.size();
	if (n < 3) return 0;
	if (n == 3) {
		double a = theVertices[0].distance(theVertices[1]);	// Lengths of
		double b = theVertices[1].distance(theVertices[2]);	// the sides of
		double c = theVertices[2].distance(theVertices[0]);	// the triangle
		double s = 0.5*perimeter();
		return sqrt(s*(s-a)*(s-b)*(s-c));
	}
	vector<Point> aux_vec = {theVertices[n-2], theVertices[n-1], theVertices[0]};
	ConvexPolygon polyg_copy = *this;
	polyg_copy.remove_last_vertex();
	return (ConvexPolygon(aux_vec).area() + ConvexPolygon(polyg_copy).area());
}

/** Returns the centroid of the polygon. */
Point ConvexPolygon::centroid () const {
	double sum_x = 0, sum_y = 0;
	for (const Point& p : theVertices) {
		sum_x += p.X(); sum_y += p.Y();
	}
	int n = theVertices.size();
	sum_x /= n; sum_y /= n;
	return Point(sum_x, sum_y);
}

/** Sets the color of the polygon. */
void ConvexPolygon::set_color (double R, double G, double B) {
	r = R; g = G; b = B;
}

/** Enlarges this, so it becomes a convex union of this with another polygon. */
ConvexPolygon& ConvexPolygon::operator+= (const ConvexPolygon& cpol) {
	// Concatenation of vectors of points
	for (const Point& p : cpol.theVertices) {
		theVertices.push_back(p);
	}
	theVertices = convex_hull(theVertices);
	return *this;
}


/** Returns the convex union of this and another polygon. */
ConvexPolygon ConvexPolygon::operator+ (const ConvexPolygon& cpol) const {
	ConvexPolygon dpol = cpol;
	dpol += *this;
	return dpol;
}

/** Sets and returns this as the smallest rectangle that contains all polygons. */
ConvexPolygon ConvexPolygon::bounding_box (const vector<ConvexPolygon>& polygons) {
	double x_min = polygons[0].vertices()[0].X(), x_max = x_min;
	double y_min = polygons[0].vertices()[0].Y(), y_max = y_min;
	for (const ConvexPolygon& cp : polygons) {
		for (const Point& p : cp.vertices()) {
			if (p.X() < x_min) x_min = p.X();
			else if (p.X() > x_max) x_max = p.X();
			if (p.Y() < y_min) y_min = p.Y();
			else if (p.Y() > y_max) y_max = p.Y();
		}
	}
	vector<Point> vertices_bbox = {Point(x_min, y_min), Point(x_max, y_min), Point(x_min, y_max), Point(x_max, y_max)};
	*this = ConvexPolygon(vertices_bbox);
	return *this;
}

/** Sets and returns this as the smallest rectangle that contains all polygons. Also changes the coordinates
 * of the lower left and upper right.
 */
ConvexPolygon ConvexPolygon::bounding_box (const vector<ConvexPolygon>& polygons, Point& LL, Point& UR) {
	double x_min = polygons[0].vertices()[0].X(), x_max = x_min;
	double y_min = polygons[0].vertices()[0].Y(), y_max = y_min;
	for (const ConvexPolygon& cp : polygons) {
		for (const Point& p : cp.vertices()) {
			if (p.X() < x_min) x_min = p.X();
			else if (p.X() > x_max) x_max = p.X();
			if (p.Y() < y_min) y_min = p.Y();
			else if (p.Y() > y_max) y_max = p.Y();
		}
	}
	LL = Point(x_min, y_min);
	UR = Point(x_max, y_max);
	vector<Point> vertices_bbox = {Point(x_min, y_min), Point(x_max, y_min), Point(x_min, y_max), Point(x_max, y_max)};
	*this = ConvexPolygon(vertices_bbox);
	return *this;
}

/** Tells whether a point is inside a triangle by checking if all
 * vertex-vertex-point turns are counter-clockwise.
 */
bool ConvexPolygon::p_inside_triangle(const Point& p) const {
	bool turn_a = cross_p(vertices()[0], vertices()[1], p) >= 1e-12;
	bool turn_b = cross_p(vertices()[1], vertices()[2], p) >= 1e-12;
	bool turn_c = cross_p(vertices()[2], vertices()[0], p) >= 1e-12;
	return turn_a and turn_b and turn_c;
}

/** Tells whether a point is inside this polygon. 
 *  It uses a divide and conquer algorithm that divides each polygon into
 *  two smaller ones and a triangle, then recursively checking for each one.
*/
bool ConvexPolygon::p_is_inside (const Point& p) const {
	int n = vertices().size();
	if (n < 3) {
		// If both points are the same
		if (n == 1 and abs(vertices()[0].X()-p.X()) < 1e-12 and abs(vertices()[0].Y()-p.Y()) < 1e-12) return true;
		// The three points are collinear
		if (n == 2 and abs(cross_p(vertices()[0], vertices()[1], p)) < 1e-12) return true;
		return false;
	}
	if (n == 3) return p_inside_triangle(p);
	else {
		auto middle = vertices().begin() + n/2;
		vector<Point> v1(vertices().begin(), middle);
		vector<Point> v2(middle, vertices().end()); v2.push_back(vertices()[0]);
		vector<Point> vtriangle = {*(middle-1), *middle, vertices()[0]};
		ConvexPolygon cpol1(v1, true);
		ConvexPolygon cpol2(v2, true);
		ConvexPolygon triangle(vtriangle, true);
		return triangle.p_inside_triangle(p) or cpol1.p_is_inside(p) or cpol2.p_is_inside(p);
	}
}

/** Tells whether this polygon is inside the input polygon.
 *  Checks for all vertices of this polygon.
 */
bool ConvexPolygon::is_inside (const ConvexPolygon& cpol) const {
	bool inside = true;
	for (const Point& p : vertices()) if (not cpol.p_is_inside(p)) inside = false;
	return inside;
}

/** Draws the list of polygons given as input. */
void ConvexPolygon::draw (const char* img_name, const vector<ConvexPolygon>& lpol) const {
	Point LL, UR;
	ConvexPolygon box;
	box.bounding_box(lpol, LL, UR);
	const int size = 500;
	int scale = min(((size-4))/(UR.Y()-LL.Y()), ((size-4))/(UR.X()-LL.X())); // Scale factor: to fill the whole space.
	Point centroid = box.centroid();
	Point scaled_centroid = Point(scale*(centroid.X() - LL.X()) + 2, scale*(centroid.Y() - LL.Y()) + 2);
	Point displacement = Point(250, 250) - scaled_centroid; // Used to center all elements in the image.
	pngwriter png(size, size, 1.0, img_name);
	for (const ConvexPolygon& pol : lpol) {
		int n = pol.vertices().size(); ++n;
		int points[2*n], i=0;
		for (const Point& p : pol.vertices()) {
			points[i++] = scale*(p.X() - LL.X()) + 2 + displacement.X();
			points[i++] = scale*(p.Y() - LL.Y()) + 2 + displacement.Y();
		}
		points[i++] = scale*(pol.vertices()[0].X() - LL.X()) + 2 + displacement.X();
		points[i++] = scale*(pol.vertices()[0].Y() - LL.Y()) + 2 + displacement.Y();
		png.polygon(points, n, pol.r, pol.g, pol.b);
	}
	png.close();
}

/** Returns true if an intersection between the given lines (r and s) is found and, 
 *  if true, places its value in the intersection variable.
 */
static bool intersection_segments (const Point& r1, const Point& r2, const Point& s1, const Point& s2, Point& intersection) {
	// Finding the two lines that lay on the points
	double rA = r2.Y() - r1.Y();
	double rB = r1.X() - r2.X();
	double rC = rA*r1.X() + rB*r1.Y();

	double sA = s2.Y() - s1.Y();
	double sB = s1.X() - s2.X();
	double sC = sA*s1.X() + sB*s1.Y();

	// Solving the system using Cramer's rule
	double det = rA*sB - rB*sA;
	if (abs(det) < 1e-12) return false; // Parallel lines

	double x = (sB*rC - rB*sC)/det;
	double y = (rA*sC - sA*rC)/det;
	intersection = Point{x, y};

	vector<Point> bbox_vert = {r1, r2, s1, s2};
	ConvexPolygon bbox(bbox_vert);
	if (bbox.p_is_inside(intersection)) return true;
	return false;
}

/** Returns the points of a polygon that are inside of this polygon. */
vector<Point> ConvexPolygon::list_points_inside (const ConvexPolygon& cpol) const {
	vector<Point> v;
	for (const Point& p : cpol.vertices()) {
		if (p_is_inside(p)) v.push_back(p);
	}
	return v;
}

/** Intersects this polygon with another one and returns this polygon.
 *  It finds the vertices of one polygon that lay inside of the other. It then checks
 *  for all possible intersections between sides and adds them to the list. It finally
 *  computes the convex hull of all points and returns it.
 */
ConvexPolygon& ConvexPolygon::operator*= (const ConvexPolygon& cpol) {
	vector<Point> intersection_vertices;

	// Finding the vertices that lay inside a polygon.
	vector<Point> pts_inside = cpol.list_points_inside(*this);
	intersection_vertices.insert(intersection_vertices.end(), pts_inside.begin(), pts_inside.end());
	pts_inside = list_points_inside(cpol);
	intersection_vertices.insert(intersection_vertices.end(), pts_inside.begin(), pts_inside.end());

	// Checking all intersections of sides of the polygons.
	int n = vertices().size(), m = cpol.vertices().size();
	for (int i=0, ii=n-1; i<n; ii=i++) {
		for (int j=0, jj=m-1; j<m; jj=j++) {
			Point intersection;
			if (intersection_segments(vertices()[ii], vertices()[i], cpol.vertices()[jj], cpol.vertices()[j], intersection)) {
				intersection_vertices.push_back(intersection);
			}
		}
	}
	theVertices = ConvexPolygon(intersection_vertices).vertices();
	return *this;
}

/** Returns the intersection of this polygon with another one. */
ConvexPolygon ConvexPolygon::operator* (const ConvexPolygon& cpol) const {
	ConvexPolygon dpol = cpol;
	dpol *= *this;
	return dpol;
}

/** Tells whether the polygon is regular or not. 
 *  It first checks for all sides then for all angles.
 */
bool ConvexPolygon::is_regular () const {
	// Checking for all sides
	int n = vertices().size();
	double dist = vertices()[n-1].distance(vertices()[0]);
	for (int i=1, ii=0; i<n; ii=i++) {
		if (abs(dist - vertices()[ii].distance(vertices()[i])) > 1e-12) return false;
	}

	// Checking for all angles using the cross product.
	// Precondition: if all sides are equal, the cross products depends only on the angle.
	double cross = cross_p(vertices()[n-2], vertices()[n-1], vertices()[0]);
	for (int i=1, ii = 0, iii = n-1; i<n; iii=ii, ii=i++) {
		if (abs(cross - cross_p(vertices()[iii], vertices()[ii], vertices()[i])) > 1e-12) return false;
	}
	return true;
}
