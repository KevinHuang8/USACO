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
ifstream fin("visitfj.in");
ofstream fout("visitfj.out");

/*
Assumes Heap class
Assumes global variables:
dist[] - key: T value: int
adjacency_list[] - key: T, value: vector<T>
weight[][] - key: T, T value: int
optional: distances[][] - shortest path from a to b
useful for multiple dijkstra runs from different sources
*/
//min heap
template<typename T>
class Heap {
	vector<T> heap;
	int heap_size;

	int parent(int i) const { return (i - 1) / 2; }
	int left(int i) const { return 2 * i + 1; }
	int right(int i) const { return 2 * i + 2; }
	//make subtree rooted at index i a min heap
	void min_heapify(int i) {
		int L = left(i);
		int R = right(i);
		int smallest;
		if (L < heap_size && heap[L] < heap[i])
			smallest = L;
		else
			smallest = i;
		if (R < heap_size && heap[R] < heap[smallest])
			smallest = R;
		if (smallest != i) {
			swap(heap[smallest], heap[i]);
			min_heapify(smallest);
		}
	}

	//turn heap into a min heap
	void build_heap() {
		heap_size = heap.size();
		for (int i = heap.size() / 2 - 1; i >= 0; --i)
			min_heapify(i);
	}

public:

	Heap(vector<T>& initial_list)
		: heap(initial_list)
	{
		build_heap();
	}

	T get_min() const {
		return heap[0];
	}

	T extract_min() {
		if (heap_size < 1) {
			//raise exception
		}
		T min = heap[0];
		heap[0] = heap[heap_size - 1];
		--heap_size;
		min_heapify(0);
		return min;
	}

	void decrease_key(T item, T key) {
		auto it = find(heap.begin(), heap.end(), item);
		int i;
		if (it == heap.end()) {
			//raise exception
			return;
		}
		else {
			i = it - heap.begin();
		}
		heap[i] = key;
		while (i > 0 && heap[parent(i)] > heap[i]) {
			swap(heap[i], heap[parent(i)]);
			i = parent(i);
		}
	}

	bool contains(T key) {
		auto it = find(heap.begin(), heap.end(), key);
		if (it - heap.begin() >= heap_size)
			return false;
		return true;
	}

	bool empty() {
		if (heap_size < 1)
			return true;
		return false;
	}

};

struct field {
	int x;
	int y;
	field(int a, int b) : y(a), x(b) {}
	field() {}
	bool operator==(const field& other) const{
		return x == other.x && y == other.y;
	}
	bool operator<(const field& other) const {
		if (x < other.x)
			return true;
		else
			return y < other.y;
	}
};

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

struct field_hash : public unary_function<pair<field, int>, size_t>
{
	size_t operator()(const pair<field, int>& k) const
	{
		key_hash h2;
		hash<int> h;
		size_t seed = h2(make_pair(k.first.x, k.first.y));
		seed = h2(make_pair(k.first.x, k.first.y)) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		return seed ^ (h(k.second) + 0x9e3779b9 + (seed << 6) + (seed >> 2));
	}
};

unordered_map<pair<field, int>, vector<pair<field, int>>, field_hash> adjacency_list;
unordered_map<pair<field, int>, unordered_map<pair<field, int>, int, field_hash>, field_hash> weight;
unordered_map<pair<field, int>, int, field_hash> dist;

/*
Assumes Heap class
Assumes global variables:
dist[] - key: T value: int
adjacency_list[] - key: T, value: vector<T>
weight[][] - key: T, T value: int
optional: distances[][] - shortest path from a to b
useful for multiple dijkstra runs from different sources
*/
template <typename T>
void dijkstra(vector<T> node_list, T source) {
	vector<pair<int, T>> v;
	for (int i = 0; i < node_list.size(); ++i) {
		T val = node_list[i];
		if (val == source) {
			dist[source] = 0;
			//distances[source][source] = 0;
			v.push_back(make_pair(0, source));
			continue;
		}
		dist[val] = 2100000000;
		v.push_back(make_pair(dist[val], val));
	}

	Heap<pair<int, T>> to_process(v);
	while (!to_process.empty()) {
		pair<int, T> node = to_process.extract_min();
		for (T adj : adjacency_list[node.second]) {
			if (dist[adj] > dist[node.second] + weight[node.second][adj]) {
				to_process.decrease_key(make_pair(dist[adj], adj), make_pair(dist[node.second] + weight[node.second][adj], adj));
				dist[adj] = dist[node.second] + weight[node.second][adj];
				//distances[source][adj] = dist[adj];
			}
		}
	}
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

void add_weight(pair<field, int> p1, pair<field, int> p2, int w) {
	if (weight.find(p1) == weight.end()) {
		unordered_map<pair<field, int>, int, field_hash> u;
		weight[p1] = u;
	}
	weight[p1][p2] = w;
}

int board[101][101];
field fields[101][101];

int main(){
	int n, t;
	fin >> n >> t;

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			int grass;
			fin >> grass;
			field f(i, j);
			fields[i][j] = f;
			board[i][j] = grass;
		}
	}
	unordered_set<pair<field, int>, field_hash> nodes;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			pair<field, int> p1 = make_pair(fields[i][j], 0);
			pair<field, int> p2 = make_pair(fields[i][j], 1);
			pair<field, int> p3 = make_pair(fields[i][j], 2);
			nodes.insert(p1);
			nodes.insert(p2);
			nodes.insert(p3);

			if (j < n) {
				pair<field, int> adj1 = make_pair(fields[i][j + 1], 0);
				pair<field, int> adj2 = make_pair(fields[i][j + 1], 1);
				pair<field, int> adj3 = make_pair(fields[i][j + 1], 2);
				nodes.insert(adj1);
				nodes.insert(adj2);
				nodes.insert(adj3);
				add_map(p1, adj2, adjacency_list);
				add_weight(p1, adj2, t);
				add_map(p2, adj3, adjacency_list);
				add_weight(p2, adj3, t);
				add_map(p3, adj1, adjacency_list);
				add_weight(p3, adj1, t + board[i][j + 1]);
			}

			if (i < n) {
				pair<field, int> adj1 = make_pair(fields[i + 1][j], 0);
				pair<field, int> adj2 = make_pair(fields[i + 1][j], 1);
				pair<field, int> adj3 = make_pair(fields[i + 1][j], 2);
				nodes.insert(adj1);
				nodes.insert(adj2);
				nodes.insert(adj3);
				add_map(p1, adj2, adjacency_list);
				add_weight(p1, adj2, t);
				add_map(p2, adj3, adjacency_list);
				add_weight(p2, adj3, t);
				add_map(p3, adj1, adjacency_list);
				add_weight(p3, adj1, t + board[i + 1][j]);
			}

			if (j > 0) {
				pair<field, int> adj1 = make_pair(fields[i][j - 1], 0);
				pair<field, int> adj2 = make_pair(fields[i][j - 1], 1);
				pair<field, int> adj3 = make_pair(fields[i][j - 1], 2);
				nodes.insert(adj1);
				nodes.insert(adj2);
				nodes.insert(adj3);
				add_map(p1, adj2, adjacency_list);
				add_weight(p1, adj2, t);
				add_map(p2, adj3, adjacency_list);
				add_weight(p2, adj3, t);
				add_map(p3, adj1, adjacency_list);
				add_weight(p3, adj1, t + board[i][j - 1]);
			}

			if (i > 0) {
				pair<field, int> adj1 = make_pair(fields[i - 1][j], 0);
				pair<field, int> adj2 = make_pair(fields[i - 1][j], 1);
				pair<field, int> adj3 = make_pair(fields[i - 1][j], 2);
				nodes.insert(adj1);
				nodes.insert(adj2);
				nodes.insert(adj3);
				add_map(p1, adj2, adjacency_list);
				add_weight(p1, adj2, t);
				add_map(p2, adj3, adjacency_list);
				add_weight(p2, adj3, t);
				add_map(p3, adj1, adjacency_list);
				add_weight(p3, adj1, t + board[i - 1][j]);
			}
		}
	}

	vector<pair<field, int>> node_list(nodes.size());

	for (auto n : nodes) {
		node_list.push_back(n);
	}

	dijkstra(node_list, make_pair(field(0, 0), 0));

	field fin = field(n - 1, n - 1);
	int d = min(min(dist[make_pair(fin, 0)], dist[make_pair(fin, 1)]), dist[make_pair(fin, 2)]);

	fout << d << endl;

	return 0;
}