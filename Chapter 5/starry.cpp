/*
ID: Kevun1
LANG: C++11
TASK: starry
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
ifstream fin("starry.in");
ofstream fout("starry.out");

int board[100][100];
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


//T must be hashable
template <typename T, typename Hash>
struct DisjointSet {
	unordered_set<T, Hash> sets;
	unordered_map<T, int, Hash> rank;
	unordered_map<T, T, Hash> parent;

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
		if (root1 == root2)
			return;

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

//Adds value to m[key], and creates a new vector if it doesn't exist
template <typename T, typename U, typename Hash>
void add_map(T key, U value, unordered_map<T, vector<U>, Hash>& m) {
	if (m.find(key) == m.end()) {
		vector<U> v;
		m[key] = v;
	}
	m[key].push_back(value);
}

struct vector_hash {
	size_t operator()(vector<pair<int, int>> const& vec) const {
		key_hash h;
		size_t seed = vec.size();
		for (auto& i : vec) {
			seed ^= h(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		}
		return seed;
	}
};

int w, h;
unordered_map<pair<int, int>, vector<pair<int, int>>, key_hash> clusters;
unordered_map<pair<int, int>, int, key_hash> hashes;
unordered_map<pair<int, int>, int, key_hash> hashes1; //rotated 90
unordered_map<pair<int, int>, int, key_hash> hashes2; //rotated 180
unordered_map<pair<int, int>, int, key_hash> hashes3; //rotated 270
unordered_map<pair<int, int>, int, key_hash> hashes4; //relect
unordered_map<pair<int, int>, int, key_hash> hashes5; //reflect and rotate 90
unordered_map<pair<int, int>, int, key_hash> hashes6; //reflect and rotate 180
unordered_map<pair<int, int>, int, key_hash> hashes7; //reflect and rotate 270
unordered_map<pair<int, int>, pair<int, int>, key_hash> clustersize;
unordered_set<pair<int, int>, key_hash> stars;

int main(){
	fin >> w >> h;

	DisjointSet<pair<int, int>, key_hash> DSU;

	for (int i = 0; i < h; ++i) {
		string line;
		fin >> line;
		for (int j = 0; j < w; ++j) {
			board[i][j] = line[j] - 48;
			if (board[i][j]) {
				DSU.new_set(make_pair(i, j));
				stars.insert(make_pair(i, j));
			}
		}
	}

	//using disjoint set, union all coordinates that are part of one cluster
	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			if (!board[i][j]) continue;

			if (i < h - 1 && board[i + 1][j])
				DSU.union_set(make_pair(i, j), make_pair(i + 1, j));
			if (i < h - 1 && j < w - 1 && board[i + 1][j + 1])
				DSU.union_set(make_pair(i, j), make_pair(i + 1, j + 1));
			if (i < h - 1 && j > 0 && board[i + 1][j - 1])
				DSU.union_set(make_pair(i, j), make_pair(i + 1, j - 1));
			if (i > 0 && board[i - 1][j])
				DSU.union_set(make_pair(i, j), make_pair(i - 1, j));
			if (i > 0 && j > 0 && board[i - 1][j - 1])
				DSU.union_set(make_pair(i, j), make_pair(i - 1, j - 1));
			if (i > 0 && j < w - 1 && board[i - 1][j + 1])
				DSU.union_set(make_pair(i, j), make_pair(i - 1, j + 1));
			if (j < w - 1 && board[i][j + 1])
				DSU.union_set(make_pair(i, j), make_pair(i, j + 1));
			if (j > 0 && board[i][j - 1])
				DSU.union_set(make_pair(i, j), make_pair(i, j - 1));
		}
	}
	
	//corner maps the top left corner of a cluster to its representative
	unordered_map<pair<int, int>, pair<int, int>, key_hash> corner;
	//in order to get the lexiographically smallest solution, the clusters will need to be processed in increasing
	//order of their topleftmost star
	set<pair<int, int>> order;

	//find the coordinates of the stars that belong to each cluster
	vector_hash vh;
	for (auto p : DSU.sets) {
		//the corners of the box that bounds the cluster
		int minx = 101, miny = 101, maxx = 0, maxy = 0;
		pair<int, int> topleft = make_pair(101, 101);
		for (auto star : stars) {
			if (DSU.find(star) == p) {
				minx = min(minx, star.second);
				miny = min(miny, star.first);
				maxx = max(maxx, star.second);
				maxy = max(maxy, star.first);
				topleft = min(topleft, star);
				add_map(p, star, clusters);
			}
		}

		order.insert(topleft);
		corner[topleft] = p;

		//make each coordinate the coordinate of the local box
		for (int i = 0; i < clusters[p].size(); ++i) {
			clusters[p][i] = make_pair(clusters[p][i].first - miny, clusters[p][i].second - minx);
		}
		sort(clusters[p].begin(), clusters[p].end());
		hashes[p] = vh(clusters[p]);
		clustersize[p] = make_pair(maxy - miny + 1, maxx - minx + 1);
	}

	//for each cluster, find the hash of each possible rotation
	key_hash ph;
	for (auto p : DSU.sets) {
		int h = clustersize[p].first;
		int w = clustersize[p].second;
		vector<pair<int, int>> v1, v2, v3, v4, v5, v6, v7;

		for (auto star : clusters[p]) {
			v1.push_back(make_pair(star.second, h - 1 - star.first));
			v2.push_back(make_pair(h - 1 - star.first, w - 1 - star.second));
			v3.push_back(make_pair(w - 1 - star.second, star.first));
			v4.push_back(make_pair(star.first, w - 1 - star.second));
			v5.push_back(make_pair(w - 1 - star.second, h - 1 - star.first));
			v6.push_back(make_pair(h - 1 - star.first, star.second));
			v7.push_back(make_pair(star.second, star.first));
		}

		sort(v1.begin(), v1.end());
		sort(v2.begin(), v2.end());
		sort(v3.begin(), v3.end());
		sort(v4.begin(), v4.end());
		sort(v5.begin(), v5.end());
		sort(v6.begin(), v6.end());
		sort(v7.begin(), v7.end());

		hashes1[p] = vh(v1);
		hashes2[p] = vh(v2);
		hashes3[p] = vh(v3);
		hashes4[p] = vh(v4);
		hashes5[p] = vh(v5);
		hashes6[p] = vh(v6);
		hashes7[p] = vh(v7);
	}

	unordered_map<pair<int, int>, char, key_hash> mark;
	unordered_set<pair<int, int>, key_hash> visited;

	char symbol = 'a';
	for (auto p : order) {
		auto p1 = corner[p];
		if (visited.find(p1) != visited.end())
			continue;
		mark[p1] = symbol;
		for (auto p2 : DSU.sets) {
			if (hashes[p2] == hashes[p1] || hashes1[p2] == hashes[p1] || hashes2[p2] == hashes[p1] || hashes3[p2] == hashes[p1]
				|| hashes4[p2] == hashes[p1] || hashes5[p2] == hashes[p1] || hashes6[p2] == hashes[p1] || hashes7[p2] == hashes[p1]) {
				//double check in case of hash collision
				
				visited.insert(p2);
				mark[p2] = symbol;
			}
		}
		++symbol;
	}

	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			if (!board[i][j])
				fout << 0;
			else 
				fout << mark[DSU.find(make_pair(i, j))];
		}
		fout << endl;
	}

	return 0;
}