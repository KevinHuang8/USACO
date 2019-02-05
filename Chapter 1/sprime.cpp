/*
ID: Kevun1
LANG: C++11
TASK: sprime
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
ifstream fin("sprime.in");
ofstream fout("sprime.out");

int max_length;
vector<int> superprimes;

bool is_prime(int n) {
	if (n == 1)
		return false;

	if (n == 2)
		return true;

	for (int i = 3; i*i <= n; ++i) {
		if (n % i == 0)
			return false;
	}
	return true;
}
/*
DFS on all possible integer combinations
*/
void generate(int n, int length) {
	if (length == max_length) {
		superprimes.push_back(n);
		return;
	}
	//2 can be the first digit
	if (length == 0) {
		generate(2, length + 1);
	}
	for (int i = 1; i <= 9; i += 2) {
		int new_n = n * 10 + i;
		if (is_prime(new_n))
			generate(new_n, length + 1);
	}
}

int main(){
	fin >> max_length;

	generate(0, 0);

	sort(superprimes.begin(), superprimes.end());

	for (int i : superprimes) {
		fout << i << endl;
	}
	return 0;
}