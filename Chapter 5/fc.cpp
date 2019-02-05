/*
ID: Kevun1
LANG: C++11
TASK: fc
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <utility>
#include <numeric>
#include <iomanip>
using namespace std;


//ifstream fin("in.txt");
//ofstream fout("out.txt");
ifstream fin("fc.in");
ofstream fout("fc.out");

//euclidean distance between point a and b
double distance(pair<double, double> a, pair<double, double> b) {
	return sqrt(pow((a.first - b.first), 2) + pow((a.second - b.second), 2));
}

//computes PQ X PR
//1 = R is counterclockwise to Q with respect to P, -1 = counterclockwise, 0 = same
int orientation(pair<double, double> p, pair<double, double> q, pair<double, double> r) {
	double cross_product = (q.first - p.first) * (r.second - p.second) - (r.first - p.first) * (q.second - p.second);
	if (cross_product == 0)
		return 0;
	else if (cross_product > 0)
		return 1;
	else
		return -1;
}

vector<pair<double, double>> points;
vector<pair<double, double>> hull;

void convex_hull(pair<double, double> initial_point) {
	auto p = initial_point;
	pair<double, double> endpoint = initial_point;
	do {
		hull.push_back(p);
		//endpoint = possible next point on the convex hull
		endpoint = points[0];
		//search through all possible next points
		for (auto point : points) {
			//find the most counterclockwise point, if tied, take the farthest away
			if (orientation(p, endpoint, point) == 1)
				endpoint = point;
			else if (orientation(p, endpoint, point) == 0) {
				if (distance(p, point) > distance(p, endpoint))
					endpoint = point;
			}
		}
		p = endpoint;
	} while (p != initial_point);
}

int main(){
	int n;
	fin >> n;
	double xcoord, ycoord;
	for (int i = 0; i < n; ++i) {
		fin >> xcoord >> ycoord;
		points.push_back(make_pair(xcoord, ycoord));
	}
	sort(points.begin(), points.end());

	convex_hull(points[0]);

	double total_dist = 0;
	auto start = hull[0];
	for (auto p : hull) {
		total_dist += distance(start, p);
		start = p;
	}
	total_dist += distance(start, hull[0]);

	fout << fixed;
	fout << setprecision(2);
	fout << total_dist << endl;

	return 0;
}