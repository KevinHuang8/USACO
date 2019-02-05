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

vector<pair<int, int>> cows;

double distance(pair<int, int> a, pair<int, int> b) {
	return sqrt(pow((a.first - b.first), 2) + pow((a.second - b.second), 2));
}

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
double distances[1001];
int n;

double prim(int source) {
	double max_dist = 0;
	vector<pair<double, int>> v;
	for (int i = 0; i < n; ++i) {
		if (i == source) {
			distances[source] = 0.0;
			v.push_back(make_pair(0.0, source));
		}
		else {
			distances[i] = 2147483647.0;
			v.push_back(make_pair(distances[i], i));
		}
	}

	Heap<pair<double, int>> to_process(v);
	while (!to_process.empty()) {
		pair<double, int> node = to_process.extract_min();
		if (distances[node.second] > max_dist)
			max_dist = distances[node.second];
		for (int i = 0; i < n; ++i) {
			if (i == node.second)
				continue;
			int adj = i;
			double weight = distance(cows[i], cows[node.second]);

			if (to_process.contains(make_pair(distances[adj], adj)) && weight < distances[adj]) {
				to_process.decrease_key(make_pair(distances[adj], adj), make_pair(weight, adj));
				distances[adj] = weight;
			}
		}
	}
	return max_dist;
}

int main(){
	fin >> n;

	for (int i = 0; i < n; ++i) {
		int x, y;
		fin >> x >> y;
		cows.push_back(make_pair(x, y));
	}

	double max_dist = prim(0);

	double square = pow(max_dist, 2);
	if (square - (int)square < 0.0001) {
		fout << (int)square << endl;
	}
	else {
		fout << (int)ceil(square) << endl;
	}

	return 0;
}