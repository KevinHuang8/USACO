/*
ID: Kevun1
LANG: C++11
TASK: maze1
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
ifstream fin("maze1.in");
ofstream fout("maze1.out");

//pair hash
struct key_hash : public unary_function<pair<int, int>, size_t>
{
	size_t operator()(const pair<int, int>& k) const
	{
		return k.first ^ k.second;
	}
};
unordered_map<pair<int, int>, vector<pair<int, int>>, key_hash> adjacency_list;

//Adds value to m[key], and creates a new vector if it doesn't exist
template <typename T, typename U, typename Hash>
void add_map(T key, U value, unordered_map<T, vector<U>, Hash>& m) {
	if (m.find(key) == m.end()) {
		vector<U> v;
		m[key] = v;
	}
	m[key].push_back(value);
}

vector<pair<int, int>> exits;
int w, h;
/*
BFS on graph
*/
int main(){
	string x;
	getline(fin, x);
	w = stoi(x.substr(0, x.find(" ")));
	h = stoi(x.substr(x.find(" ")));

	string line;
	for (int i = 0; i < 2 * h + 1; ++i) {
		getline(fin, line);
		for (int j = 0; j < 2 * w + 1; ++j) {
			if (i % 2 == 1) {
				if (j % 2 == 1)
					continue;
				if ((j == 0 || j == 2 * w) && line[j] == ' ') {
					if (j == 0)
						exits.push_back(make_pair(i / 2, j / 2 - 1));
					if (j == 2 * w)
						exits.push_back(make_pair(i / 2, j / 2));
				}
				if (line[j] == ' ') {
					add_map(make_pair(i / 2, j / 2 - 1), make_pair(i / 2, j / 2), adjacency_list);
					add_map(make_pair(i / 2, j / 2), make_pair(i / 2, j / 2 - 1), adjacency_list);
				}
			}
			else if (i % 2 == 0) {
				if ((i == 0 || i == 2 * h) && line[j] == ' ') {
					if (i == 0)
						exits.push_back(make_pair(i / 2 - 1, j / 2));
					if (i == 2 * h)
						exits.push_back(make_pair(i / 2, j / 2));
				}
				if (line[j] == ' ') {
					add_map(make_pair(i / 2 - 1, j / 2), make_pair(i / 2, j / 2), adjacency_list);
					add_map(make_pair(i / 2, j / 2), make_pair(i / 2 - 1, j / 2), adjacency_list);
				}
			}
		}
	}

	//distances from exits 1 and 2
	unordered_map<pair<int, int>, int, key_hash> distance1;
	unordered_map<pair<int, int>, int, key_hash> distance2;
	//Breadth First Search in order to calculate distance
	distance1[exits[0]] = 0;
	int level = 1;
	vector<pair<int, int>> frontier = { exits[0] };
	vector<pair<int, int>> next_frontier;
	while (!frontier.empty()) {
		next_frontier.clear();
		for (auto node : frontier) {
			for (auto adj : adjacency_list[node]) {
				if (distance1.find(adj) == distance1.end()) {
					distance1[adj] = level;
					next_frontier.push_back(adj);
				}
			}
		}
		frontier = next_frontier;
		++level;
	}

	level = 1;
	frontier = { exits[1] };
	next_frontier.clear();
	distance2[exits[1]] = 0;
	while (!frontier.empty()) {
		next_frontier.clear();
		for (auto node : frontier) {
			for (auto adj : adjacency_list[node]) {
				if (distance2.find(adj) == distance2.end()) {
					distance2[adj] = level;
					next_frontier.push_back(adj);
				}
			}
		}
		frontier = next_frontier;
		++level;
	}
	
	int max_dist = 0;
	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			int dist = min(distance1[make_pair(i, j)], distance2[make_pair(i, j)]);
			if (dist > max_dist)
				max_dist = dist;
		}
	}

	fout << max_dist << endl;
	return 0;
}