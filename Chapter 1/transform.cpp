/*
ID: Kevun1
LANG: C++11
TASK: transform
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

ifstream fin("in.txt");
ofstream fout("out.txt");
//ifstream fin("transform.in");
//ofstream fout("transform.out");

class board {
public:
	vector<vector<char>> rows;
	vector<vector<char>> columns;
	board(vector<vector<char>> r, vector<vector<char>> c)
		: rows(r)
		, columns(c)
	{}

	board() {}

	//rotates n*90 times
	board n_rotate(int n) {
		board b = rotate();
		for (int i = 0; i < n - 1; ++i) {
			b = b.rotate();
		}
		return b;
	}

	board reflect() {
		auto cx = columns;
		auto rx = rows;

		for (int i = 0; i < rx.size(); ++i) {
			auto c = rx[i];
			reverse(c.begin(), c.end());
			rx[i] = c;
		}
		reverse(cx.begin(), cx.end());

		board b = board(rx, cx);

		return b;
	}

	bool operator==(board other) {
		return rows == other.rows;
	}
	//rotates 90
	board rotate() {
		auto cx = columns;
		auto rx = rows;

		for (int i = 0; i < cx.size(); ++i) {
			auto c = cx[i];
			reverse(c.begin(), c.end());
			cx[i] = c;
		}
		reverse(rx.begin(), rx.end());


		swap(rx, cx);

		return board(rx, cx);
	}
};


void print_board(board b) {
	for (auto r : b.rows) {
		for (auto x : r) {
			cout << x << " ";
		}
		cout << endl;
	}
}

int main() {
	vector<vector<char>> r;
	vector<vector<char>> c;

	string n;
	getline(fin, n);
	int size = stoi(n);

	//create original board
	for (int i = 0; i < size; ++i) {
		vector<char> v;
		c.push_back(v);
	}

	string row;
	for (int i = 0; i < size; ++i) {
		vector<char> curr_row;
		getline(fin, row);
		for (int j = 0; j < size; ++j) {
			curr_row.push_back(row[j]);
			c[j].push_back(row[j]);
		}
		r.push_back(curr_row);
	}

	//create destination board
	vector<vector<char>> r1;
	vector<vector<char>> c1;

	for (int i = 0; i < size; ++i) {
		vector<char> v;
		c1.push_back(v);
	}

	for (int i = 0; i < size; ++i) {
		vector<char> curr_row;
		getline(fin, row);
		for (int j = 0; j < size; ++j) {
			curr_row.push_back(row[j]);
			c1[j].push_back(row[j]);
		}
		r1.push_back(curr_row);
	}

	board B(r, c);
	board B1(r1, c1);

	print_board(B);
	cout << endl;
	print_board(B.reflect());

	int transform = 0;

	if (B.n_rotate(1) == B1)
		transform = 1;
	else if (B.n_rotate(2) == B1)
		transform = 2;
	else if (B.n_rotate(3) == B1)
		transform = 3;
	else if (B.reflect() == B1)
		transform = 4;
	else {
		board reflect_B = B.reflect();
		if (reflect_B.n_rotate(1) == B1 || reflect_B.n_rotate(2) == B1 || reflect_B.n_rotate(3) == B1) {
			transform = 5;
		}
		else if (B == B1)
			transform = 6;
		else
			transform = 7;
	}

	fout << transform << endl;
	return 0;
}
