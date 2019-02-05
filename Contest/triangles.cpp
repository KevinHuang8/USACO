/*
ID: Kevun1
LANG: C++11
TASK: name
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <utility>
#include <unordered_set>
#include <set>
#include <map>
#include <queue>
#include <sstream>
#include <numeric>
using namespace std;


ifstream fin("in.txt");
ofstream fout("out.txt");
//ifstream fin("triangles.in");
//ofstream fout("triangles.out");

//pair hash
struct key_hash : public unary_function<pair<int, int>, size_t>
{
	size_t operator()(const pair<int, int>& k) const
	{
		return k.first ^ k.second;
	}
};

vector<pair<int, int>> points;
//points_below[i,j] = number of points below line i, j. Does not include points directly under i or j
unordered_map<pair<int, int>, int, key_hash> points_below;
//colinear[p] = 1 if there is a point directly underneath its
int colinear[301] = { 0 };
//inside[v] = number of triangles with v points inside it
int inside[300] = { 0 };

//computes PQ X PR
//1 = R is counterclockwise to Q with respect to P, -1 = clockwise, 0 = same
int orientation(const pair<int, int>& p, const pair<int, int>& q, const pair<int, int>& r) {
	double cross_product = (q.first - p.first) * (r.second - p.second) - (r.first - p.first) * (q.second - p.second);
	if (cross_product == 0)
		return 0;
	else if (cross_product > 0)
		return 1;
	else
		return -1;
}

bool is_below(pair<int, int>& p, pair<int, int>& a, pair<int, int>& b) {
	if (p.second > max(a.second, b.second) || p.first >= max(a.first, b.first)
		|| p.first <= min(a.first, b.first))
		return false;

	if (orientation(min(a, b), p, max(a, b)) != 1)
		return false;

	return true;
}

pair<int, int> max_height(pair<int, int> a, pair<int, int> b) {
	if (a.second > b.second)
		return a;
	return b;
}

int main(){
	int n;
	fin >> n;
	for (int i = 0; i < n; ++i) {
		int x, y;
		fin >> x >> y;
		points.push_back(make_pair(x, y));
	}

	for (int i = 0; i < n; ++i) {
		auto p1 = points[i];
		for (int j = i + 1; j < n; ++j) {
			auto p2 = points[j];
			for (auto point : points) {
				if (is_below(point, p1, p2)) {
					++points_below[make_pair(i, j)];
					++points_below[make_pair(j, i)];
				}
				if (point.first == p1.first && point.second < p1.second) {
					++colinear[i];
				}
				if (point.first == p2.first && point.second < p2.second) {
					++colinear[j];
				}
			}
		}
	}

	for (int i = 0; i < n; ++i) {
		auto p1 = points[i];
		for (int j = i + 1; j < n; ++j) {
			auto p2 = points[j];
			for (int k = j + 1; k < n; ++k) {
				auto p3 = points[k];
				int num = 0;
				//i is on top
				if (p1.first >= min(p2.first, p3.first) && p1.first <= max(p2.first, p3.first)
					&& orientation(min(p2, p3), p1, max(p2, p3)) == -1) {
					num = points_below[make_pair(i, j)] + points_below[make_pair(i, k)] + colinear[i]
						- points_below[make_pair(j, k)];

					//case where the top point is directly over another point
					if (p1.first == p2.first || p1.first == p3.first)
						--colinear[i];
				}
				//i is on bottom
				else if (p1.first >= min(p2.first, p3.first) && p1.first <= max(p2.first, p3.first)
					&& orientation(min(p2, p3), p1, max(p2, p3)) == 1) {
					num = points_below[make_pair(j, k)] - points_below[make_pair(i, j)]
						- points_below[make_pair(i, k)] - 1;
				}
				//j is on top
				else if (p2.first >= min(p1.first, p3.first) && p2.first <= max(p1.first, p3.first)
					&& orientation(min(p1, p3), p2, max(p1, p3)) == -1) {
					num = points_below[make_pair(i, j)] + points_below[make_pair(j, k)] + colinear[j]
						- points_below[make_pair(i, k)];

					if (p2.first == p1.first || p2.first == p3.first)
						--colinear[j];
				}
				//j is on bottom
				else if (p2.first >= min(p1.first, p3.first) && p2.first <= max(p1.first, p3.first)
					&& orientation(min(p1, p3), p2, max(p1, p3)) == 1) {
					num = points_below[make_pair(i, k)] - points_below[make_pair(i, j)]
						- points_below[make_pair(j, k)] - 1;
				}
				//k is on top
				else if (p3.first >= min(p1.first, p2.first) && p3.first <= max(p1.first, p2.first)
					&& orientation(min(p2, p1), p3, max(p2, p1)) == -1) {
					num = points_below[make_pair(i, k)] + points_below[make_pair(j, k)] + colinear[k]
						- points_below[make_pair(i, j)];
	
					if (p3.first == p2.first || p3.first == p1.first)
						--colinear[k];
				}
				//k is on bottom
				else if (p3.first >= min(p1.first, p2.first) && p3.first <= max(p1.first, p2.first)
					&& orientation(min(p2, p1), p3, max(p2, p1)) == 1) {
					num = points_below[make_pair(i, j)] - points_below[make_pair(i, k)]
						- points_below[make_pair(j, k)] - 1;
				}
				++inside[num];
			}
		}
	}

	for (int i = 0; i <= n - 3; ++i) {
		fout << inside[i] << endl;
	}

	return 0;
}