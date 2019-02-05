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
ifstream fin("circlecross.in");
ofstream fout("circlecross.out");

int values[100000];
int firstindex[50001];
int secondindex[50001];
bool found[50001];

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
bool done[50001];

int main(){
	int n;
	fin >> n;

	for (int i = 0; i < 2*n; ++i) {
		fin >> values[i];
		if (!found[values[i]]) {
			firstindex[values[i]] = i;
			found[values[i]] = true;
		}
		else {
			secondindex[values[i]] = i;
		}
	}

	BinaryIndexedTree<int> BIT(2*n + 1);

	int answer = 0;
	for (int i = 0; i < 2*n; ++i) {
		if (!done[values[i]]) {
			int a = firstindex[values[i]];
			int b = secondindex[values[i]];
			answer += BIT.sum_between(a, b);
			BIT.update(b, 1);
			done[values[i]] = true;
		}
	}

	fout << answer << endl;

	return 0;
}