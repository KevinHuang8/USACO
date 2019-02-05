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
ifstream fin("cownav.in");
ofstream fout("cownav.out");


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

int board[21][21];

struct location {
	int i;
	int j;
	char direction;
	location(int a, int b, char c)
		: i(a), j(b), direction(c) {}
};

int main(){
	int n;
	fin >> n;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			char c;
			fin >> c;
			if (c == 'E')
				board[i][j] = 1;
			else
				board[i][j] = 0;
		}
	}


	unordered_set<pair<int, int>, key_hash> visited;
	unordered_map<pair<int, int>, int, key_hash> dist;

	int level = 1;
	vector<pair<int, int>> frontier = { make_pair(n - 1, 0) };
	while (!frontier.empty()) {
		vector<pair<int, int>> next_frontier;
		for (pair<int, int> node : frontier) {
			//go up
			if (node.first != 0 && board[node.first - 1][node.second]) {
				if (visited.find(make_pair(node.first - 1, node.second)) == visited.end()) {
					visited.insert(make_pair(node.first - 1, node.second));
					next_frontier.push_back(make_pair(node.first - 1, node.second));
					dist[make_pair(node.first - 1, node.second)] = level;
				}
			}
			//go right
			if (node.second != n - 1 && board[node.first][node.second + 1]) {
				if (visited.find(make_pair(node.first, node.second + 1)) == visited.end()) {
					visited.insert(make_pair(node.first, node.second + 1));
					next_frontier.push_back(make_pair(node.first, node.second + 1));
					dist[make_pair(node.first, node.second + 1)] = level;
				}
			}
			//go down
			if (node.first	!= n - 1 && board[node.first + 1][node.second]) {
				if (visited.find(make_pair(node.first + 1, node.second)) == visited.end()) {
					visited.insert(make_pair(node.first + 1, node.second));
					next_frontier.push_back(make_pair(node.first + 1, node.second));
					dist[make_pair(node.first + 1, node.second)] = level;
				}
			}
			//go left
			if (node.second != 0 && board[node.first][node.second - 1]) {
				if (visited.find(make_pair(node.first, node.second - 1)) == visited.end()) {
					visited.insert(make_pair(node.first, node.second - 1));
					next_frontier.push_back(make_pair(node.first, node.second - 1));
					dist[make_pair(node.first, node.second - 1)] = level;
				}
			}
		}
		frontier = next_frontier;
		level += 1;
	}

	fout << dist[make_pair(0, n - 1)]*2 + 1 << endl;

	return 0;
}