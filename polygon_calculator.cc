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

string vert_output(const string& name, const ConvexPolygon& polyg) {
	ostringstream oss;
	oss.setf(ios::fixed);
    oss.precision(3);
	oss << name;
	vector<Point> vert = polyg.vertices();
	for (const Point& p : vert) {
		oss << "  " << p.X() << ' ' << p.Y();
	}
	oss << endl;
	return oss.str();
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

void list(const map<string, ConvexPolygon>& polygons) {
	for (const auto& elem : polygons) {
		cout << elem.first << endl;
	}
}

void save(map<string, ConvexPolygon>& polygons) {
	string filename;
	cin >> filename;
	string s;
	getline(cin, s);
	istringstream iss(s);
	string name;
	ofstream f(filename);
	while (iss >> name) {
		f << vert_output(name, polygons[name]);
	}
	f.close();
}

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
		string sx, sy;
		while (iss >> sx >> sy) {
			points.push_back(Point(stod(sx), stod(sy)));
		}
		polygons[name] = ConvexPolygon(points, true);
	}
}

void setcol(map<string, ConvexPolygon>& polygons) {
	string name;
	cin >> name;
	double r, g, b;
	cin >> r >> g >> b;
	polygons[name].set_color(r, g, b);
}

void draw(map<string, ConvexPolygon>& polygons) {
	string img_name;
	cin >> img_name;
	string s;
	getline(cin, s);
	istringstream iss(s);
	vector<ConvexPolygon> pols;
	string name;
	while (iss >> name) {
		pols.push_back(polygons[name]);
	}
	polygons[name].draw(img_name.c_str(), pols);
}

void p_union(map<string, ConvexPolygon>& polygons) {
	string result_name;
	cin >> result_name;
	string s;
	getline(cin, s);
	istringstream iss(s);
	string pol;
	while(iss >> pol) polygons[result_name] += polygons[pol];
}

void inside(map<string, ConvexPolygon>& polygons) {
	string name1, name2;
	cin >> name1 >> name2;
	cout << polygons[name1].is_inside(polygons[name2]) << endl;
}

void bbox(map<string, ConvexPolygon>& polygons) {
	string name;
	cin >> name;
	// Building a vector of all polygons.
	vector<ConvexPolygon> cpols;
	string s;
	getline(cin, s);
	istringstream iss(s);
	string pol_name;
	while(iss >> pol_name) {
		cpols.push_back(polygons[pol_name]);
	}
	polygons[name].bounding_box(cpols);
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
		// else if (action == "intersection")	intersection(polygons);
		else if (action == "union")		p_union(polygons);
		else if (action == "inside")	inside(polygons);
		else if (action == "bbox") bbox(polygons);
		else {
			string s;
			getline(cin, s);
			cout << "error: unrecognized command" << endl;
		}
	}
}
