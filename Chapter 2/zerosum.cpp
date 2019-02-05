/*
ID: Kevun1
LANG: C++11
TASK: zerosum
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
ifstream fin("zerosum.in");
ofstream fout("zerosum.out");

int n;

int eval(string s) {
	int value = 0;
	//get first number
	int next_num = 0;
	int j = 0;
	while (j < s.length()) {
		char next_char = s[j];
		if (next_char == '+' || next_char == '-')
			break;
		if (next_char == ' ')
			++j;
		else {
			next_num = next_num * 10 + (next_char - 48);
			++j;
		}
	}
	value = next_num;
	//search string for next number
	for (int i = 0; i < s.length(); ++i) {
		int next_num = 0;
		int j = i;
		if (s[j] == '+' || s[j] == '-')
			++j;
		while (j < s.length()) {
			char next_char = s[j];
			if (next_char == '+' || next_char == '-')
				break;
			if (next_char == ' ')
				++j;
			else {
				next_num = next_num * 10 + (next_char - 48);
				++j;
			}
		}
		if (s[i] == '+')
			value += next_num;
		else if (s[i] == '-')
			value -= next_num;
		else
			continue;
	}
	return value;
}

//generate all possible string sequences
void generate(string sequence, int size) {
	if (size == n) {
		if (eval(sequence) == 0) {
			fout << sequence << endl;
		}
		return;
	}
	generate(sequence + " " + to_string(size + 1), size + 1);
	generate(sequence + "+" + to_string(size + 1), size + 1);
	generate(sequence + "-" + to_string(size + 1), size + 1);
	
}
/*
DFS
*/
int main(){
	fin >> n;
	generate("1", 1);
	return 0;
}