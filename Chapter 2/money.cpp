/*
ID: Kevun1
LANG: C++11
TASK: money
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
ifstream fin("money.in");
ofstream fout("money.out");

//DP array
//combos[m][c] = number of ways to make m money with first c coins
//combos[m][c] = combos[m, c - 1] + combos[m - k, c]; k = value of cth coin
//  = (ways to make c w/o last coin) + (ways to make [c - k] w/ at least one of the last coin, value k)
long long combos[10001][26];

int main(){
	int v, n;
	fin >> v >> n;
	vector<int> coins;
	for (int i = 0; i < v; ++i) {
		int coin;
		fin >> coin;
		coins.push_back(coin);
	}
	sort(coins.begin(), coins.end());

	//can't make any amount of money without any coins
	for (int m = 1; m <= n; ++m) {
		combos[m][0] = 0;
	}
	//one way to make zero coins (don't choose anything)
	for (int c = 0; c <= v; ++c) {
		combos[0][c] = 1;
	}

	for (int c = 1; c <= v; ++c) {
		for (int m = 1; m <= n; ++m) {
			combos[m][c] = combos[m][c - 1];
			//coins[c - 1] is value of the cth coin
			//must do -1 because the coins array is zero indexed
			if (m - coins[c - 1] >= 0)
				combos[m][c] += combos[m - coins[c - 1]][c];
		}
	}

	fout << combos[n][v] << endl;
	return 0;
}