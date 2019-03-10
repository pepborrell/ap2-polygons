#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include "ConvexPolygon.h"

using namespace std;

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
	vector<Point> vertices = polygons[name].return_vertices();
	for (const Point& p : vertices) {
		cout << "  " << p.X() << ' ' << p.Y();
	}
	cout << endl;
}

int main() {
	map<string, ConvexPolygon> polygons;
	string action;
	while (cin >> action) {
		     if (action == "polygon")	polygon(polygons);
		else if (action == "print")		print(polygons);
	}
}