/*
ID: Kevun1
LANG: C++11
TASK: stamps
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
#define LIMIT 2030003
using namespace std;

//ifstream fin("in.txt");
//ofstream fout("out.txt");
ifstream fin("stamps.in");
ofstream fout("stamps.out");

//short so can fit
//stamps_needed[x] = number of stamps needed to make x
//stamps_needed[x] = min(stamps_needed[x - k] + 1| for k in stamps)
//in order to make value x, you need to add a kth stamp. Try all the possible
//kth stamp values you can add. The number of combos is therefore just the number
//to make x - k, plus 1 (the kth stamp you add)
short stamps_needed[LIMIT];

int main(){
	int k, n;
	fin >> k >> n;
	vector<int> stamps;
	for (int i = 0; i < n; ++i) {
		int s;
		fin >> s;
		stamps.push_back(s);
	}
	sort(stamps.begin(), stamps.end());

	stamps_needed[0] = 0;
	for (int i = 1; i < LIMIT; ++i) {
		int min_number = 2100000000;
		for (int stamp : stamps) {
			if (stamp > i)
				continue;
			if (stamps_needed[i - stamp] + 1 < min_number)
				min_number = stamps_needed[i - stamp] + 1;
		}
		stamps_needed[i] = min_number;
	}

	int longest_unbroken = 0;
	int chain = 0;
	for (int i = 0; i < stamps.back()*k + 2; ++i) {
		if (stamps_needed[i] > k) {
			longest_unbroken = max(longest_unbroken, chain);
			chain = 0;
		}
		else {
			++chain;
		}
	}

	fout << longest_unbroken  - 1 << endl;

	return 0;
}