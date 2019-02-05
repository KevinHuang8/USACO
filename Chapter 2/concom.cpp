/*
ID: Kevun1
LANG: C++11
TASK: concom
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <utility>
#include <numeric>
using namespace std;


//ifstream fin("in.txt");
//ofstream fout("out.txt");
ifstream fin("concom.in");
ofstream fout("concom.out");

struct comp {
	int share, other_company;
	comp(int s, int o) : share(s), other_company(o) {}
};

unordered_map<int, vector<comp>> adjacency_list;
set<int> companies;
//share[c1][c2] = percent share of c2 that c1 owns, directly + indirectly
int share[101][101];

//adds comp(p, c2) to adjacency_list[c1]
//creates a new vector if c1 is a new key
void build_graph(int c1, int c2, int p) {
	if (adjacency_list.find(c1) == adjacency_list.end()) {
		vector<comp> v;
		adjacency_list[c1] = v;
	}
	comp c(p, c2);
	adjacency_list[c1].push_back(c);
}

//the visited nodes end up being the companies that 'source' controls
set<int> visited;
void dfs(int source, int node) {
	for (auto adj : adjacency_list[node]) {
		share[source][adj.other_company] += adj.share;
	
		//only recurse on controlled companies, which have a combined control percentage > 50
		//do not recurse on a node twice
		if (share[source][adj.other_company] >= 50 && visited.find(adj.other_company) == visited.end()) {
			visited.insert(adj.other_company);
			dfs(source, adj.other_company);
		}
	}
}
/*
DFS on a directed graph
*/
int main(){
	int n;
	fin >> n;
	memset(share, 0, sizeof(share));

	int company1, company2, percentage;
	while (fin >> company1 >> company2 >> percentage) {
		companies.insert(company1);
		companies.insert(company2);
		build_graph(company1, company2, percentage);
	}

	for (int c : companies) {
		//every company controls itself
		share[c][c] = 100;
	}

	for (int c : companies) {
		visited.insert(c);
		dfs(c, c);
		for (int c2 : visited) {
			if (c != c2)
				fout << c << " " << c2 << endl;
		}
		//reset visited for each new source
		set<int> empty_visited;
		visited = empty_visited;
	}

	return 0;
}