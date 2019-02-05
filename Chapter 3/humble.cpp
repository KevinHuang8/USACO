/*
ID: Kevun1
LANG: C++11
TASK: humble
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
ifstream fin("humble.in");
ofstream fout("humble.out");

/*
Brute force with optimization
*/
int main(){
	int k, n;
	fin >> k >> n;
	int humble[100001];
	humble[0] = 1;
	vector<int> primes;
	for (int i = 0; i < k; ++i) {
		int prime;
		fin >> prime;
		primes.push_back(prime);
	}
	//the minimum humble you need to start look at for a prime
	int min_h[1001] = { 0 };
	for (int i = 1; i <= n; ++i) {
		int next_humble = 2100000000;
		for (int p : primes) {
			//find smallest humble such that p*humble > previous humble
			for (int h = min_h[p]; h < i; ++h) {
				if (humble[h] * p <= humble[i - 1])
					continue;

				if (humble[h] * p < next_humble) {
					next_humble = humble[h] * p;
				}
				//for the next humble number, when using this prime
				//you know that you don't need to look at humbles before
				//h, because the product would be less than the current humble number
				min_h[p] = h;
				break;
			}
		}
		humble[i] = next_humble;
	}

	fout << humble[n] << endl;

	return 0;
}