
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
ifstream fin("lasers.in");
ofstream fout("lasers.out");

struct key_hash : public unary_function<pair<int, char>, size_t>
{
	size_t operator()(const pair<int, char>& k) const
	{
		return k.first ^ k.second;
	}
};

unordered_set<int> xcoords;
unordered_set<int> ycoords;
unordered_set<pair<int, int>, key_hash> posts;

int dist[100001] = { 0 };

int main(){
	int n;
	fin >> n;

	int x0, y0;
	fin >> x0 >> y0;
	int xb, yb;
	fin >> xb >> yb;

	posts.insert(make_pair(x0, y0));
	for (int i = 1; i <= n; ++i) {
		int x, y;
		fin >> x >> y;
		xcoords.insert(x);
		ycoords.insert(y);
		posts.insert(make_pair(x, y));
	}
	xcoords.insert(xb);
	ycoords.insert(yb);
	posts.insert(make_pair(xb, yb));

	unordered_set<pair<int, char>, key_hash> visited;
	int dist = -1;
	int level = 1;
	bool found = false;
	vector<pair<int, char>> frontier = { make_pair(x0, 'x'), make_pair(y0, 'y') };
	visited.insert(make_pair(x0, 'x')); visited.insert(make_pair(y0, 'y'));
	while (!frontier.empty()) {
		vector<pair<int, char>> next_frontier;
		for (pair<int, char> node : frontier) {
			if (node.second == 'x') {
				for (int y : ycoords) {
					if (posts.find(make_pair(node.first, y)) != posts.end()
						&& visited.find(make_pair(y, 'y')) == visited.end()) {
						visited.insert(make_pair(y, 'y'));
						next_frontier.push_back(make_pair(y, 'y'));
						if (y == yb) {
							dist = level;
							next_frontier.clear();
							break;
						}
					}
				}
			}

			else if (node.second == 'y') {
				for (int x : xcoords) {
					if (posts.find(make_pair(x, node.first)) != posts.end()
						&& visited.find(make_pair(x, 'x')) == visited.end()) {
						visited.insert(make_pair(x, 'x'));
						next_frontier.push_back(make_pair(x, 'x'));
						if (x == xb) {
							dist = level;
							next_frontier.clear();
							break;
						}
					}
				}
			}
		}
		frontier = next_frontier;
		++level;
	}

	fout << dist << endl;


	return 0;
}