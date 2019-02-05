/*
ID: Kevun1
LANG: C++11
TASK: frameup
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <set>
#include <unordered_set>
#include <utility>
#include <numeric>
#define INF 210000000
using namespace std;

char board[31][31];
int top[27];
int leftframe[27];
int rightframe[27];
int bottom[27];

//ifstream fin("in.txt");
//ofstream fout("out.txt");
ifstream fin("frameup.in");
ofstream fout("frameup.out");

//Adds value to m[key], and creates a new set if it doesn't exist, uses set<U>
template <typename T, typename U, typename Hash>
void add_map(T key, U value, unordered_map<T, set<U>, Hash>& m) {
	if (m.find(key) == m.end()) {
		set<U> s;
		m[key] = s;
	}
	m[key].insert(value);
}

//on_top[c] - all frames that are on top of c
unordered_map<char, set<char>> on_top;
set<char> frames;
vector<string> sequences;
unordered_set<int> used;

//can only add a frame if all other frames on top of it are already in s
bool can_add(string s, char frame) {
	for (char c : on_top[frame]) {
		if (find(s.begin(), s.end(), c) == s.end())
			return false;
	}
	return true;
}

//s - top to bottom
//dfs to recursively generate all possible sequences, accepting only ones
//that satisfy the constraints establishe by on_top
void build_sequence(string s) {
	
	if (s.length() == frames.size()) {
		reverse(s.begin(), s.end());
		sequences.push_back(s);
		return;
	}

	for (char f : frames) {
		if (used.find(f) == used.end() && can_add(s, f)) {
			used.insert(f);
			build_sequence(s + string(1, f));
			used.erase(f);
		}
	}

}
/*
Dfs
*/
int main(){
	for (int i = 0; i < 26; ++i) {
		top[i] = INF;
		leftframe[i] = INF;
		rightframe[i] = 0;
		bottom[i] = 0;
	}

	int h, w;
	fin >> h >> w;
	string s;
	for (int i = 0; i < h; ++i) {
		fin >> s;
		for (int j = 0; j < w; ++j) {
			board[i][j] = s[j];
		}
	}

	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			char c = board[i][j];
			if (c == '.')
				continue;
			frames.insert(c);
			if (i < top[c - 65])
				top[c - 65] = i;
			if (i > bottom[c - 65])
				bottom[c - 65] = i;
			if (j < leftframe[c - 65])
				leftframe[c - 65] = j;
			if (j > rightframe[c - 65])
				rightframe[c - 65] = j;
		}
	}
	//walk through every position a frame is supposed to be in. If another frame is found instead,
	//that means it is on top of it
	for (char f : frames) {
		set<char> s;
		on_top[f] = s;
		int T = top[f - 65];
		int B = bottom[f - 65];
		int L = leftframe[f - 65];
		int R = rightframe[f - 65];
		//top side
		for (int j = L; j <= R; ++j) {
			char c = board[T][j];
			if (c == f || c == '.')
				continue;
			add_map(f, c, on_top);

		}
		//left side
		for (int i = T; i <= B; ++i) {
			char c = board[i][L];
			if (c == f || c == '.')
				continue;
			add_map(f, c, on_top);
		}
		//bottom side
		for (int j = L; j <= R; ++j) {
			char c = board[B][j];
			if (c == f || c == '.')
				continue;
			add_map(f, c, on_top);
		}
		//right side 
		for (int i = T; i <= B; ++i) {
			char c = board[i][R];
			if (c == f || c == '.')
				continue;
			add_map(f, c, on_top);
		}

	}

	build_sequence("");

	sort(sequences.begin(), sequences.end());

	for (string seq : sequences) {
		fout << seq << endl;
	}

	return 0;
}