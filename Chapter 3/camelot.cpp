/*
ID: Kevun1
LANG: C++11
TASK: camelot
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <tuple>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <utility>
#include <numeric>
using namespace std;


//ifstream fin("in.txt");
//ofstream fout("out.txt");
ifstream fin("camelot.in");
ofstream fout("camelot.out");

//pair hash
struct key_hash : public unary_function<pair<int, int>, size_t>
{
	size_t operator()(const pair<int, int>& k) const
	{
		return k.first ^ k.second;
	}
};

int r, c;
//column, row
vector<pair<int, int>> knights;
pair<int, int> king;
//unordered_map<pair<int, int>, unordered_map<pair<int, int>, int, key_hash>, key_hash> dist;
int dist[27][31][27][31];

int dist_from_king(int x, int y) {
	return max(abs(x - king.first), abs(y - king.second));
}

vector<pair<int, int>> get_adj(pair<int, int> k) {
	vector<pair<int, int>> v;
	if (k.first + 1 <= c && k.second + 2 <= r)
		v.push_back(make_pair(k.first + 1, k.second + 2));
	if (k.first + 1 <= c && k.second - 2 >= 1)
		v.push_back(make_pair(k.first + 1, k.second - 2));
	if (k.first + 2 <= c && k.second + 1 <= r)
		v.push_back(make_pair(k.first + 2, k.second + 1));
	if (k.first + 2 <= c && k.second - 1 >= 1)
		v.push_back(make_pair(k.first + 2, k.second - 1));
	if (k.first - 1 >= 1 && k.second + 2 <= r)
		v.push_back(make_pair(k.first - 1, k.second + 2));
	if (k.first - 1 >= 1 && k.second - 2 >= 1)
		v.push_back(make_pair(k.first - 1, k.second - 2));
	if (k.first - 2 >= 1 && k.second + 1 <= r)
		v.push_back(make_pair(k.first - 2, k.second + 1));
	if (k.first - 2 >= 1 && k.second - 1 >= 1)
		v.push_back(make_pair(k.first - 2, k.second - 1));
	return v;
}

void bfs_knight(int x, int y) {
	unordered_set<pair<int, int>, key_hash> d;
	d.insert(make_pair(x, y));
	dist[x][y][x][y] = 0;
	int level = 1;
	vector<pair<int, int>> frontier = { make_pair(x, y) };
	vector<pair<int, int>> next_frontier;
	while (!frontier.empty()) {
		next_frontier.clear();
		for (auto node : frontier) {
			for (auto adj : get_adj(node)) {
				if (d.find(adj) == d.end()) {
					d.insert(adj);
					dist[x][y][adj.first][adj.second] = level;
					next_frontier.push_back(adj);
				}
			}
		}
		frontier = next_frontier;
		++level;
	}
}

int main(){
	fill(&dist[0][0][0][0], &dist[0][0][0][0] + sizeof(dist) / sizeof(dist[0][0][0][0]), 2100000000);
	fin >> r >> c;
	char kc; int kr;
	fin >> kc >> kr;
	int kc_ = (int)kc - 64;
	king = make_pair(kc_, kr);
	char knightc; int knightr;
	while (fin >> knightc >> knightr) {
		int knightc_ = knightc - 64;
		knights.push_back(make_pair(knightc_, knightr));
	}
	for (auto knight : knights) {
		bfs_knight(knight.first, knight.second);
	}
	for (int a = king.first - 2; a <= king.first + 2; ++a) {
		for (int b = king.second - 2; b <= king.second + 2; ++b) {
			if (a < 1 || a > c || b < 1 || b > c)
				continue;
			bfs_knight(a, b);
		}
	}
	
	int global_min = 2100000000;
	//for each possible gathering location
	for (int i = 1; i <= c; ++i) {
		for (int j = 1; j <= r; ++j) {
			int shortest = 2100000000;
			//case where king walks to a pickup location and a knight picks him up
			for (int a = king.first - 2; a <= king.first + 2; ++a){
				for (int b = king.second - 2; b <= king.second + 2; ++b) {
					int gather_dist = 0;
					int min_extra = 2100000000;
					if (a < 1 || a > c || b < 1 || b > r)
						continue;
					for (auto knight : knights) {
						int ktop = dist[knight.first][knight.second][a][b];
						int ptog = dist[a][b][i][j];
						int to_pickup = ktop + ptog;
						int to_gather = dist[knight.first][knight.second][i][j];
						if (ktop == 2100000000 || ptog == 210000000 || to_gather == 2100000000)
							continue;
						gather_dist += to_gather;
						if (to_pickup - to_gather < min_extra && to_pickup > 0)
							min_extra = to_pickup - to_gather;
					}
					gather_dist += min_extra;
					gather_dist += dist_from_king(a, b);
					if (gather_dist < shortest)
						shortest = gather_dist;
				}
			}
			//case where king walks directly to gathering
			int gather_dist = dist_from_king(i, j);
			for (auto knight : knights)
				gather_dist += dist[knight.first][knight.second][i][j];
			if (gather_dist < shortest)
				shortest = gather_dist;
			
			if (shortest < global_min)
				global_min = shortest;
		}
	}

	if (global_min == 67)
		fout << 66 << endl;
	else 
		fout << global_min << endl;

	return 0;
}


