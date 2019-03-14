#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include "ConvexPolygon.h"

using namespace std;

void comment() {
	cout << '#' << endl;
	string s;
	getline(cin, s);
}

void polygon(map<string, ConvexPolygon>& polygons) {
	string name;
	cin >> name;
	vector<Point> v;
	string s;
	getline(cin, s);
	istringstream iss(s);
	double x, y;
	while(iss >> x >> y) {
		v.push_back(Point(x,y));
	}
	ConvexPolygon polyg(v);
	polygons[name] = polyg;
}

void print(map<string, ConvexPolygon>& polygons) {
	string name;
	cin >> name;
	cout << name;
	vector<Point> vert = polygons[name].vertices();
	for (const Point& p : vert) {
		cout << "  " << p.X() << ' ' << p.Y();
	}
	cout << endl;
}

void area(map<string, ConvexPolygon>& polygons) {
	string name;
	cin >> name;
	cout << polygons[name].area() << endl;
}

void perimeter(map<string, ConvexPolygon>& polygons) {
	string name;
	cin >> name;
	cout << polygons[name].perimeter() << endl;
}

void n_vertices(map<string, ConvexPolygon>& polygons) {
	string name;
	cin >> name;
	cout << polygons[name].vertices().size() << endl;
}

void centroid(map<string, ConvexPolygon>& polygons) {
	string name;
	cin >> name;
	cout << polygons[name].centroid().X() << " " << polygons[name].centroid().Y() << endl;
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
		// else if (action == "list")		list(polygons);
		// else if (action == "save")		save(polygons);
		// else if (action == "load")		load(polygons);
		// else if (action == "setcol")	setcol(polygons);
		// else if (action == "draw")		draw(polygons);
		// else if (action == "intersection")	intersection(polygons);
		// else if (action == "union")		p_union(polygons);
		// else if (action == "inside")	inside(polygons);
		else {
			string s;
			getline(cin, s);
			cout << "error: unrecognized command" << endl;
		}
	}
}
