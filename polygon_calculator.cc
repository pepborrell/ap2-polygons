#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <fstream>

#include "ConvexPolygon.h"

using namespace std;

void comment() {
	cout << '#' << endl;
	string s;
	getline(cin, s);
}

// To define a polygon
void polygon(map<string, ConvexPolygon>& polygons) {
	string s;
	getline(cin, s);
	istringstream iss(s);

	string name;
	iss >> name;
	vector<Point> v;
	double x, y;
	while (iss.rdbuf()->in_avail()) { // Istringstream is not empty

		// Error handling
		if (!(iss >> x >> y)) {
			cout << "error: command with wrong number or type of arguments" << endl;
			return;
		}
		v.push_back(Point(x,y));
	}
	ConvexPolygon polyg(v);
	polygons[name] = polyg;
	cout << "ok" << endl;
}

// Prints a polygon in clockwise order
void print(map<string, ConvexPolygon>& polygons) {
	string s;
	getline(cin, s);
	istringstream iss(s);
	string name;
	iss >> name;

	// Error handling
	if (polygons.count(name) == 0) {
		cout << "error: undefined polygon identifier" << endl;
		return;
	}

	cout << name;
	vector<Point> vert = polygons[name].vertices();

	// Printing in clockwise order
	cout << ' ' << vert[0].X() << ' ' << vert[0].Y();
	reverse(vert.begin(), vert.end());
	vert.pop_back();
	for (const Point& p : vert) {
		cout << ' ' << p.X() << ' ' << p.Y();
	}
	cout << endl;
}

// Prints the area of the polygon
void area(map<string, ConvexPolygon>& polygons) {
	string s;
	getline(cin, s);
	istringstream iss(s);
	string name;
	iss >> name;

	// Error handling
	if (polygons.count(name) == 0) {
		cout << "error: undefined polygon identifier" << endl;
		return;
	}

	cout << polygons[name].area() << endl;
}

// Prints the perimeter
void perimeter(map<string, ConvexPolygon>& polygons) {
	string s;
	getline(cin, s);
	istringstream iss(s);
	string name;
	iss >> name;

	// Error handling
	if (polygons.count(name) == 0) {
		cout << "error: undefined polygon identifier" << endl;
		return;
	}
	
	cout << polygons[name].perimeter() << endl;
}

// Prints the number of vertices of the polygon
void n_vertices(map<string, ConvexPolygon>& polygons) {
	string s;
	getline(cin, s);
	istringstream iss(s);
	string name;
	iss >> name;

	// Error handling
	if (polygons.count(name) == 0) {
		cout << "error: undefined polygon identifier" << endl;
		return;
	}
	
	cout << polygons[name].vertices().size() << endl;
}

// Prints the centroid
void centroid(map<string, ConvexPolygon>& polygons) {
	string s;
	getline(cin, s);
	istringstream iss(s);
	string name;
	iss >> name;

	// Error handling
	if (polygons.count(name) == 0) {
		cout << "error: undefined polygon identifier" << endl;
		return;
	}
	
	cout << polygons[name].centroid().X() << " " << polygons[name].centroid().Y() << endl;
}

// Lists all polygons
void list(const map<string, ConvexPolygon>& polygons) {
	bool first = true;
	for (const auto& elem : polygons) {
		if (not first) cout << ' ';
		else first = false;
		cout << elem.first;
	}
	cout << endl;
}

// Returns a string with the output that would be printed when print is called.
string vert_output(const string& name, const ConvexPolygon& polyg) {
	ostringstream oss;
	oss.setf(ios::fixed);
	oss.precision(3);

	oss << name;
	vector<Point> vert = polyg.vertices();

	// Printing in clockwise order
	oss << ' ' << vert[0].X() << ' ' << vert[0].Y();
	reverse(vert.begin(), vert.end());
	vert.pop_back();
	for (const Point& p : vert) {
		oss << ' ' << p.X() << ' ' << p.Y();
	}
	oss << endl;

	return oss.str();
}

// Saves the polygons in a file
void save(map<string, ConvexPolygon>& polygons) {
	string filename;
	cin >> filename;
	string s;
	getline(cin, s);
	istringstream iss(s);
	string name;
	ofstream f(filename);
	while (iss >> name) {

		// Error handling
		if (polygons.count(name) == 0) {
			cout << "error: undefined polygon identifier" << endl;
			return;
		}
		
		f << vert_output(name, polygons[name]);
	}
	f.close();
	cout << "ok" << endl;
}

// Loads the polygons from a file. In case they are not sorted,
// the ConvexPolygon constructor is set to false.
void load(map<string, ConvexPolygon>& polygons) {
	string filename;
	cin >> filename;
	ifstream f(filename);
	string gl;
	while (getline(f, gl)) {
		istringstream iss(gl);
		string name;
		iss >> name;
		vector<Point> points;
		double x, y;
		while (iss.rdbuf()->in_avail()) { // There are still elements in the istringstream

			// Error handling
			if (!(iss >> x >> y)) {
				cout << "error: wrong format" << endl;
				return;
			}

			points.push_back(Point(x, y));
		}
		polygons[name] = ConvexPolygon(points, false);
	}
	cout << "ok" << endl;
}

// Sets the color of the polygon
void setcol(map<string, ConvexPolygon>& polygons) {
	string s;
	getline(cin, s);
	istringstream iss(s);
	string name;
	iss >> name;
	
	// Error handling
	if (polygons.count(name) == 0) {
		cout << "error: undefined polygon identifier" << endl;
		return;
	}
	
	double r, g, b;

	// Error handling
	if (!(iss >> r >> g >> b)) {
		cout << "error: command with wrong number or type of arguments" << endl;
		return;
	}

	polygons[name].set_color(r, g, b);
	cout << "ok" << endl;
}

// Draws the polygons given
void draw(map<string, ConvexPolygon>& polygons) {
	string img_name;
	cin >> img_name;
	string s;
	getline(cin, s);
	istringstream iss(s);
	vector<ConvexPolygon> pols;
	string name;
	while (iss >> name) {

		// Error handling
		if (polygons.count(name) == 0) {
			cout << "error: undefined polygon identifier" << endl;
			return;
		}
		
		pols.push_back(polygons[name]);
	}
	polygons[name].draw(img_name.c_str(), pols);
	cout << "ok" << endl;
}

// Computes the intersection of the two polygons given as input.
// If the input consists of 2 polygons the first is redefined as the intersection.
// If the input are 3 polygons, the first is redefined as the intersection of the other ones.
void intersection(map<string, ConvexPolygon>& polygons) {
	string s;
	getline(cin, s);
	istringstream iss(s);
	string name1;
	iss >> name1;

	// Error handling
	if (polygons.count(name1) == 0) {
		cout << "error: undefined polygon identifier" << endl;
		return;
	}
	vector<string> names;
	int i = 0;
	while (iss >> s) {

		// Error handling
		if (polygons.count(s) == 0) {
			cout << "error: undefined polygon identifier" << endl;
			return;
		}

		names.push_back(s); ++i;
	}
	if (i == 1) polygons[name1] *= polygons[names[0]];
	else polygons[name1] = polygons[names[0]] * polygons[names[1]];
	cout << "ok" << endl;
}

// Computes the convex union of the two polygons given as input.
// If the input consists of 2 polygons the first is redefined as the convex union.
// If the input are 3 polygons, the first is redefined as the convex union of the other ones.
void p_union(map<string, ConvexPolygon>& polygons) {
	string s;
	getline(cin, s);
	istringstream iss(s);
	string result_name;
	iss >> result_name;

	// Error handling
	if (polygons.count(result_name) == 0) {
		cout << "error: undefined polygon identifier" << endl;
		string s;
		getline(cin, s);
		return;
	}
	
	vector<string> names;
	int i = 0;
	while(iss >> s) {

		// Error handling
		if (polygons.count(s) == 0) {
			cout << "error: undefined polygon identifier" << endl;
			return;
		}

		names.push_back(s); ++i;
	}
	if (i == 1) polygons[result_name] += polygons[names[0]];
	else polygons[result_name] = polygons[names[0]] + polygons[names[1]];
	cout << "ok" << endl;
}

// Prints if the first polygon is inside the second one
void inside(map<string, ConvexPolygon>& polygons) {
	string s;
	getline(cin, s);
	istringstream iss(s);
	string name1, name2;
	iss >> name1 >> name2;

	// Error handling
	if (polygons.count(name1) == 0 or polygons.count(name2) == 0) {
		cout << "error: undefined polygon identifier" << endl;
		return;
	}
	
	cout << (polygons[name1].is_inside(polygons[name2]) ? "yes" : "no") << endl;
}

// Defines the first polygon as the bounding box of the subsequent ones.
void bbox(map<string, ConvexPolygon>& polygons) {
	string s;
	getline(cin, s);
	istringstream iss(s);
	string name;
	iss >> name;

	// Building a vector of all polygons.
	vector<ConvexPolygon> cpols;
	string pol_name;
	while(iss >> pol_name) {

		// Error handling
		if (polygons.count(pol_name) == 0) {
			cout << "error: undefined polygon identifier" << endl;
			return;
		}

		cpols.push_back(polygons[pol_name]);
	}
	polygons[name].bounding_box(cpols);
	cout << "ok" << endl;
}

// Prints if the polygon is regular
void regular(map<string, ConvexPolygon>& polygons) {
	string s;
	getline(cin, s);
	istringstream iss(s);
	string name;
	iss >> name;

	// Error handling
	if (polygons.count(name) == 0) {
		cout << "error: undefined polygon identifier" << endl;
		return;
	}

	cout << (polygons[name].is_regular() ? "yes" : "no") << endl;
}

int main() {
	cout.setf(ios::fixed);
    cout.precision(3);
	map<string, ConvexPolygon> polygons;
	string action;
	while (cin >> action) {
			 if (action == "#")			comment();
		else if (action == "polygon")	polygon(polygons);
		else if (action == "print")		print(polygons);
		else if (action == "area")		area(polygons);
		else if (action == "perimeter")	perimeter(polygons);
		else if (action == "vertices")	n_vertices(polygons);
		else if (action == "centroid")	centroid(polygons);
		else if (action == "list")		list(polygons);
		else if (action == "save")		save(polygons);
		else if (action == "load")		load(polygons);
		else if (action == "setcol")	setcol(polygons);
		else if (action == "draw")		draw(polygons);
		else if (action == "intersection")	intersection(polygons);
		else if (action == "union")		p_union(polygons);
		else if (action == "inside")	inside(polygons);
		else if (action == "bbox") bbox(polygons);
		else if (action == "regular") regular(polygons);

		// Error handling
		else {
			string s;
			getline(cin, s);
			cout << "error: unrecognized command" << endl;
		}
	}
}
