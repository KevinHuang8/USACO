/*
ID: Kevun1
LANG: C++11
TASK: barn1
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
ifstream fin("barn1.in");
ofstream fout("barn1.out");

int main(){
	int max_boards, n_stalls, n_cows;
	fin >> max_boards >> n_stalls >> n_cows;
	vector<int> cows;
	int cow;
	while (fin >> cow) {
		cows.push_back(cow);
	}
	sort(cows.begin(), cows.end());
	//create intervals that represent a series of adjacent cows
	//ex: | |X| |X|X|X| | |X|X|
	//would make intervals <2,2>, <4,6>, and <9,10>
	vector<pair<int, int>> cow_intervals;
	int prev_cow = cows[0] - 1, interval_start = cows[0];
	for (int c : cows) {
		if (c != prev_cow + 1) {
			cow_intervals.push_back(make_pair(interval_start, prev_cow));
			interval_start = c;
		}
		prev_cow = c;
	}
	cow_intervals.push_back(make_pair(interval_start, prev_cow));
	//amount of boards to cover only cows
	int num_boards = cow_intervals.size();
	//the amount of boards missing
	int overflow = num_boards - max_boards;

	//generate the number of open stalls between each cow interval
	vector<int> gaps;
	for (int i = 0; i < cow_intervals.size() - 1; ++i) {
		auto p = cow_intervals[i];
		auto next = cow_intervals[i + 1];

		int distance = next.first - p.second - 1;
		gaps.push_back(distance);
	}
	
	//combine the intervals that have the smallest gaps, for each extra overflowing board 
	sort(gaps.begin(), gaps.end());
	for (int i = 0; i < overflow; ++i) {
		n_cows += gaps[i];
	}

	fout << n_cows << endl;

	return 0;
}