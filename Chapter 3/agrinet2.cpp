/*
ID: Kevun1
LANG: C++11
TASK: agrinet
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
using namespace std;


//ifstream fin("in.txt");
//ofstream fout("out.txt");
ifstream fin("agrinet.in");
ofstream fout("agrinet.out");

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

	Heap() {
		vector<T> h;
		heap = h;
		heap_size = 0;
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

int n;
int adjacency_matrix[101][101];
int distances[101];
int parent[101];

/*
Assumes global variables:
distances[] - a unordered_map or array
parent[]
adjacency_matrix[][] = weight
*/
template <typename T>
int prim(vector<T> node_list, T source) {
	int treecost = 0;
	vector<pair<int, T>> v;
	for (int i = 0; i < node_list.size(); ++i) {
		T val = node_list[i];
		if (val == source) {
			distances[source] = 0;
			v.push_back(make_pair(0, source));
		}
		else {
			distances[val] = 2147483647;
			v.push_back(make_pair(distances[val], val));
		}
	}

	Heap<pair<int, T>> to_process(v);
	while (!to_process.empty()) {
		pair<int, T> node = to_process.extract_min();
		treecost += distances[node.second];
		for (T adj : node_list) {
			if (adjacency_matrix[node.second][adj] == 0)
				continue;
			int weight = adjacency_matrix[node.second][adj];
			if (to_process.contains(make_pair(distances[adj], adj)) && weight < distances[adj]) {
				to_process.decrease_key(make_pair(distances[adj], adj), make_pair(weight, adj));
				distances[adj] = weight;
				parent[adj] = node.second;
			}
		}
	}
	return treecost;
}
/*
Minimum Spanning Tree
*/
int main() {
	fin >> n;

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			int w;
			fin >> w;
			adjacency_matrix[i][j] = w;
		}
	}

	vector<int> v;
	for (int i = 0; i < n; ++i) {
		v.push_back(i);
	}

	int treecost = prim(v, 0);

	fout << treecost << endl;

	return 0;
}