/*
ID: Kevun1
LANG: C++11
TASK: lgame
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
//ifstream dict("dict.txt");
ifstream fin("lgame.in");
ofstream fout("lgame.out");
ifstream dict("lgame.dict");

string words[40000];
string letters;
int values[26] = { 2, 5, 4, 4, 1, 6, 5, 5, 1, 7, 6, 3, 5, 2, 3, 5, 7, 2, 1, 2, 4, 6, 6, 7, 5, 7 };
//                 a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z
bool can_make(string word) {
	//how many chars of each type you need
	unordered_map<char, int> letter_amounts;
	for (char c : word)
		++letter_amounts[c];
	for (char c : letters)
		--letter_amounts[c];
	for (char c = 'a'; c <= 'z'; ++c)
		if (letter_amounts[c] > 0)
			return false;
	return true;
}

int value(string word) {
	int val = 0;
	for (char c : word) {
		val += values[c - 97];
	}
	return val;
}

struct word_pair {
	string w1;
	string w2;
	word_pair(string a, string b) {
		if (a < b || b == "") {
			w1 = a;
			w2 = b;
		}
		else {
			w1 = b;
			w2 = a;
		}
	}
	bool operator<(word_pair& other) {
		return w1 + w2 < other.w1 + other.w2;
	}
};

/*
Brute force
*/
int main(){
	fin >> letters;

	string s;
	dict >> s;
	int i = 0;
	while (s != ".") {
		if (can_make(s)) {
			words[i] = s;
			++i;
		}
		dict >> s;
	}
	int max_val = 0;
	vector<word_pair> best_words;
	for (int j = 0; j < i; ++j) {
		int v = value(words[j]);
		if (v > max_val) {
			max_val = v;
			best_words.clear();
			best_words.push_back(word_pair(words[j], ""));
		}
		else if (v == max_val) {
			best_words.push_back(word_pair(words[j], ""));
		}
		//check case where you have two possible words
		for (int k = j + 1; k < i; ++k) {
			if (!can_make(words[j] + words[k]))
				continue;
			int v2 = value(words[k]);
			if (v + v2 > max_val) {
				max_val = v + v2;
				best_words.clear();
				best_words.push_back(word_pair(words[j], words[k]));
			}
			else if (v + v2 == max_val) {
				best_words.push_back(word_pair(words[j], words[k]));
			}
		}
	}

	sort(best_words.begin(), best_words.end());
	
	fout << max_val << endl;
	for (word_pair w : best_words) {
		fout << w.w1;
		if (w.w2 != "")
			fout << " " << w.w2;
		fout << endl;
	}
	return 0;
}