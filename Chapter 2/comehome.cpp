/*
ID: Kevun1
LANG: C++11
TASK: comehome
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <unordered_map>
#include <set>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <utility>
#include <numeric>
using namespace std;

//ifstream fin("in.txt");
//ofstream fout("out.txt");
ifstream fin("comehome.in");
ofstream fout("comehome.out");

int weight[123][123];
int dist[123][123];

set<char> cow_locations;
/*
Shortest Paths
*/
int main(){
	int n;
	fin >> n;
	for (int i = 0; i < 123; ++i) {
		for (int j = 0; j < 123; ++j) {
			weight[i][j] = 100000000;
		}
	}

	for (int i = 0; i < n; ++i) {
		char a, b;
		int d;
		fin >> a >> b >> d;
		if (isupper(a) && a != 'Z')
			cow_locations.insert(a);
		if (isupper(b) && b != 'Z')
			cow_locations.insert(b);
		if (d < weight[a][b]) {
			weight[a][b] = d;
			weight[b][a] = d;
		}
	}

	//floyd warshall
	for (int i = 0; i < 123; ++i) {
		for (int j = 0; j < 123; ++j) {
			dist[i][j] = weight[i][j];
		}
	}
	for (int k = 0; k < 123; ++k) {
		for (int i = 0; i < 123; ++i) {
			for (int j = 0; j < 123; ++j) {
				if (dist[i][k] + dist[k][j] < dist[i][j])
					dist[i][j] = dist[i][k] + dist[k][j];
			}
		}
	}

	int min_distance = 99999;
	char min_cow;
	for (int cow : cow_locations) {
		if (dist[90][cow] < min_distance) {
			min_distance = dist[90][cow];
			min_cow = cow;
		}
	}

	fout << min_cow << " " << min_distance << endl;

	return 0;
}