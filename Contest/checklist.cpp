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
#define INF 10e20
using namespace std;

long long fix_double(double d, double tolerance = 0.00001) {
	long long result;
	if (d - (long long)d < tolerance) {
		result = (long long)d;
	}
	else if ((long long)d + 1 - d < tolerance) {
		result = (long long)d + 1;
	}
	return result;
}

ifstream fin("in.txt");
ofstream fout("out.txt");
//ifstream fin("checklist.in");
//ofstream fout("checklist.out");

//H[i][j] = cost to get to end if you are at h_i, and you have visited g_1...g_j
//G[i][j] = cost to get to end if you are at g_j and you have visited h_1...h_i
//H[i][j] = min(H[i + 1][j] + dist[h_i, h_i+1], G[i][j + 1] + dist[h_i, g_j+1])
//G[i][j] = min(H[i + 1][j] + dist[g_j, h_i+1], G[i][j + 1] + dist[g_j, g_j+1])
//either visit next h or next g
double H[1001][1001];
double G[1001][1001];

vector<pair<int, int>> holsteins;
vector<pair<int, int>> guernseys;

double distance(pair<int, int> a, pair<int, int> b) {
	return sqrt(pow((a.first - b.first), 2) + pow((a.second - b.second), 2));
}

int main(){
	int h, g;
	fin >> h >> g;
	holsteins.push_back(make_pair(-1, -1));
	guernseys.push_back(make_pair(-1, -1));
	for (int i = 0; i < h; ++i) {
		int x, y;
		fin >> x >> y;
		holsteins.push_back(make_pair(x, y));
	}
	for (int i = 0; i < g; ++i) {
		int x, y;
		fin >> x >> y;
		guernseys.push_back(make_pair(x, y));
	}
	holsteins.push_back(make_pair(-1, -1));
	guernseys.push_back(make_pair(-1, -1));

	//cannot go to g that doesn't exist
	for (int i = 0; i <= h; ++i) {
		H[i][g + 1] = INF;
		G[i][g + 1] = INF;
	}
	//can't go to last h without visiting all g first
	for (int j = 0; j < g; ++j) {
		H[h][j] = INF;
	}

	H[h][g] = 0;

	for (int i = h - 1; i >= 0; --i) {
		for (int j = g; j >= 0; --j) {
			H[i][j] = min(H[i + 1][j] + pow(distance(holsteins[i], holsteins[i + 1]), 2),
				G[i][j + 1] + pow(distance(holsteins[i], guernseys[j + 1]), 2));
			G[i][j] = min(H[i + 1][j] + pow(distance(guernseys[j], holsteins[i + 1]), 2),
				G[i][j + 1] + pow(distance(guernseys[j], guernseys[j + 1]), 2));
		}
	}

	long long answer = fix_double(H[1][0]);

	fout << answer << endl;

	return 0;
}