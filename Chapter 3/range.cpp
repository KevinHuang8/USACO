/*
ID: Kevun1
LANG: C++11
TASK: range
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
ifstream fin("range.in");
ofstream fout("range.out");

int field[251][251];
//DP array
//largest[i][j] - largest square possible with (i,j) as the bottom right corner
//largest[i][j] = min(largest[i - 1][j], largest[i][j - 1], largest[i - 1][j - 1]) + 1, if field[i][j] == 1
int largest[251][251] = { 0 };
//sizes[s] = number of squares of size s in the entire field
int sizes[251] = { 0 };

/*
DP
*/
int main(){
	int n;
	fin >> n;
	string line;
	for (int i = 0; i < n; ++i) {
		fin >> line;
		for (int j = 0; j < n; ++j) {
			field[i][j] = line[j] - 48;
		}
	}

	for (int i = 0; i < n; ++i) {
		if (field[0][i] == 1)
			largest[0][i] = 1;
		if (field[i][0] == 1)
			largest[i][0] = 1;
	}

	for (int i = 1; i < n; ++i) {
		for (int j = 1; j < n; ++j) {
			if (field[i][j] == 1) {
				largest[i][j] = min(min(largest[i][j - 1], largest[i - 1][j]), largest[i - 1][j - 1]) + 1;
				//if you can make a square of size largest[i][j], you can make a square of all sizes below that
				for (int s = 2; s <= largest[i][j]; ++s) {
					++sizes[s];
				}
			}
		}
	}

	for (int i = 2; i <= n; ++i) {
		if (sizes[i])
			fout << i << " " << sizes[i] << endl;
	}

	return 0;
}