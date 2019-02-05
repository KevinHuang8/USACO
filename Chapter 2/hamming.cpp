/*
ID: Kevun1
LANG: C++11
TASK: hamming
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
ifstream fin("hamming.in");
ofstream fout("hamming.out");

int hamming_distance(int a, int b) {
	int count = 0;
	int x = a ^ b;
	while (x > 0) {
		count += 1;
		x &= (x - 1);
	}
	return count;
}

vector<int> codes;

int main(){
	int n, b, d;
	fin >> n >> b >> d;

	cout << hamming_distance(0, 127);

	for (int i = 0; i < pow(2, b); ++i) {
		bool can_add = true;
		for (int c : codes) {
			if (hamming_distance(i, c) < d) {
				can_add = false;
				break;
			}
		}
		if (can_add)
			codes.push_back(i);
		if (codes.size() >= n)
			break;
	}

	for (int i = 0; i < codes.size(); ++i) {
		fout << codes[i];
		if (i % 10 == 9)
			fout << endl;
		else if (i != codes.size() - 1)
			fout << " ";
		else if (i == codes.size() - 1)
			fout << endl;
	}

	return 0;
}