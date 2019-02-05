/*
ID: Kevun1
LANG: C++11
TASK: shuttle
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
ifstream fin("shuttle.in");
ofstream fout("shuttle.out");

int s;
char board[25] = { 0 };
char solved[25] = { 0 };
vector<int> sequence;

void move_white(int amount) {
	int a = 0;
	for (int i = s * 2; i >= 0; --i) {
		if (a >= amount)
			break;
		if (board[i] == 'b' || board[i] == ' ')
			continue;
		if (i < s * 2 && board[i + 1] == ' ') {
			++a;
			swap(board[i + 1], board[i]);
			sequence.push_back(i + 1);
		}
		else if (i + 1 < s * 2 && board[i + 1] == 'b' && board[i + 2] == ' ') {
			++a;
			swap(board[i + 2], board[i]);
			sequence.push_back(i + 1);
		}
	}
}

void move_black(int amount) {
	int a = 0;
	for (int i = 0; i <= s * 2; ++i) {
		if (a >= amount)
			break;
		if (board[i] == 'w' || board[i] == ' ')
			continue;
		if (i > 0 && board[i - 1] == ' ') {
			++a;
			swap(board[i - 1], board[i]);
			sequence.push_back(i + 1);
		}
		else if (i > 1 && board[i - 1] == 'w' && board[i - 2] == ' ') {
			++a;
			swap(board[i - 2], board[i]);
			sequence.push_back(i + 1);
		}
	}
}

bool array_equals(char a[], char b[]) {
	for (int i = 0; i < 25; ++i) {
		if (a[i] != b[i])
			return false;
	}
	return true;
}

int main(){
	fin >> s;
	for (int i = 0; i < s; ++i) {
		board[i] = 'w';
		solved[i] = 'b';
	}
	board[s] = ' ';
	solved[s] = ' ';
	for (int i = s + 1; i <= s * 2; ++i) {
		board[i] = 'b';
		solved[i] = 'w';
	}
	//amounts = [1, 2, 3, s...s, 3, 2, 1] where the sum of the numbers is as close to 2^s + 1 as possible
	vector<int> amounts;
	int sum = 0;
	for (int i = 1; i < s; ++i) {
		amounts.push_back(i);
		sum += i;
	}
	for (int i = 0; i < round((pow(2, s + 1) - sum*2) / s); ++i) {
		amounts.push_back(s);
	}
	for (int i = s - 1; i > 0; --i) {
		amounts.push_back(i);
	}

	int count = 0;
	while (!array_equals(board, solved)) {
		if (count % 2 == 0)
			move_white(amounts[count]);
		else
			move_black(amounts[count]);
		++count;
	}

	for (int i = 0; i < sequence.size(); ++i) {
		fout << sequence[i];
		if (i % 20 == 19 || i == sequence.size() - 1)
			fout << endl;
		else
			fout << " ";
	}

	return 0;
}