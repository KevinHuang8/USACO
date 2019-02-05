/*
ID: Kevun1
LANG: C++11
TASK: name
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


ifstream fin("in.txt");
ofstream fout("out.txt");
//ifstream fin("roboherd.in");
//ofstream fout("roboherd.out");

int enumerate(int location, long long budget) {
	next[location] = 

	for (int i = 0; i < next.size(); ++i) {
		if (next[i] > budget)
			break;
		enumerate(i, budget - next[i]);
	}
}

int main() {
	
}