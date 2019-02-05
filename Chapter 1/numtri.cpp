/*
ID: Kevun1
LANG: C++11
TASK: numtri
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
ifstream fin("numtri.in");
ofstream fout("numtri.out");

/*
DP
*/
int main(){
	int n;
	fin >> n;
	
	vector<vector<int>> triangle;
	string line;
	for (int i = 0; i < n; ++i) {
		vector<int> row;
		int x;
		for (int j = 0; j <= i; ++j) {
			fin >> x;
			row.push_back(x);
		}
		triangle.push_back(row);	
	}

	//DP array, holds the maximum value of the path to that index on a certain row
	//old_max contains the values of the row above it
	//would use DP[1001][1001], but that's too big
	int max_value[1001];
	int old_max[1001];
	old_max[0] = triangle[0][0];
	for (int i = 1; i < n; ++i) {
		for (int j = 0; j <= i; ++j) {
			int num = triangle[i][j];
			int left = j - 1;
			int right = j;
			//Out of bounds checking
			if (j == 0)
				left = j;
			if (j == i)
				right = j - 1;
			max_value[j] = max(old_max[left], old_max[right]) + triangle[i][j];
		}
		for (int j = 0; j <= i; ++ j) {
			old_max[j] = max_value[j];
		}
	}

	int max_path = 0;
	for (int i = 0; i < n; ++i) {
		if (max_value[i] > max_path)
			max_path = max_value[i];
	}

	fout << max_path << endl;
	return 0;
}