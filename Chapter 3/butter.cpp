/*
ID: Kevun1
LANG: C++11
TASK: butter
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <utility>
#include <numeric>
using namespace std;


//ifstream fin("in.txt");
//ofstream fout("out.txt");
ifstream fin("butter.in");
ofstream fout("butter.out");

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

//Adds value to m[key], and creates a new vector if it doesn't exist
template <typename T, typename U, typename Hash>
void add_map(T key, U value, unordered_map<T, vector<U>, Hash>& m) {
	if (m.find(key) == m.end()) {
		vector<U> v;
		m[key] = v;
	}
	m[key].push_back(value);
}

vector<int> cows;
set<int> pastures;
unordered_map<int, vector<int>> adjacency_list;
short weight[801][801];
int distances[801][801];
int dist[801];

void dijkstra(int source) {	
	vector<pair<int, int>> v;
	for (int i = 0; i < 801; ++i) {
		if (i == source) {
			dist[source] = 0;
			distances[source][source] = 0;
			v.push_back(make_pair(0, source));
			continue;
		}
		dist[i] = 2100000000;
		v.push_back(make_pair(dist[i], i));
	}

	Heap<pair<int, int>> to_process(v);
	while (!to_process.empty()) {
		pair<int, int> node = to_process.extract_min();
		for (int adj : adjacency_list[node.second]) {
			if (dist[adj] > dist[node.second] + weight[node.second][adj]) {
				to_process.decrease_key(make_pair(dist[adj], adj), make_pair(dist[node.second] + weight[node.second][adj], adj));
				dist[adj] = dist[node.second] + weight[node.second][adj];
				distances[source][adj] = dist[adj];
			}
		}
	}
}

int main(){
	//c - num of cows, p - num of pastures, n - num of paths
	int c, p, n;
	fin >> c >> p >> n;
	for (int i = 0; i < c; ++i) {
		int cow;
		fin >> cow;
		cows.push_back(cow);
	}
	for (int i = 0; i < n; ++i) {
		int p1, p2, w;
		fin >> p1 >> p2 >> w;
		pastures.insert(p1);
		pastures.insert(p2);
		add_map(p1, p2, adjacency_list);
		add_map(p2, p1, adjacency_list);
		weight[p1][p2] = w;
		weight[p2][p1] = w;
	}

	unordered_set<int> calculated;
	for (int i : cows) {
		if (calculated.find(i) != calculated.end())
			continue;
		calculated.insert(i);
		dijkstra(i);
	}

	int shortest_dist = 2100000000;
	int total_dist = 0;
	//which pasture to place candy on
	for (int pasture : pastures) {
		total_dist = 0;
		for (int cow : cows) {
			total_dist += distances[cow][pasture];
		}
		shortest_dist = min(total_dist, shortest_dist);
	}

	fout << shortest_dist << endl;

	return 0;
}