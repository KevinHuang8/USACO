/*
ID: Kevun1
LANG: C++11
TASK: cowtour
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <iomanip>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <utility>
#include <numeric>
using namespace std;

//ifstream fin("in.txt");
//ofstream fout("out.txt");
ifstream fin("cowtour.in");
ofstream fout("cowtour.out");

//euclidean distance between point a and b
double distance(pair<int, int> a, pair<int, int> b) {
	return sqrt(pow((a.first - b.first), 2) + pow((a.second - b.second), 2));
}

int n;
vector<pair<int, int>> pastures;
int adjacency_matrix[150][150];
//dist[a][b] = shortest path between a and b
double dist[150][150];
//max_dist[p] = maximum shortest path originating from pasture p
double max_dist[150];
//diameters[f] = diameter of field f
double diameters[150];
//field[p] = field pasture p belongs to
unordered_map<int, int> field;

void floyd_warshall() {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (adjacency_matrix[i][j])
				dist[i][j] = distance(pastures[i], pastures[j]);
			else
				dist[i][j] = 10000000; //infinity
		}
	}

	for (int k = 0; k < n; ++k) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (dist[i][k] + dist[k][j] < dist[i][j])
					dist[i][j] = dist[i][k] + dist[k][j];
			}
		}
	}
}

/*
All pairs shortest paths
*/
int main(){
	fin >> n;
	for (int i = 0; i < n; ++i) {
		int x, y;
		fin >> x >> y;
		pastures.push_back(make_pair(x, y));
	}
	for (int i = 0; i < n; ++i) {
		string line;
		fin >> line;
		for (int j = 0; j < n; ++j) {
			if (line[j] == '1') {
				adjacency_matrix[i][j] = 1;
			}
			else
				adjacency_matrix[i][j] = 0;
		}
	}

	floyd_warshall();

	//calculate which field each pasture belongs to
	int f = 0;
	for (int p1 = 0; p1 < n; ++p1) {
		if (field.find(p1) == field.end()) {
			field[p1] = f;
			++f;
		}
		for (int p2 = 0; p2 < n; ++p2) {
			if (dist[p1][p2] < 10000000) {
				field[p2] = field[p1];
			}
		}
	}
	
	//for each pasture, find the maximum shortest path from it to any other pasture within the same field
	//the reason is that if the new connected path includes the pasture, then the diameter will be calculated
	//using this value
	for (int p1 = 0; p1 < n; ++p1) {
		double farthest = 0;
		for (int p2 = 0; p2 < n; ++p2) {
			if (p1 == p2)
				continue;
			//the two pastures must be within the same field
			if (dist[p1][p2] < 10000000) {
				if (dist[p1][p2] > farthest)
					farthest = dist[p1][p2];
			}
		}
		max_dist[p1] = farthest;
	}

	//calculate field diameters
	for (int i = 0; i < f; ++i) {
		double longest_diam = 0;
		for (int p1 = 0; p1 < n; ++p1) {
			if (field[p1] != i)
				continue;
			if (max_dist[p1] > longest_diam)
				longest_diam = max_dist[p1];
		}
		diameters[i] = longest_diam;
	}

	//choose 2 pastures to connect
	double best_distance = 9999999;
	for (int p1 = 0; p1 < n; ++p1) {
		for (int p2 = 0; p2 < n; ++p2) {
			if (p1 == p2)
				continue;
			//must be pastures on different fields
			if (dist[p1][p2] < 10000000)
				continue;
			//total diameter
			//you have to take into consideration the diameters of the original field b/c the new path
			//might not be the longest shorter path
			//for example if a pasture is in between another like this:
			//           D
			//			 1
			// A----10---B---10---C
			//the correct answer is 20, because ABD is only 11
			double d = max(max_dist[p1] + distance(pastures[p1], pastures[p2]) + max_dist[p2], 
				max(diameters[field[p1]], diameters[field[p2]]));

			if (d < best_distance)
				best_distance = d;
		}
	}
	
	fout << fixed;
	fout << setprecision(6);
	fout << best_distance << endl;

	return 0;
}