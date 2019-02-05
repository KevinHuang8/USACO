/*
ID: Kevun1
LANG: C++11
TASK: nocows
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <unordered_map>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <utility>
#include <numeric>
using namespace std;


//ifstream fin("in.txt");
//ofstream fout("out.txt");
ifstream fin("nocows.in");
ofstream fout("nocows.out");

int main(){
	int n, k;
	fin >> n >> k;
	//pedigrees[n][h] = pedigrees with n nodes and h height
	int pedigrees[200][100];
	//pedigrees with n nodes less than or equal to k height
	int smaller_pedigrees[200][100];
	memset(pedigrees, 0, sizeof(pedigrees));
	memset(smaller_pedigrees, 0, sizeof(smaller_pedigrees));
	pedigrees[1][1] = 1;
	for (int h = 1; h <= k; ++h) {
		smaller_pedigrees[1][h] = 1;
	}

	if (n % 2 == 0) {
		fout << 0 << endl;
		return 0;
	}

	for (int h = 2; h <= k; ++h) {
		for (int m = 3; m <= n; m += 2) {
			pedigrees[m][h] = 0;
			//i is basically how you want to partition the tree into its two subtrees.
			//you partition the tree into one node, one subtree with i nodes, and one subtree with m - 1 - i nodes
			//then you count up how many combinations there are within each partition
			for (int i = 1; i <= (m - 1)/2; i += 2) {
				//assume larger subtree is on the left, and multiply result by 2 (b/c you can swap the two subtrees)
				//if the two subtrees are equal, you don't multiply by 2 because it will result in identical trees
				int multiplier = 1;
				if (i != (m - 1) / 2) {
					multiplier = 2;
				}
				//there are 3 cases depending on which subtree reaches the required height, h - 1 (one must to satisfy criteria)
				//the subtree reaching the height limit is constrained to that height while the other subtree can be any height
				//In cases one and two, where only one of the trees reach the height, smaller_pedigrees[i][h - 2] must be
				//used (not h - 1) because if it also reaches the height, it will be double counted in the other case 
				//where it does in fact reach the height
				pedigrees[m][h] += (pedigrees[m - i - 1][h - 1] * smaller_pedigrees[i][h - 2] //right subtree reaches height
					+ pedigrees[i][h - 1] * smaller_pedigrees[m - i - 1][h - 2] //left subtree reaches height
					+ pedigrees[m - i - 1][h - 1] * pedigrees[i][h - 1]) * multiplier; //both reach height
				pedigrees[m][h] %= 9901;
			}
			smaller_pedigrees[m][h] = smaller_pedigrees[m][h - 1] + pedigrees[m][h];
			smaller_pedigrees[m][h] %= 9901;
		}
	}

	fout << pedigrees[n][k] << endl;

	return 0;
}