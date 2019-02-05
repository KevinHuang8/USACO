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
//ifstream fin("nocross.in");
//ofstream fout("nocross.out");

template <typename V>
struct node {
	int low;
	int high;
	V val;
	V lazy;
	node() {}
	node(int lo, int hi, V v) : low(lo), high(hi), val(v), lazy() {}
};

template <typename V>
class SegmentTree {
private:
	vector<node<V>> nodes;
	vector<V> elements;

	void build_tree(int index, int low, int high) {
		if (low == high) {
			nodes[index] = node<V>(low, high, elements[low]);
			return;
		}

		int leftchild = 2 * index + 1;
		int rightchild = 2 * index + 2;
		int mid = (low + high) / 2;
		build_tree(leftchild, low, mid);
		build_tree(rightchild, mid + 1, high);
		nodes[index] = merge(nodes[leftchild], nodes[rightchild]);
	}

	//get node responsible for segment [start, end]. Start search from node[index]
	node<V> query_node(int index, int start, int end) {
		node<V> n = nodes[index];

		if (start == n.low && end == n.high)
			return n;

		int mid = (n.low + n.high) / 2;

		//if the required interval is completely to the left or completely to the right
		if (start > mid)
			return query_node(2 * index + 2, start, end);
		if (end <= mid)
			return query_node(2 * index + 1, start, end);

		return merge(query_node(2 * index + 1, start, mid), query_node(2 * index + 2, mid + 1, end));
	}

	void update(int node_index, int index, V new_val) {
		node<V> &n = nodes[node_index];

		//is leaf node
		if (n.low == n.high) {
			change_value(n, new_val);
			return;
		}

		int mid = (n.low + n.high) / 2;
		int leftchild = 2 * node_index + 1;
		int rightchild = 2 * node_index + 2;
		//binary search for the leaf containing the index
		if (index <= mid)
			update(leftchild, index, new_val);
		else
			update(rightchild, index, new_val);

		//propagate updates upward
		n = merge(nodes[leftchild], nodes[rightchild]);
	}

	//obtain value of combined segment from left subsegment and right subsegment
	node<V> merge(node<V> left, node<V> right) {
		//depends on what value you are storing
		node<V> new_node(left.low, right.high, max(left.val, right.val));
		return new_node;
	}

	//update the value in node n by new_val
	//affects how update() works
	void change_value(node<V> &n, V new_val) {
		n.val = new_val;
	}

public:
	SegmentTree(vector<V> v) {
		int p = 1;
		while (pow(2, p) < v.size())
			++p;
		nodes.resize(pow(2, p + 1));
		elements = v;
		build_tree(0, 0, elements.size() - 1);
	}

	//return value of segment [left, right] inclusive
	V query(int start, int end) {
		return query_node(0, start, end).val;
	}

	//updates value at index with new_val
	void update(int index, V new_val) {
		update(0, index, new_val);
	}
};

int cows[100001];
int second_loc[100001];

int main(){
	int n;
	fin >> n;

	for (int i = 0; i < n; ++i) {
		fin >> cows[i];
	}
	for (int i = 0; i < n; ++i) {
		int c;
		fin >> c;
		second_loc[c] = i;
	}

	vector<int> v(n + 2);
	SegmentTree<int> dp(v);

	for (int i = 0; i < n; ++i) {
		vector<int> compatible;
		for (int j = max(1, cows[i] - 4); j < min(n + 1, cows[i] + 5); ++j) {
			compatible.push_back(second_loc[j]);
		}

		sort(compatible.begin(), compatible.end());
		for (int j = compatible.size() - 1; j >= 0; --j) {
			int index = compatible[j];
			int prev_max = 0;
			if (index > 0)
				prev_max = dp.query(0, index - 1);
			dp.update(index, prev_max + 1);
		}
	}

	fout << dp.query(0, n);

	return 0;
}