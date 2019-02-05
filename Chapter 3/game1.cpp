/*
ID: Kevun1
LANG: C++11
TASK: game1
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
ifstream fin("game1.in");
ofstream fout("game1.out");

int board[101];
//max_value[a][b] - max number of points obtainable for board[a...b]
//max_value[a][b] = max( /*choose a*/ board[a] + min(max_value[a + 2][b], max_value[a + 1][b - 1])<-opponent picks their max, so you get min
//                     ( /*choose b*/ board[b] + min(max_value[a][b - 2], max_value[a + 1][b - 1])
int max_value[101][101];

int main(){
	int n;
	fin >> n;
	int x;
	for (int i = 0; i < n; ++i) {
		fin >> x;
		board[i] = x;
	}

	for (int i = 0; i < n; ++i) {
		max_value[i][i] = board[i];
		if (i != n - 1)
			max_value[i][i + 1] = max(board[i], board[i + 1]);
	}

	//order - start with smaller boards, then get larger. i.e. calculate all sub-boards of len 3, then len 4, etc.
	for (int len = 2; len < n; ++len) {
		for (int i = 0; i + len < n; ++i) {
			int j = i + len;
			max_value[i][j] = max(min(max_value[i + 2][j], max_value[i + 1][j - 1]) + board[i],
						  		  min(max_value[i][j - 2], max_value[i + 1][j - 1]) + board[j]);
			
		}
	}
	int sum = 0;
	for (int i = 0; i < n; ++i)
		sum += board[i];
	//opponent is left with whatever you didn't pick
	fout << max_value[0][n - 1] << " " << sum - max_value[0][n - 1] << endl;

	return 0;
}