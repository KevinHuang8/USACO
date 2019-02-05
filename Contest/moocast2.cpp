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


//ifstream fin("in.txt");
//ofstream fout("out.txt");
ifstream fin("moocast.in");
ofstream fout("moocast.out");

template <typename T>
struct DisjointSet {
	unordered_set<T> sets;
	unordered_map<T, int> rank;
	unordered_map<T, T> parent;

	void new_set(T key) {
		if (sets.find(key) != sets.end())
			return;
		parent[key] = key;
		rank[key] = 0;
		sets.insert(key);
	}

	//return representative of key
	T find(T n) {
		if (n != parent[n])
			parent[n] = find(parent[n]);
		return parent[n];
	}

	void union_set(T root1, T root2) {
		root1 = find(root1);
		root2 = find(root2);

		if (rank[root1] > rank[root2]) {
			parent[root2] = root1;
			sets.erase(root2);
		}
		else {
			parent[root1] = root2;
			sets.erase(root1);
			if (rank[root1] == rank[root2])
				++rank[root2];
		}
	}
};

double distance(pair<int, int> a, pair<int, int> b) {
	return sqrt(pow((a.first - b.first), 2) + pow((a.second - b.second), 2));
}

vector<pair<int, int>> cows;
unordered_map<double, pair<int, int>> edge_with_dist;
vector<double> distances;

int main() {
	int n;
	fin >> n;
	for (int i = 0; i < n; ++i) {
		int x, y;
		fin >> x >> y;
		cows.push_back(make_pair(x, y));
	}
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			double d = distance(cows[i], cows[j]);
			distances.push_back(d);
			edge_with_dist[d] = make_pair(i, j);
		}
	}

	sort(distances.begin(), distances.end());

	DisjointSet<int> components;

	for (int i = 0; i < n; ++i)
		components.new_set(i);

	double largest_edge = 0;
	for (double d : distances) {
		int first = edge_with_dist[d].first;
		int second = edge_with_dist[d].second;

		if (components.find(first) != components.find(second)) {
			components.union_set(first, second);
			largest_edge = d;
		}
	}

	double square = pow(largest_edge, 2);
	if (square - (int)square < 0.0001) {
		fout << (int)square << endl;
	}
	else {
		fout << (int)ceil(square) << endl;
	}

	return 0;
}