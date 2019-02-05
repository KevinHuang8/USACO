/*
ID: Kevun1
LANG: C++11
TASK: sort3
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
ifstream fin("sort3.in");
ofstream fout("sort3.out");

/*
You know that iin the end sorted sequence, [0, n1) has to be all 1s, [n1, n1 + n2) has to be all 2s, 
and [n1 + n2, end) has to be all 3s
*/
int main(){
	int n;
	fin >> n;
	vector<int> sequence;
	int num;
	//number of 1s, 2s, and 3s
	int n1 = 0, n2 = 0, n3 = 0;
	while (fin >> num) {
		sequence.push_back(num);
		if (num == 1)
			++n1;
		else if (num == 2)
			++n2;
		else if (num == 3)
			++n3;
	}

	int swaps = 0;

	//sort 1s section
	for (int i = 0; i < n1; ++i) {
		int x = sequence[i];
		if (x == 1)
			continue;
		if (x == 2) {
			for (int j = n1; j < sequence.size(); ++j) {
				if (sequence[j] == 1) {
					swap(sequence[i], sequence[j]);
					++swaps;
					break;
				}
			}
		}

		if (x == 3) {
			//found in third section
			bool found = false;
			//look in 3s section first before 2s, so that you can save a swap later
			for (int j = n1 + n2; j < sequence.size(); ++j) {
				if (sequence[j] == 1) {
					swap(sequence[i], sequence[j]);
					++swaps;
					found = true;
					break;
				}
			}
			if (!found) {
				for (int j = n1; j < n1 + n2; ++j) {
					if (sequence[j] == 1) {
						swap(sequence[i], sequence[j]);
						++swaps;
						break;
					}
				}
			}
		}
	}

	//sort 2s section
	for (int i = n1; i < n1 + n2; ++i) {
		int x = sequence[i];
		if (x == 2)
			continue;
		if (x == 3) {
			for (int j = n1 + n2; j < sequence.size(); ++j) {
				if (sequence[j] == 2) {
					swap(sequence[i], sequence[j]);
					++swaps;
					break;
				}
			}
		}
	}

	fout << swaps << endl;
	
	return 0;
}