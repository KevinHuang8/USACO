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
ifstream fin("hps.in");
ofstream fout("hps.out");

int dp[100001][21];
char games[100001];
int H[100001];
int P[100001];
int S[100001];

int cost(int a, int b) {
	if (a == 0)
		return max(max(H[b], P[b]), S[b]);
	return max(max(H[b] - H[a - 1], P[b] - P[a - 1]), S[b] - S[a - 1]);
}

void DP_divide_and_conquer(long long i, long long jstart, long long jend, long long kstart, long long kend) {
	long long mid = (jstart + jend) / 2;
	long long bestk = -1;
	dp[mid][i] = 0;

	for (long long k = kstart; k <= kend, k < mid; ++k) {
		if (dp[k][i - 1] + cost(k, mid) > dp[mid][i]) {
			dp[mid][i] = dp[k][i - 1] + cost(k, mid);
			bestk = k;
		}
	}

	if (mid - 1 >= jstart)
		DP_divide_and_conquer(i, jstart, mid - 1, kstart, bestk);

	if (jend >= mid + 1)
		DP_divide_and_conquer(i, mid + 1, jend, bestk, kend);
}

int main(){
	
	int n, k;
	fin >> n >> k;

	for (int i = 0; i < n; ++i) {
		fin >> games[i];
		if (i != 0) {
			H[i] = H[i - 1];
			P[i] = P[i - 1];
			S[i] = S[i - 1];
		}
		if (games[i] == 'H') {
			++H[i];
		}
		if (games[i] == 'P') {
			++P[i];
		}
		if (games[i] == 'S') {
			++S[i];
		}
	}

	for (int i = 0; i < n; ++i) {
		dp[i][0] = cost(0, i);
	}
	for (int c = 1; c <= k; ++c) {
		DP_divide_and_conquer(c, 0, n - 1, 0, n - 1);
		/*
		for (int i = 0; i < n; ++i) {
			
			int m = 1;
			for (int j = 0; j < i; ++j) {
				m = max(m, dp[j][c - 1] + cost(j, i));
			}
			dp[i][c] = m;
			
		}
		*/
	}

	fout << dp[n - 1][k] << endl;

	return 0;
}