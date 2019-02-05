/*
ID: Kevun1
LANG: C++11
TASK: kimbits
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
ifstream fin("kimbits.in");
ofstream fout("kimbits.out");

//DP[L][K] = number of bit sequences of length L with <= K '1's
//DP[L][K] = DP[L - 1][K] + DP[L - 1][K - 1]
//			 (MSB is a 0)    (MSB is a 1)
int DP[32][32];

/*
DP with some clever searching
*/
int main() {
	//N - bit length, L - number of 1s, I - index
	int N, L;
	long long I;
	fin >> N >> L >> I;

	for (int i = 0; i <= L; ++i) {
		//always can have a null set
		DP[0][i] = 1;
	}
	for (int i = 0; i <= N; ++i) {
		//you can always make a sequence with only '0's
		DP[i][0] = 1;
	}
	for (int k = 1; k <= L; ++k) {
		for (int len = 1; len <= N; ++len) {
			DP[len][k] = DP[len - 1][k] + DP[len - 1][k - 1];
		}
	}
	string output;
	int curr_length = N, curr_ones = L;
	while (curr_length > 0) {
		//index of point that separates sequences that begin with 0 and sequences that begin with 1
		int cutoff_point = DP[curr_length - 1][curr_ones];
		if (I > cutoff_point) {
			output += '1';
			I -= cutoff_point;
			--curr_length;
			--curr_ones;
		}
		else if (I <= cutoff_point) {
			output += '0';
			--curr_length;
		}
	}

	fout << output << endl;

	return 0;
}