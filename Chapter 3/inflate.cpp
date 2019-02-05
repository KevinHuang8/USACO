/*
ID: Kevun1
LANG: C++11
TASK: inflate
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
ifstream fin("inflate.in");
ofstream fout("inflate.out");

//points[m][k] = best way to use m modules w/ first k problems
//points[m][k] = max(points[m - p.t][k] + p.points, points[m][k - 1]
//either include the kth category or don't
//this can be reduced to a 1D array, eliminate k, b/c only depends on k-1
int points[10001];

/*
DP
*/
int main(){
	int m, n;
	fin >> m >> n;
	vector<pair<int, int>> problems;
	for (int i = 0; i < n; ++i) {
		int t, p;
		fin >> p >> t;
		pair<int, int> prob = make_pair(p, t);
		problems.push_back(prob);
	}
	points[0] = 0;
	for (int t = 1; t <= m; ++t) {
		for (auto p : problems) {
			if (p.second > t)
				continue;
			points[t] = max(points[t - p.second] + p.first, points[t]);
		}
	}
	fout << points[m] << endl;

	return 0;
}