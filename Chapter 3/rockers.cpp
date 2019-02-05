/*
ID: Kevun1
LANG: C++11
TASK: rockers
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

//zifstream fin("in.txt");
//ofstream fout("out.txt");
ifstream fin("rockers.in");
ofstream fout("rockers.out");

//number[s][d][c] = number of songs you can fit given that you can use song s...end, you are on disk d, and 
//you have capacity c left on the current disk
int number[21][21][21];
int nsongs, disks, capacity;
vector<int> duration;

int main()
{
	fin >> nsongs >> capacity >> disks;
	int dur;
	while (fin >> dur) {
		duration.push_back(dur);
	}
	reverse(duration.begin(), duration.end());
	for (int c = 0; c <= capacity; ++c) {
		for (int d = 1; d < disks; ++d) {
			if (duration.back() <= capacity)
				number[nsongs - 1][d][c] = 1;
			else
				number[nsongs - 1][d][c] = 0;
		}
		if (duration.back() > c)
			number[nsongs - 1][disks][c] = 0;
		else
			number[nsongs - 1][disks][c] = 1;
	}


	for (int song = nsongs - 2; song >= 0; --song) {
		for (int d = disks; d >= 1; --d) {
			for (int cap = 0; cap <= capacity; ++cap) {
				//if you can fit the song onto the current disk
				if (duration[song] <= cap) {
					//either take song or not take song
					number[song][d][cap] = max(number[song + 1][d][cap - duration[song]] + 1, number[song + 1][d][cap]);
				}
				else {
					//if you can't fit song on current disk, decide whether you want to move on to the next disk and put it there
					if (d < disks && duration[song] <= capacity && number[song + 1][d + 1][capacity - duration[song]] + 1 > number[song + 1][d][cap]) {
						number[song][d][cap] = number[song + 1][d + 1][capacity - duration[song]] + 1;
					}
					else {
						number[song][d][cap] = number[song + 1][d][cap];
					}
				}


			}
		}
	}

	fout << number[0][1][capacity] << endl;
	return 0;
}

