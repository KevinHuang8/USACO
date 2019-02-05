/*
ID: Kevun1
LANG: C++11
TASK: snail
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


//ifstream fin("in.txt");
//ofstream fout("out.txt");
ifstream fin("snail.in");
ofstream fout("snail.out");

//computes PQ X PR
//1 = R is counterclockwise to Q with respect to P, -1 = counterclockwise, 0 = same
int orientation(pair<int, int> p, pair<int, int> q, pair<int, int> r) {
	double cross_product = (q.first - p.first) * (r.second - p.second) - (r.first - p.first) * (q.second - p.second);
	if (cross_product == 0)
		return 0;
	else if (cross_product > 0)
		return 1;
	else
		return -1;
}

bool on_segment(pair<int, int> p, pair<int, int> q, pair<int, int> r) {
	if ((min(p.first, q.first) <= r.first && r.first <= max(p.first, q.first)) && (min(p.second, q.second)
		<= r.second && r.second <= max(p.second, q.second)))
		return true;
	return false;
}

//returns whether P1P2 intersects P3P4
bool segment_intersect(pair<int, int> p1, pair<int, int> p2, pair<int, int> p3,
	pair<int, int> p4) {

	int d1 = orientation(p3, p1, p4);
	int d2 = orientation(p3, p2, p4);
	int d3 = orientation(p1, p3, p2);
	int d4 = orientation(p1, p4, p2);
	if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) && ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)))
		return true;
	else if (d1 == 0 && on_segment(p3, p4, p1))
		return true;
	else if (d2 == 0 && on_segment(p3, p4, p2))
		return true;
	else if (d3 == 0 && on_segment(p1, p2, p3))
		return true;
	else if (d4 == 0 && on_segment(p1, p2, p4))
		return true;
	return false;
}

//Adds value to m[key], and creates a new vector if it doesn't exist
template <typename T, typename U, typename Hash>
void add_map(T key, U value, unordered_map<T, set<U>, Hash>& m) {
	if (m.find(key) == m.end()) {
		set<U> v;
		m[key] = v;
	}
	m[key].insert(value);

}
int n, b;
unordered_map<int, set<int>> barrier_rows;
unordered_map<int, set<int>> barrier_columns;
int max_dist = 0;

void dfs(int row, int column, char orientation, int dist, vector<pair<pair<int, int>, pair<int, int>>> visited_rows, 
	vector<pair<pair<int, int>, pair<int, int>>> visited_cols) {
	if (orientation == 'U') {
		int new_row = 1;
		auto it = barrier_columns[column].lower_bound(row);
		if (it != barrier_columns[column].begin()) {
			--it;
			new_row = *it;
			++new_row;
		}

		//find the first intersection
		int min_intersection = 500;
		for (auto vis : visited_rows) {
			if (segment_intersect(make_pair(row - 1, column), make_pair(new_row, column), vis.first, vis.second)) {
				int new_dist = (row - vis.first.first - 1);
				min_intersection = min(min_intersection, new_dist);
			}
		}
		if (min_intersection != 500) {
			if (min_intersection < 0) min_intersection = 0;
			max_dist = max(max_dist, min_intersection + dist);
			return;
		}

		visited_cols.push_back(make_pair(make_pair(row, column), make_pair(new_row, column)));
		int new_dist = row - new_row;

		dfs(new_row, column, 'L', dist + new_dist, visited_rows, visited_cols);
		dfs(new_row, column, 'R', dist + new_dist, visited_rows, visited_cols);
	}

	else if (orientation == 'L') {
		int new_col = 1;
		auto it = barrier_rows[row].lower_bound(column);
		if (it != barrier_rows[row].begin()) {
			--it;
			new_col = *it;
			++new_col;
		}

		int min_intersection = 500;
		for (auto vis : visited_cols) {
			if (segment_intersect(make_pair(row, column - 1), make_pair(row, new_col), vis.first, vis.second)) {
				int new_dist = (column - vis.first.second - 1);
				min_intersection = min(min_intersection, new_dist);
			}
		}
		if (min_intersection != 500) {
			if (min_intersection < 0) min_intersection = 0;
			max_dist = max(max_dist, min_intersection + dist);
			return;
		}

		visited_rows.push_back(make_pair(make_pair(row, column), make_pair(row, new_col)));
		int new_dist = column - new_col;

		dfs(row, new_col, 'U', dist + new_dist, visited_rows, visited_cols);
		dfs(row, new_col, 'D', dist + new_dist, visited_rows, visited_cols);
	}

	else if (orientation == 'D') {
		int new_row = n;
		auto it = barrier_columns[column].upper_bound(row);
		if (it != barrier_columns[column].end()) {
			new_row = *it;
			--new_row;
		}

		int min_intersection = 500;
		for (auto vis : visited_rows) {
			if (segment_intersect(make_pair(row + 1, column), make_pair(new_row, column), vis.first, vis.second)) {
				int new_dist = (vis.first.first - row - 1);
				min_intersection = min(min_intersection, new_dist);
			}
		}
		if (min_intersection != 500) {
			if (min_intersection < 0) min_intersection = 0;
			max_dist = max(max_dist, min_intersection + dist);
			return;
		}

		visited_cols.push_back(make_pair(make_pair(row, column), make_pair(new_row, column)));
		int new_dist = new_row - row;

		dfs(new_row, column, 'L', dist + new_dist, visited_rows, visited_cols);
		dfs(new_row, column, 'R', dist + new_dist, visited_rows, visited_cols);
	}

	else if (orientation == 'R') {
		int new_col = n;
		auto it = barrier_rows[row].upper_bound(column);
		if (it != barrier_rows[row].end()) {
			new_col = *it;
			--new_col;
		}

		int min_intersection = 500;
		for (auto vis : visited_cols) {
			if ((segment_intersect(make_pair(row, column + 1), make_pair(row, new_col), vis.first, vis.second))) {
				int new_dist = (vis.first.second - column - 1);
				min_intersection = min(min_intersection, new_dist);
			}
		}
		if (min_intersection != 500) {
			if (min_intersection < 0) min_intersection = 0;
			max_dist = max(max_dist, min_intersection + dist);
			return;
		}

		visited_rows.push_back(make_pair(make_pair(row, column), make_pair(row, new_col)));
		int new_dist = new_col - column;

		dfs(row, new_col, 'U', dist + new_dist, visited_rows, visited_cols);
		dfs(row, new_col, 'D', dist + new_dist, visited_rows, visited_cols);
	}
}
int main(){
	fin >> n >> b;

	string barrier;
	for (int i = 0; i < b; ++i) {
		fin >> barrier;
		add_map(stoi(barrier.substr(1)), barrier[0] - 64, barrier_rows);
		add_map(barrier[0] - 64, stoi(barrier.substr(1)), barrier_columns);
	}

	vector<pair<pair<int, int>, pair<int, int>>> visited_cols;
	vector<pair<pair<int, int>, pair<int, int>>> visited_rows;
	dfs(1, 1, 'D', 1, visited_rows, visited_cols);
	dfs(1, 1, 'R', 1, visited_rows, visited_cols);

	fout << max_dist << endl;

	return 0;
}