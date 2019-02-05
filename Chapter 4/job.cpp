/*
ID: Kevun1
LANG: C++11
TASK: job
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
#define INF 2100000000
using namespace std;


//ifstream fin("in.txt");
//ofstream fout("out.txt");
ifstream fin("job.in");
ofstream fout("job.out");

int atime[31];
int btime[31];
int aqueue[31] = { 0 };
int bqueue[31] = { 0 };

/*
Greedy
*/
int main(){
	int jobs, a, b;
	fin >> jobs >> a >> b;
	for (int i = 0; i < a; ++i) {
		int t;
		fin >> t;
		atime[i] = t;
	}
	for (int i = 0; i < b; ++i) {
		int t;
		fin >> t;
		btime[i] = t;
	}

	int finishing_times[1000] = { 0 };
	//perform A
	for (int i = 0; i < jobs; ++i) {
		int min_finish = INF;
		int machine;
		for (int j = 0; j < a; ++j) {
			if (atime[j] + aqueue[j] < min_finish) {
				min_finish = atime[j] + aqueue[j];
				machine = j;
			}
		}
		aqueue[machine] += atime[machine];
		finishing_times[i] += min_finish;
	}

	int max_timea = 0;
	for (int i = 0; i < jobs; ++i) {
		if (finishing_times[i] > max_timea)
			max_timea = finishing_times[i];
	}

	fout << max_timea << " ";
	
	//perform B
	for (int i = jobs - 1; i >= 0; --i) {
		int min_finish = INF;
		int machine;
		for (int j = 0; j < b; ++j) {
			if (btime[j] + bqueue[j] < min_finish) {
				min_finish = btime[j] + bqueue[j];
				machine = j;
			}
		}
		bqueue[machine] += btime[machine];
		finishing_times[i] += min_finish;
	}

	int max_timeb = 0;
	for (int i = 0; i < jobs; ++i) {
		if (finishing_times[i] > max_timeb)
			max_timeb = finishing_times[i];
	}

	fout << max_timeb << endl;

	return 0;
}