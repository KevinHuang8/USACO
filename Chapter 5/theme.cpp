/*
ID: Kevun1
LANG: C++11
TASK: theme
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
ifstream fin("theme.in");
ofstream fout("theme.out");

int melody[5001];

int main(){
	int n;
	fin >> n;

	for (int i = 0; i < n; ++i) {
		fin >> melody[i];
	}

	int maxlength = 0;

	//i is the potential beginning of the first occurence, j is the potential beginning of the second occurence
	for (int i = 0; i < n; ++i) {
		if (i + 2 * max(5, maxlength) >= n)
			continue;

		//once you have found a theme of length maxlength, you don't need to search for shorter sequences
		for (int j = i + max(5, maxlength); j < n; ++j) {
			//try finding the longest theme possible where the first occurence starts at i and the second at j
			int transpose = melody[j] - melody[i];
			int count = 0;
			//once the two sequences, one starting at i and the other starting at j, no longer have a difference of transpose,
			//you know that the theme has ended
			while (i + count < j && j + count < n && melody[j + count] - melody[i + count] == transpose) {
				++count;
			}
			if (count >= 5)
				maxlength = max(maxlength, count);
		}
	}

	fout << maxlength << endl;

	return 0;
}