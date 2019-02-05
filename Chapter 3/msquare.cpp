/*
ID: Kevun1
LANG: C++11
TASK: msquare
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <tuple>
#include <queue>
#include <algorithm>
#include <cmath>
#include <utility>
#include <numeric>
using namespace std;

//ifstream fin("in.txt");
//ofstream fout("out.txt");
ifstream fin("msquare.in");
ofstream fout("msquare.out");

struct vector_hash {
	size_t operator()(vector<int> const& vec) const {
		size_t seed = vec.size();
		for (auto& i : vec) {
			seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		}
		return seed;
	}
};

vector<int> A(vector<int> input) {
	swap(input[0], input[7]);
	swap(input[1], input[6]);
	swap(input[2], input[5]);
	swap(input[3], input[4]);
	return input;
}
vector<int> B(vector<int> input) {
	int end1 = input[3], end2 = input[4];
	for (int i = 3; i > 0; --i)
		input[i] = input[i - 1];
	for (int i = 4; i < 7; ++i)
		input[i] = input[i + 1];
	input[0] = end1;
	input[7] = end2;
	return input;
}
vector<int> C(vector<int> input) {
	swap(input[2], input[6]);
	swap(input[1], input[2]);
	swap(input[5], input[6]);
	return input;
}

struct square_state {
	string seq;
	vector<int> state;
	int length;
	square_state(string s, vector<int> v) :seq(s), state(v) { length = seq.length(); }
};
/*
Breadth First Search
*/
int main(){
	vector<int> square = { 1, 2, 3, 4, 5, 6, 7, 8 };
	vector<int> goal;
	
	int n;
	while (fin >> n)
		goal.push_back(n);

	unordered_set<vector<int>, vector_hash> visited;
	visited.insert(square);
	string output;
	int shortest_length = 2100000000;
	queue<square_state> Q;
	Q.push(square_state("", square));
	while (!Q.empty()) {
		square_state state = Q.front();
		Q.pop();
		if (state.length > shortest_length) {
			break;
		}
		if (state.state == goal) {
			//when you have a solution, you have to check the rest of the solutions of
			//that length, take the one that is the smallest lexiographically
			if (output == "" || state.seq < output) {
				output = state.seq;
				shortest_length = state.length;
			}
		}
		//you don't want to repeat states b/c that is clearly not the most efficient path
		auto a = A(state.state);
		auto b = B(state.state);
		auto c = C(state.state);

		if (visited.find(a) == visited.end()) {
			visited.insert(a);
			Q.push(square_state(state.seq + "A", a));
		}
		if (visited.find(b) == visited.end()) {
			visited.insert(b);
			Q.push(square_state(state.seq + "B", b));
		}
		if (visited.find(c) == visited.end()) {
			visited.insert(c);
			Q.push(square_state(state.seq + "C", c));
		}
	}

	fout << shortest_length << endl;
	fout << output << endl;

	return 0;
}