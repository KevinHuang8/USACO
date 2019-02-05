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
//ifstream fin("name.in");
//ofstream fout("name.out");

int disable_count(unsigned int v) {
	static const int MultiplyDeBruijnBitPosition[32] =
	{
		0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
		31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
	};
	return MultiplyDeBruijnBitPosition[((uint32_t)((v & (~v + 1)) * 0x077CB531U)) >> 27];
}

int main(){
	int x = 10;
	fout << disable_count(x);
	return 0;
}