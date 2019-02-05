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
//ifstream fin("mincross.in");
//ofstream fout("mincross.out");

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
		T sum = 0;
		index += 1;
		while (index > 0) {
			sum += tree[index];
			//parent
			index = index - (index & -index);
		}
		return sum;
	}

	void update(int index, T val) {
		values[index] += val;
		index += 1;
		while (index <= values.size()) {
			tree[index] += val;
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

int n;
int x[100001];
int y[100001];
int firstloc[100001];
int secondloc[100001];

int main(){
	fin >> n;

	for (int i = 0; i < n; ++i) {
		fin >> x[i];
		firstloc[x[i]] = i;
	}
	for (int i = 0; i < n; ++i) {
		fin >> y[i];
		secondloc[y[i]] = i;
	}

	vector<int> seq(n);

	for (int i = 0; i < n; ++i)
		seq[i] = secondloc[x[i]];

	BinaryIndexedTree<int> BIT(n + 2);
	int k = 0;
	for (int i = 0; i < n; ++i) {
		k += BIT.prefix_sum(n - 1 - seq[i]);
		BIT.update(n - 1 - seq[i], 1);
	}

	int mincross = k;
	for (int i = 0; i < n; ++i) {
		int back = seq[n - 1 - i];
		k -= n - 1 - back;
		k += back;
		mincross = min(mincross, k);
	}

	fout << mincross << endl;

	return 0;
}