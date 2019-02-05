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
/*
Minimum Spanning Tree
*/
int main(){
	fin >> n;

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			int w;
			fin >> w;
			adjacency_matrix[i][j] = w;
		}
	}

	//prim
	int distances[101];
	int treecost = 0;
	vector<pair<int, int>> farms;
	for (int i = 1; i < n; ++i) {
		distances[i] = 100000000;
		farms.push_back(make_pair(distances[i], i));
	}
	distances[0] = 0;
	farms.push_back(make_pair(0, 0));

	Heap<pair<int, int>> to_process(farms);
	while (!to_process.empty()) {
		pair<int, int> farm = to_process.extract_min();
		treecost += distances[farm.second];
		for (int i = 0; i < n; ++i) {
			if (adjacency_matrix[farm.second][i] == 0)
				continue;
			int weight = adjacency_matrix[farm.second][i];
			if (to_process.contains(make_pair(distances[i], i)) && weight < distances[i]) {
				to_process.decrease_key(make_pair(distances[i], i), make_pair(weight, i));
				distances[i] = weight;
			}

		}
	}

	fout << treecost << endl;

	return 0;
}