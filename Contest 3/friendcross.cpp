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


//ifstream fin("in.txt");
//ofstream fout("out.txt");
ifstream fin("friendcross.in");
ofstream fout("friendcross.out");

template <typename T>
struct BinaryIndexedTree {
	vector<T> values;
	vector<T> tree;

	BinaryIndexedTree(int size) : values(size), tree(size) {}

	BinaryIndexedTree(vector<T>& v) : values(v), tree(v.size() + 1) {
		vector<T> temp = values;
		for (int i = 0; i < values.size(); ++i) {
			update(i, values[i]);
		}
		values = temp;
	}
	//return sum of values[0...index] inclusive
	T prefix_sum(int index) {
		T sum;
		index += 1;
		while (index > 0) {
			sum = sum + tree[index];
			//parent
			index = index - (index & -index);
		}
		return sum;
	}

	void update(int index, T val) {
		values[index] = values[index] + val;
		index += 1;
		while (index <= values.size()) {
			tree[index] = tree[index] + val;
			index = index + (index & -index);
		}
	}

	//returns sum of values[a...b], inclusive
	T sum_between(int a, int b) {
		if (a == 0)
			return prefix_sum(b);
		else if (b == 0)
			return prefix_sum(a);
		else if (a > b)
			return prefix_sum(a) - prefix_sum(b - 1);
		else
			return prefix_sum(b) - prefix_sum(a - 1);
	}
};

struct s {
	vector<int> v;
	s(int x) {
		v.push_back(x);
	}

	s(vector<int> x) {
		for (int i : x) {
			v.push_back(i);
		}
	}

	s() {}

	s operator+(const s& other) const{
		vector<int> joined;
		for (int i : v)
			joined.push_back(i);
		for (int i : other.v)
			joined.push_back(i);
		return s(joined);
	}

	void operator=(const s& other) {
		v = other.v;
	}
};

int x[100001];
int secondloc[100001];
unordered_map<int, int> convert;

int main(){
	int n, k;
	fin >> n >> k;

	for (int i = 0; i < n; ++i) {
		fin >> x[i];
	}
	for (int i = 0; i < n; ++i) {
		int y;
		fin >> y;
		secondloc[y] = i;
	}

	vector<s> seq(100001);
	vector<int> seq2(100001);

	for (int i = 0; i < n; ++i) {
		seq[i] = s(secondloc[x[i]]);
		seq2[i] = secondloc[x[i]];
		convert[secondloc[x[i]]] = x[i];
	}

	int answer = 0;

	BinaryIndexedTree<s> BIT(100003);
	for (int i = 0; i < n; ++i) {
		s intersections = BIT.prefix_sum(n - 1 - seq2[i]);
		BIT.update(n - 1 - seq2[i], seq[i]);
		for (int inter : intersections.v) {
			int a = convert[inter];
			int b = convert[seq2[i]];
			if (abs(a - b) > k)
				++answer;
		}
	}

	fout << answer << endl;

	return 0;
}