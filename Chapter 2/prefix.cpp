/*
ID: Kevun1
LANG: C++11
TASK: prefix
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
ifstream fin("prefix.in");
ofstream fout("prefix.out");

//is_reachable[a] - whether or not you can have a prefix made from the primitives up to position a
bool is_reachable[200001];

/*
DP
*/
int main(){
	vector<string> primitives;
	string primitive;
	fin >> primitive;
	while (primitive != ".") {
		primitives.push_back(primitive);
		fin >> primitive;
	}

	string s;
	string row;
	while (fin >> row) {
		s += row;
	}

	int longest = 0;
	for (int i = 0; i < s.length(); ++i) {
		//walk through string, stopping only if you can get to the prefix using primitives
		if (!is_reachable[i] && i != 0)
			continue;
		for (string p : primitives) {
			if (s.substr(i, p.length()) == p) {
				//you know that the current prefix is reachable, so curr_prefix + primitive
				//must also be reachable
				is_reachable[i + p.length()] = true;
				if (i + p.length() > longest)
					longest = i + p.length();
			}
		}
	}

	fout << longest << endl;

	return 0;
}