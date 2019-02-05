/*
ID: Kevun1
LANG: C++11
TASK: holstein
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
ifstream fin("holstein.in");
ofstream fout("holstein.out");

vector<int> requirements;
vector<vector<int>> feeds;
int lowest_scoops = 99999;
int n_feeds;
vector<int> list_of_scoops;


vector<int> add_scoop(vector<int> base, vector<int> amounts) {
	for (int i = 0; i < amounts.size(); ++i) {
		base[i] += amounts[i];
	}
	return base;
}

bool meet_requirements(vector<int> amounts) {
	for (int i = 0; i < amounts.size(); ++i) {
		if (amounts[i] < requirements[i])
			return false;
	}
	return true;
}

vector<int> include_scoop(vector<int> scoop_list, int new_scoop) {
	scoop_list.push_back(new_scoop);
	return scoop_list;
}

//DFS for all possible combinations of scoops
void search(vector<int> vitamins, int f, int scoops, vector<int> scoops_used) {
	if (f >= n_feeds) {
		if (meet_requirements(vitamins) && scoops < lowest_scoops) {
			lowest_scoops = scoops;
			list_of_scoops = scoops_used;
		}
		return;
	}

	//either include or not include scoop
	search(add_scoop(vitamins, feeds[f]), f + 1, scoops + 1, include_scoop(scoops_used, f + 1));
	search(vitamins, f + 1, scoops, scoops_used);
}

int main(){

	int n_vitamins;
	fin >> n_vitamins;
	for (int i = 0; i < n_vitamins; ++i) {
		int vit;
		fin >> vit;
		requirements.push_back(vit);
	}
	fin >> n_feeds;
	for (int i = 0; i < n_feeds; ++i) {
		vector<int> v;
		for (int j = 0; j < n_vitamins; ++j) {
			int vit;
			fin >> vit;
			v.push_back(vit);
		}
		feeds.push_back(v);
	}

	vector<int> base(n_vitamins);
	vector<int> x;
	search(base, 0, 0, x);

	fout << lowest_scoops << " ";

	for (int i = 0; i < list_of_scoops.size() - 1; ++i) {
		fout << list_of_scoops[i] << " ";
	}
	fout << list_of_scoops.back() << endl;
	return 0;
}