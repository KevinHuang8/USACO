/*
ID: Kevun1
LANG: C++11
TASK: contact
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
ifstream fin("contact.in");
ofstream fout("contact.out");

//first sort by decreasing frequency, then increasing length, then lexiographically
struct comp {
	bool operator()(const pair<string, int> &left, const pair<string, int> &right) {
		if (left.second == right.second) {
			if (left.first.length() == right.first.length())
				return left.first < right.first;
			return left.first.length() < right.first.length();
		}
		return left.second > right.second;
	}
};

template <typename T, typename U>
void sort_by_second(vector<pair<T, U>>& v) {
	sort(v.begin(), v.end(), comp());
}

int main(){
	int a, b, n;
	fin >> a >> b >> n;
	string line, sequence = "";
	while (fin >> line) {
		sequence += line;
	}
	//frequency[pattern] holds how many times pattern occurs
	unordered_map<string, int> frequency;
	string pattern;
	for (int i = 0; i < sequence.length(); ++i) {
		for (int len = a; len <= b; ++len) {
			if (i + len > sequence.length())
				continue;
			pattern = sequence.substr(i, len);
			++frequency[pattern];
		}
	}

	vector<pair<string, int>> patterns(frequency.begin(), frequency.end());
	sort_by_second(patterns);

	//output
	int freq = 0;
	int count = 0;
	int x = 0;
	for (int i = 0; i < patterns.size(); ++i) {
		pair<string, int> p = patterns[i];
		//start a new frequency
		if (p.second != freq) {
			x = 0;
			++count;
			if (count > n)
				break;
			if (i != 0) {
				fout << endl;
			}
			fout << p.second << endl;
		}
		else {
			if (x != 6)
				fout << " ";
		}
		if (x == 6) {
			x = 0;
			fout << endl;
		}
		fout << p.first;
		++x;
		freq = p.second;
		
	}
	fout << endl;
	return 0;
}