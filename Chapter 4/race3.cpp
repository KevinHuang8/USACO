/*
ID: Kevun1
LANG: C++11
TASK: race3
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
#include <unordered_set>
#define INF 2100000000
using namespace std;


//ifstream fin("in.txt");
//ofstream fout("out.txt");
ifstream fin("race3.in");
ofstream fout("race3.out");

unordered_map<int, vector<int>> adjacency_list;
int dist[51][51];
//dist_wo[a][b][s] - dist from a to b without s;
int dist_wo[51][51][51];

//Adds value to m[key], and creates a new vector if it doesn't exist
template <typename T, typename U, typename Hash>
void add_map(T key, U value, unordered_map<T, vector<U>, Hash>& m) {
	if (m.find(key) == m.end()) {
		vector<U> v;
		m[key] = v;
	}
	m[key].push_back(value);
}

vector<int> intersection(vector<int> a, vector<int> b) {
	vector<int> result;
	for (int i : a) {
		if (find(b.begin(), b.end(), i) != b.end())
			result.push_back(i);
	}
	return result;
}

void bfs(int source) {
	unordered_set<int> visited;
	dist[source][source] = INF;
	if (find(adjacency_list[source].begin(), adjacency_list[source].end(), source) != adjacency_list[source].end())
		dist[source][source] = 1;
	int level = 1;
	vector<int> frontier = { source };
	vector<int> next_frontier;
	while (!frontier.empty()) {
		next_frontier.clear();
		for (int node : frontier) {
			for (int adj : adjacency_list[node]) {
				if (visited.find(adj) == visited.end()) {
					dist[source][adj] = level;
					next_frontier.push_back(adj);
					visited.insert(adj);
				}
			}
		}
		frontier = next_frontier;
		++level;
	}
}

void bfs(int source, int unavoidable) {
	unordered_set<int> visited;
	visited.insert(unavoidable);
	dist_wo[source][source][unavoidable] = INF;
	if (find(adjacency_list[source].begin(), adjacency_list[source].end(), source) != adjacency_list[source].end())
		dist_wo[source][source][unavoidable] = 1;
	int level = 1;
	vector<int> frontier = { source };
	vector<int> next_frontier;
	while (!frontier.empty()) {
		next_frontier.clear();
		for (int node : frontier) {
			for (int adj : adjacency_list[node]) {
				if (visited.find(adj) == visited.end()) {
					dist_wo[source][adj][unavoidable] = level;
					next_frontier.push_back(adj);
					visited.insert(adj);
				}
			}
		}
		frontier = next_frontier;
		++level;
	}
}

void reset_dist() {
	for (int i = 0; i < 51; ++i) {
		for (int j = 0; j < 51; ++j) {
			dist[i][j] = INF;
			for (int k = 0; k < 51; ++k) {
				dist_wo[i][j][k] = INF;
			}
		}
	}
}

int main(){
	int in;
	fin >> in;
	int n = 0;
	while (in != -1) { 
		while (in != -2) {
			add_map(n, in, adjacency_list);
			fin >> in;
		}
		++n;
		fin >> in;
	}

	reset_dist();
	vector<int> unavoidables;

	//BFS from start to finish, except with a different node removed each time
	//if you remove a node and can't get from start to finish, then you know its unavoidable
	for (int i = 1; i < n - 1; ++i) {
		bfs(0, i);
		if (dist_wo[0][n - 1][i] == INF)
			unavoidables.push_back(i);
	}

	fout << unavoidables.size();
	if (unavoidables.size() > 0) {

		fout << " ";

		for (int i = 0; i < unavoidables.size() - 1; ++i) {
			fout << unavoidables[i] << " ";
		}
		fout << unavoidables.back();
	}
	fout << endl;

	for (int i = 0; i < n; ++i) {
		bfs(i);
	}
	
	vector<int> splittables;
	/*
	In order for s to be splittable, two well-defined courses have to be formed with s
	as the only common point and without any common arrows. 
	(s is the finish of the first and the start of the second)
	So for each of the two courses:
		1. Every point in the course can be reached from the start.
		2. The finish can be reached from each point in the course.
		3. The finish has no outgoing arrows.

	First assume the first course is well-defined. 1. is trivially satisfied because the start
	is just the start of the entire course, which is given as well-defined. 3. is also satisfied because
	we assume that any arrows leaving s are not part of the 1st course. To satisfy 2., we include all points
	that can reach s from start without going through s.

	Then the second course must also be well-defined. 2. and 3. are trivially satisfied since the finish is given
	by the input. To satisfy 1., we include all points that are reachable from s.
	
	s can only be a unavoidable point, or else there will be another path from course1 to course2,
	meaning there will be a common arrow.

	Course1 and Course2 cannot have any points in common, because that would violate the condition that 
	s is the only point in common.

	so (course1 intersect course2) == null && s in unavoidable
	in order for s to be a splittable point
	*/
	for (int s : unavoidables) {
		vector<int> course1, course2;
		course1.push_back(0);
		for (int i = 0; i < n; ++i) {
			//s is reachable from i
			if (dist_wo[0][i][s] != INF)
				course1.push_back(i);
			//i is reachable from s
			if (dist[s][i] != INF)
				course2.push_back(i);
		}
		if (intersection(course1, course2).empty()) {
			splittables.push_back(s);
		}
	}

	fout << splittables.size();
	if (splittables.size() > 0) {
		fout << " ";

		for (int i = 0; i < splittables.size() - 1; ++i) {
			if (splittables.size() == 0)
				break;
			fout << splittables[i] << " ";
		}
		fout << splittables.back();
	}

	fout << endl;

	return 0;
}