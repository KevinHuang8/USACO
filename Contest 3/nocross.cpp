/*
ID: Kevun1
LANG: C++11
TASK: name
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <utility>
#include <unordered_set>
#include <set>
#include <map>
#include <queue>
#include <sstream>
#include <numeric>
using namespace std;


//ifstream fin("in.txt");
//ofstream fout("out.txt");
ifstream fin("nocross.in");
ofstream fout("nocross.out");

int x[5001];
int y[5001];

int dp[5001][5001];

int match(int a, int b) {
	if (abs(a - b) <= 4)
		return 1;
	else
		return 0;
}

int main(){
	int n;
	fin >> n;
	for (int i = 0; i < n; ++i) {
		fin >> x[i];
		dp[0][i] = 0;
		dp[i][0] = 0;
	}
	for (int i = 0; i < n; ++i) {
		fin >> y[i];
	}

	for (int a = 1; a <= n; ++a) {
		for (int b = 1; b <= n; ++b) {
			dp[a][b] = max(max(dp[a - 1][b - 1] + match(x[a - 1], y[b - 1]), dp[a - 1][b]), dp[a][b - 1]);
		}
	}

	fout << dp[n][n] << endl;

	return 0;
}