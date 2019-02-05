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
ifstream fin("grass.in");
ofstream fout("grass.out");

struct BitStack {
	unsigned int bits[6250];
	const int MultiplyDeBruijnBitPosition[32] =
	{
		0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
		31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
	};

	BitStack() {
		for (int i = 0; i < 6250; ++i) {
			bits[i] = (1 << 32) - 1;
		}
	}

	int disable_count(unsigned int v) {
		return MultiplyDeBruijnBitPosition[((uint32_t)((v & (-v)) * 0x077CB531U)) >> 27];
	}

	//invalidate (clear) nth bit
	void clear(int n) {
		int height = n / 32;
		int pos = n % 32;
		uint32_t mask = ~(1 << pos);
		uint32_t x = bits[height] & mask;
		bits[height] = x;
	}

	void set(int n) {
		int height = n / 32;
		int pos = n % 32;
		bits[height] |= 1 << pos;
	}

	int get_first() {
		for (int i = 0; i < 6250; ++i) {
			int trailing = disable_count(bits[i]);
			if (trailing != 32) {
				return i * 32 + trailing;
			}
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

unordered_map<int, vector<int>> adjacency_list;
vector<pair<int, pair<int, int>>> edge_list;
unordered_map<pair<int, int>, int, key_hash> edge_to_pos;
int grass_types[200001];

int main(){
	int n, m, k, q;
	fin >> n >> m >> k >> q;
	for (int i = 0; i < m; ++i) {
		int a, b, l;
		fin >> a >> b >> l;
		add_map(a - 1, b - 1, adjacency_list);
		add_map(b - 1, a - 1, adjacency_list);
		edge_list.push_back(make_pair(l, make_pair(a - 1, b - 1)));
	}
	for (int i = 0; i < n; ++i) {
		int type;
		fin >> type;
		grass_types[i] = type;
	}

	BitStack bits;
	sort(edge_list.begin(), edge_list.end());

	for (int i = 0; i < edge_list.size(); ++i) {
		edge_to_pos[edge_list[i].second] = i;
		edge_to_pos[make_pair(edge_list[i].second.second, edge_list[i].second.first)] = i;
	}

	for (int i = 0; i < n; ++i) {
		for (int adj : adjacency_list[i]) {
			if (grass_types[i] == grass_types[adj]) {
				bits.clear(edge_to_pos[make_pair(i, adj)]);
			}
		}
	}

	for (int i = 0; i < q; ++i) {
		int a, new_type;
		fin >> a >> new_type;
		grass_types[a - 1] = new_type;
		for (int adj : adjacency_list[a - 1]) {
			if (grass_types[i] == grass_types[adj]) {
				bits.clear(edge_to_pos[make_pair(i, adj)]);
			}
			else {
				bits.set(edge_to_pos[make_pair(i, adj)]);
			}
		}
		int x = bits.get_first();
		fout << edge_list[x].first << endl;
	}

	return 0;
}