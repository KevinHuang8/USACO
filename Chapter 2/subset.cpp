/*
ID: Kevun1
LANG: C++11
TASK: subset
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


ifstream fin("in.txt");
ofstream fout("out.txt");
//ifstream fin("subset.in");
//ofstream fout("subset.out");

//DP array
//combos[a, m] = number of ways to create a sum of 'a' with integers 1...m
//combos[a, m] = combos[a - m, m - 1] + combos[a, m - 1]
//				     (include m)        (don't include m)
long long combos[781][40];
/*
DP
*/
int main(){
	int n;
	fin >> n;

	//no way to partition the set into 2 equal sums, b/c the total sum is odd
	if (n*(n + 1) % 4 != 0) {
		fout << 0 << endl;
		return 0;
	}

	//base conditions
	for (int i = 0; i <= n; ++i) {
		//can always make 0 from any set (don't include anything)
		combos[0][i] = 1;
		if (i != 0) {
			//can always make 1 as long as set isn't null set
			combos[1][i] = 1;
			//can't make any number from a null set except for 0
			combos[i][0] = 0;
		}
	}

	for (int a = 2; a <= n*(n - 1) / 2; ++a) {
		for (int m = 1; m <= n; ++m) {
			if (m > a)
				combos[a][m] = combos[a][m - 1];
			else
				combos[a][m] = combos[a - m][m - 1] + combos[a][m - 1];
		}
	}

	fout << combos[n*(n + 1) / 4][n]/2 << endl;

	return 0;
}