/*
ID: Kevun1
LANG: C++11
TASK: fence
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <tuple>
#include <set>
#include <algorithm>
#include <cmath>
#include <utility>
#include <numeric>
using namespace std;


//ifstream fin("in.txt");
//ofstream fout("out.txt");
ifstream fin("fence.in");
ofstream fout("fence.out");

//Adds value to m[key], and creates a new vector if it doesn't exist, uses set<U>
template <typename T, typename U, typename Hash>
void add_map(T key, U value, unordered_map<T, vector<U>, Hash>& m) {
	if (m.find(key) == m.end()) {
		vector<U> s;
		m[key] = s;
	}
	m[key].push_back(value);
}
int circuit[50001];
int position = 0;
unordered_map<int, vector<int>> adjacency_list;

//remove first instance of element in v, does not keep order
template <typename T>
void remove_element(vector<T> &v, T element) {
	auto it = find(v.begin(), v.end(), element);

	if (it != v.end()) {
		swap(*it, v.back());
		v.pop_back();
	}
}

void euler_tour(int node) {
	if (adjacency_list[node].empty()) {
		circuit[position] = node;
		++position;
	}
	else {
		while (!adjacency_list[node].empty()) {
			//select adj of node
			int adj = *(min_element(adjacency_list[node].begin(), adjacency_list[node].end()));
			//delete edge between node and adj
			remove_element(adjacency_list[node], adj);
			remove_element(adjacency_list[adj], node);
			euler_tour(adj);
		}
		circuit[position] = node;
		++position;
	}
}
/*
Euler Tour
*/
int main(){
	int n;
	fin >> n;
	set<int> verticies;
	for (int i = 0; i < n; ++i) {
		int a, b;
		fin >> a >> b;
		verticies.insert(a);
		verticies.insert(b);
		add_map(a, b, adjacency_list);
		add_map(b, a, adjacency_list);
	}

	int odd_count = 0;
	vector<int> odd_verticies;
	for (int v : verticies) {
		if (adjacency_list[v].size() % 2 == 1) {
			odd_verticies.push_back(v);
			++odd_count;
		}
	}
	int initial_node;
	if (odd_count == 2) {
		initial_node = min(odd_verticies[0], odd_verticies[1]);
	}
	else {
		initial_node = *(verticies.begin());
	}

	euler_tour(initial_node);

	for (int i = position - 1; i >= 0; --i) {
		fout << circuit[i] << endl;
	}

	return 0;
}