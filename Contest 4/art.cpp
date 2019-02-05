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
#define INF 2100000000
using namespace std;


//ifstream fin("in.txt");
//ofstream fout("out.txt");
ifstream fin("art.in");
ofstream fout("art.out");

template <typename T, typename U>
void sort_by_second(vector<pair<T, U>>& v) {
	sort(v.begin(), v.end(), [](const pair<T, U> &left, const pair<T, U> &right) {
		return left.second < right.second;
	});
}

//pair hash
struct key_hash : public unary_function<pair<int, int>, size_t>
{
	size_t operator()(const pair<int, int>& k) const
	{
		hash<int> h;
		size_t seed = h(k.first);
		seed = h(k.first) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		return seed ^ (h(k.second) + 0x9e3779b9 + (seed << 6) + (seed >> 2));
	}
};

unordered_set<int> on_top;
unordered_map<pair<int, int>, int, key_hash> point_to_color;

class range_tree_2d {
	typedef std::pair<int, int> point;

	std::vector<point> P;
	std::vector<std::vector<point> > seg;

	static inline bool comp1(const point & a, const point & b) {
		return a.second < b.second;
	}

	static inline bool comp2(const point & a, int v) {
		return a.second < v;
	}

	void build(int n, int lo, int hi) {
		if (P[lo].first == P[hi].first) {
			for (int i = lo; i <= hi; i++)
				seg[n].push_back(point(i, P[i].second));
			return;
		}
		int l = n * 2 + 1, r = n * 2 + 2;
		build(l, lo, (lo + hi) / 2);
		build(r, (lo + hi) / 2 + 1, hi);
		seg[n].resize(seg[l].size() + seg[r].size());
		std::merge(seg[l].begin(), seg[l].end(), seg[r].begin(), seg[r].end(),
			seg[n].begin(), comp1);
	}

	int xl, xh, yl, yh;

	template<class ReportFunction>
	void query(int n, int lo, int hi, ReportFunction f, vector<point> exclusive) {
		if (P[hi].first < xl || P[lo].first > xh) return;
		if (xl <= P[lo].first && P[hi].first <= xh) {
			if (!seg[n].empty() && yh >= yl) {
				std::vector<point>::iterator it;
				it = std::lower_bound(seg[n].begin(), seg[n].end(), yl, comp2);
				for (; it != seg[n].end(); ++it) {
					if (it->second > yh) break;
					point pt = P[it->first];
					if (find(exclusive.begin(), exclusive.end(), pt) == exclusive.end())
						on_top.insert(point_to_color[pt]);
				}
			}
		}
		else if (lo != hi) {
			query(n * 2 + 1, lo, (lo + hi) / 2, f, exclusive);
			query(n * 2 + 2, (lo + hi) / 2 + 1, hi, f, exclusive);
		}
	}

public:
	range_tree_2d(int n, vector<point> v) : seg(4 * n + 1) {
		std::sort(v.begin(), v.end());
		P = v;
		build(0, 0, n - 1);
	}

	template<class ReportFunction>
	void query(int x1, int y1, int x2, int y2, ReportFunction f, vector<point> exclusive) {
		xl = x1; xh = x2;
		yl = y1; yh = y2;
		query(0, 0, P.size() - 1, f, exclusive);
	}
};

void f(pair<int, int> x) {
	fout << x.first << " " << x.second << endl;
}

//Adds value to m[key], and creates a new vector if it doesn't exist
template <typename T, typename U, typename Hash>
void add_map(T key, U value, unordered_map<T, vector<U>, Hash>& m) {
	if (m.find(key) == m.end()) {
		vector<U> v;
		m[key] = v;
	}
	m[key].push_back(value);
}


unordered_set<int> colors;
int top[1000001];
int lefts[1000001];
int rights[1000001];
int bottom[1000001];
int board[1001][1001];

int main(){
	int n;
	fin >> n;

	for (int i = 1; i <= n*n; ++i) {
		lefts[i] = INF;
		top[i] = INF;
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			int color;
			fin >> board[i][j];
			color = board[i][j];
			if (!color)
				continue;
			colors.insert(color);
			lefts[color] = min(lefts[color], j);
			rights[color] = max(rights[color], j);
			top[color] = min(top[color], i);
			bottom[color] = max(bottom[color], i);
		}
	}

	vector<pair<int, int>> points;
	unordered_map<int, vector<pair<int, int>>> color_to_points;
	for (int color : colors) {
		if (board[top[color]][lefts[color]] == color) {
			points.push_back(make_pair(lefts[color], top[color]));
			point_to_color[make_pair(lefts[color], top[color])] = color;
			add_map(color, make_pair(lefts[color], top[color]), color_to_points);
		}
		if (board[top[color]][rights[color]] == color) {
			points.push_back(make_pair(rights[color], top[color]));
			point_to_color[make_pair(rights[color], top[color])] = color;
			add_map(color, make_pair(rights[color], top[color]), color_to_points);
		}
		if (board[bottom[color]][lefts[color]] == color) {
			points.push_back(make_pair(lefts[color], bottom[color]));
			point_to_color[make_pair(lefts[color], bottom[color])] = color;
			add_map(color, make_pair(lefts[color], bottom[color]), color_to_points);
		}
		if (board[bottom[color]][rights[color]] == color) {
			points.push_back(make_pair(rights[color], bottom[color]));
			point_to_color[make_pair(rights[color], bottom[color])] = color;
			add_map(color, make_pair(rights[color], bottom[color]), color_to_points);
		}
	}
	
	range_tree_2d range_tree(points.size(), points);

	
	for (int color : colors) {
		range_tree.query(lefts[color], top[color], rights[color], bottom[color], f, color_to_points[color]);
	}
	
	if (colors.size() == 1)
		fout << n * n - 1 << endl;
	else
		fout << n * n - on_top.size() << endl;

	return 0;
}