/*
ID: Kevun1
LANG: C++11
TASK: milk3
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
ifstream fin("milk3.in");
ofstream fout("milk3.out");

int visited[21][21][21];

struct bucket {
	int amount;
	int max;
	bucket(int a, int m)
		: amount(a)
		, max(m)
	{}
};

struct state {
	vector<bucket> buckets;
	state(bucket a, bucket b, bucket c) {
		buckets = { a, b, c };
	}
};

//Note: for DFS, when modifying objects, returning a new object is prefered (so you don't have to undo)
state pour_milk(int a, int b, state s) {
	bucket from = s.buckets[a];
	bucket to = s.buckets[b];
	int to_pour = min(from.amount, to.max - to.amount);
	to.amount += to_pour;
	from.amount -= to_pour;
	state result = s;
	result.buckets[a] = from;
	result.buckets[b] = to;
	return result;
}

/*
DFS
*/
vector<int> possible_states;
void search(state s) {
	bucket a = s.buckets[0];
	bucket b = s.buckets[1];
	bucket c = s.buckets[2];
	if (visited[a.amount][b.amount][c.amount])
		return;

	if (a.amount == 0 && find(possible_states.begin(), possible_states.end(), c.amount) == possible_states.end()) {
		possible_states.push_back(c.amount);
	}

	visited[a.amount][b.amount][c.amount] = 1;

	//note: no undo pour, b/c a new separate object is created
	search(pour_milk(0, 1, s));
	search(pour_milk(1, 0, s));
	search(pour_milk(0, 2, s));
	search(pour_milk(2, 0, s));
	search(pour_milk(1, 2, s));
	search(pour_milk(2, 1, s));

}

int main(){
	int a_max, b_max, c_max;
	fin >> a_max >> b_max >> c_max;

	bucket a(0, a_max);
	bucket b(0, b_max);
	bucket c(c_max, c_max);
	state s(a, b, c);
	search(s);
	sort(possible_states.begin(), possible_states.end());
	for (int i = 0; i < possible_states.size() - 1; ++i) {
		fout << possible_states[i] << " ";
	}
	fout << possible_states.back() << endl;
	return 0;
}