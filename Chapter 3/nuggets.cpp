/*
ID: Kevun1
LANG: C++11
TASK: nuggets
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
//ifstream fin("nuggets.in");
//ofstream fout("nuggets.out");

int is_possible[257] = { 0 };
int old_array[257];

int gcd(int a, int b) {
	if (b == 0)
		return a;
	else
		return gcd(b, a % b);
}

int main() {
	int n;
	fin >> n;
	vector<int> sizes;
	int x;
	while (fin >> x) {
		sizes.push_back(x);
	}
	is_possible[0] = 1;
	int gcd_ = sizes[0];
	for (int i = 1; i < sizes.size(); ++i) {
		gcd_ = gcd(gcd_, sizes[i]);
	}
	if (gcd_ > 1){
		fout << 0 << endl;
		return 0;
	}	

	int largest_possible = 0;
	int count = 0;
	while (count < 2000000000) {
		int consequtive = true;
		for (int i = 0; i < 257; ++i) {
			for (int s : sizes) {
				int index = (count - s) % 256;
				if (index >= i && is_possible[index - 1]) {
					if (count > largest_possible)
						largest_possible = count;
					is_possible[i] = 1;
					break;
				}
				else if (index < i && (old_array[index] || (count < 257 && is_possible[index]))) {
					if (count > largest_possible)
						largest_possible = count;
					is_possible[i] = 1;
					break;
				}
				else
					consequtive = false;
			}
			copy(begin(is_possible), end(is_possible), begin(old_array));
			memset(is_possible, 0, sizeof(is_possible));
			++count;
		}
		if (consequtive) {
			fout << largest_possible << endl;
			break;
		}
	}

	fout << "ERROR" << endl;

	return 0;
}